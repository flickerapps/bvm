#include <stdio.h>
#include <vm.h>

int hello_world[] = {
    ICONST, 10, /* push 10*/
    PRINT, /* print 10 */
    HALT /* exit */
};

int main(){
    vm_t* vm = vm_create(hello_world, sizeof(hello_world), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    return 0;
}
