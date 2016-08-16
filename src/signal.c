#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define STARTLEVEL 5
#define CELLDELAY 7
#define CELLLEVEL 8
#define ZERODELAY 11
#define ZEROTEST 12
#define PURGE 13
#define TOTALMERCURYDELAY 21
#define TOTALMERCURY 22
#define ELEMENTALMERCURYDELAY 26
#define ELEMENTALMERCURY 27
#define PRECALIBRATIONDELAY 31
#define CALIBRATION 32
#define POSTCALIBRATIONDELAY 33

#define STARTLEVELSECONDS 8
#define CELLDELAYSECONDS 12
#define CELLLEVELSECONDS 30
#define ZERODELAYSECONDS 12
#define ZEROTESTSECONDS 30
#define PURGESECONDS 32768
#define TOTALMERCURYDELAYSECONDS 15
#define TOTALMERCURYSECONDS 720
#define ELEMENTALMERCURYDELAYSECONDS 5
#define ELEMENTALMERCURYSECONDS 100
#define PRECALIBRATIONDELAYSECONDS 5
#define CALIBRATIONSECONDS 64
#define POSTCALIBRATIONDELAYSECONDS 10

int modenumber = 0;

int modeseconds(int modeneed)
{
 switch (modeneed)
 {
	 case STARTLEVEL: return STARTLEVELSECONDS;
	 case CELLDELAY: return CELLDELAYSECONDS;
	 case CELLLEVEL:	return CELLLEVELSECONDS;
	 case ZERODELAY: return ZERODELAYSECONDS;
	 case ZEROTEST: return ZEROTESTSECONDS;
	 case PURGE: return PURGESECONDS;
	 case TOTALMERCURYDELAY: return TOTALMERCURYDELAYSECONDS;
	 case TOTALMERCURY: return TOTALMERCURYSECONDS;
	 case ELEMENTALMERCURYDELAY: return ELEMENTALMERCURYDELAYSECONDS;
	 case ELEMENTALMERCURY: return ELEMENTALMERCURYSECONDS;
	 case PRECALIBRATIONDELAY: return PRECALIBRATIONDELAYSECONDS;
	 case CALIBRATION: return CALIBRATIONSECONDS;
	 case POSTCALIBRATIONDELAY: return POSTCALIBRATIONDELAYSECONDS;
 }
 return 0;
}

int sequence(int modetosequence)
{
	switch(modetosequence)
	{
		case STARTLEVEL:
			return CELLDELAY;
		break;
		case CELLDELAY:
			return CELLLEVEL;
		break;
		case CELLLEVEL:
			return TOTALMERCURYDELAY;
		break;
		case ZERODELAY:
			return ZEROTEST;
		break;
		case ZEROTEST:
			return TOTALMERCURYDELAY;
		break;
		case PURGE:
			return TOTALMERCURYDELAY;
		break;
		case TOTALMERCURYDELAY:
			return TOTALMERCURY;
		break;
		case TOTALMERCURY:
			return TOTALMERCURY;
		break;
		case ELEMENTALMERCURYDELAY:
			return ELEMENTALMERCURY;
		break;
		case ELEMENTALMERCURY:
			return TOTALMERCURY;
		break;
		case PRECALIBRATIONDELAY:
			return CALIBRATION;
		break;
		case CALIBRATION:
			return POSTCALIBRATIONDELAY;
		break;
		case POSTCALIBRATIONDELAY:
			return TOTALMERCURYDELAY;
		break;
		default:
			return TOTALMERCURY;
		break;
	}
	return TOTALMERCURY;
}

void entermode(int modetoenter)
{
	modenumber = modetoenter;
	printf("enter mode %d\n", modetoenter);
	alarm(modeseconds(modetoenter));
	printf("waiting %d seconds\n",modeseconds(modenumber));
	printf("next mode duration %d seconds\n",modeseconds(sequence(modenumber)));
}

void exitmode(int modetoexit)
{
	printf("exit mode %d\n",modetoexit);
	entermode(sequence(modetoexit));
}

void alarm_handler(int signal)
{
	printf("alarm\n");
	exitmode(modenumber);
}

int main(void)
{
	signal(SIGALRM, alarm_handler);
	entermode(STARTLEVEL);
	alarm(10);
	while (1)
		sleep(1);
	return 0;
}
