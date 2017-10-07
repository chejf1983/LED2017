#include "stdafx.h"
#include "RegistHandle.h"
#include "HardDisk.h"
#include "MD5Checksum.h"

char mappinglist[10] = {'A', 'S', 'H', 'X', 'D', 'Z', 'B', 'Y', 'G', 'L'};
CString strRegistID;
CString strRecentTime;
int leftTimeAft = 0;

CString GetCPUID()
{
	CString cpu;

	unsigned   long   s1,s2;   
	unsigned   char   vendor_id[] = "------------";   

	CString strCPUID0;
	CString strCPUID1;
	CString strCPUID2;

	__asm{   
			xor   eax,eax   
			cpuid   
			mov   dword   ptr   vendor_id,ebx   
			mov   dword   ptr   vendor_id[+4],edx   
			mov   dword   ptr   vendor_id[+8],ecx   
		}   
	strCPUID0.Format("%s",vendor_id);   
	__asm{   
			mov   eax,01h   
			xor   edx,edx   
			cpuid   
			mov   s1,edx   
			mov   s2,eax   
		}   
	strCPUID1.Format("%08X%08X",s1,s2);   
	__asm{   
			
			mov   eax,03h   
			xor   ecx,ecx   
			xor   edx,edx   
			cpuid   
			mov   s1,edx   
			mov   s2,ecx   
		}   
	strCPUID2.Format("%08X%08X",s1,s2);   

	cpu = strCPUID1;

	return cpu;
}

CString GetHardDiskID()
{
	CString hardDisk;
	hardDisk = "";

	char strSerialNumber[16]; 
	memset(strSerialNumber, 0, 16); 
	
	BOOL bRet = GetHDSerialCode(strSerialNumber); 
	
	if(bRet) 
	{
		hardDisk.Format("%s", strSerialNumber);
	}

	return hardDisk;
}

CString GetCharacterCode()
{
	CString str_CharacCode;
	CString str_cpu, str_disk;
	int num1 = 0, num2 = 0;
	char m, d, h;

	CTime t = CTime::GetCurrentTime();

	str_cpu = GetCPUID();
	str_disk = GetHardDiskID();

	str_CharacCode = str_cpu + str_disk;

	srand(time(0));
	num1 = rand()%100;
	num2 = rand()%100;

	if(num1 < 10)
	{
		num1 = 10;
	}
	if(num2 < 10)
	{
		num2 = 10;
	}

	m = t.GetMonth() + 65;
	d = t.GetDay()/2 + 65; 
	h = t.GetHour() + 65;
	str_CharacCode.Format("%s%d%s%c%c%s%c%s%d",
		str_cpu.Mid(4, 3), num1, str_cpu.Left(4), h, d, str_disk.Mid(2, 4), m, str_disk.Left(2), num2);

	return str_CharacCode;
}


CString InsertDays(CString str, int days)
{
	CString newCode;
	char c[20];	
	int d[2];

	strcpy(c, str);
	d[0] = c[2] + days/10;
	d[1] = c[12] + days%10; 

	c[2] = d[0];
	c[12] = d[1];

	newCode = c;
	return newCode; 
}

CString TransformToString(int year, int month, int day)
{
	CString str;
	int num[8];
	num[0] = year/1000;
	num[1] = (year - num[0] * 1000) / 100;
	num[2] = (year - num[0] * 1000 - num[1] * 100) / 10;
	num[3] = year%10;
	num[4] = month / 10;
	num[5] = month % 10;
	num[6] = day / 10;
	num[7] = day % 10;

	str = "";
	for(int i=0; i<8; i++)
	{
		str += mappinglist[num[i]];
	}
	return str;
}

int TransformToInt(CString str)
{
	int date = 0, num[8];
	char c[8];
	strcpy(c, str);
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(c[i] == mappinglist[j])
			{
				num[i] = j;
				j = 10;
			}
		}
	}

	date = num[0] * 10000000 + num[1] * 1000000
		   + num[2] * 100000 + num[3] * 10000
		   + num[4] * 1000 + num[5] * 100
		   + num[6] * 10 + num[7];
	
	return date;
}

CString Encrypt(CString str, int days)
{
	CString strcode, strafteradd;
	
	strafteradd = InsertDays(str, days);
	strcode = CMD5Checksum::GetMD5( (BYTE*)(const char*)strafteradd, strafteradd.GetLength());

	return strcode;
}

