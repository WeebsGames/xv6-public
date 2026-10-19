#include "types.h"
#include "defs.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "memlayout.h"
#include "vga.h"
#define VGA_FRAME_BYTES (320 * 200)

static int
displaywrite(struct file *f, char *buf, int n)
{
  // TODO: Validate n and f->off, then copy at most the remaining frame bytes
  // to (uchar*)P2V(0xA0000) + f->off. Advance f->off and return bytes copied.
  
  (void)f;
  (void)buf;
  (void)n;
  return -1;
}
static int
displayioctl(struct file *f, int command, int value)
{
  uint packed;
  (void)f;
  switch(command){
  case 1:
    if(value == 0x13)
      vgaMode13();
    else if(value == 0x03){
      vgaMode3();
      cgaRestorePalette(); // TODO: implement this in vga.c
    }else
      return -1;
    return 0;
  case 2:
    packed = (uint)value;
    vgaSetPalette((packed >> 24) & 0xff,
                  (packed >> 16) & 0x3f,
                  (packed >> 8) & 0x3f,
                  packed & 0x3f);
    return 0;
  default:
    return -1;
  }
}
void
displayinit(void)
{
  devsw[DISPLAY].write = displaywrite;
  devsw[DISPLAY].ioctl = displayioctl;
}