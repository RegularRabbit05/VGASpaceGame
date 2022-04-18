#include <VGAXUA.h>

VGAXUA vga;

__attribute__((unused)) void setup() {
  vga.begin();
}

__attribute__((unused)) void loop() {
  vga.putpixel(vga.rand()%VGAX_WIDTH, vga.rand()%VGAX_HEIGHT, vga.rand()%2);
  vga.setExtendedColorsMask(0);
}