int Decrypt(CString str)
{
	CString str_cpu, str_disk;
	char c[3][40];
	int trialTime = 0;
	int a[3] = {0, 0, 0}, b[3] = {0, 0, 0};

	str_cpu = GetCPUID();
	str_disk = GetHardDiskID();

	strcpy(c[0], str_cpu);
	strcpy(c[1], str_disk);
	strcpy(c[2], str);

	a[0] = c[0][6];
	b[0] = c[1][3];
	a[1] = c[2][2];
	b[1] = c[2][12];

	a[2] = a[1] - a[0]; 
	b[2] = b[1] - b[0];
	
	trialTime = a[2] * 10 + b[2];

	return trialTime;
}

CString CalSubKey(CString str)
{
	CString strKey;
	strKey = str.Left(3) + str.Mid(9, 7);
	return strKey;
}

bool ReadRegFile()
{
	return TRUE;
	CString str;
	CString path = "C:\\WINDOWS\\system32\\xpmagn.reg";
	CStdioFile m_file;
	if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
	{
		for(int i=0; i<99; i++)
		{
			m_file.ReadString(str);
		}
		m_file.ReadString(strRegistID);
		m_file.ReadString(strRecentTime);
		m_file.Close();
		return true;
	}
	return false;
}

bool WriteRegFile(CString str, int days)
{
	return TRUE;
	CString path = "C:\\WINDOWS\\system32\\xpmagn.reg";
	CStdioFile m_file;
	CTime t = CTime::GetCurrentTime();
	int a = 0, b = 0;

	if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
	{
		CString str_write;
		for(int i=0; i<99;i++)
		{
			m_file.WriteString("\n");
		}
		a = days/10;
		b = days%10;
		str_write = mappinglist[b] + str + mappinglist[a];
		m_file.WriteString(str_write);
		m_file.WriteString("\n");

		str_write = TransformToString(t.GetYear(), t.GetMonth(), t.GetDay());
		m_file.WriteString(str_write);
		
		m_file.Close();
	}
	return true;
}

bool WriteRegester(CString str, int days)
{
	return TRUE;
	HKEY hky;
	DWORD dw;

	CTime t = CTime::GetCurrentTime();
	CString strUser, strvalue;
	LPCTSTR strUserValue;
	strvalue = TransformToString(t.GetYear(), t.GetMonth(), t.GetDay());
	strUserValue = strvalue;

	strUser = CalSubKey(InsertDays(str, days));

	long ret0 = ::RegCreateKeyEx(HKEY_CLASSES_ROOT, strUser, 0, REG_NONE, 
		             REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hky, &dw);
	if(ret0 != ERROR_SUCCESS)
	{
		return false;
	}
	
	long ret1 = ::RegSetValueEx(hky, strUser, 0, REG_SZ, 
	           	(const BYTE *)strUserValue,	strlen(strUserValue)+1);
	if(ret1 != ERROR_SUCCESS)
	{
		return false;
	}
	
	return true;
}


int CaculateDays(int date1, int date2)
{
	int days = 0;
	int year[2], month[2], day[2];
	int i = 0;

	year[0] = date1 / 10000;
	month[0] = (date1 - year[0] * 10000) / 100;
	day[0] = date1 % 100;

	year[1] = date2 / 10000;
	month[1] = (date2 - year[1] * 10000) / 100;
	day[1] = date2 % 100;
	
	days = day[1] - day[0];
	if(year[0] == year[1])
	{		
		for(i=month[0]; i<month[1]; i++)
		{
			if(i == 2)
			{
				if(((year[0]%4 == 0) && (year[0]%100 != 0)) ||(year[0]%400 == 0))
				{
					days += 29;
				}
				else
				{
					days += 28;
				}
			}
			else if((i == 4) || (i == 6) || (i == 9) || (i == 11))
			{
				days += 30;
			}
			else
			{
				days += 31;
			}
		}
	}
	else
	{
		if(year[1] - year[0] > 1)
		{
			return 0;
		}
		else
		{
			for(i=month[0]; i<13; i++)
			{
				if(i == 2)
				{
					if(((year[0]%4 == 0) && (year[0]%100 != 0)) ||(year[0]%400 == 0))
					{
						days += 29;
					}
					else
					{
						days += 28;
					}
				}
				else if((i == 4) || (i == 6) || (i == 9) || (i == 11))
				{
					days += 30;
				}
				else
				{
					days += 31;
				}
			}
			for(i=1; i<month[1]; i++)
			{
				if(i == 2)
				{
					if(((year[0]%4 == 0) && (year[0]%100 != 0)) ||(year[0]%400 == 0))
					{
						days += 29;
					}
					else
					{
						days += 28;
					}
				}
				else if((i == 4) || (i == 6) || (i == 9) || (i == 11))
				{
					days += 30;
				}
				else
				{
					days += 31;
				}
			}
		}
	}
	
	return days;
}

