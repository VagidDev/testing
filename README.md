# All lab works for Testing

## Basic commands for C

1. Compiling - clang *-g* -o test test.c **or** gcc -o killo killo.c
2. Run - ./test

## GDB commands

1. Run gdb - **gdb**
2. Load file - **file 'name of file'**
3. Quit - **q**
4. Backtrace - **bt**
5. Display memory as machine instructions - **disas**
6. Create breakpoint - **b *where_is_error +0**

## File dump

1. Binary code - **nm hello**
2. Binary dump - **objdump -D hello** *or* **objdump -S hello**
3. Hex dump - **hd hello**
4. Hex dump to file - **xxd -g 1 hello > hexhello**
5. Hex dump to execution file - **xxd -r hexhello hello2**
