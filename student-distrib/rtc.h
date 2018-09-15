#ifndef RTC_H
#define RTC_H

#include "lib.h"
#include "i8259.h"

//Calls the test interrupt and sends end of interrupt
void rtc_handler();
//Enable the RTC on PIC and initialize RTC with desired frequency(2Hz)
void rtc_init();

#define RTC_REG     0x70
#define RTC_REG_1   0x71
#define REG_A		0x8A
#define TWO_HZ      0x0F
#define REG_B		0x8B
#define RTC_LINE     8
#define BIT_SIX     0x40

#endif
