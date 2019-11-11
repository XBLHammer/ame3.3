using System;
using System.Linq;
using System.Drawing;
using System.Windows.Forms;
using DevComponents.DotNetBar.Controls;

namespace Server.Extensions
{
    class Tools
    {
        public static void Wait(int milliseconds)
        {
            DateTime DT = DateTime.Now + new TimeSpan(0, 0, 0, 0, milliseconds);
            while (DT > DateTime.Now)
                Application.DoEvents();
        }

        public static int RandomInt(int length)
        {
            const string chars = "0123456789";
            var random = new Random();
            return Convert.ToInt32(new string(Enumerable.Repeat(chars, length).Select(s => s[random.Next(s.Length)]).ToArray()));
        }

        public static string RandomString(int length)
        {
            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"; // abcdefghijklmnopqrstuvwxyz
            var random = new Random();
            return new string(Enumerable.Repeat(chars, length).Select(s => s[random.Next(s.Length)]).ToArray());
        }

        public static string BytesToString(byte[] buffer)
        {
            string str = "";
            for (int i = 0; i < buffer.Length; i++)
            {
                str = str + buffer[i].ToString("");
            }
            return str;
        }

        public static string BytesToHexString(byte[] buffer)
        {
            string str = "";
            for (int i = 0; i < buffer.Length; i++)
            {
                str = str + buffer[i].ToString("X2");
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

        public static bool CompareStrings(string str1, string str2)
        {
            if (str1 == str2)
                return true;
            else
                return false;
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
                        rtb.AppendText("[" + time + "] " + str + "\n");
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
                    rtb.AppendText("[" + time + "] " + str + "\n");
                    rtb.SelectionColor = rtb.ForeColor;
                    rtb.SelectionStart = rtb.Text.Length;
                    rtb.ScrollToCaret();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "XCS", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}