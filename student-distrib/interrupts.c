
#include "interrupts.h"
#include "x86_desc.h"
#include "i8259.h"
#include "lib.h"
//#include "interrupts.S"

/*
 * here is the definition of each of the exceptions defined in the
 * IA-32 Intel® Architecture Software Developer’s Manual with their names that will be printed out
 * if any of the exception is called.
 * The Macro for defining these structures is located in the h file
 */
set_exc(exc_div_0,"FAULT: Divide Error Exception (#DE)");
set_exc(exc_debug,"FAULT: Debug Exception (#DB)");
set_exc(exc_nmi,"The Nonmaskable Interrupt Interrupt");
set_exc(exc_breakpoint,"TRAP: Breakpoint Exception (#BP)");

set_exc(exc_overflow,"TRAP: Overflow Exception (#OF)");
set_exc(exc_bound_RE,"FAULT: BOUND Range Exceeded Exception (#BR)");
set_exc(exc_inv_opc,"FAULT: Invalid Opcode Exception (#UD)");
set_exc(exc_DNI,"FAULT: Device Not Available Exception (#NM)");

set_exc(exc_dbl_flt,"ABORT: Double Fault Exception (#DF)");
set_exc(exc_cp_s_or,"ABORT: Coprocessor Segment Overrun");
set_exc(exc_invalid_tss,"FAULT: Invalid TSS Exception (#TS)");
set_exc(exc_snp,"FAULT: Segment Not Present (#NP)");

set_exc(exc_ssf,"FAULT: Stack Fault Exception (#SS)");
set_exc(exc_gen_proct,"FAULT: General Protection Exception (#GP)");
set_exc(exc_page_fault,"FAULT: Page-Fault Exception (#PF)");
set_exc(exc_int_reserved,"INT RESERVE 1");

set_exc(exc_fpu_flt_pt_err,"FAULT: x87 FPU Floating-Point Error (#MF)");
set_exc(exc_align_check,"FAULT: Alignment Check Exception (#AC)");
set_exc(exc_machine_chk,"ABORT: Machine-Check Exception (#MC)");
set_exc(exc_simd_flt_pt,"FAULT: SIMD Floating-Point Exception (#XF)");

set_exc(ecx_virtualization,"FAULT: Divide Error Exception (#DE)");
set_exc(ecx_int_resv_2,"INT RESERVE 2");
set_exc(ecx_int_resv_3,"INT RESERVE 3");
set_exc(ecx_int_resv_4,"INT RESERVE 4");

set_exc(ecx_int_resv_5,"INT RESERVE 5");
set_exc(ecx_int_resv_6,"INT RESERVE 6");
set_exc(ecx_int_resv_7,"INT RESERVE 7");
set_exc(ecx_int_resv_8,"INT RESERVE 8");

set_exc(ecx_int_resv_9,"INT RESERVE 9");
set_exc(ecx_int_resv_10,"INT RESERVE 10");
set_exc(ecx_security,"SECURITY RESEVED");
set_exc(ecx_int_resv_12,"INT RESERVE 12");

//static int count;
/*
 * system_call
 *   DESCRIPTION: 
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 *
 */
void system_call()
{
	//while(1) or z
	return;
}

/*
//		RTC INTERRUPTS
//
//
void rtc_init()
{
	//while(1) or iret
	printf("RTC HANDLER");
	//asm volatile ("iret");

	outb(0x8A,0x70);	// write to Status Register A for setting the frequency
	outb(0x0F,0x71);	// Frequency is 2Hz.
	//cli();				// disable interrupts
	outb(0x8B, 0x70);		// select register B, and disable NMI
	char prev=inb(0x71);	// read the current value of register B
	outb(0x8B, 0x70);		// set the index again (a read will reset the index to register D)
	outb(prev | 0x40,0x71);	// write the previous value ORed with 0x40. This turns on bit 6 of register B
	enable_irq(8);
	printf("RTC_INIT\n");
	//sti();				//Enable interrupts

}

void rtc_handler()
{
	test_interrupts();
	printf("RTC_HANDLER\n");
	printf("RTC_HANDLER\n");
	outb(0x0C,0x70);		// select register C
	inb(0x71);				// just throw away contents

	send_eoi(8);

}
*/

