#include "stdafx.h"
#include "ChipsHandle.h"
#include "Functions.h"

extern int c[3];
extern int intCommonfoot;
extern int intSetway;
extern int intTestWay;
extern int intMixLight;
extern LightParam PolParam[3];
extern int selectchiptype;

extern int DeadLed;
bool MixLedLight[3] = {true, true, true};/////�ж����������� �������
extern int intMiddleWave1, intMiddleWave2;

void Handle2Pin1Chip()
{
	intMixLight = 0;
	if((0 == selectchiptype) || (10 == selectchiptype))
	{
		HandleZ21();
	}
}

void Handle2Pin2Chip()
{
	intMixLight = 0;
	if((1 == selectchiptype) || (11 == selectchiptype))
	{
		HandleZ22();
	}
}

void Handle3Pin2Chip()
{
	intMixLight = 0;
	if(2 == selectchiptype)   
	{
		HandleZ3200();
	}
	else if(3 == selectchiptype)  
	{
		HandleZ3201();
	}	
	else if(4 == selectchiptype)  
	{
		HandleZ3210();
	}
	else if(5 == selectchiptype)   
	{
		HandleZ3211();
	}	
}

void Handle4Pin2Chip()
{
	intMixLight = 0;
	HandleT42();
}

void Handle4Pin3Chip()
{
	switch(selectchiptype)
	{
	case 6:
		HandleZ4300();
		break;
	case 7:
		HandleZ4301();
		break;
	case 8:
		HandleZ4310();
		break;
	case 9:
		HandleZ4311();
		break;
	case 13:
		HandleT430A();
		break;
	case 14:
		HandleT430B();
		break;
	case 15:
		HandleT431A();
		break;
	case 16:
		HandleT431B();
		break;
	default:
		break;
	}	
}

void Handle6Pin3Chip()
{
	//T63
	HandleT63();
}

void testway(int chip)
{
	if(0 == intMixLight)
	{
		if(0 == intTestWay)
		{	
			test(chip);
		}
		else
		{
			KeepLight_test(chip);
		}
	}
	else
	{
		if(0 == intTestWay)
		{	
			MixLedLight[chip] = MixLight_test(chip);
		}
		else
		{
			MixKeepLight_test(chip);
		}
	}
}


/////////////����
bool ifDead = false;
void HandleZ21()
{
	if(c[0] != 0)
	{
		SetCommonfoot(0);
		SetChip(1);
		
		if(0 == DeadLed)
		{
			GetPOL(intSetway, 0);
		}
		else
		{
			if(0 == setway1(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay)) 
			{
				ifDead = true;
			}
		}
		
		if(!ifDead)
		{
			testway(0);
		}		
	}	
}

void HandleT21()
{
	HandleZ21();
}

////////////˫��
void HandleZ22()
{
	bool choose = true;

	SetCommonfoot(0);
	SetChip(1);
	setBering(true);
	choose = PWLPOL(0, intMiddleWave1);
	if(c[0] != 0)
	{
		setBering(choose);
		if(0 == intTestWay)
		{	
			test2(0);
		}
		else
		{
			KeepLight_test2(0);
		}
	}
	if(c[1] != 0)
	{
		setBering(!choose);
		if(0 == intTestWay)
		{	
			test2(1);
		}
		else
		{
			KeepLight_test2(1);
		}
	}
}

void HandleT22()
{
	HandleZ22();
}

void HandleZ3200()
{
	bool choose = true;

	SetCommonfoot(1);
	setBering(true);

	SetChip(1);
	choose = PWLPOL(0, intMiddleWave1);

	if(c[0] != 0)
	{
		if(choose)
		{
			SetChip(1);
		}
		else
		{
			SetChip(3);
		}

		testway(0);
	}
	if(c[1] != 0)
	{
		if(choose)
		{
			SetChip(3);
		}
		else
		{
			SetChip(1);
		}

		testway(1);
	}
}

void HandleZ3201()
{
	double value = 0;
	setBering(true);

	SetCommonfoot(0);
	SetChip(1);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);

	if((value > (PolParam[0].Current - 1)) && (value < (PolParam[0].Current + 1)))
	{
		SetCommonfoot(0);
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
	}
	else
	{
		SetCommonfoot(2);
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
	}
}

