*This project has been created as part of the 42 curriculum by suyoun.*

# get_next_line

## Description

The **get_next_line** project is a foundational programming exercise that focuses on file reading and memory management in C. The goal of this project is to implement a function that reads a file (or standard input) line by line, returning one line at each call.

This project introduces important concepts such as:

* Static variables
* File descriptors
* Dynamic memory allocation
* Buffer management
* Handling partial reads

The function must efficiently manage input streams and ensure that each call returns the next line until the end of the file is reached.

---

## Instructions

### Compilation

To compile the project, use:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can adjust `BUFFER_SIZE` depending on your testing needs.

### Usage

Example of how to use the function:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Notes

* The function returns `NULL` when there is nothing left to read or an error occurs.
* Memory allocated for each line must be freed after use.
* The function must handle multiple file descriptors if the bonus part is implemented.

---

## Algorithm Explanation and Justification

The chosen algorithm relies on a **persistent buffer system using a static variable** to store leftover data between function calls.

### Core Idea

Each time `get_next_line` is called:

1. Read data from the file descriptor into a buffer.
2. Append this data to a static string (stash).
3. Check if a newline (`\n`) exists in the stash.
4. If found:

   * Extract the line up to and including the newline.
   * Save the remaining part for the next call.
5. If not found:

   * Continue reading until a newline or EOF is reached.

### Why This Algorithm?

* **Efficiency**: Avoids re-reading the file from the beginning.
* **Continuity**: The static variable preserves state between calls.
* **Flexibility**: Works with any buffer size and supports partial reads.
* **Scalability (Bonus)**: Easily extended to support multiple file descriptors using an array or linked structure.

### Complexity

* Time Complexity: O(n) per file (each byte is processed once)
* Space Complexity: O(n) depending on line size and buffer

This approach is optimal for streaming input where data is processed incrementally.

---

## Features

* Reads one line at a time from a file descriptor
* Supports any buffer size
* Handles standard input (stdin)
* Bonus: supports multiple file descriptors simultaneously

---

## Resources

### Documentation & References

* The C Programming Language – Kernighan & Ritchie
* POSIX `read()` manual
* 42 Intra subject documentation

### Helpful Links

* https://man7.org/linux/man-pages/man2/read.2.html
* https://cplusplus.com/reference/cstdio/

### AI Usage

AI tools (such as ChatGPT) were used in this project for:

* Clarifying concepts related to static variables and file descriptors
* Understanding edge cases (EoF handling, empty files, etc.)
* Reviewing algorithm design and improving readability
* Debugging assistance and code explanation

No AI-generated code was copied directly without understanding; all implementations were written and validated manually.

---

## Additional Notes

This project is a key step in mastering low-level I/O operations in C and builds a strong foundation for future projects involving file handling, parsing, and system programming.

---
