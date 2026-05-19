# find (xv6 user program)

## Goal

Implement a simple version of the UNIX `find` program that searches 
a directory tree and prints all files with a specific name.

Example:

$ find . b
./b
./a/b
./a/aa/b

The program takes two arguments:
- the directory to search in (`.` means current directory)
- the filename to look for (`b`)

It must search recursively through all subdirectories, 
without recursing into `.` and `..`.