void HandleZ3210()
{
	bool choose = true;

	SetCommonfoot(1);
	setBering(false);

	SetChip(1);
	choose = PWLPOL(0, intMiddleWave1);

	if(c[0] != 0)
	{
		if(choose)
		{
			SetChip(1);
		}
		else
		{
			SetChip(3);
		}

		testway(0);
	}
	if(c[1] != 0)
	{
		if(choose)
		{
			SetChip(3);
		}
		else
		{
			SetChip(1);
		}

		testway(1);
	}
}

void HandleZ3211()
{
	double value = 0;
	setBering(false);

	SetCommonfoot(0);
	SetChip(1);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);

	if((value > (PolParam[0].Current - 1)) && (value < (PolParam[0].Current + 1)))
	{
		SetCommonfoot(0);
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
	}
	else
	{
		SetCommonfoot(3);
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
	}
}

void HandleT42()
{
	bool choose = true;
	SetCommonfoot(1);
	SetChip(3);
	setBering(true);
	choose = PWLPOL(0, intMiddleWave1);
	if(choose)
	{
		AfxMessageBox("true");
	}
	else
	{
		AfxMessageBox("false");
	}
	

	if(c[0] != 0)
	{
		if(choose)
		{
			SetCommonfoot(1);
			SetChip(3);
			setBering(true);
		}
		else
		{
			SetCommonfoot(2);
			SetChip(1);
			setBering(false);
		}
		
		testway(0);
	}
	if(c[1] != 0)
	{
		if(choose)
		{
			SetCommonfoot(2);
			SetChip(1);
			setBering(false);
			
		}
		else
		{
			SetCommonfoot(1);
			SetChip(3);
			setBering(true);
		}

		testway(1);
	}	
}

void HandleT42Same()
{
	SetCommonfoot(0);
	SetChip(1);
	GetPOL(intSetway, 0);
	
	if(getBering())
	{
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(3);
			testway(1);
		}	
	}
	else
	{
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}	
		
		if(c[1] != 0)
		{
			SetChip(1);
			testway(1);
		}	
	}
}

/////////////����
void testT43chips()
{
	if(c[0] != 0)
	{
		SetChip(1);
		testway(0);
	}
	if(c[1] != 0)
	{
		SetChip(2);
		testway(1);
	}
	if(c[2] != 0)
	{
		SetChip(3);
		testway(2);
	}
}

void HandleZ4300()
{
	//������ΪA�򹫹���ΪB  ����
	double value = 0;
	SetCommonfoot(1);
	SetChip(1);
	setBering(true);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		//������ΪA
		SetCommonfoot(1);
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(1);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(2);
			testway(2);
		}
	}
	else
	{
		//������ΪB
		SetCommonfoot(2);
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(3);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(2);
			testway(2);
		}
	}
	
	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleZ4301()
{
	//������ΪD��C
	double value = 0;
	SetCommonfoot(0);
	SetChip(1);
	setBering(true);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(0);
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(3);
			testway(2);
		}
	}
	else
	{
		SetCommonfoot(3);
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(1);
			testway(2);
		}
	}

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleZ4310()
{
	double value = 0;
	SetCommonfoot(1);
	SetChip(1);
	setBering(false);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(1);
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(1);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(2);
			testway(2);
		}
	}
	else
	{
		SetCommonfoot(2);
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(3);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(2);
			testway(2);
		}
	}

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleZ4311()
{
	double value = 0;
	SetCommonfoot(0);
	SetChip(1);
	setBering(false);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(0);
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(3);
			testway(2);
		}
	}
	else
	{
		SetCommonfoot(3);
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(1);
			testway(2);
		}
	}

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleT430A()
{
	//������ΪA��C  ����
	double value = 0;
	setBering(true);

	SetCommonfoot(1);
	SetChip(1);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(1);
	}
	else
	{
		SetCommonfoot(3);
	}

	testT43chips();

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleT430B()
{
	//������ΪB��D  ����
	double value = 0;
	SetCommonfoot(0);
	SetChip(1);
	setBering(true);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(0);	
	}
	else
	{
		SetCommonfoot(2);
	}

	testT43chips();

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleT431A()
{
	//������ΪA��C  ����
	double value = 0;
	SetCommonfoot(1);
	SetChip(1);
	setBering(false);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(1);	
	}
	else
	{
		SetCommonfoot(3);
	}

	testT43chips();

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleT431B()
{
	//������ΪB��D ����
	double value = 0;
	SetCommonfoot(0);
	SetChip(1);
	setBering(false);
	value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
	if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
	{
		SetCommonfoot(0);	
	}
	else
	{
		SetCommonfoot(2);
	}

	testT43chips();

	if(1 == intMixLight)
	{
		testgetSpectrum2(0);
	}
}

