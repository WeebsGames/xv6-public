#include"types.h"
#include"x86.h"

void
splashmain(void)
{
    volatile unsigned char *video = (volatile unsigned char *)0xA0000;
    for(int i = 0; i < 320; i+=2){
        video[i + (320 * i)] = 0x0f;  // Set each pixel to a default color (black background, white foreground)
    }
    while (1)
        ;
}