/*char scancode[16*4] = {'T','T','1','2','3','4','5','6','7','8','9','0','-','=','T','T',
				'q','w','e','r','t','y','u','i','o','p','[',']','T','T','a','s',
				'd','f','g','h','j','k','l',';','T','T','T','T','z','x','c','v',
				'b','n','m',',','.','/','T','*','T',' ','T','T','T','T','T','T'};


char getScancode() {
    unsigned char c=0;
    do {
        if(inb(0x60)!=c) {
            c=inb(0x60);
			printf("\n%c\n",c);
            if(c>0)
                return c;
        }
    } while(1);
}


void keyboard_init() {
	enable_irq(1);
	return;
}

static char char_buffer[50];
int index = 0;
int char_max = 49;

void keyboard_handler()
{
	//printf("KEYBOARD HANDLER");
	cli();

	int j = 0;

	//int c=0;
	int i = 0;
	//int b = 0;
    do {
        if((j=inb(0x60))!=0) {
            i=inb(0x60);

			if (i < 0x60) {
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ");

				char_buffer[index%char_max] = scancode[i];
				index++;

				printf("%s", char_buffer);
				//printf("%c", scancode[i]);
			}
            if(i>0)
                break;
        }
    } while(1);

	send_eoi(1);
	sti();
	//return;
	//asm volatile ("iret");
}*/

void timer_chip() {
	//asm volatile ("iret");
}

/*
 * initialize_idt
 *   DESCRIPTION: Initialize the idt table
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 *
 */
