#include <vm.h>
#include <stdio.h>
#include <stdlib.h>

vm_t* vm_create(int* code, int code_size, int nglobals){
    vm_t* vm = (vm_t*)calloc(1, sizeof(vm_t) );
    vm_init(vm, code, code_size, nglobals);
    return vm;
}

void vm_init(vm_t* vm, int* code, int code_size, int nglobals){
    vm->code = code;
    vm->code_size = code_size;
    vm->globals = (int*)calloc(nglobals, sizeof(int));
    vm->nglobals = nglobals;
}

void vm_free(vm_t* vm){
    free(vm->globals);
    free(vm);
}


void vm_exec(vm_t* vm, int start_ip, bool trace){
    int i = 0, ip, opcode, st = -1;
    ip = start_ip;
    opcode = vm->code[ip];

    while(opcode != HALT && ip < vm->code_size){
        if(trace) printf("Hello");
        ip++; /* jump to next operation in code */
        switch( opcode ){
            case ICONST:
                vm->stack[++st] = vm->code[ip++];
                break;
            case PRINT:
                printf("%d\n", vm->stack[st--]);
                break;
            default:
                printf("[-]Invalid Opcode %d in line: %d\n", opcode, st);
                break;
        }
        opcode = vm->code[ip];
    }
}
