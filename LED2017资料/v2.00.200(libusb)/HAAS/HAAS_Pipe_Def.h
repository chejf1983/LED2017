// HAAS_Pipe_def.h

#ifndef __HAAS_PIPE_DEF_H__
#define __HAAS_PIPE_DEF_H__

/* 客户端用的名字 , 注:ServerName要变的不是固定的 */
#define  HAAS_PIPE_NAME_CLIENT    "\\\\ServerName\\pipe\\SpectraNexus" 

/* 服务端用的名字 */
#define  HAAS_PIPE_NAME_SREVER    "\\\\.\\pipe\\SpectraNexus"          

#define  HAAS_SAMPLE                       "[Sample    ]"
#define  HAAS_READ_DATA                    "[ReadData  ]"
#define  HAAS_CLEAR_ALL                    "[ClearAll  ]"

#endif
