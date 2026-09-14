#include"types.h"
#include"x86.h"

// void splashmain() {

//     // REPLACE THIS INFINITE LOOP WITH YOUR CODE
    
//     while(1);
// }

void
splashmain(void)
{
    volatile unsigned short *video = (volatile unsigned short *)0xB8000;
    video[0] = 0x0F48;  // H
    while (1)
        ;
}