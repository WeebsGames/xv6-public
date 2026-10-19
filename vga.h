/* switch to vga Mode 13 */
void vgaMode13();

/* set graphics mode palette value */
void vgaSetPalette(int index, int r, int g, int b);

/* restore the text-mode palette saved before switching to Mode 13 */
void cgaRestorePalette(void);

/* switch to vga Mode 3 (text) */
void vgaMode3();