void HandleT63()
{
	//����
	SetCommonfoot(0);
	SetChip(1);
	GetPOL(intSetway, 0);

	if(getBering())
	{
		if(c[0] != 0)
		{
			SetChip(1);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(3);
			testway(2);
		}
	}
	else
	{
		if(c[0] != 0)
		{
			SetChip(3);
			testway(0);
		}
		if(c[1] != 0)
		{
			SetChip(2);
			testway(1);
		}
		if(c[2] != 0)
		{
			SetChip(1);
			testway(2);
		}
	}

	if((1 == intMixLight) && MixLedLight[0] && MixLedLight[1] && MixLedLight[2])
	{
		testgetSpectrum2(0);
	}
}


void OpenLightSet(int type, int chip)
{
	double value = 0;
	bool choose = true;

	switch(type)
	{
	case 0:  //˫�ŵ���
		SetCommonfoot(0);
		SetChip(1);
		GetPOL(intSetway, 0);
		break;
	case 1:  //˫��˫��
		SetCommonfoot(0);
		SetChip(1);
		choose = PWLPOL(0, intMiddleWave1);
		if(0 == chip)
		{
			setBering(choose);
		}
		else if(1 == chip)
		{
			setBering(!choose);
		}
		break;
	case 2: //����˫�����������������м�
		SetCommonfoot(1);
		setBering(true);

		SetChip(1);
		choose = PWLPOL(0, intMiddleWave1);

		if(0 == chip)
		{
			if(choose)
			{
				SetChip(1);
			}
			else
			{
				SetChip(3);
			}
		}
		else if(1 == chip)
		{
			if(choose)
			{
				SetChip(3);
			}
			else
			{
				SetChip(1);
			}
		}
		break;
	case 3:		//����˫�����������������Ա�
		setBering(true);	
		SetCommonfoot(0);
		SetChip(1);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		
		if((value > (PolParam[0].Current - 1)) && (value < (PolParam[0].Current + 1)))
		{
			SetCommonfoot(0);
			if(0 == chip)
			{
				SetChip(1);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
		}
		else
		{
			SetCommonfoot(2);
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
		}
		break;
	case 4://����˫�����������������м�
		SetCommonfoot(1);
		setBering(false);

		SetChip(1);
		choose = PWLPOL(0, intMiddleWave1);

		if(0 == chip)
		{
			if(choose)
			{
				SetChip(1);
			}
			else
			{
				SetChip(3);
			}
		}
		else if(1 == chip)
		{
			if(choose)
			{
				SetChip(3);
			}
			else
			{
				SetChip(1);
			}
		}
		break;
	case 5://����˫�����������������Ա�
		setBering(false);
		SetCommonfoot(0);
		SetChip(1);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		
		if((value > (PolParam[0].Current - 1)) && (value < (PolParam[0].Current + 1)))
		{
			SetCommonfoot(0);
			if(0 == chip)
			{
				SetChip(1);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
		}
		else
		{
			SetCommonfoot(2);
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
		}
		break;
	case 6: //�Ľ����������������ſ��м�
		SetCommonfoot(1);
		SetChip(1);
		setBering(true);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			//������ΪA
			SetCommonfoot(1);
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(1);
			}
			else if(2 == chip)
			{
				SetChip(2);
			}
		}
		else
		{
			//������ΪB
			SetCommonfoot(2);
			if(0 == chip)
			{
				SetChip(1);
			}
			else if(1 == chip)
			{
				SetChip(3);
			}
			else if(2 == chip)
			{
				SetChip(2);
			}
		}
		break;
	case 7: ////�Ľ����������������ſ���
		SetCommonfoot(0);
		SetChip(1);
		setBering(true);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(0);
			if(0 == chip)
			{
				SetChip(1);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
			else if(2 == chip)
			{
				SetChip(3);
			}
		}
		else
		{
			SetCommonfoot(3);
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
			else if(2 == chip)
			{
				SetChip(1);
			}
		}
		break;
	case 8://�Ľ����������������ſ��м�
		SetCommonfoot(1);
		SetChip(1);
		setBering(false);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(1);	
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(1);
			}
			else if(2 == chip)
			{
				SetChip(2);
			}
		}
		else
		{
			SetCommonfoot(2);
			if(0 == chip)
			{
				SetChip(1);
			}
			else if(1 == chip)
			{
				SetChip(3);
			}
			else if(2 == chip)
			{
				SetChip(2);
			}
		}
		break;
	case 9://�Ľ����������������ſ���
		SetCommonfoot(0);
		SetChip(1);
		setBering(false);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(0);
			if(0 == chip)
			{
				SetChip(1);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
			else if(2 == chip)
			{
				SetChip(3);
			}
		}
		else
		{
			SetCommonfoot(3);
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
			else if(2 == chip)
			{
				SetChip(1);
			}
		}
		break;
	case 10:  ///˫�ŵ���
		SetCommonfoot(0);
		SetChip(1);
		GetPOL(intSetway, 0);
		break;
	case 11:  ///˫��˫��
		SetCommonfoot(0);
		SetChip(1);
		choose = PWLPOL(0, intMiddleWave1);
		if(0 == chip)
		{
			setBering(choose);
		}
		else if(1 == chip)
		{
			setBering(!choose);
		}
		break;
	case 12:///�Ľ�˫��
		if(false)
		{
			SetCommonfoot(0);
			SetChip(1);
			GetPOL(intSetway, 0);

			if(getBering())
			{
				if(0 == chip)
				{
					SetChip(1);
				}
				else if(1 == chip)
				{
					SetChip(3);
				}	
			}
			else
			{
				if(0 == chip)
				{
					SetChip(3);
				}
				else if(1 == chip)
				{
					SetChip(1);
				}	
			}
		}
		else
		{
			SetCommonfoot(1);
			SetChip(3);
			setBering(true);
			choose = PWLPOL(0, intMiddleWave1);
			
			if(0 == chip)
			{
				if(choose)
				{
					SetCommonfoot(1);
					SetChip(3);
				}
				else
				{
					SetCommonfoot(2);
					SetChip(1);
					
				}
				setBering(choose);
			}
			if(1 == chip)
			{
				if(choose)
				{
					SetCommonfoot(2);
					SetChip(1);
				}
				else
				{
					SetCommonfoot(1);
					SetChip(3);
					
				}
				setBering(!choose);
			}
		}
		break;
	case 13: ////�Ľ���������, A/CΪ������
		setBering(true);
		SetCommonfoot(1);
		SetChip(1);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(1);	
		}
		else
		{
			SetCommonfoot(3);
		}
		SetChip(chip+1);
		break;
	case 14: ////�Ľ�����������B/DΪ������
		SetCommonfoot(0);
		SetChip(1);
		setBering(true);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(0);	
		}
		else
		{
			SetCommonfoot(2);
		}
		SetChip(chip+1);
		break;
	case 15:////�Ľ���������, A/CΪ������
		SetCommonfoot(1);
		SetChip(1);
		setBering(false);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(1);	
		}
		else
		{
			SetCommonfoot(3);
		}
		SetChip(chip+1);
		break;
	case 16:////�Ľ���������, B/DΪ������
		SetCommonfoot(0);
		SetChip(1);
		setBering(false);
		value = getIF(PolParam[0].Voltage, PolParam[0].Current, PolParam[0].Delay);
		if((value > PolParam[0].Current - 1) && (value < PolParam[0].Current + 1))
		{
			SetCommonfoot(0);	
		}
		else
		{
			SetCommonfoot(2);
		}
		SetChip(chip+1);
		break;
	case 17: ///��������
		SetCommonfoot(0);
		SetChip(1);
		GetPOL(intSetway, 0);

		if(getBering())
		{
			SetChip(chip+1);
		}
		else
		{
			if(0 == chip)
			{
				SetChip(3);
			}
			else if(1 == chip)
			{
				SetChip(2);
			}
			else if(2 == chip)
			{
				SetChip(1);
			}
		}
		
		break;
	default:
		break;
	}
}


