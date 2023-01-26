#ifndef GDT_H_INCLUDED
#define GDT_H_INCLUDED

#define GDT_NULL_INDEX 0
#define GDT_CS_INDEX 1
#define GDT_DS_INDEX 2

#define GDT_CS_SELECTOR (GDT_CS_INDEX << 3)
#define GDT_DS_SELECTOR (GDT_DS_INDEX << 3)

#ifndef __ASSEMBLER__
void reload_segment_regs(void);
#endif // ifndef __ASSEMBLER__

#endif // ifndef GDT_H_INCLUDED
