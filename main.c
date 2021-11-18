#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd = open("tmp.txt", O_RDONLY);
	char *s;

	s = get_next_line(fd);
	printf("%s||", s);
	free(s);
	s = get_next_line(fd);
	printf("%s||", s);
	free(s);
	s = get_next_line(fd);
	printf("%s||", s);
	free(s);
	s = get_next_line(fd);
	printf("%s||", s);
	free(s);
}
