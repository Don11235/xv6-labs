# sixfive (xv6 user program)

## Goal

Implement a program `sixfive` that reads one or more files and prints all numbers that are multiples of **5 or 6**.

Numbers are defined as sequences of decimal digits separated by characters from the string:

" -\r\t\n./,"

Example:

$ sixfive sixfive.txt
5
100
18
6

Important rule from the exercise:

- "xv6" → should NOT print `6`
- "/6," → should print `6`

This means numbers must be properly separated by the allowed separator characters.

---

# Concepts Practiced

## 1. File system calls in xv6

This program uses low-level system calls:

- `open()` → open a file and get a file descriptor
- `read()` → read bytes from the file
- `close()` → close the file descriptor

Instead of reading large buffers, the program reads **one character at a time**:

read(fd, &c, 1);

Reading character-by-character makes it easier to parse numbers and detect separators.

---

## 2. Parsing numbers from a stream

The main challenge is detecting **valid numbers inside text**.

A number must satisfy two conditions:

1. It is composed only of digits
2. It is surrounded by separators or file boundaries

Example:

Valid:

/18,
 5
-100

Invalid:

xv6
abc12

---

## 3. Handling multi-digit numbers

My **first implementation had a bug**.

The program only worked for **single-digit numbers** because it checked digits one by one.

Example problem:

100

The program would see:

1
0
0

instead of the full number.

To fix this, I created a helper function:

read_full_number()

This function continues reading digits until it reaches a non-digit character, allowing the program to extract the complete integer.

---

## 4. Tracking separators

To ensure numbers are valid, I track the **previous character** using a variable:

char sep;

When a number is read, I verify:

- the previous character is a separator
- the next character is a separator or end of file

This ensures the number is correctly delimited.

---

## 5. Checking multiples

Once a valid number is extracted, the program checks:

nb % 5 == 0 || nb % 6 == 0

If the condition is true, the number is printed.

---

# Implementation Strategy

The program works as follows:

1. Open the file using `open()`
2. Read the file character by character
3. If the character is a digit:
   - call `read_full_number()` to read the entire number
4. Verify the number is surrounded by separators
5. Check if the number is divisible by 5 or 6
6. Print the number if valid
7. Continue until the end of the file
