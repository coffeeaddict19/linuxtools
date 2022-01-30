# linuxtools
A set of tools for examining the virtual memory of a running process. Provides a sample and a memory reader.

## To build:
```
git clone repo
cd repo
mkdir build
cd build
cmake ..
cmake --build .
```

## Run the sample:
```
cd memorytester
$ ./memorytester 
Hit enter with nothing to exit. Or type in an integral number of bytes to try to allocate.
10
fill character: a count: 10
10
fill character: b count: 10
```

## Print memory address ranges:
```
$ pidof memorytester
83448
$ sudo cat /proc/83448/maps | grep heap
01e5a000-01e7b000 rw-p 00000000 00:00 0                                  [heap]
$ sudo cat /proc/83448/maps | grep stack
7fff0816b000-7fff0818c000 rw-p 00000000 00:00 0                          [stack]
```

## Read virtual memory of the sample:
```
Run the memory reader and write stack and heap to disk. Read from the address range between typing an integral and enter. That will switch out the stack and heap each time you enter an integral.
$ sudo ./readliveprocmem 83448 01e5a000-01e7b000 /home/jlaird/Documents/heap1.bin
135168 bytes read from pid 83448
bytes read: 135168
135168 bytes written to: /home/jlaird/Documents/heap1.bin
$ sudo ./readliveprocmem 83448 7fff0816b000-7fff0818c000 /home/jlaird/Documents/stack1.bin
135168 bytes read from pid 83448
bytes read: 135168
135168 bytes written to: /home/jlaird/Documents/stack1.bin
$ sudo ./readliveprocmem 83448 01e5a000-01e7b000 /home/jlaird/Documents/heap2.bin
135168 bytes read from pid 83448
bytes read: 135168
135168 bytes written to: /home/jlaird/Documents/heap2.bin
$ sudo ./readliveprocmem 83448 7fff0816b000-7fff0818c000 /home/jlaird/Documents/stack2.bin
135168 bytes read from pid 83448
bytes read: 135168
135168 bytes written to: /home/jlaird/Documents/stack2.bin
```

## Analysis
```
Use strings to peek at the heap and stack files. Or use a hex editor to get a deeper look.
$ strings heap1.bin 
fill character: a count: 10
it. Or type in an integral number of bytes to try to allocate.
aaaaaaaaa
j$ strings heap2.bin 
fill character: b count: 10
it. Or type in an integral number of bytes to try to allocate.
bbbbbbbbb
$ strings stack1.bin 
fill character: 
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
fill character: 
abcdefghijklmnopqrstuvwxyz
```
