using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Security.Cryptography;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;

using DevComponents.DotNetBar.Metro;
using DevComponents.DotNetBar;

using Server.Helpers;

namespace Server
{
    public partial class Form1 : MetroForm
    {
        private TcpListener Listener;
        private Thread ListenerThread;
        private bool Listening = false;

        enum TitleID
        {
            DASHBOARD = 1,
            GTAV
        };
        enum UserClasses
        {
            ADMIN = 1,
            BETA,
            CLIENT,
        };

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            Database _Database = new Database(this);
        }
        private void Form1_Shown(object sender, EventArgs e)
        {
            superTabControl1.SelectedTab = superTabItem2;
            Database.ListUsers();

            superTabControl1.SelectedTab = superTabItem1;
            Listener = new TcpListener(IPAddress.Any, 2245);
            ListenerThread = new Thread(new ThreadStart(ClientCatch));
            ListenerThread.Start();
            Listening = true;
        }
        private void ClientCatch()
        {
            Listener.Start();
            while (true)
            {
                if (!Listening)
                    return;

                Thread.Sleep(200);
                if (Listener.Pending())
                {
                    ThreadStart ts = () =>
                    {
                        ClientHandle(Listener.AcceptTcpClient());
                    };
                    Thread t = new Thread(ts);
                    t.Start();
                }
            }
        }
        private void ClientHandle(TcpClient Client)
        {
            NetworkStream Stream = Client.GetStream();
            string IPAddress = ((IPEndPoint)Client.Client.RemoteEndPoint).Address.ToString();
            string Port = ((IPEndPoint)Client.Client.RemoteEndPoint).Port.ToString();

            try
            {
                byte[] buffer1 = new byte[8];
                if (Stream.Read(buffer1, 0, 8) != 8)
                {
                    Client.Close();
                    return;
                }

                EndianIO IO1 = new EndianIO(buffer1, EndianStyle.BigEndian);
                uint Command = IO1.Reader.ReadUInt32();
                int Length = IO1.Reader.ReadInt32();
        
                if (Length > 16512)
                {
                    Client.Close();
                    return;
                }
                byte[] buffer2 = new byte[Length];
                if (Stream.Read(buffer2, 0, Length) != Length)
                {
                    Client.Close();
                    return;
                }
                else
                {
                    EndianIO IO2 = new EndianIO(buffer2, EndianStyle.BigEndian)
                    {
                        Writer = new EndianWriter(Stream, EndianStyle.BigEndian)
                    };
                    switch (Command)
                    {
                    case (int)TitleID.DASHBOARD:
                        {
                            byte[] CPUKey = IO2.Reader.ReadBytes(0x10);
                            byte[] FUSEKey = IO2.Reader.ReadBytes(0x10);
                            byte[] ModuleDigest = IO2.Reader.ReadBytes(0x14);

                            Database.User User = new Database.User();
                            if (Database.UserExists(ref User, Tools.BytesToHexString(CPUKey)))
                            {
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { "Enforcer [", IPAddress, "] connected" }), Color.Black);
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | CPUKey: '", Tools.BytesToHexString(CPUKey), "'" }), Color.Black);
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | FUSEKey: '", Tools.BytesToHexString(FUSEKey), "'" }), Color.Black);
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | ModuleDigest: '", Tools.BytesToHexString(ModuleDigest), "'" }), Color.Black);

                                byte[] LatestModuleClient = System.IO.File.ReadAllBytes("client/GTAVEnforcer.xex");
                                byte[] LatestModuleBeta = System.IO.File.ReadAllBytes("beta/GTAVEnforcer.xex");
                                byte[] LatestModuleAdmin = System.IO.File.ReadAllBytes("admin/GTAVEnforcer.xex");

                                switch (User.userclass)
                                {
                                case (int)UserClasses.CLIENT:

                                    if (User.enabled == 0)
                                    {
                                        IO2.Writer.Write((uint)0xE0000000);
                                        IO2.Writer.Write(Enumerable.Repeat<byte>(0xFF, 0x04).ToArray());
                                        Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Client: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Not Authenticated]" }), Color.Red);
                                    } else {

                                        if (Tools.CompareBytes(ModuleDigest, Tools.CSHA(LatestModuleClient)))
                                        {
                                            if (User.firstTime == "0")
                                            {
                                                Database.SetFuseHash(User.cpukey, Tools.BytesToHexString(FUSEKey));
                                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Client: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " Grabbing Fuse Digest" }), Color.Orange);
                                            } else {

                                                if (User.firstTime != Tools.BytesToHexString(FUSEKey))
                                                {
                                                    IO2.Writer.Write((uint)0xD0000000);
                                                    IO2.Writer.Write(Enumerable.Repeat<byte>(0x00, 0x04).ToArray());
                                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Client: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Hacker]" }), Color.Red);
                                                } else {

                                                    if (User.ip != IPAddress)
                                                    {
                                                        Database.SetIpAddress(User.firstTime, IPAddress);
                                                    }
                                                    IO2.Writer.Write((uint)0xD0000000);
                                                    IO2.Writer.Write(Enumerable.Repeat<byte>(0x00, 0x04).ToArray());
                                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Client: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Authenticated]" }), Color.Green);
                                                }
                                            }
                                        } else {
                                            IO2.Writer.Write((uint)0xC0000000);
                                            IO2.Writer.Write(Enumerable.ToArray<byte>(Enumerable.Repeat<byte>((byte)0, 4)));
                                            Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Outdated module, sending latest" }), Color.Blue);
                                            IO2.Writer.Write(LatestModuleClient.Length);
                                            IO2.Writer.Write(LatestModuleClient);
                                        }
                                    }
                                    break;
                                case (int)UserClasses.BETA:

                                    if (User.enabled == 0)
                                    {
                                        IO2.Writer.Write((uint)0xE0000000);
                                        IO2.Writer.Write(Enumerable.Repeat<byte>(0xFF, 0x04).ToArray());
                                        Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Beta: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Not Authenticated]" }), Color.Red);
                                    } else {

                                        if (Tools.CompareBytes(ModuleDigest, Tools.CSHA(LatestModuleBeta)))
                                        {
                                            if (User.firstTime == "0")
                                            {
                                                Database.SetFuseHash(User.cpukey, Tools.BytesToHexString(FUSEKey));
                                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Beta: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " Grabbing Fuse Digest" }), Color.Orange);
                                            } else {

                                                if (User.firstTime != Tools.BytesToHexString(FUSEKey))
                                                {
                                                    IO2.Writer.Write((uint)0xD0000000);
                                                    IO2.Writer.Write(Enumerable.Repeat<byte>(0x00, 0x04).ToArray());
                                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Beta: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Hacker]" }), Color.Red);
                                                } else {

                                                    if (User.ip != IPAddress)
                                                    {
                                                        Database.SetIpAddress(User.firstTime, IPAddress);
                                                    }
                                                    IO2.Writer.Write((uint)0xD0000000);
                                                    IO2.Writer.Write(Enumerable.Repeat<byte>(0x00, 0x04).ToArray());
                                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Beta: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Authenticated]" }), Color.Green);
                                                }
                                            }
                                        } else {
                                            IO2.Writer.Write((uint)0xC0000000);
                                            IO2.Writer.Write(Enumerable.ToArray<byte>(Enumerable.Repeat<byte>((byte)0, 4)));
                                            Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Outdated module, sending latest" }), Color.Blue);
                                            IO2.Writer.Write(LatestModuleBeta.Length);
                                            IO2.Writer.Write(LatestModuleBeta);
                                        }
                                    }
                                    break;
                                case (int)UserClasses.ADMIN:

                                    if (User.enabled == 0)
                                    {
                                        IO2.Writer.Write((uint)0xE0000000);
                                        IO2.Writer.Write(Enumerable.Repeat<byte>(0xFF, 0x04).ToArray());
                                        Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Admin: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Not Authenticated]" }), Color.Red);
                                    } else {

                                        if (Tools.CompareBytes(ModuleDigest, Tools.CSHA(LatestModuleAdmin)))
                                        {
                                            if (User.firstTime == "0")
                                            {
                                                Database.SetFuseHash(User.cpukey, Tools.BytesToHexString(FUSEKey));
                                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Admin: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " Grabbing Fuse Digest" }), Color.Orange);
                                            } else {

                                                if (User.firstTime != Tools.BytesToHexString(FUSEKey))
                                                {
                                                    IO2.Writer.Write((uint)0xD0000000);
                                                    IO2.Writer.Write(Enumerable.Repeat<byte>(0x00, 0x04).ToArray());
                                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Admin: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Hacker]" }), Color.Red);
                                                } else {

                                                    if (User.ip != IPAddress)
                                                    {
                                                        Database.SetIpAddress(User.firstTime, IPAddress);
                                                    }
                                                    IO2.Writer.Write((uint)0xD0000000);
                                                    IO2.Writer.Write(Enumerable.Repeat<byte>(0x00, 0x04).ToArray());
                                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Admin: '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Authenticated]" }), Color.Green);
                                                }
                                            }
                                        } else {
                                            IO2.Writer.Write((uint)0xC0000000);
                                            IO2.Writer.Write(Enumerable.ToArray<byte>(Enumerable.Repeat<byte>((byte)0, 4)));
                                            Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Outdated module, sending latest" }), Color.Blue);
                                            IO2.Writer.Write(LatestModuleAdmin.Length);
                                            IO2.Writer.Write(LatestModuleAdmin);
                                        }
                                    }
                                    break;
                                }
                            }
                        } break;
                    case (int)TitleID.GTAV:
                        {
                            byte[] CPUKey = IO2.Reader.ReadBytes(0x10);
                            byte[] FUSEKey = IO2.Reader.ReadBytes(0x10);

                            byte[] FakePatches = System.IO.File.ReadAllBytes("bin/FakePatches.bin");
                            byte[] Patches = System.IO.File.ReadAllBytes("bin/Patches.bin");

                            Database.User User = new Database.User();
                            if (Database.UserExists(ref User, Tools.BytesToHexString(CPUKey)))
                            {
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { "Enforcer [", IPAddress, "] connected" }), Color.Black);
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | CPUKey: '", Tools.BytesToHexString(CPUKey), "'" }), Color.Black);
                                Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | FUSEKey: '", Tools.BytesToHexString(FUSEKey), "'" }), Color.Black);

                                if (User.firstTime != Tools.BytesToHexString(FUSEKey))
                                {
                                    IO2.Writer.Write(FakePatches);
                                    Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | FakePatches.bin was sent to Client" }), Color.Red);
                                } else {

                                    if (User.enabled == 0)
                                    {
                                        Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | User '", User.name, "', ", Tools.BytesToHexString(CPUKey), " [Not Authenticated]" }), Color.Red);
                                    } else {

                                        IO2.Writer.Write(Patches);
                                        Tools.AppendText(richTextBoxEx1, string.Concat(new object[] { IPAddress, " | Patches.bin was sent to Client" }), Color.Blue);
                                    }
                                }
                            }
                        } break;
                    }
                    Client.Close();
                    return;
                }
            }
            catch (Exception ex)
            {
                if (Client.Connected)
                    Client.Close();

                MessageBox.Show(ex.Message, "Server", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }
        private void checkBoxX1_CheckedChanged(object sender, EventArgs e)
        {
            
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Environment.Exit(-0);
        }
    }
}