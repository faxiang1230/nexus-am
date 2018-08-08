#include <am.h>
#include <x86.h>

#include "klib.h"
static void *(*pgalloc_usr)(size_t);
static void (*pgfree_usr)(void *);

static void *pgalloc() {
  void *ret = pgalloc_usr(PGSIZE);
  if (!ret) _halt(34);
  for (int i = 0; i < PGSIZE / sizeof(uint32_t); i++) {
    ((uint32_t *)ret)[i] = 0;
  }
  return ret;
}

static void pgfree(void *ptr) {
  pgfree_usr(ptr);
}


static intptr_t first_proc = 1;
static PDE *kpt;

static _Area prot_vm_range = {
  .start = (void*)0x40000000,
  .end   = (void*)0x80000000,
};
static _Area segments[] = {
    {.start = (void*)0,          .end = (void*)0x10000000},  //   Low memory: kernel data
    {.start = (void*)0xf0000000, .end = (void*)(0)},         //   High memory: APIC and VGA
};

// must be called atomically per-cpu
int _pte_init(void * (*pgalloc_f)(size_t), void (*pgfree_f)(void *)) {
  pgalloc_usr = pgalloc_f;
  pgfree_usr = pgfree_f;

  if (first_proc) {
    // first processor, create kernel page table

    kpt = pgalloc();
    for (int i = 0; i < sizeof(segments) / sizeof(segments[0]); i++) {
      _Area *seg = &segments[i];
      for (uint32_t pa = (uint32_t)seg->start; pa != (uint32_t)seg->end; pa += PGSIZE) {
        PTE *ptab;
        if (!(kpt[PDX(pa)] & PTE_P)) {
          ptab = pgalloc();
          kpt[PDX(pa)] = PTE_P | PTE_W | (uint32_t)ptab;
        } else {
          ptab = (PTE*)PTE_ADDR(kpt[PDX(pa)]);
        }
        ptab[PTX(pa)] = PTE_P | PTE_W | pa;
      }
    }

    set_cr3(kpt);
    set_cr0(get_cr0() | CR0_PG);
    _atomic_xchg(&first_proc, 0);
  }
  return 0;
}

int _protect(_Protect *p) {
  p->pgsize = PGSIZE;
  p->area = prot_vm_range;
  PDE *upt = pgalloc();
  for (int i = 0; i < PGSIZE / sizeof(PDE *); i++) {
    upt[i] = kpt[i];
  }
  p->ptr = upt;
  return 0;
}

void _unprotect(_Protect *p) {
  PDE *upt = p->ptr;
  // TODO: free up all spaces
  pgfree(upt);
}

void _switch(_Protect *p) {
  set_cr3(p->ptr);
}

int _map(_Protect *p, void *va, void *pa, int prot) {
  PDE *pt = (PDE*)p->ptr;
  PDE *pde = &pt[PDX(va)];

  if (!(*pde & PTE_P)) {
    *pde = PTE_P | PTE_W | PTE_U | (uint32_t)(pgalloc());
  }

  PTE *pte = &((PTE*)PTE_ADDR(*pde))[PTX(va)];
  if (prot & _PROT_NONE) {
    *pte = 0;
  } else {
    *pte = PTE_P | ((prot & _PROT_WRITE) ? PTE_W : 0) | PTE_U | (uint32_t)(pa);
  }
  return 0;
}

/*
int _protect(_Protect *p) {
  PDE *updir = (PDE*)(palloc_f(PGSIZE));
  p->pgsize = PGSIZE;
  p->ptr = updir;
  // map kernel space
  for (int i = 0; i < 1024; i ++)
    updir[i] = kpdir[i];

  // exact copy of kernel page table
  // no user memory is mapped

  p->area.start = (void*)0x40000000;
  p->area.end = (void*)0xc0000000;
  return 0;
}

void _unprotect(_Protect *p) {
  // DFS pages and call release
}

void _switch(_Protect *p) {
  set_cr3(p->ptr);
}

int _map(_Protect *p, void *va, void *pa, int prot) {
  PDE *pt = (PDE*)p->ptr;
  PDE *pde = &pt[PDX(va)];
  uint32_t wflag = 0; // TODO: this should be not accessible
  if (prot & _PROT_WRITE) wflag = PTE_W;
  if (!(*pde & PTE_P)) {
    *pde = PTE_P | wflag | PTE_U | (uint32_t)(palloc_f(PGSIZE));
  }
  PTE *pte = &((PTE*)PTE_ADDR(*pde))[PTX(va)];
  if (!(*pte & PTE_P)) {
    *pte = PTE_P | wflag | PTE_U | (uint32_t)(pa);
  }
  return 0;
}

_RegSet *_umake(_Protect *p, _Area ustack, _Area kstack, void (*entry)(void *), void *args) {
  _RegSet *regs = (_RegSet*)kstack.start;
  regs->cs = USEL(SEG_UCODE);
  regs->ds = regs->es = regs->ss = USEL(SEG_UDATA);
  regs->esp3 = (uint32_t)ustack.end;
  regs->ss0 = KSEL(SEG_KDATA);
  regs->esp0 = (uint32_t)kstack.end;
  regs->eip = (uint32_t)entry;
  regs->eflags = FL_IF;

  uint32_t esp = regs->esp3;
  regs->esp3 = esp;
  // TODO:
  // push args to ustack
  // prepare kstack
  // make every register correct

  return regs;
}
*/
