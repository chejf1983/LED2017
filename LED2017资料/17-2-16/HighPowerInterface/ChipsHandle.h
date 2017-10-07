#include "highpower.h"

void Handle2Pin1Chip();
void Handle2Pin2Chip();
void Handle3Pin2Chip();
void Handle4Pin2Chip();
void Handle4Pin3Chip();
void Handle6Pin3Chip();

void testway(int chip);

void HandleZ21();
void HandleT21();
void HandleZ22();
void HandleT22();
void HandleZ3200();
void HandleZ3201();
void HandleZ3210();
void HandleZ3211();
void HandleT42();
void HandleT42Same();

void testT43chips();

void HandleZ4300();
void HandleZ4301();
void HandleZ4310();
void HandleZ4311();
void HandleT430A();
void HandleT430B();
void HandleT431A();
void HandleT431B();
void HandleT63();

void OpenLightSet(int type, int chip);

int OnFigureZ32style(double voltage, double current, long delay);
int OnFigureZ43style(double voltage, double current, long delay);
int OnFigureT43style(double voltage, double current, long delay);