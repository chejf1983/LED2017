using System;
using System.Data.SQLite;

namespace LTISDLL.User
{
    /// <summary>
    /// sqlite 文件数据库，没有使用try catch，默认文件读写不会有异常，如果异常后期再处理
    /// </summary>
    public class SQLDB
    {
        //private SQLiteConnection m_dbConnection;
        private string connectstring;
        private readonly string DBFile = "db.sqlite";
        private readonly string TableName = "usertable";
        private readonly string user = "name";
        private readonly string password = "password";
        private readonly string authority = "authority";

        /// <summary>
        /// 初始化数据库
        /// </summary>
        public void InitDB()
        {
            this.connectstring = "Data Source=" + DBFile + ";Version=3;";
            ///判断数据库是否存在
            if (!System.IO.File.Exists(DBFile))
            {
                ///创建数据库文件
                SQLiteConnection.CreateFile(DBFile);

                using (SQLiteConnection m_dbConnection = new SQLiteConnection(connectstring))
                {
                    ///创建数据库table
                    m_dbConnection.Open();
                    string sql = "create table " + TableName + " (" +
                       user + " varchar(20) not null primary key unique, " +
                       authority + " int, " +
                       password + " varchar(50))";
                    SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                    command.ExecuteNonQuery();
                }

                ///添加一个默认admin用户
                this.Adduser(new User("admin", "admin", UserCenter.Authority.MANAGER, this));
            }
        }

        /// <summary>
        /// 添加用户
        /// </summary>
        /// <param name="name"></param>
        /// <param name="pwd"></param>
        public void Adduser(User newuser)
        {
            lock (this)
            {
                using (SQLiteConnection m_dbConnection = new SQLiteConnection(connectstring))
                {
                    string sql = "insert into " + TableName +
                    " (" + user + "," + authority + "," + password + ") " +
                    "values (@user, @authority, @password)";
                    m_dbConnection.Open();
                    SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                    command.Parameters.AddRange(new[] {
                    new SQLiteParameter ("@user", newuser.Name),
                    new SQLiteParameter ("@authority", newuser.AcessLevel),
                    new SQLiteParameter ("@password", newuser.Pwd),});
                    command.ExecuteNonQuery();
                    command.Dispose();
                }
            }
        }

        /// <summary>
        /// 根据用户名找到用户
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public User FindUser(string name)
        {
            lock (this)
            {
                User ret_user = null;

                using (SQLiteConnection m_dbConnection = new SQLiteConnection(connectstring))
                {
                    string sql = "select * from " + TableName + " where " + user + " = @user";

                    m_dbConnection.Open();
                    SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                    command.Parameters.AddRange(new[] { new SQLiteParameter("@user", name) });
                    SQLiteDataReader reader = command.ExecuteReader();

                    if (reader.Read())
                    {
                        ret_user = new User(name, reader[password].ToString(), (UserCenter.Authority)reader[authority], this);
                    }
                    reader.Close();
                    command.Dispose();
                }
                return ret_user;
            }
        }

        /// <summary>
        /// 删除用户
        /// </summary>
        /// <param name="name"></param>
        public void DeleteUser(string name)
        {
            lock (this)
            {
                using (SQLiteConnection m_dbConnection = new SQLiteConnection(connectstring))
                {
                    string sql = "delete from " + TableName + " where " + user + " = @user";
                    m_dbConnection.Open();
                    SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                    command.Parameters.Add(new SQLiteParameter("@user", name));
                    command.ExecuteNonQuery();
                    command.Dispose();
                }
            }
        }

        /// <summary>
        /// 获取所有用户名称
        /// </summary>
        /// <returns></returns>
        public User[] FindAllUser()
        {
            lock (this)
            {
                System.Collections.Generic.List<User> ret = new System.Collections.Generic.List<User>();
                using (SQLiteConnection m_dbConnection = new SQLiteConnection(connectstring))
                {
                    string sql = "select * from " + TableName;

                    m_dbConnection.Open();
                    SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                    SQLiteDataReader reader = command.ExecuteReader();
                    while (reader.Read())
                    {
                        ret.Add(new User(reader[user].ToString(), reader[password].ToString(), (UserCenter.Authority)reader[authority], this));
                    }

                    reader.Close();
                    command.Dispose();
                }

                return ret.ToArray();
            }
        }
    }
}
