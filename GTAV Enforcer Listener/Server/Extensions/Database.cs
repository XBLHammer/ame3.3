using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace Server.Extensions
{
    class Database
    {
        public static Form1 mForm;

        [StructLayout(LayoutKind.Sequential)]
        public struct User
        {
            public int id;
            public string name;
            public string cpukey;
            public string ip;
            public DateTime expiry;
            public int enabled;
        }

        public Database(Form1 Form)
        {
            mForm = Form;
        }

        public static List<User> RetreieveUsers()
        {
            List<User> users = new List<User>();
            MySqlConnection connection = new MySqlConnection("datasource=;port=;username=;password=;database=;");
            connection.Open();
            MySqlCommand command = new MySqlCommand("SELECT * FROM `users`", connection);
            MySqlDataReader reader = command.ExecuteReader();
            try
            {
                while (reader.Read())
                {
                    User user = new User();
                    if (!reader.IsDBNull(reader.GetOrdinal("id")))
                        user.id = (int)reader["id"];
                    else
                        user.id = 0;

                    if (!reader.IsDBNull(reader.GetOrdinal("name")))
                        user.name = (string)reader["name"];
                    else
                        user.name = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("cpukey")))
                        user.cpukey = (string)reader["cpukey"];
                    else
                        user.cpukey = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("ip")))
                        user.ip = (string)reader["ip"];
                    else
                        user.ip = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("expiry")))
                        user.expiry = DateTime.Parse((string)reader["expiry"].ToString());
                    else
                        user.expiry = DateTime.Parse("0001-01-01 00:00:00");

                    if (!reader.IsDBNull(reader.GetOrdinal("enabled")))
                        user.enabled = (int)reader["enabled"];
                    else
                        user.enabled = 0;

                    users.Add(user);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Server", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                reader.Close();
            }
            return users;
        }

        public static bool UserExists(ref User user, string cpukey)
        {
            MySqlConnection connection = new MySqlConnection("datasource=;port=;username=;password=;database=;");
            connection.Open();
            MySqlCommand command = new MySqlCommand("SELECT * FROM `users` WHERE cpukey=@CPUKEY", connection);
            command.Parameters.AddWithValue("@CPUKEY", cpukey);
            MySqlDataReader reader = command.ExecuteReader();
            try
            {
                if (reader.Read())
                {
                    if (!reader.IsDBNull(reader.GetOrdinal("name")))
                        user.name = (string)reader["name"];
                    else
                        user.name = "";


                    if (!reader.IsDBNull(reader.GetOrdinal("cpukey")))
                        user.cpukey = (string)reader["cpukey"];
                    else
                        user.cpukey = "";


                    if (!reader.IsDBNull(reader.GetOrdinal("ip")))
                        user.ip = (string)reader["ip"];
                    else
                        user.ip = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("expiry")))
                        user.expiry = DateTime.Parse((string)reader["expiry"].ToString());
                    else
                        user.expiry = DateTime.Parse("0001-01-01 00:00:00");

                    if (!reader.IsDBNull(reader.GetOrdinal("enabled")))
                        user.enabled = (int)reader["enabled"];
                    else
                        user.enabled = 0;

                    return true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Server", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                reader.Close();
            }
            return false;
        }

        public static void UpdateUser(ref User user)
        {
            MySqlConnection connection = new MySqlConnection("datasource=;port=;username=;password=;database=;");
            connection.Open();
            MySqlCommand command = new MySqlCommand("UPDATE `users` SET ip=@IP, expiry=@EXPIRY, enabled=@ENABLED WHERE cpukey=@CPUKEY", connection);
            command.Parameters.AddWithValue("@CPUKEY", user.cpukey);
            command.Parameters.AddWithValue("@IP", user.ip);
            command.Parameters.AddWithValue("@EXPIRY", user.expiry.ToString("yyyy:M:dd h:mm:sstt"));
            command.Parameters.AddWithValue("@ENABLED", user.enabled);
            command.ExecuteNonQuery();
            connection.Close();
        }

        public static void ListUsers()
        {
            if (mForm.InvokeRequired)
            {
                mForm.Invoke(new MethodInvoker(delegate
                    {
                        mForm.listViewEx1.Items.Clear();
                        Tools.Wait(10);
                    }));
            }
            else
            {
                mForm.listViewEx1.Items.Clear();
                Tools.Wait(10);
            }
            List<User> users = RetreieveUsers();
            for (int i = 0; i < users.Count; i++)
            {
                User user = users[i];
                ListViewItem item = new ListViewItem("");
                item.Checked = (user.enabled == 1 ? true : false);
                item.SubItems.Add(user.id.ToString());
                item.SubItems.Add(user.name.ToString());
                item.SubItems.Add(user.cpukey.ToString());
                item.SubItems.Add(user.ip.ToString());
                item.SubItems.Add(user.expiry.ToString());
                if (mForm.InvokeRequired)
                {
                    mForm.Invoke(new MethodInvoker(delegate
                    {
                        mForm.listViewEx1.Items.Add(item);
                        Tools.Wait(10);
                    }));
                }
                else
                {
                    mForm.listViewEx1.Items.Add(item);
                    Tools.Wait(10);
                }
            }
        }
    }
}



