#include <vm.h>
#include <stdio.h>
#include <stdlib.h>

vm_instruction_t commands[] = {
        { "ERR", 0 },
        { "IADD", 0},
        { "ISUB", 0},
        { "IMUL", 0},
        { "IDIV", 0},
        { "IGT", 0},
        { "ILT", 0},
        { "IET", 0},
        { "BR", 1},
        { "BRIT", 1},
        { "BRIF", 1} ,
        { "ICONST", 1},
        { "STORE", 1},
        { "GSTORE", 1},
        { "LOAD", 1},
        { "GLOAD", 1},
        { "POP", 0},
        { "CALL", 3},
        { "PRINT", 0},
        { "RET", 0},
        { "HALT", 0}
};


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


void vm_exec(vm_t* vm, int start_ip, bool debug){
    int i = 0, ip = 0, opcode = 0, st = -1, a = 0, b = 0, offset = 0, callst = -1, addr = 0;
    ip = start_ip;
    opcode = vm->code[ip];
    while(opcode != HALT && ip < vm->code_size){
        if(debug) vm_print_instruction(vm->code, ip);
        ip++; /* jump to next operation in code */
        switch( opcode ){
            case IADD:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = a + b;
                break;
            case ISUB:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = a - b;
                break;
            case IMUL:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = a * b;
                break;
            case IDIV:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = a / b;
                break;
            case IGT:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = (a > b) ? true : false;
                break;
            case ILT:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = (a < b) ? true : false;
                break;
            case IET:
                b = vm->stack[st--];
                a = vm->stack[st--];
                vm->stack[++st] = (a == b) ? true : false;
                break;
            case STORE:
                offset = vm->code[ip++];
                vm->call_stack[callst].locals[offset] = vm->stack[st--];
                break;
            case GSTORE:
                addr = vm->code[ip++];
                vm->globals[addr] = vm->stack[st--];
                break;
            case LOAD:
                offset = vm->code[ip++];
                vm->stack[++st] = vm->call_stack[callst].locals[offset];
                break;
            case GLOAD:
                addr = vm->code[ip++];
                vm->stack[++st] = vm->globals[addr];
                break;
            case ICONST:
                vm->stack[++st] = vm->code[ip++];
                break;
            case PRINT:
                printf("%d\n", vm->stack[st--]);
                break;
            case POP:
                --st;
                break;
            case BR:
                ip = vm->code[ip];
            case BRIT:
                addr = vm->code[ip++];
                if(vm->stack[st--] == true) ip = addr;
                break;
            case BRIF:
                addr =  vm->code[ip++];
                if(vm->stack[st--] == false) ip = addr;
                break;
            case CALL:
                addr = vm->code[ip++]; /* index of target function */
                int nargs = vm->code[ip++]; /* args */
                int nlocals = vm->code[ip++]; /* locals */
                ++callst;
                vm_context_init(&vm->call_stack[callst], ip, ( nargs + nlocals ) );
                int i;
                for(i = 0; i < nargs; i++){
                    vm->call_stack[callst].locals[i] = vm->stack[(st - i)];
                }
                st -= nargs;
                ip = addr; // jump to function
                break;
            case RET:
                ip = vm->call_stack[callst].ret_ip;
                callst--;
                break;
            default:
                printf("[-]Invalid Opcode %d in instruction: %d\n", opcode, (ip - 1) );
                break;
        }
        // if(debug) vm_print_stack(vm->stack, st);
        opcode = vm->code[ip];
    }
    if(debug) vm_print_data(vm->globals, vm->nglobals);
}

void vm_context_init(vm_context_t* ctx, int ip, int nlocals){
    if(nlocals > NUM_LOCALS){
        fprintf(stderr, "too many arguments: %d\n", nlocals);
    }
    ctx->ret_ip = ip;
}

void vm_print_instruction(int* code, int ip){
    int opcode = code[ip];
    vm_instruction_t cmd = commands[opcode];
    switch(cmd.nargs){
        case 1:
            printf("%04d\t%s\t%d\n", ip ,cmd.cmd, code[ip+1]);
            break;
        case 2:
            printf("%04d\t%s\t%d, %d\n", ip ,cmd.cmd, code[ip+1], code[ip+2]);
            break;
        case 3:
            printf("%04d\t%s\t%d, %d, %d\n", ip ,cmd.cmd, code[ip+1], code[ip+2], code[ip + 3]);
            break;
        default:
            printf("%04d\t%s\n", ip ,cmd.cmd);
            break;
    }
}


void vm_print_stack(int* stack, int st){
    printf("\t\t\tstack = [");
    int i;
    for (i = 0; i <= st; i++){
        printf(" %d", stack[i]);
    }
    printf(" ]\n");
}
void vm_print_data(int* globals, int nglobals){
    printf("Data memory:\n");
    int i;
    for (i = 0; i < nglobals; i++){
        printf("%04d:\t%d\n", i, globals[i]);
    }
}
