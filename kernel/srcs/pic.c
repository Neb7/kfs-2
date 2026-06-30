// #include <stdint.h>
#include "kernel.h"

inline void outb(uint16_t port, uint8_t val)
{
	__asm__ volatile ("outb %0, %1" :: "a"(val), "Nd"(port));
}

inline uint8_t inb(uint16_t port)
{
	uint8_t val;
	__asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
	return val;
}

void pic_init()
{
	// ICW1 — début d'initialisation
	outb(PIC1_CMD,  0x11);
	outb(PIC2_CMD,  0x11);

	// ICW2 — remapping des vecteurs
	outb(PIC1_DATA, 0x20);  // IRQ0-7  → vecteurs 32-39
	outb(PIC2_DATA, 0x28);  // IRQ8-15 → vecteurs 40-47

	// ICW3 — cascade
	outb(PIC1_DATA, 0x04);  // PIC1 : PIC2 connecté sur IRQ2
	outb(PIC2_DATA, 0x02);  // PIC2 : connecté sur IRQ2 du PIC1

	// ICW4 — mode 8086
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);

	// Masques — tout masqué sauf IRQ1 (clavier)
	outb(PIC1_DATA, 0xFD);  // 1111 1101
	outb(PIC2_DATA, 0xFF);
}
