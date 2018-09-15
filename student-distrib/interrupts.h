#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "lib.h"
#include "interrupts_asm.h"

#define sys_call 0x80
#define keybrd 0x21
#define rtc 0x28


/* Sets runtime-settable parameters in the GDT entry for the LDT */
/*
 * set_exc
 *   DESCRIPTION: This is a macro we defined to hole the name of the exception and
 *          the message it should be printed out. THe macro must write in one line
 *   INPUTS: exception -- the function name that can prints out a specific input print_out
 *            print_out -- the string that holds the message you want to print out
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 *
 */
#define set_exc(exception,print_out)\
void exception(){\
cli();\
clear(); \
printf("\n%s\n",print_out);\
while(1);\
}
/* function to initialize the Keyboard */
void keyboard_init();
/* function to initialize the idt */
void initialize_idt();
/* function of the keyboard handler that handles the inputs */
void keyboard_handler();
//void rtc_handler();
//void rtc_init();

#endif
