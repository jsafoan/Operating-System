#include "rtc.h"

/*
 * rtc_init
 *   DESCRIPTION:Enable the RTC on PIC and initialize RTC with desired frequency(2Hz)
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Enables the RTC interrupt line on the PIC
 *
 */

void rtc_init()
{
	outb(REG_A,RTC_REG);		// write to Status Register A for setting the frequency
	outb(TWO_HZ,RTC_REG_1);		// Frequency is 2Hz.
	outb(REG_B, RTC_REG);		// select register B, and disable NMI
	char prev=inb(RTC_REG_1);	// read the current value of register B
	outb(REG_B, RTC_REG);		// set the index again (a read will reset the index to register D)
	outb(prev | BIT_SIX,RTC_REG_1);	// write the previous value ORed with 0x40. This turns on bit 6 of register B
	enable_irq(RTC_LINE);				//enable the RTC on the PIC
}

/*
 * rtc_handler
 *   DESCRIPTION:Calls the test interrupt and sends end of interrupt
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: calls send_eoi to receive subsequent interrupts
 *
 */

void rtc_handler()
{
	test_interrupts();		// call the test from lib.c
	outb(0x0C,RTC_REG);		// select register C
	inb(RTC_REG_1);				// just throw away contents
	send_eoi(8);			//send eoi for subsequent interrupts
}
