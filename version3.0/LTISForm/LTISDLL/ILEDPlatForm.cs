using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.SYSControl;

namespace LTISDLL
{
    public interface ILEDPlatForm
    {
        void InitPlatForm();

        User.UserCenter UserCenter { get; }

        ControlSystem ControlManager { get; }
    }
}
