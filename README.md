Basic Virtual Machine
====
Basic virtual machine (bvm) is writen in c.
Usage:
====
Install:
```
$ git clone https://github.com/flickerapps/bvm.git
$ cd bvm
$ make
```
Run test:
```
$ make run
```

Example program:
`Hello World` in bvm:
```c

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
```

Super Fork of: [simple-virtual-machine-c](https://github.com/parrt/simple-virtual-machine-C)
License
====
[MIT](LICENSE.md)
