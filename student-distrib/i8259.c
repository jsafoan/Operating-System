/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"
#include "lib.h"
//#include <linux/spinlock.h>
//#include <linux/delay.h>
#define ASM     1

/* Interrupt masks to determine which interrupts are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7  */
uint8_t slave_mask;  /* IRQs 8-15 */
//static spinlock_t i8259_lock = SPIN_LOCK_UNLOCKED;


/* void i8259_init(void);
 * Inputs: none
 * Return Value: void
 * Function: Initialize the 8259 PIC
 */
void i8259_init(void) {
  //unsigned long flags;
  uint8_t f = 0xff;
  //cli();
  //spinlock_irqsave(&i8259_lock ,flags);

  //master_mask = inb(MASTER_8259_PORT_1);
  //slave_mask = inb(SLAVE_8259_PORT_1);

  // need these two codes so that the PIC is maksed
  outb(f, MASTER_8259_PORT_1);
  outb(f, SLAVE_8259_PORT_1);
  master_mask = f;
  slave_mask = f;


  outb(ICW1, MASTER_8259_PORT);  //start the initialization
  //udelay(100);
  outb(ICW2_MASTER, MASTER_8259_PORT_1);// ICW2: Master PIC vector offset
  //udelay(100);
  outb(ICW3_MASTER, MASTER_8259_PORT_1);// ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  //udelay(100);
  outb(ICW4, MASTER_8259_PORT_1);
  //udelay(100);

  outb(ICW1, SLAVE_8259_PORT);
  //udelay(100);
  outb(ICW2_SLAVE, SLAVE_8259_PORT_1);// ICW2: Slave PIC vector offset
  //udelay(100);
  outb(ICW3_SLAVE, SLAVE_8259_PORT_1);// ICW3: tell Slave PIC its cascade identity (0000 0010)
  //udelay(100);
  outb(ICW4, SLAVE_8259_PORT_1);
  //udelay(100);

  //enable slave pic
  enable_irq(2);

  //outb(master_mask, MASTER_8259_PORT_1);
  //outb(slave_mask, SLAVE_8259_PORT_1);

  //spin_unlock_irgrestore(&i8259_lock, flags);

  //dont sti until interrupt handlers have been implemented
  //sti();
  return;
}
/*
*   enable_irq(uint32_t irq_num)
*   Inputs: the IRQ number that needs to be enabled on slave or master PIC
*   Return Value: none
*   Function: Enable (unmask) the specified IRQ
*/
void enable_irq(uint32_t irq_num) {
  uint8_t irq = irq_num & MASK_FOR_IRQ_NUM;//0xff is the mask for irq
  uint8_t byte, mask, bit;
  bit = 0x01;   // setting this value to one so that i can xor this to get the mask
  byte = 0xff;  // setting this to all 1's so once xor'd it enables the interupt
  // checking if the irq is on the master or the slave
//  cli();
  if (irq > MASTERORSLAVE) //IRQ at slave PIC
    {
      mask = slave_mask;
      irq = irq - SET_IRQ_BITS_OFFESET; //irq number on slave goes from 8-15
                      //So need to minus 8 inorder to set the bits correctly
      bit = bit << irq;   //shift bits
      byte = byte ^ bit;
      mask = mask & byte;
      outb(mask, SLAVE_8259_PORT_1);
      slave_mask = mask;
    }
    // this is for the master as the irq is less than to 8
  else //IRQ at master PIC
    {
      mask = master_mask;
      bit = bit << irq;
      byte = byte ^ bit;
      mask = mask & byte;
      outb(mask, MASTER_8259_PORT_1);
      master_mask = mask;
    }
//    sti();
}
/*
*   disable_irq(uint32_t irq_num)
*   Inputs: the IRQ number that needs to be disabled on slave or master PIC
*   Return Value: none
*   Function: Disable (mask) the specified IRQ
*/
void disable_irq(uint32_t irq_num) {
  uint8_t irq = irq_num & MASK_FOR_IRQ_NUM;
  uint8_t byte, mask;
  // as disable is the setting of 1 on the masked irq,
  byte = 0x01;
  // checking if the irq is on the master or the slave
//  cli();
  if (irq > MASTERORSLAVE)//slave pic
    {
      mask = slave_mask;
      irq = irq - SET_IRQ_BITS_OFFESET;
      byte = byte << irq;
      mask = mask | byte;
      outb(mask, SLAVE_8259_PORT_1);
      slave_mask = mask;
    }
    // this is for the master as the irq is less than to 8
  else          //Master PIC
    {
      mask = master_mask;
      byte = byte << irq;
      mask = mask | byte;
      outb(mask, MASTER_8259_PORT_1);
      master_mask = mask;
    }
  //sti();
}
/*
*   send_eoi(uint32_t irq_num)
*   Inputs: the irq number that we need to send end of interrupt signal
*   Return Value: none
*   Function: Send end-of-interrupt signal for the specified IRQ
*/
void send_eoi(uint32_t irq_num) {
  /*uint8_t irq = irq_num & 0xff;
  if (irq > 0x07)
    {
      irq = irq - 7;
      irq = irq | EOI;
      outb(irq, SLAVE_8259_PORT_1);
    }

	  irq = irq_num & 0xff;
	  irq = irq | EOI;
      outb(irq, MASTER_8259_PORT_1);*/

	//uint8_t irq = irq_num & 0xff;
  if (irq_num > MASTERORSLAVE) //slave PIC
  {
    outb((irq_num-SET_IRQ_BITS_OFFESET) | EOI, SLAVE_8259_PORT);
    outb(EOI | 2, MASTER_8259_PORT);
  }

	else {               //Master PIC
    outb( irq_num | EOI, MASTER_8259_PORT);
  }
}
