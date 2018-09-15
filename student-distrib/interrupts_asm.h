#ifndef _INTERRUPTS_ASM_H
#define _INTERRUPTS_ASM_H

#ifndef ASM
/*
 * the function that wraps the keyboard_handler function
 * in order not to mess up the registers after return
 */
void isr_wrapper_keyboard();

/*
 * the function that wraps the rtc_handler function
 * in order not to mess up the registers after return
 */
void isr_wrapper_rtc();

#endif

#endif
