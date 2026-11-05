*This project has been created as part of the 42 curriculum by sbouadai.*

# get_next_line

## Description

**get_next_line** is a C function that returns one line at a time from a file descriptor, each time it is called.

```c
char *get_next_line(int fd);
```

- It returns the line that was read, **including the trailing `\n`** (except for the last line if the file does not end with one).
- It returns `NULL` when there is nothing more to read, or when an error occurs.
- It works with regular files, standard input, and any other readable file descriptor.
- It works with any `BUFFER_SIZE` defined at compile time (1, 42, 10000000...).

### Goal of the project

The goal is to learn about:

- **File descriptors** and the `read` system call.
- **Static variables**: keeping data between function calls.
- **Dynamic memory management**: `malloc`, `free`, and avoiding leaks.
- **Edge cases**: empty files, no final newline, read errors, very small or very large buffers.

### Bonus

The bonus version handles **several file descriptors at the same time**. You can alternate calls between different fds and each one keeps its own reading position, without mixing the content. It uses a single static array indexed by fd.

### How it works

`read` moves the file offset forward and it cannot go back. If `BUFFER_SIZE` is larger than the current line, `read` also consumes bytes that belong to the next lines. These extra bytes are kept in a **static variable** (the "stash") until the next call.

1. `ft_read_to_left`: reads `BUFFER_SIZE` bytes at a time and appends them to the stash until it contains a `\n`, or until `read` returns `0` (EOF) or `-1` (error).
2. `ft_line`: extracts the line (up to and including `\n`) from the stash.
3. `ft_new_left`: builds a new stash with what remains after the `\n`, and frees the old one.

### Technical choices

- **Static stash**: `static char *left[FD_MAX]` (bonus), `static char *left` (mandatory). Without an initializer, it lives in the **BSS** section and starts as `NULL`. The pointer is static, but the text it points to is allocated with `malloc` on the **heap** and freed at EOF or on error.
- **Heap buffer**: the read buffer is allocated with `malloc` instead of a local array, so a huge `BUFFER_SIZE` does not overflow the stack.
- **`FD_MAX` macro** (default `1024`): the size of the stash array. The function returns `NULL` if `fd < 0` or `fd >= FD_MAX`, to avoid reading outside the array.
- **Error handling**: on a `read` error or an allocation failure, the stash and the buffer are freed, the stash is set to `NULL`, and the function returns `NULL`.
- **Allowed functions**: only `read`, `malloc`, and `free`.

## Instructions

### Files

| File | Content |
|---|---|
| `get_next_line.c` | main function and helpers |
| `get_next_line_utils.c` | utility functions (`ft_strlen`, `ft_strchr`, `ft_strjoin`...) |
| `get_next_line.h` | header, prototypes, default `BUFFER_SIZE` |
| `get_next_line_bonus.c` | bonus: multiple file descriptors |
| `get_next_line_utils_bonus.c` | bonus utilities |
| `get_next_line_bonus.h` | bonus header, `FD_MAX` |

### Compilation

The function has no `main`. Compile it together with your own test file. `BUFFER_SIZE` is set with `-D`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

Bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

If `-D BUFFER_SIZE` is not given, the header defines a default value. `FD_MAX` can also be overridden with `-D FD_MAX=4096`.

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Each returned line must be freed by the caller.

### Testing

Check memory with valgrind (Linux) and try several buffer sizes:

```bash
cc -g -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c -o gnl
valgrind --leak-check=full --show-leak-kinds=all ./gnl
```

Cases to test: normal file, empty file, file with only `\n`, file without a final newline, invalid fd (`-1`), a directory, standard input, `BUFFER_SIZE` of 1, 42 and 10000000, and (bonus) alternating between several fds.

## Resources

### References

- `man 2 read`, `man 2 open`, `man 2 close`: system call documentation.
- `man 3 malloc`, `man 3 free`: dynamic allocation.
- [The Linux man-pages project](https://man7.org/linux/man-pages/)
- [Valgrind documentation](https://valgrind.org/docs/manual/manual.html)
- [AddressSanitizer (Clang documentation)](https://clang.llvm.org/docs/AddressSanitizer.html)
- *The C Programming Language*, Kernighan & Ritchie: static variables, storage duration, and the preprocessor.
- *Operating Systems: Three Easy Pieces* (OSTEP), free online: file descriptors, system calls, and virtual memory.

### Use of AI

AI was used as a **learning and review tool**. It was **not** used to write the project code.

- **Understanding concepts:** explanations of the memory layout (stack, heap, BSS, data), `static` variables, file descriptors and the kernel tables behind them (fd table, open file description, inode), the `read` and `open` system calls, user mode vs kernel mode, and macros.
- **Testing:** advice on how to use valgrind and AddressSanitizer, and a list of edge cases to test (empty file, no final newline, directory, high fd, different `BUFFER_SIZE` values).
- **Review and preparation:** a code review of `get_next_line_bonus.c` (error paths, leaks, bounds check on `fd`) and mock evaluation questions to prepare for the peer evaluation.
- **README:** help with the structure of this file.

All the code was written and tested by me, and I verified and understood every suggestion before using it.