bool IfOverdue(CString strReg)
{
	leftTimeAft = 365;
	return FALSE;
	char a[22];
	int num1 = 0, num2 = 0;
	int txtTime = 0, regTime = 0, currentTime = 0;
	int leftTimeBef = 0, totalRegTime = 0;

	CTime t = CTime::GetCurrentTime();

	/////首先查看读到的ID中的时间和使用时间
	strcpy(a, strRegistID);

	for(int i=0; i<10; i++)
	{
		if(a[0] == mappinglist[i])
		{
			num1 = i;
		}
		if(a[21] == mappinglist[i])
		{
			num2 = i;
		}
	}

	leftTimeBef = num2 * 10 + num1;
	totalRegTime = Decrypt(strRegistID.Mid(1, 20)); 

	//////永久注册
	if(0 == leftTimeBef)
	{
		if((0 == regTime) && (0 == totalRegTime))
		{
			leftTimeAft = 365;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if((leftTimeBef >= 1) && (leftTimeBef <= totalRegTime))
	{		
		/////文档中获取最近使用时间
		txtTime = TransformToInt(strRecentTime);
		/////注册表项值转换为注册时间
		regTime = TransformToInt(strReg);
		
		//注册时间必须早于或等于最近使用时间  最近使用时间 - 注册时间 = 总注册时间 - 剩余时间
		if((regTime <= txtTime) && (CaculateDays(regTime, txtTime) == (totalRegTime - leftTimeBef)))
		{
			currentTime = TransformToInt(TransformToString(t.GetYear(), t.GetMonth(), t.GetDay()));
			if(txtTime <= currentTime)//判断最近使用时间是否小于等于当前时间
			{
				///计算剩余试用时间  若剩余时间大于0
				leftTimeAft = leftTimeBef - CaculateDays(txtTime, currentTime);
				if(leftTimeAft > 0)
				{
	                //更新注册文档中ID的首尾项用以记录剩余时间   更新最近使用时间
				    WriteRegFile(strRegistID.Mid(1, 20), leftTimeAft); 
					return true;
				}
			}
		}
	}

	return false;
}

int IsRegisted()
{
	leftTimeAft = 365;
	return 2;
	//打开文件读取产品唯一ID
	if(ReadRegFile())
	{
		CString str, strUser, strValue;
		HKEY hKEY;
		HKEY hKeyRoot = HKEY_CLASSES_ROOT;

		str = strRegistID.Mid(1, 20);
		strUser = CalSubKey(str);

		long ret = ::RegOpenKeyEx(hKeyRoot, strUser, 0, KEY_READ, &hKEY);
		if(ret == ERROR_SUCCESS)//如果注册
		{
			//读取注册项Value  
			LPBYTE getValue = new BYTE[80];//得到的键
			DWORD keyType = REG_SZ;//定义数据类型
			DWORD DataLen = 80;//定义数据长度
			long ret1=::RegQueryValueEx(hKEY,strUser,NULL,&keyType,getValue,&DataLen);
			if(ret1 == ERROR_SUCCESS)
			{
				strValue = getValue;
				
				///判断是否到期
				if(IfOverdue(strValue))
				{   
					return 0;
				}
				else
				{
					////到期 删除注册表项
					BOOL isdelete = RegDeleteKey(HKEY_CLASSES_ROOT, strUser);
					while(isdelete != ERROR_SUCCESS)
					{
						isdelete = RegDeleteKey(HKEY_CLASSES_ROOT, strUser);
					}
					return 1;
				}
			}
		}
	}

	return 2;
}

void DeleteRegedit()
{
	//打开文件读取产品唯一ID
	if(ReadRegFile())
	{
		CString str, strUser;
		HKEY hKEY;
		HKEY hKeyRoot = HKEY_CLASSES_ROOT;

		str = strRegistID.Mid(1, 20);
		strUser = CalSubKey(str);

		long ret = ::RegOpenKeyEx(hKeyRoot, strUser, 0, KEY_READ, &hKEY);
		if(ret == ERROR_SUCCESS)
		{
			LPBYTE getValue = new BYTE[80];//得到的键
			DWORD keyType = REG_SZ;//定义数据类型
			DWORD DataLen = 80;//定义数据长度
			long ret1=::RegQueryValueEx(hKEY,strUser,NULL,&keyType,getValue,&DataLen);
			if(ret1 == ERROR_SUCCESS)
			{
				BOOL isdelete = RegDeleteKey(HKEY_CLASSES_ROOT, strUser);;
				while(isdelete != ERROR_SUCCESS)
				{
					isdelete = RegDeleteKey(HKEY_CLASSES_ROOT, strUser);
				}
			}
		}
	}
}
