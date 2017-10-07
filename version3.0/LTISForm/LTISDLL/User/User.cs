using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LTISDLL.FaultSystem;

namespace LTISDLL.User
{
    public class User
    {   /// <summary>
        /// 用户数据库
        /// </summary>
        private SQLDB sqldb;

        //权限
        private UserCenter.Authority level;
        public UserCenter.Authority AcessLevel { get { return this.level; } }

        //用户名
        private string username;
        public string Name { get { return this.username; } }

        //密码
        private string pwd;
        public string Pwd { get { return this.pwd; } }

        public User(string username, string pwd, UserCenter.Authority level, SQLDB sqldb)
        {
            this.sqldb = sqldb;
            this.level = level;
            this.username = username;
            this.pwd = pwd;
        }

        /// <summary>
        /// 检查密码
        /// </summary>
        /// <param name="pwd"></param>
        /// <returns></returns>
        public bool CheckPWD(string pwd)
        {
            return this.Pwd.Equals(pwd);
        }

        /// <summary>
        /// 检查权限
        /// </summary>
        /// <param name="level"></param>
        /// <returns></returns>
        public bool CheckAccessLevel(UserCenter.Authority level)
        {
            return level <= this.AcessLevel;
        }

        /// <summary>
        /// 修改密码
        /// </summary>
        /// <param name="oldpwd"></param>
        /// <param name="newpwd"></param>
        /// <returns></returns>
        public bool ChangPassword(string oldpwd, string newpwd)
        {
            try
            {
                ///找到当前用户的信息
                User userinfo = this.sqldb.FindUser(this.Name);
                if (userinfo != null)
                {
                    ///如果密码正确，删除旧用户信息，添加新用户信息
                    if (userinfo.pwd == oldpwd)
                    {
                        this.sqldb.DeleteUser(this.Name);
                        this.sqldb.Adduser(new User(this.Name, newpwd, this.AcessLevel, this.sqldb));
                        return true;
                    }
                    else
                    {
                        //密码错误，报错
                        FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                                     "密码错误！");
                        return false;
                    }
                }
                else
                {
                    ///如果找不到当前用户信息,表示当前用户信息丢失，直接添加新用户
                    this.sqldb.Adduser(new User(this.Name, newpwd, this.AcessLevel, this.sqldb));
                    return true;
                }
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "用户数据库异常，无法修改密码！\r\n" + ex.ToString());
                return false;
            }
        }
    }
}
