// #include <stdint.h>
#include "kernel.h"

struct idt_entry idt[256];
struct idt_ptr   idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector  = selector;
    idt[num].zero      = 0;
    idt[num].flags     = flags;
}

void idt_init()
{
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    // Mettre toutes les entrées à zéro par défaut
    for (int i = 0; i < 256; i++)
        idt_set_gate(i, 0, 0, 0);

    __asm__ volatile ("lidt %0" :: "m"(idtp));
}
