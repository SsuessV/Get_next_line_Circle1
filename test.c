#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int 	fd;
	char 	buffer[10];
	ssize_t bytes;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	bytes = read(fd, buffer, 1);
	buffer[bytes] = '\0';

	printf("Read: %s\n", buffer);

	close(fd);
	return (0);
}