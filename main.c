#include <stdio.h>
#include "cmdio.h"

static char *sbuf = "this is a test";

int main(void)
{
	char *ps = sbuf;
	size_t row = 1, col = 1;

	coclear();
	printf("%s", ps);
	comove(row, col);


	int ch;
	while (*ps)
	{
		if (cokbhit())
		{
			ch = cogetch();
			if (ch == '\b' && ps - sbuf > 0)
			{
				printf("\033[0m");
				putchar(*(ps--));
				comove(row, --col);
				continue;
			}

			ch == *ps
				? printf("\033[32m")
				: printf("\033[31m");

			putchar(*(ps++));
			comove(row, ++col);
		}
	}

	printf("\033[0m");
	return 0;
}
