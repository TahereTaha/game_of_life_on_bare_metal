#constant declaration

.set ALIGN,		1<<0
.set MEMINFO,	1<<1
.set FLAGS,		ALIGN | MEMINFO
.set MAGIC,		0x1BAD002
.set CHECKSUM,	-(MAGIC + FLAGS)

#multiboot header that marks program as kernel. the multiboot will search for this values (signature) in the first 8kb of the file

.section	.multiboot
.align		4
.long		MAGIC
.long		FLAGS
.long		CHECKSUM

#defining the stack so it's generated properly, sign at top sign at bottom 16kb in the middle has to be aligned at 16 bits (not sure what that means)

.section	.bss
.align		16
stack_bottom:
.skip 16384 #b = 16 KiB (kibibytes~=kilobites)
stack_top:

#bootloader will jump here once the kernel is loaded

.section	.text
.global		start
.type		_start, @function
_start:

mov $stack_top, %esp

call kernel_main


#gugridigugridigu
#things to do :)
#gugridigugridigu


#infinite loop for when we run out of thing to do
	cli			#disable interrupts
1:	hlt			#waits for next interrupt, since they are disabled this will lock the computer
	jmp 1b		#if it ever goes past the hlt (by non maskable interrupt or something) it will jump bakc to 1 (hlt)

.size _start, . - _start
