#include "mmu.h"
#include "asm.h"

.code16
.global start
start:




// YOUR CODE GOES HERE
  mov $hello, %si
  
  print: //prints hello
    movb (%si), %al
    movb $0x0e, %ah
    testb %al, %al
    jz done
    int $0x10
    inc %si
    jmp print

  done:

  movb $0x00, %ah //wait for keystroke
  int $0x16
  movb $0x00, %ah 
  movb $0x13, %al //set video mode to 320x200 256 color graphics (MCGA,VGA)
  int $0x10

# Change to 32-bit protected mode so we can run C code
cli
lgdt    gdtdesc
movl    %cr0, %eax
orl     $CR0_PE, %eax
movl    %eax, %cr0

ljmp    $(SEG_KCODE<<3), $start32
.code32  # Tell assembler to generate 32-bit code now.
start32:

movw    $(SEG_KDATA<<3), %ax    # Our data segment selector
movw    %ax, %ds                # -> DS: Data Segment
movw    %ax, %ss                # -> SS: Stack Segment

mov     $0x1000, %esp
call splashmain

loop:
    jmp loop

hello: .string "Welcome to xv6@UIC. Press any key to continue"

# Bootstrap GDT
.p2align 2                                # force 4 byte alignment
gdt:
  SEG_NULLASM                             # null seg
  SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)   # code seg
  SEG_ASM(STA_W, 0x0, 0xffffffff)         # data seg

gdtdesc:
  .word   (gdtdesc - gdt - 1)             # sizeof(gdt) - 1
  .long   gdt                             # address gdt