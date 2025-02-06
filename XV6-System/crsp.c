#include "types.h"
#include "param.h"
#include "proc.h"
#include "x86.h"
#include "defs.h"
#include "mmu.h"
#include "spinlock.h"

extern struct {
    struct spinlock lock;
    struct proc proc[NPROC];
} ptable;

int sys_crsp(void) {
    struct proc *p;

    // Acquire a lock to protect access to shared data structures, such as ptable
    acquire(&ptable.lock);

    // Print a header for the process information
    cprintf("name\t\tpid\t\tstate\n");
    cprintf("---------------------------------\n");

    // Iterate over ptable to find and print information about RUNNING and SLEEPING processes
    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
        if (p->state == RUNNABLE) {
            cprintf("%s\t\t%d\t\tRUNNABLE\n", p->name, p->pid);
        } else if (p->state == RUNNING) {
            cprintf("%s\t\t%d\t\tRUNNING\n", p->name, p->pid);
        } else if (p->state == SLEEPING) {
            cprintf("%s\t\t%d\t\tSLEEPING\n", p->name, p->pid);
        }
    }

    // Release the lock
    release(&ptable.lock);

    return 0;
}