int OnFigureZ32style(double voltage, double current, long delay)
{
	CString str;
	double value = 0;

	SetCommonfoot(1);
	SetChip(3);
	setBering(true);
	value = getIF(voltage, current, delay);
	if((value > (current - 1)) && (value < (current + 1)))
	{
		SetChip(1);
		value = getIF(voltage, current, delay);
		if((value > (current - 1)) && (value < (current + 1)))
		{
			return 2;
		}
		else
		{
			return 5;
		}
	}
	else
	{
		setBering(false);
		value = getIF(voltage, current, delay);
		if((value > (current - 1)) && (value < (current + 1)))
		{
			SetChip(1);
			value = getIF(voltage, current, delay);
			if((value > (current - 1)) && (value < (current + 1)))
			{
				return 4;
			}
			else
			{
				return 3;
			}
		}
		else
		{
			SetCommonfoot(2);
			SetChip(3);
			setBering(true);
			value = getIF(voltage, current, delay);
			if((value > (current - 1)) && (value < (current + 1)))
			{
				return 3;
			}
			else
			{
				return 5;
			}
		}
	}

	return 0;
}

int OnFigureZ43style(double voltage, double current, long delay)
{
	CString str;
	double value = 0;

	SetCommonfoot(1);
	SetChip(3);
	setBering(true);
	value = getIF(voltage, current, delay);
	if((value > (current - 1)) && (value < (current + 1)))
	{
		SetChip(2);
		value = getIF(voltage, current, delay);
		if((value > (current - 1)) && (value < (current + 1)))
		{
			return 6;
		}
		else
		{
			return 9;
		}
	}
	else
	{
		setBering(false);
		value = getIF(voltage, current, delay);
		if((value > (current - 1)) && (value < (current + 1)))
		{
			SetChip(2);
			value = getIF(voltage, current, delay);
			if((value > (current - 1)) && (value < (current + 1)))
			{
				return 8;
			}
			else
			{
				return 7;
			}
		}
		else
		{
			SetChip(2);
			value = getIF(voltage, current, delay);
			if((value > (current - 1)) && (value < (current + 1)))
			{
				return 7;
			}
			else
			{
				setBering(true);
				value = getIF(voltage, current, delay);
				if((value > (current - 1)) && (value < (current + 1)))
				{
					return 9;
				}
				else
				{
					SetChip(1);
					value = getIF(voltage, current, delay);
					if((value > (current - 1)) && (value < (current + 1)))
					{
						return 8;
					}
					else
					{
						return 6;
					}
				}
			}
		}
	}
	return 0;
}

