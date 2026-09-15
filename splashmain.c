#include"types.h"
#include"x86.h"

void
splashmain(void)
{
    volatile unsigned char *video = (volatile unsigned char *)0xA0000;
    for(int i = 0; i < 20; i+=2){
        video[30 + 320*10 + (320 * i)] = 0x0f;
        video[60 + 320*10 + (320 * i)] = 0x0f;
    }
    for(int i = 0; i < 30; i++){
        video[50*320 + 30 + i + (-320*((i*i)/30) + 30)] = 0x0f;
    }
    while (1)
        ;
}