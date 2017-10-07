using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LTISDLL.User
{
    public class NahonUser : User
    {
        public NahonUser() : base("nahon","nahon",UserCenter.Authority.SUPPER, null)
        {

        }

        public new bool ChangPassword(string oldpwd, string newpwd)
        {
            return false;
        }
    }
}
