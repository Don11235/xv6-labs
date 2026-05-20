# find (xv6 user program)

## Goal

Implement a simple version of the UNIX `find` program that searches 
a directory tree and prints all files with a specific name.

Example:
```
$ find . b
./b
./a/b
./a/aa/b
```
The program takes two arguments:
- the directory to search in (`.` means current directory)
- the filename to look for (`b`)

It must search recursively through all subdirectories, 
without recursing into `.` and `..`.

## Concepts Practiced

### 1. Recursion

Recursion is a technique to solve problems where a big problem is 
built from smaller subproblems of the same kind.

Example: sum from 1 to 100
```
1
1 + 2
1 + 2 + 3
...
1 + 2 + ... + 100
```
Each step is the same problem but with a smaller size. So instead 
of solving it all at once, we call the same function with a smaller 
input each time.

Every recursion has two parts:

- **recursive case** — call the same function with a smaller problem
- **base case** — the condition where we stop, no more recursive calls

Without the base case, the function calls itself forever until the 
stack overflows and the program crashes.

![Recursion](recursion_diagram.svg)

### 2. Directories

A directory is just a file that stores a list of entries. Each entry 
describes a file inside that directory. In xv6, each entry is a 
`struct dirent` with two fields (real UNIX systems may have more):

```c
struct dirent {
    ushort inum;        // inode number (0 = empty slot)
    char name[DIRSIZ];  // file name (max 14 chars in xv6)
};
```

To read a directory, you open it like a regular file and read 
`struct dirent` entries one by one.

One thing I discovered during this exercise: not every slot is used.
Empty slots have `inum == 0` and must be skipped:

```c
if (de.inum == 0)
    continue;
```

Ignoring this caused bugs in my first attempt — the program would 
try to process empty entries as real files.

## Implementation Strategy
```
find(path, fileName):
    1. open(path)
    2. fstat(path) → get file type

    3. if T_FILE:
           extract name from path
           if name matches fileName → print path

    4. if T_DIR:
           read entries one by one (struct dirent)
           skip if:
               - inum == 0        (empty slot)
               - name == "."      (current directory)
               - name == ".."     (parent directory)
           build full path:  path + "/" + entry.name
           call find(fullPath, fileName)  ← recursion
```

## Helper Functions

getname(path, name)
    extracts the filename from a full path
    walks backward from end of path until it finds '/'

match(fileName, name)
    compares two strings character by character
    returns 0 if equal (like strcmp)

joinpath(path, name, fullPath)
    builds a new path:  path + "/" + name
    checks it does not exceed MAXPATH
