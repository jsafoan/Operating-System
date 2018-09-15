#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "lib.h"
#include "i8259.h"
#include "rtc.h"

#define NUM_OF_CHAR_ON_SCREEN 50
#define CHAR_MAX              49 // predefined number for mod
#define INPUT_PORT            0x60

/* return the ascii code we get from inb */
char getScancode();
/* enable the irq num = 1 */
void keyboard_init();
/* Called everytime when the interrupt occurs */
void keyboard_handler();

#endif
