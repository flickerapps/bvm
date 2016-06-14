Basic Virtual Machine
====
Basic virtual machine (bvm) is writen in c.
Usage:
====
Install:
```
$ git clone
$ cd bvm
$ make
```
Run test:
```
$ make run
```

Example program:
`Hello Wordl` in bvm:
```c
int hello[] = {
    ICONST, 10, /* push integer => 10 */
    PRINT, /* Pop stack (10) and print the integer */
    HALT    /* exit the program */
};
```