void initialize_idt() {

	    lidt(idt_desc_ptr);
	//set up everything except offset for 32 exceptions
	int i;
	for (i = 0; i <= 0x1F; i++) { // initializes the first 32 idt entries
		//all 0 for any idt entry,  bit[32:39]
		idt[i].reserved4 = 0x0;

		//trap gate = 0b1111,  bit[40:43]
		idt[i].reserved3 = 1;// type and attributes
		idt[i].reserved2 = 1;
		idt[i].reserved1 = 1;
		idt[i].size      = 1;

		//always 0 bit[44]
		idt[i].reserved0 = 0;

		//should be 0 for exceptions,  bit[45:46]
		idt[i].dpl = 0;

		//set 1 for working interrupts,  bit[47]
		idt[i].present = 1;

		//segment selector   1 1 000,  bit[16:31]
		idt[i].seg_selector = KERNEL_CS;
	}


	//32 exceptions each with its name and predefined location in idt table
	SET_IDT_ENTRY(idt[0], &exc_div_0);
	SET_IDT_ENTRY(idt[1], &exc_debug);
	SET_IDT_ENTRY(idt[2], &exc_nmi);
	SET_IDT_ENTRY(idt[3], &exc_breakpoint);

	SET_IDT_ENTRY(idt[4], &exc_overflow);
	SET_IDT_ENTRY(idt[5], &exc_bound_RE);
	SET_IDT_ENTRY(idt[6], &exc_inv_opc);
	SET_IDT_ENTRY(idt[7], &exc_DNI);

	SET_IDT_ENTRY(idt[8], &exc_dbl_flt);
	SET_IDT_ENTRY(idt[9], &exc_cp_s_or);
	SET_IDT_ENTRY(idt[10], &exc_invalid_tss);
	SET_IDT_ENTRY(idt[11], &exc_snp);

	SET_IDT_ENTRY(idt[12], &exc_ssf);
	SET_IDT_ENTRY(idt[13], &exc_gen_proct);
	SET_IDT_ENTRY(idt[14], &exc_page_fault);
	SET_IDT_ENTRY(idt[15], &exc_int_reserved);

	SET_IDT_ENTRY(idt[16], &exc_fpu_flt_pt_err);
	SET_IDT_ENTRY(idt[17], &exc_align_check);
	SET_IDT_ENTRY(idt[18], &exc_machine_chk);
	SET_IDT_ENTRY(idt[19], &exc_simd_flt_pt);

	SET_IDT_ENTRY(idt[20], &ecx_virtualization);
	SET_IDT_ENTRY(idt[21], &ecx_int_resv_2);
	SET_IDT_ENTRY(idt[22], &ecx_int_resv_3);
	SET_IDT_ENTRY(idt[23], &ecx_int_resv_4);

	SET_IDT_ENTRY(idt[24], &ecx_int_resv_5);
	SET_IDT_ENTRY(idt[25], &ecx_int_resv_6);
	SET_IDT_ENTRY(idt[26], &ecx_int_resv_7);
	SET_IDT_ENTRY(idt[27], &ecx_int_resv_8);

	SET_IDT_ENTRY(idt[28], &ecx_int_resv_9);
	SET_IDT_ENTRY(idt[29], &ecx_int_resv_10);
	SET_IDT_ENTRY(idt[30], &ecx_security);
	SET_IDT_ENTRY(idt[31], &ecx_int_resv_12);





	//initalize system call
	//all 0 for any idt entry,  bit[32:39]
	idt[sys_call].reserved4 = 0x00;

	//system call use trap gate = 0b1111,  bit[40:43]
	idt[sys_call].reserved3 = 1;
	idt[sys_call].reserved2 = 1;
	idt[sys_call].reserved1 = 1;
	idt[sys_call].size      = 1;

	//always 0 bit[44]
	idt[sys_call].reserved0 = 0;

	//most likely 0,  bit[45:46]
	idt[sys_call].dpl = 0x3;

	//set 1 for working interrupts,  bit[47]
	idt[sys_call].present = 1;

	//segment selector   1 1 000,  bit[16:31]
	idt[sys_call].seg_selector = KERNEL_CS;

	SET_IDT_ENTRY(idt[sys_call], &system_call);


	//initalize interrupt keyboard
	//all 0 for any idt entry,  bit[32:39]
	idt[keybrd].reserved4 = 0x00;

	//system call use interrupt gate = 0b1110,  bit[40:43]    0 before
	idt[keybrd].reserved3 = 0;            //bit[40]
	idt[keybrd].reserved2 = 1;			//bit[41]
	idt[keybrd].reserved1 = 1;			//bit[42]
	idt[keybrd].size      = 1;			//bit[43]

	//always 0 bit[44]
	idt[keybrd].reserved0 = 0;

	//0 for interrupts,  bit[45:46]
	idt[keybrd].dpl = 0;

	//set 1 for working interrupts,  bit[47]
	idt[keybrd].present = 1;

	//segment selector   1 1 000,  bit[16:31]
	idt[keybrd].seg_selector = KERNEL_CS;

	SET_IDT_ENTRY(idt[keybrd], isr_wrapper_keyboard);



	//initalize interrupt rtc
	//all 0 for any idt entry,  bit[32:39]
	idt[rtc].reserved4 = 0x00;

	//system call use interrupt gate = 0b1110,  bit[40:43]
	idt[rtc].reserved3 = 0;            //bit[40]
	idt[rtc].reserved2 = 1;			//bit[41]
	idt[rtc].reserved1 = 1;			//bit[42]
	idt[rtc].size      = 1;			//bit[43]

	//always 0 bit[44]
	idt[rtc].reserved0 = 0;

	//0 for interrupts,  bit[45:46]
	idt[rtc].dpl = 0;

	//set 1 for working interrupts,  bit[47]
	idt[rtc].present = 1;

	//segment selector   1 1 000,  bit[16:31]
	idt[rtc].seg_selector = KERNEL_CS;

	SET_IDT_ENTRY(idt[rtc], isr_wrapper_rtc);




	//init for interrupts on PIC
	int j = 0x0;
	for (j = 0x0; j < 256; j++) {
		if (j == 0x21 || j == 0x28 || j == 0x80 || j < 32) {
			continue;
		}

			//initalize interrupt keyboard
		//all 0 for any idt entry,  bit[32:39]
		idt[j].reserved4 = 0x00;

		//system call use interrupt gate = 0b1110,  bit[40:43]
		idt[j].reserved3 = 0;            //bit[40]
		idt[j].reserved2 = 1;			//bit[41]
		idt[j].reserved1 = 1;			//bit[42]
		idt[j].size      = 1;			//bit[43]

		//always 0 bit[44]
		idt[j].reserved0 = 0;

		//0 for interrupts,  bit[45:46]
		idt[j].dpl = 0;

		//set 1 for working interrupts,  bit[47]
		idt[j].present = 1;

		//segment selector   1 1 000,  bit[16:31]
		idt[j].seg_selector = KERNEL_CS;

		SET_IDT_ENTRY(idt[j], &timer_chip);
	}
}
