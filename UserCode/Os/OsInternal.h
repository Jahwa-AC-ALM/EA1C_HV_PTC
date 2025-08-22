#ifndef __OS_INTERNAL_H__
#define __OS_INTERNAL_H__

#include"types.h"

extern void OsGetCurrentSP(volatile unsigned int* CurrentSpPtr);
extern void OsGetPSR(volatile unsigned int* CurrentPsr);

boolean OsIsInterruptContext(void);
boolean OsIsCat2IntContext(void);

#endif