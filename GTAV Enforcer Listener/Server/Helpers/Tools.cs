using System;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Windows.Forms;
using System.IO;
using System.IO.Compression;

using DevComponents.DotNetBar.Controls;

namespace Server.Helpers
{
    class Tools
    {
        public static void Wait(int seconds)
        {
            DateTime dt = DateTime.Now + new TimeSpan(0, 0, seconds);
            while (dt > DateTime.Now)
                Application.DoEvents();
        }

        public static int RandomInt32(int length)
        {
            const string chars = "0123456789";
            var random = new Random();
            return Convert.ToInt32(new string(Enumerable.Repeat(chars, length).Select(s => s[random.Next(s.Length)]).ToArray()));
        }

        public static int RandomHexInt32(int length)
        {
            const string chars = "0123456789ABCDEF";
            var random = new Random();
            return Convert.ToInt32("0x" + new string(Enumerable.Repeat(chars, length).Select(s => s[random.Next(s.Length)]).ToArray()));
        }

        public static string BytesToString(byte[] buffer)
        {
            string str = "";
            for (int i = 0; i < buffer.Length; i++)
            {
                str += buffer[i].ToString("");
            }
            return str;
        }

        public static string BytesToHexString(byte[] buffer)
        {
            string str = "";
            for (int i = 0; i < buffer.Length; i++)
            {
                str += buffer[i].ToString("X2");
            }
            return str;
        }

        public static bool CompareBytes(byte[] buffer1, byte[] buffer2)
        {
            if (buffer1.Length != buffer2.Length)
            {
                return false;
            }
            for (int i = 0; i < buffer1.Length; i++)
            {
                if (buffer1[i] != buffer2[i])
                {
                    return false;
                }
            }
            return true;
        }

        public static byte[] Compress(byte[] buffer)
        {
            MemoryStream stream = new MemoryStream();
            MemoryStream stream2 = new MemoryStream(buffer);
            DeflateStream stream3 = new DeflateStream(stream, CompressionMode.Compress);
            byte[] buffer2 = new byte[0x1000];
            int count = 0;
            while ((count = stream2.Read(buffer2, 0, buffer2.Length)) != 0)
            {
                stream3.Write(buffer2, 0, count);
            }
            stream3.Close();
            return stream.ToArray();
        }

        public static byte[] Decompress(byte[] buffer)
        {
            MemoryStream stream = new MemoryStream();
            MemoryStream stream2 = new MemoryStream(buffer);
            DeflateStream stream3 = new DeflateStream(stream2, CompressionMode.Decompress);
            byte[] buffer2 = new byte[0x1000];
            int count = 0;
            while ((count = stream3.Read(buffer2, 0, buffer2.Length)) != 0)
            {
                stream.Write(buffer2, 0, count);
            }
            return stream.ToArray();
        }

        public static string FormatSize(long FileSize)
        {
            if (FileSize >= Math.Pow(2.0, 80.0))
            {
                return string.Format("{0} YB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 80.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 70.0))
            {
                return string.Format("{0} ZB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 70.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 60.0))
            {
                return string.Format("{0} EB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 60.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 50.0))
            {
                return string.Format("{0} PB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 50.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 40.0))
            {
                return string.Format("{0} TB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 40.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 30.0))
            {
                return string.Format("{0} GB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 30.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 20.0))
            {
                return string.Format("{0} MB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 20.0)), 2));
            }
            if (FileSize >= Math.Pow(2.0, 10.0))
            {
                return string.Format("{0} KB", Math.Round((double)(((double)FileSize) / Math.Pow(2.0, 10.0)), 2));
            }
            return string.Format("{0} Bytes", FileSize);
        }

        public static byte[] CSHA(byte[] data)
        {
            SHA1Managed SHA1 = new SHA1Managed();
            SHA1.Initialize();
            SHA1.TransformFinalBlock(data, 0, data.Length);
            return SHA1.Hash;
        }

        public static byte[] CRC4(byte[] data, byte[] key)
        {
            byte num = 0;
            int num2 = 0;
            byte[] buffer = new byte[256];
            byte[] buffer2 = new byte[256];
            for (num2 = 0; num2 < 256; num2++)
            {
                buffer[num2] = (byte)num2;
                buffer2[num2] = key[num2 % key.GetLength(0)];
            }
            int index = 0;
            for (num2 = 0; num2 < 256; num2++)
            {
                index = ((index + buffer[num2]) + buffer2[num2]) % 256;
                num = buffer[num2];
                buffer[num2] = buffer[index];
                buffer[index] = num;
            }
            num2 = index = 0;
            for (int i = 0; i < data.GetLength(0); i++)
            {
                num2 = (num2 + 1) % 256;
                index = (index + buffer[num2]) % 256;
                num = buffer[num2];
                buffer[num2] = buffer[index];
                buffer[index] = num;
                int num3 = (buffer[num2] + buffer[index]) % 256;
                data[i] = (byte)(data[i] ^ buffer[num3]);
            }
            return data;
        }

        public static void AppendText(RichTextBoxEx rtb, string str, Color color)
        {
            try
            {
                if (rtb.InvokeRequired)
                {
                    rtb.Invoke(new MethodInvoker(delegate
                        {
                            rtb.SelectionStart = rtb.TextLength;
                            rtb.SelectionLength = 0;
                            rtb.SelectionColor = color;
                            string time = string.Format("{0:hh:mm:ss tt}", DateTime.Now.ToLocalTime());
                            rtb.AppendText(string.Concat(new object[] { "[", time, "] ", str, "\n" }));
                            rtb.SelectionColor = rtb.ForeColor;
                            rtb.SelectionStart = rtb.Text.Length;
                            rtb.ScrollToCaret();
                        }));
                }
                else
                {
                    rtb.SelectionStart = rtb.TextLength;
                    rtb.SelectionLength = 0;
                    rtb.SelectionColor = color;
                    string time = string.Format("{0:hh:mm:ss tt}", DateTime.Now.ToLocalTime());
                    rtb.AppendText(string.Concat(new object[] { "[", time, "] ", str, "\n" }));
                    rtb.SelectionColor = rtb.ForeColor;
                    rtb.SelectionStart = rtb.Text.Length;
                    rtb.ScrollToCaret();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Server", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}