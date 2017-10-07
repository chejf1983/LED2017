#include <windows.h>

#ifdef _cplusplus
#define exports extern "C" _declspec(dllexport)
#else
#define exports _declspec(dllexport)
#endif

exports bool setpixel(int x);
exports bool setsngWavelength(double *wavelength);
exports bool calsngWavelength();
exports bool setWaveParameter(double intercept, double first, double second, double third);
exports bool setsngCounts(double *counts, double *darkcounts);
exports bool setstandardpower(double *std);
exports bool setuJoulesCount(double *count);
exports bool setpowerper();
exports bool setFiberArea(double hArea);

exports bool CalPixTris();
exports bool IniPhotometer();
exports bool InitS0_S1_S2();
exports bool InitCIETestColorSample();

exports bool IFSaturated();
exports double WINAPI getWavelength(int pixel);
exports bool WINAPI getXY();
exports double WINAPI getX();
exports double WINAPI getY();
exports double WINAPI getOptics_IV(int intIVUnit, double int_Global_IntegrationTime);
exports double WINAPI getMaxPower(bool handle);
exports double WINAPI getPeakWL(int way, bool handle);
exports double WINAPI getDeltaWL();
exports double WINAPI getWL(double x, double y);
exports double WINAPI getWL_5nm(double x, double y);
exports double WINAPI getPUR(double x, double y);
exports double WINAPI getCCT(double x, double y);
exports double WINAPI getCRI(double x, double y);

exports double WINAPI getWL_New(double x, double y);
exports double WINAPI getWL_5nm_New(double x, double y);
