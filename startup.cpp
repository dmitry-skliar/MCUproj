#include <defines.h>

extern void* __stack_sram_start;
extern void kmain();

IRQ(Default_Handler);
// IRQ_DEFINE(NMI_Handler, Default_Handler);
// IRQ_DEFINE(MemManager_Handler, Default_Handler);

IRQ(Default_Handler)
{
    while(true);
}

IRQ(Reset_Handler)
{
    // TODO: Инициализация секции .data. Скопировать из флеш памяти в ram.
    kmain();
    while(true);
}

IRQ(NMI_Handler)
{
    while(true);
}

IRQ(MemManager_Handler)
{
    while(true);
}

IRQ_CREATE_TABLE
(
    IRQ_TABLE_INSERT(&__stack_sram_start)
    IRQ_TABLE_INSERT(Reset_Handler)
    IRQ_TABLE_INSERT(nullptr)
    IRQ_TABLE_INSERT(NMI_Handler)
    IRQ_TABLE_INSERT(MemManager_Handler)
)
