#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct process_table {
    struct spinlock lock;
    struct proc proc[NPROC];
};
extern struct process_table ptable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_assign_nice(void)
{
  struct proc *p;
  int pid;
  int nice;
  int oldnice;

  // Get the data from user space
  oldnice = 100;
  if (argint(0, &pid) < 1)
    return -1;
  if (argint(1, &nice) > 5)
    return -2;
 // if (pid < 1 || nice < 1)
  //  return -1;

  // Acquire the process table lock
  acquire(&ptable.lock);

    // Find and assign the nice value to the process
  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if (p->pid == pid) {
      oldnice = p->nice;
      p->nice = nice;
      release(&ptable.lock);
      return oldnice;
      }
  }
    // Release the process table lock
  release(&ptable.lock);

  return oldnice;
}