int OnFigureT43style(double voltage, double current, long delay)
{
	CString str;
	double value = 0;

	SetCommonfoot(1);
	SetChip(3);
	setBering(true);
	value = getIF(voltage, current, delay);
	if((value > (current - 1)) && (value < (current + 1)))
	{
		SetChip(2);
		value = getIF(voltage, current, delay);
		if((value > (current - 1)) && (value < (current + 1)))
		{
			/////A����
			return 13;
		}
		else
		{
			/////D����
			return 16;
		}
	}
	else
	{
		setBering(false);
		value = getIF(voltage, current, delay);
		if((value > (current - 1)) && (value < (current + 1)))
		{
			SetChip(2);
			value = getIF(voltage, current, delay);
			if((value > (current - 1)) && (value < (current + 1)))
			{
				/////A����
				return 15;
			}
			else
			{
				/////D����
				return 14;
			}
		}
		else
		{
			SetChip(2);
			value = getIF(voltage, current, delay);
			if((value > (current - 1)) && (value < (current + 1)))
			{
				/////C����
				return 13;
			}
			else
			{
				setBering(true);
				value = getIF(voltage, current, delay);
				if((value > (current - 1)) && (value < (current + 1)))
				{
					/////C����
					return 15;
				}
				else
				{
					SetChip(1);
					value = getIF(voltage, current, delay);
					if((value > (current - 1)) && (value < (current + 1)))
					{
						/////B����
						return 16;
					}
					else
					{
						/////B����
						return 14;
					}
				}
			}
		}
	}
	return 0;
}