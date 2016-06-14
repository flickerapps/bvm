#ifndef VM_H
#define VM_H

#include <stdbool.h>

/*default sizes */
#define NUM_LOCALS      16
#define CALL_STACK_SIZE NUM_LOCALS << 4
#define STACK_SIZE      CALL_STACK_SIZE << 4
#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )
enum _vm_pcode_t {
        ERR = 0, /* we will use zero for errors */
    /* ---  Math Ops -----*/
        IADD = 1, /* integer `add` operation */
        ISUB = 2, /* `sub` operation */
        IMUL = 3, /* multiplication */
        IDIV = 4, /* division */
    /* --- Binary Ops ------ */
        IGT = 5, /* int greater than */
        ILT = 6, /* int less than */
        IET = 7, /* int equal than */
    /* ----- branchs ---- */
        BR = 8, /* branch */
        BRIT = 9, /* branch if true */
        BRIF = 10 , /* branch if false */
    /* ---- store and pop --- */
        ICONST = 11, /* integer constant define */
        STORE = 12, /* store to local context */
        GSTORE = 13, /* store to global context */
        LOAD = 14, /* load from local context */
        GLOAD = 15, /* load from global context */
        POP = 16,
        CALL = 17,
        PRINT = 18, /* pop and print */
    /* ----- exit and return  ---- */
        RET = 19, /* return */
        HALT = 20, /* exit */
};

/* context for local variables in `vm` */
struct _vm_context_t {
    int ret_ip;
    int locals[NUM_LOCALS];
}; typedef struct _vm_context_t vm_context_t;

struct _vm_t_{

    /* code to run */
    int* code; /* array of instructions */
    int code_size; /* sizeof instructions */

    /* global variables */
    int* globals; /*array of blobal vars */
    int nglobals; /* num of global vars */

    /*stack and context */
    int stack[STACK_SIZE];
    vm_context_t call_stack[CALL_STACK_SIZE];

}; typedef struct _vm_t_ vm_t;


vm_t* vm_create(int*, int, int);
void vm_init(vm_t*, int*, int, int);
void vm_free(vm_t*);
void vm_exec(vm_t*, int, bool);

#endif
