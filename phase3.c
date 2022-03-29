#include <usloss.h>
#include <libuser.h>
#include <usyscall.h>
#include <phase1.h>
#include <phase2.h>
#include <phase3.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "sems.h"

int start2(char *);

int Spawn(char *name, int (*func)(char *), char *arg, int stack_size,
                  int priority, int *pid);
int spawn_real(char *name, int (*func)(char *), char *arg,
                int stack_size, int priority);

int Wait(int *pid, int *status);
int wait_real(int *status);

void Terminate(int status);
void GetTimeofDay(int *tod);
void CPUTime(int *cpu);
void GetPID(int *pid);
int  SemCreate(int value, int *semaphore);
int  SemP(int semaphore);
int  SemV(int semaphore);
int  SemFree(int semaphore);

void check_kernel_mode(char *func_name);
void nullsys3(sysargs *args_ptr);

/****************************GLOBALS***********************************************/
mbox_proc phase3_ProcTable[MAXPROC];

start2(char *arg)
{
    int		pid;
    int		status;
    
    /* Check kernel mode */
    check_kernel_mode(start2);

    /* Data structure initialization */
    
    // Process Table
    for (int i = 0; i < MAXPROC; i++) {
        phase3_ProcTable[i].pid = -1;
        phase3_ProcTable[i].status = NULL;
        phase3_ProcTable[i].name = NULL;
        phase3_ProcTable[i].numChild = -1;
        phase3_ProcTable[i].parent_ptr = NULL;
        phase3_ProcTable[i].child_ptr = NULL;
        phase3_ProcTable[i].sibling_ptr = NULL;
    }

    //Sys call handlers
    for (int i = 0; i < MAXSYSCALLS; i++) {
        sys_vec[i] = nullsys3;
    }

    //sys_vec[SYS_SPAWN] = spawn;
    //sys_vec[SYS_WAIT] = wait1;
    //sys_vec[SYS_TERMINATE] = terminate;
    //sys_vec[SYS_GETTIMEOFDAY] = getTimeOfDay;
    //sys_vec[SYS_CPUTIME] = cpuTime;
    //sys_vec[SYS_GETPID] = getPid;


    /*
     * Create first user-level process and wait for it to finish.
     * These are lower-case because they are not system calls;
     * system calls cannot be invoked from kernel mode.
     * Assumes kernel-mode versions of the system calls
     * with lower-case names.  I.e., Spawn is the user-mode function
     * called by the test cases; spawn is the kernel-mode function that
     * is called by the syscall_handler; spawn_real is the function that
     * contains the implementation and is called by spawn.
     *
     * Spawn() is in libuser.c.  It invokes usyscall()
     * The system call handler calls a function named spawn() -- note lower
     * case -- that extracts the arguments from the sysargs pointer, and
     * checks them for possible errors.  This function then calls spawn_real().
     *
     * Here, we only call spawn_real(), since we are already in kernel mode.
     *
     * spawn_real() will create the process by using a call to fork1 to
     * create a process executing the code in spawn_launch().  spawn_real()
     * and spawn_launch() then coordinate the completion of the phase 3
     * process table entries needed for the new process.  spawn_real() will
     * return to the original caller of Spawn, while spawn_launch() will
     * begin executing the function passed to Spawn. spawn_launch() will
     * need to switch to user-mode before allowing user code to execute.
     * spawn_real() will return to spawn(), which will put the return
     * values back into the sysargs pointer, switch to user-mode, and 
     * return to the user code that called Spawn.
     */
    pid = spawn_real("start3", start3, NULL, 4*USLOSS_MIN_STACK, 3);
    pid = wait_real(&status);

} /* start2 */



/* --------------------------------------------------------------------------------
   Name - check_kernel_mode
   Purpose - Checks to make sure functions are being called in Kernel mode
   Parameters - *func_name keeps track of where the mode checking is being invoked.
   Returns - nothing
   Side Effects -  if system is in usermode, print appropriate error and halt.
   -------------------------------------------------------------------------------- */
void check_kernel_mode(char *func_name) {
   char buffer[200];

   if (DEBUG3 && debugflag3) {
      sprintf(buffer, "check_kernel_mode(): called for function %s\n", func_name);
      console("%s", buffer);
   }

   /*test if in kernel mode and halts if in user mode*/
   if(psr_get() & PSR_CURRENT_MODE == 0) {
      console("%s", buffer);
      halt(1);
   }
   
} /* check_kernel_mode */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
static void nullsys3(sysargs *args_ptr) {
    printf("nullsys3(): Invalid syscall %d\n", args_ptr->number);
    printf("nullsys3(): Process %d terminating\n", getpid());
    terminate_real(1);
} /* nullsys3 */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int Spawn(char *name, int (*func)(char *), char *arg, int stack_size, int priority, int *pid) {

} /* Spawn */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int spawn_real(char *name, int (*func)(char *), char *arg, int stack_size, int priority) {

} /* spawn_real */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int Wait(int *pid, int *status) {

} /* Wait */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int wait_real(int *status) {

} /* wait_real */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
void Terminate(int status) {

} /* Terminate */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
void GetTimeofDay(int *tod) {

} /* GetTimeofDay */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
void CPUTime(int *cpu) {

} /* CPUTime */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
void GetPID(int *pid) {

} /* GetPID */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int  SemCreate(int value, int *semaphore) {

} /* SemCreate */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int  SemP(int semaphore) {

} /* SemP */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int  SemV(int semaphore) {

} /* SemV */

/* --------------------------------------------------------------------------------
   Name - 
   Purpose - 
   Parameters - 
   Returns - 
   Side Effects - 
   -------------------------------------------------------------------------------- */
int  SemFree(int semaphore) {

} /* SemFree */