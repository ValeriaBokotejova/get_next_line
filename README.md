*This project has been created as part of the 42 curriculum by vbokotej*

# Get Next Line

## Description

Get Next Line is a C function that reads and returns a single line from a file descriptor each time it is called.

This project teaches:
- static variables
- dynamic memory allocation
- file reading using `read()`
- handling partial reads and string manipulation

Each call to get_next_line() returns the next line from a file (including the \n if present), until the end of file is reached.

Prototype:  
```c
char *get_next_line(int fd);
```

Return value
- A line read from the file (including \n)
- NULL when there is nothing left to read or an error occurs

---

### Behavior

- Returns one line per call
- A line ends with \n if it exists in the file
- Returns the last line even if it does not end with \n
- Returns NULL at end of file or on error
- Works with files and standard input. BUFFER_SIZE is defined at compile time using the -D flag

### How it works

The function uses a static variable (stash) to store leftover data between calls.

It reads from the file descriptor using read() and appends data to stash until a newline or EOF is found.

Then it:
1. Extracts the next line from stash
2. Updates stash by removing the returned line
3. Returns the extracted line

**Key Idea**

The `static` variable allows the function to remember previous reads, making it possible to return one line at a time.

---

## Structure

The project consists:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

Helper Functions:

- `ft_strlen` -> string length
- `ft_strchr` -> find newline
- `ft_strjoin` -> concatenate buffers
- `ft_get_line` -> extract one line
- `ft_new_stash` -> clean remaining data

---

## Instructions

### Usage

To use or test get_next_line(), you need:  
1) at least one source file  (.txt) to read from  
2) a main.c to call the implemented function

You can create a separate main.c file or temporarily add a main function to one of the project's .c files for testing purposes.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error: cannot open file\n");
		return (1);
	}
	line = get_next_line(fd);
	if (line)
		printf("Line 1: %s", line);
	free(line);
	line = get_next_line(fd);
	if (line)
		printf("Line 2: %s", line);
	free(line);
	line = get_next_line(fd);
	if (line)
		printf("Line 3: %s", line);
	free(line);
	close(fd);
	return (0);
}
```

### Compilation

Compile with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

You can change the buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 *.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 *.c
```

Or you can compile without the `-D` flag; 
in this case, `BUFFER_SIZE` will default to `42` as defined in the header:

```bash
cc -Wall -Wextra -Werror  main.c get_next_line.c get_next_line_utils.c
```

---

## Resources

**Documentation & References**

- man 2 read, man 3 malloc, man 3 free
- GNU C Library documentation
- 42 intra project subject: get_next_line

**AI tools** were used only for educational purposes, including:

- Help structure the README
- Clarifying the behavior of read() and file descriptors
- Understanding edge cases (EOF, BUFFER_SIZE variations)
- Reviewing memory management strategies

All code logic and implementation were written and understood manually.
