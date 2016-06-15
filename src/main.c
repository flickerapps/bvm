#include <stdio.h>
#include <vm.h>

int hello_world[] = {
    /*

    def hello_world():
        print 10

    */
    ICONST, 10, /* push 10*/
    PRINT, /* print 10 */
    HALT /* exit */
};


int double_[] = {
    /*

    def double():
(1)        n = 10
(2)        a = n*2
(3)        if( a == 20):
(4)           print a

    */
    ICONST, 10,     // 0-1
    /* (1) */
    GSTORE, 0,       // 2-3
    ICONST, 2,      // 4-5
    GLOAD, 0,        // 6-7
    /* (2) */
    IMUL,           // 8
    GSTORE, 0,       // 9-10
    GLOAD, 0,        // 11-12
    ICONST, 20,     // 13-14
    /* (3) */
    IET,            // 15
    BRIF, 21,       // 16-17
    /* (4) */
    GLOAD, 0,        // 18-19
    PRINT,          // 20
    HALT            // 21
};

int f[] = {
    //                              ADDRESS
    //.def main() { print f(5, 10); }
    ICONST, 10,              // 0
    ICONST, 5,             // 2
    CALL, 10, 2, 2,          // 4
    PRINT,                  // 8
    HALT,                   // 9
    //.def f(x,y): ARGS=2, LOCALS=2
    // return x*y
    LOAD, 1,
    LOAD, 0,
    IMUL,
    RET,
    HALT
};

int factorial[] = {
//.def factorial: ARGS=1, LOCALS=0  ADDRESS
//  IF N < 2 RETURN 1
    LOAD, 0,                // 0
    ICONST, 2,              // 2
    ILT,                    // 4
    BRIF, 10,                // 5
    ICONST, 1,              // 7
    RET,                    // 9
//CONT:
//  RETURN N * FACT(N-1)
    LOAD, 0,                // 10
    LOAD, 0,                // 12
    ICONST, 1,              // 14
    ISUB,                   // 16
    CALL, 0, 1, 0,    // 17
    IMUL,                   // 21
    RET,                    // 22
//.DEF MAIN: ARGS=0, LOCALS=0
// PRINT FACT(1)
    ICONST, 5,              // 23    <-- MAIN METHOD!
    CALL, 0, 1, 0,    // 25
    PRINT,                  // 29
    HALT                    // 30
};

int mult[] = {
    /*
        def main:
            print mul(3, 5)
    */
    ICONST, 3,      // 0
    ICONST, 5,      // 2
    CALL, 10, 2, 2,  // 4
    PRINT,          // 8
    HALT,           // 9
    /*
    def mul(a, b):
        return a*b
    */
    LOAD, 0,        // 10
    LOAD, 1,        // 12
    IMUL,           // 14
    RET,            // 15
    HALT           // 16
};

int main(){
    vm_t* vm;
    printf("1. Hello_World():\n\n");
    vm = vm_create(hello_world, sizeof(hello_world), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);

    printf("\n2. double(10):\n\n");
    vm = vm_create(double_, sizeof(double_), 1);
    vm_exec(vm, 0, true);
    vm_free(vm);

    printf("\n3. f(10):\n\n");
    vm = vm_create(f, sizeof(f), 0);
    vm_exec(vm, 0, true);
    vm_free(vm);

    printf("\n4. factorial(5):\n");
    vm = vm_create(factorial, sizeof(factorial), 0);
    vm_exec(vm, 23, false);
    vm_free(vm);

    printf("\n5. mult(3,5):\n\n");
    vm = vm_create(mult, sizeof(mult), 0);
    vm_exec(vm, 0, true);
    vm_free(vm);

    return 0;
}
