#include "keyboard.h"

//This is the first draft of our map that can get the characters or numbers by input the
//Ascii code into the array index
//CURRENTLY WE HAVE 16*4 CHARACTERS
char scancode[16*4] = {'T','T','1','2','3','4','5','6','7','8','9','0','-','=','T','T',
				'q','w','e','r','t','y','u','i','o','p','[',']','T','T','a','s',
				'd','f','g','h','j','k','l',';','T','T','T','T','z','x','c','v',
				'b','n','m',',','.','/','T','*','T',' ','T','T','T','T','T','T'};

//This buffer sets the character length of each row on the screen
static char char_buffer[NUM_OF_CHAR_ON_SCREEN];

//the variable that loops the char_buffer
int index = 0;
/*
 * getScancode
 *   DESCRIPTION: return the ascii code we get from inb
 *
 *   INPUTS: none
 *   OUTPUTS: return the ascii code we get from inb
 *   RETURN VALUE: the ascii code we get from inb
 *   SIDE EFFECTS: none
 *
 */
char getScancode() {
    unsigned char c=0; // initializes the char
    do {
        if(inb(INPUT_PORT)!=c) { // if there is some thing new comes
            c=inb(INPUT_PORT);		//get the char
			printf("\n%c\n",c);	
            if(c>0)					//if char is not null, return it
                return c;
        }
    } while(1);
}

/*
 * keyboard_init
 *   DESCRIPTION: enable the irq num = 1
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 *
 */
void keyboard_init() {
	enable_irq(1);			//send enable irq signal to i8259
	return;
}

/*
 * keyboard_handler
 *   DESCRIPTION: Called everytime when the interrupt occurs
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints characters on to the screen
 *
 */
void keyboard_handler()
{
	//printf("KEYBOARD HANDLER");
	cli();

	int j = 0;//initialization
	int i = 0;//initialization

  do {
      if((j=inb(INPUT_PORT))!=0) { //get the first unused value
          i=inb(INPUT_PORT);			//get next value which is the key for scancode
					
					if (i < INPUT_PORT) {
						if (scancode[i] == 'T') {
								rtc_init();
						}
						
						
						printf("%c",scancode[i]);//prints to the lower section of the screen
						char_buffer[index%CHAR_MAX] = scancode[i]; //put the char which needs to be print on the screen
						index++;																		// get the next char and prevent the previous char from overwritten
						//printf("%s", char_buffer);									//print it to the screen
					}
          if(i>0)								//
              break;
      }
  } while(1);

	send_eoi(1);
	sti();//STI sets the interrupt flag (IF) in the EFLAGS register.
	//return;
	//asm volatile ("iret");
}
