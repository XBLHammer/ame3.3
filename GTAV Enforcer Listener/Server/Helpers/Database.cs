using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace Server.Helpers
{
    internal class Database
    {
        public static Form1 mForm;
        [StructLayout(LayoutKind.Sequential)]
        public struct User
        {
            public int id;
            public string name;
            public string email;
            public string cpukey;
            public string ip;
            public DateTime expiry;
            public int enabled;
            public string firstTime;
            public int userclass;

        }
        enum UserClasses
        {
            ADMIN = 1,
            BETA,
            CLIENT,
            BETAONE
        };
        public Database(Form1 Form)
        {
            mForm = Form;
        }
        public static List<User> RetreieveUsers()
        {
            List<User> list = new List<User>();
            MySqlConnection connection = new MySqlConnection("datasource=localhost;port=3306;username=root;password=;database=gtavenforcer;");
            connection.Open();
            MySqlDataReader reader = new MySqlCommand("SELECT * FROM `users`;", connection).ExecuteReader();
            try
            {
                while (reader.Read())
                {
                    User item = new User();
                    if (!reader.IsDBNull(reader.GetOrdinal("id")))
                        item.id = (int)reader["id"];
                    else
                        item.id = 0;

                    if (!reader.IsDBNull(reader.GetOrdinal("name")))
                        item.name = (string)reader["name"];
                    else
                        item.name = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("email")))
                        item.email = (string)reader["email"];
                    else
                        item.email = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("cpukey")))
                        item.cpukey = (string)reader["cpukey"];
                    else
                        item.cpukey = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("ip")))
                        item.ip = (string)reader["ip"];
                    else
                        item.ip = "0.0.0.0";

                    if (!reader.IsDBNull(reader.GetOrdinal("expiry")))
                        item.expiry = DateTime.Parse(reader["expiry"].ToString());
                    else
                        item.expiry = DateTime.Parse("0000-00-00 00:00:00");

                    if (!reader.IsDBNull(reader.GetOrdinal("enabled")))
                        item.enabled = (int)reader["enabled"];
                    else
                        item.enabled = 0;

                    if (!reader.IsDBNull(reader.GetOrdinal("firstTime")))
                        item.firstTime = (string)reader["firstTime"];
                    else
                        item.firstTime = "0";

                    if (!reader.IsDBNull(reader.GetOrdinal("userclass")))
                        item.userclass = (int)reader["userclass"];
                    else
                        item.userclass = (int)UserClasses.CLIENT;

                    list.Add(item);
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
            return list;
        }
        public static void SetFuseHash(string cpu, string fuse)
        {
            MySqlConnection connection = new MySqlConnection("datasource=localhost;port=3306;username=root;password=;database=gtavenforcer;");
            connection.Open();
            MySqlCommand command = new MySqlCommand("UPDATE `users` SET firstTime='" + fuse + "' WHERE cpukey='" + cpu + "';", connection);
            MySqlDataReader reader = command.ExecuteReader();
            reader.Close();
            ListUsers();
        }
        public static void SetIpAddress(string fuse, string ip)
        {
            MySqlConnection connection = new MySqlConnection("datasource=localhost;port=3306;username=root;password=;database=gtavenforcer;");
            connection.Open();
            MySqlCommand command = new MySqlCommand("UPDATE `users` SET ip='" + ip + "' WHERE firstTime='" + fuse + "';", connection);
            MySqlDataReader reader = command.ExecuteReader();
            reader.Close();
            ListUsers();
        }
        public static bool UserExists(ref User user, string cpukey)
        {
            MySqlConnection connection = new MySqlConnection("datasource=localhost;port=3306;username=root;password=;database=gtavenforcer;");
            connection.Open();
            MySqlCommand command = new MySqlCommand("SELECT * FROM `users` WHERE cpukey=@CPUKEY;", connection);
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

                    if (!reader.IsDBNull(reader.GetOrdinal("email")))
                        user.email = (string)reader["email"];
                    else
                        user.email = "";
                    
                    if (!reader.IsDBNull(reader.GetOrdinal("cpukey")))
                        user.cpukey = (string)reader["cpukey"];
                    else
                        user.cpukey = "";

                    if (!reader.IsDBNull(reader.GetOrdinal("ip")))
                        user.ip = (string)reader["ip"];
                    else
                        user.ip = "0.0.0.0";

                    if (!reader.IsDBNull(reader.GetOrdinal("expiry")))
                        user.expiry = DateTime.Parse(reader["expiry"].ToString());
                    else
                        user.expiry = DateTime.Parse("0000-00-00 00:00:00");

                    if (!reader.IsDBNull(reader.GetOrdinal("enabled")))
                        user.enabled = (int)reader["enabled"];
                    else
                        user.enabled = 0;

                    if (!reader.IsDBNull(reader.GetOrdinal("firstTime")))
                        user.firstTime = (string)reader["firstTime"];
                    else
                        user.firstTime = "0";

                    if (!reader.IsDBNull(reader.GetOrdinal("userclass")))
                        user.userclass = (int)reader["userclass"];
                    else
                        user.userclass = (int)UserClasses.CLIENT;

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

        public static void ListUsers()
        {
            if (mForm.InvokeRequired)
            {
                mForm.Invoke(new MethodInvoker(delegate
                {
                    mForm.listViewEx1.Items.Clear();
                }));
            }
            else
            {
                mForm.listViewEx1.Items.Clear();
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
                item.SubItems.Add(user.firstTime.ToString());
                item.SubItems.Add(user.ip.ToString());
                switch (user.userclass)
                {
                    case (int)UserClasses.ADMIN: item.SubItems.Add("Admin"); break;
                    case (int)UserClasses.BETAONE: item.SubItems.Add("Beta One"); break;
                    case (int)UserClasses.BETA: item.SubItems.Add("Beta"); break;
                    case (int)UserClasses.CLIENT: item.SubItems.Add("Client"); break;
                }

                if (mForm.InvokeRequired)
                {
                    mForm.Invoke(new MethodInvoker(delegate
                    {
                        mForm.listViewEx1.Items.Add(item);
                    }));
                }
                else
                {
                    mForm.listViewEx1.Items.Add(item);
                }
            }
        }
    }
}