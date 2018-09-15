
# referenced from osdev.org
# https://wiki.osdev.org/Setting_Up_Paging

.text

.globl enablePaging
.globl loadPageDirectory

# void loadPageDirectory(unsigned int*);
#
# Interface: Because C code cannot directly access the computer's registers,
#							we will need to use assembly code to access CR3.
#    Inputs: unsigned int* -- the address of the page directory
#
#   Outputs: None
# Registers: NONE

loadPageDirectory:
	pushl %ebp				# save register
	movl %esp, %ebp		# save stack pointer

	movl 8(%esp), %eax	# put the arg into eax
	movl %eax, %cr3		# put the page directory pointer in to CR3

	movl %ebp, %esp		# put stack pointer back
	popl %ebp					# pop register
	ret

# void enablePaging(void);
#
# Interface: We must set the 32th bit in the CR0 register, the paging bit.
#							This operation also requires assembly code. Once done, paging will be enabled.
#    Inputs: None
#
#   Outputs: None
# Registers: None
enablePaging:
	pushl %ebp						# save register
	movl %esp, %ebp				# save stack pointer


												# If you want to set pages as read-only for both userspace and supervisor,
												# replace 0x80000001 above with 0x80010001, which also sets the WP bit.
												#	To enable PSE (4 MiB pages) the following code is required.

	movl %cr4, %eax				# put content in cr4 into eax
	orl  $0x10, %eax			# set the 0x10 bit in the cr4
	movl %eax, %cr4				# put the result back to cr4


												# Enabling paging is actually very simple.
												# All that is needed is to load CR3 with the address of the page directory
												# and to set the paging (PG) and protection (PE) bits of CR0.
												# Note: setting the paging flag when the protection flag is clear
												# causes a general-protection exception.
												
	movl %cr0, %eax				# put the content of cr0 into eax
	orl $0x80000000, %eax	# set the 0x80000001 bits in cr0
	movl %eax, %cr0				# put the result back

	movl %ebp, %esp				# put stack pointer back
	popl %ebp							# pop register
	ret
