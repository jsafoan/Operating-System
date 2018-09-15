
#define ASM 1

#include "interrupts_asm.h"

.text

.globl   isr_wrapper_rtc
.globl   isr_wrapper_keyboard
.align   4


# void isr_wrapper_keyboard(void);
#
# Interface: push all the registers into the stack and pop them after
#            call the keyboard_handler function
#    Inputs: None
#
#   Outputs: None
# Registers: NONE
isr_wrapper_keyboard:
    pushal
    cld # Clears the DF flag in the EFLAGS register. When the DF flag is set to 0, string operations increment the index registers (ESI and/or EDI).
    call keyboard_handler
    popal
    iret # Returns program control from an exception or interrupt handler to a program
         # or procedure that was interrupted by an exception, an external interrupt, or a software-generated interrupt.

# void isr_wrapper_rtc(void);
#
# Interface: push all the registers into the stack and pop them after
#            call the rtc_handler function
#    Inputs: None
#
#   Outputs: None
# Registers: NONE
isr_wrapper_rtc:
    pushal
    cld # Clears the DF flag in the EFLAGS register. When the DF flag is set to 0, string operations increment the index registers (ESI and/or EDI).
    call rtc_handler
    popal
    iret # Returns program control from an exception or interrupt handler to a program
         # or procedure that was interrupted by an exception, an external interrupt, or a software-generated interrupt.
