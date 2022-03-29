#define DEBUG3 1

typedef struct mbox_proc mbox_proc;
typedef struct mbox_proc *mbox_proc_ptr;

struct mbox_proc {
   short         pid;
   int           status;
   char         *name;
   int           numChild;
   int           mbox_start;
   char         *start_arg;
   int          (* start_func)(char *);
   mbox_proc_ptr parent_ptr;
   mbox_proc_ptr child_ptr;
   mbox_proc_ptr sibling_ptr;
};