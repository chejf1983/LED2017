using LTISDLL.FaultSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.User
{
    public delegate void UserStateChanged(User user);
    public class UserCenter
    {
        public enum Authority
        {
            USER,
            MANAGER,
            SUPPER
        }

        public event UserStateChanged UserChangeEvent;

        /// <summary>
        /// 默认超级用户
        /// </summary>
        private readonly User nahonuser = new NahonUser();

        /// <summary>
        /// 当前用户
        /// </summary>
        private User currentUser = null;
        public User CurrentUser { get { return this.currentUser; } }

        /// <summary>
        /// 用户数据库
        /// </summary>
        private SQLDB sqldb;

        #region 用户控制
        public void UpdateUserEvent()
        {
           //currentUser = nahonuser;
            if (this.UserChangeEvent != null)
            {
                this.UserChangeEvent(this.currentUser);
            }
        }

        /// <summary>
        /// 初始化用户中心
        /// </summary>
        public void InitUserCenter()
        {
            sqldb = new SQLDB();
            sqldb.InitDB();
        }

        /// <summary>
        /// 用户登录
        /// </summary>
        /// <param name="user"></param>
        /// <param name="inpwd"></param>
        /// <returns></returns>
        public bool Login(string user, string inpwd)
        {
            ///当前有用户登录，先登出
            if (this.CurrentUser != null)
            {
                ///登出当前用户
                this.Logout();
            }

            User userinfo;

            try
            {
                if (user == nahonuser.Name)
                {
                    ///如果是超级用户，直接返回超级用户信息
                    userinfo = this.nahonuser;
                }
                else
                {
                    ///查找数据库中的用户信息
                    userinfo = this.sqldb.FindUser(user);
                }
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                   "数据库异常，无法登录：" + ex.ToString());
                return false;
            }

            ///不存在此用户
            if (userinfo == null)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "用户不存在：" + user);
                return false;
            }

            ///密码错误
            if (!userinfo.CheckPWD(inpwd))
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "密码错误！");
                return false;
            }
            else
            {

                this.currentUser = userinfo;

                if (this.UserChangeEvent != null)
                {
                    this.UserChangeEvent(this.currentUser);
                }
                return true;
            }
        }

        /// <summary>
        /// 登出用户
        /// </summary>
        public void Logout()
        {
            ///用户名不删除，只取消系统权限
            this.currentUser = null;

            if (this.UserChangeEvent != null)
            {
                this.UserChangeEvent(null);
            }
        }

        /// <summary>
        /// 检查当前用户权限
        /// </summary>
        /// <param name="level"></param>
        /// <returns></returns>
        public bool CheckCurrentAccessLevel(Authority level)
        {
            if (this.currentUser == null)
            {
                return false;
            }

            return this.currentUser.CheckAccessLevel(level);
        }

        /// <summary>
        /// 添加用户
        /// </summary>
        /// <param name="username"></param>
        /// <param name="pwd"></param>
        /// <param name="newlevel"></param>
        /// <returns></returns>
        public bool AddUser(string username, string pwd, Authority newlevel)
        {
            ///检查当前用户是否有权限添加用户
            if (!this.CheckCurrentAccessLevel(Authority.MANAGER))
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "当前用户没有权限添加新用户！");
                return false;
            }

            ///检查新加用户权限是否高于当前用户权限
            if (!this.currentUser.CheckAccessLevel(newlevel))
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                          "新建用户权限无法高于当前权限！");
                return false;
            }

            ///检查是否和超级用户重名
            if (username == nahonuser.Name)
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                         "非法用户名！");
                return false;
            }

            try
            {
                ///检查用户是否已经存在
                if (sqldb.FindUser(username) != null)
                {
                   FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                             "改用户已经存在！");
                    return false;
                }

                ///添加新用户
                this.sqldb.Adduser(new User(username, pwd, newlevel, this.sqldb));
                return true;
            }
            catch (Exception ex)
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "用户数据库异常，无法添加新用户！\r\n" + ex.ToString());
                return false;
            }
        }

        /// <summary>
        /// 删除用户
        /// </summary>
        /// <param name="username"></param>
        /// <returns></returns>
        public bool DeleteUser(string username)
        {
            ///检查当前用户是否有权限删除用户
            if (!this.CheckCurrentAccessLevel(Authority.MANAGER))
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "当前用户没有权限删除用户！");
                return false;
            }

            ///超级用户，不能删除
            if (username == nahonuser.Name)
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                    "不能删除超级用户");
                return false;
            }


            ///超级用户，不能删除
            if (username == this.currentUser.Name)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                     "不能删除当前用户");
                return false;
            }

            try
            {
                this.sqldb.DeleteUser(username);
                return true;
            }
            catch (Exception ex)
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "用户数据库异常，无法删除用户！\r\n" + ex.ToString());
                return false;
            }
        }

        /// <summary>
        /// 获取所有用户信息
        /// </summary>
        /// <returns></returns>
        public User[] GetAllUser()
        {
            ///检查当前用户是否有权限
            if (!this.CheckCurrentAccessLevel(Authority.MANAGER))
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                       "当前用户没有权限！");
                return new User[0];
            }

            try
            {
                return this.sqldb.FindAllUser();
            }
            catch (Exception ex)
            {
               FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                          "用户数据库异常，无法获取用户！\r\n" + ex.ToString());
                return new User[0];
            }
        }
        #endregion
    }
}
