*This project has been created as part of the 42 curriculum by suyoun.*

# get_next_line

## Description

The **get_next_line** project is a foundational programming exercise that focuses on file reading and memory management in C.  
The **objective** of this project is to implement a function that reads a file (or standard input) line by line, returning one line at each call.

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

To compile the project, use the following command:  
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c` 

The BUFFER_SIZE value can be changed to test the function with different buffer sizes.  
Example:  
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c`  
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c`


### Usage

Include the get_next_line header file in your program and call the function with a valid file descriptor.

Example:
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
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

The function reads the file one line at a time and returns each line until the end of the file is reached. The returned string must be freed after each use to avoid memory leaks.

### Notes

* The function returns NULL when there is no more data to read or when an error occurs.
* Each line returned by get_next_line is dynamically allocated and must be freed by the caller after use.

---

## Algorithm Explanation and Justification

The chosen algorithm uses a persistent buffer system with a static variable to store leftover data between function calls.

When get_next_line is called, it first checks if there is any remaining data from the previous call. If a complete line is already available, it extracts and returns that line.  
Otherwise, it continues reading from the file descriptor and appends the new data to the buffer until a newline character is found or the end of file is reached.

Using a static variable allows the function to preserve unread data between calls without requiring the user to manage additional storage.  
This makes it possible to read a file line by line while keeping memory usage efficient.

For the bonus implementation, the static storage is extended to handle multiple file descriptors by maintaining an independent buffer for each file descriptor.

### Core Idea

Each time `get_next_line` is called:

1. Read data from the file descriptor into a temp_buf.
2. Append this data to a static string (storage/stash).
3. Check if a newline (`\n`) exists in the temp_buf.
4. If found:

   * Extract the line up to and including the newline.
   * Save the remaining part (in storage) for the next call.
5. If not found:

   * Continue reading until a newline or EOF is reached.

---

## Resources

* cppreference C documentation
* POSIX manual pages
* Linux man pages


### AI Usage

AI tools (such as ChatGPT) were used in this project for:

* Clarifying concepts related to static variables and file descriptors
* Understanding edge cases (EoF handling, empty files, etc.)
* Reviewing algorithm design and improving readability
* Debugging assistance and code explanation
* Helping write the main and test.txt file to test the codes

No AI-generated code was used directly. AI was only used for explanations, debugging assistance, and reviewing ideas.  
All code was written, tested, and validated manually.

---

## Additional Notes

This project is a key step in mastering low-level I/O operations in C and builds a strong foundation for future projects involving file handling, parsing, and system programming.

---
