
////ExEverLincese.h
//版权所有 2014 杭州远方光电信息股份有限公司(EVERFINE)

#ifndef _EXEVERLINCESE_H_
#define _EXEVERLINCESE_H_

//读取授权码是否到期
//输入EVERFINE_EVERFINE则不管授权码
//return :
//       -1:未读取到授权文件 
//        0:OK 
//        1:产品型号不匹配
//        2:产品编号不匹配
//        3:产品授权起始时间和电脑不匹配
//        4:产品授权已超期
//		  5:计算机时间被修改过

extern int __stdcall EVER_Lincese(char *cModel,char *cSN);

#endif
