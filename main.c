#include <stdio.h>
#include "cmdio.h"
#include <stdlib.h>
#include <string.h>

int pop(void);
void push(size_t val);
static char *sbuf = "this is a test\nthis is also test\nAnd this is also test";

int main(int argc, char *argv[])
{
	int r, c;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "generate") == 0)
		{
			i = i < argc ? i + 1 : i;

			if ( strcmp(argv[i], "numbers") == 0)
			{
				printf("numbers generator\n");
			}
			else if (strcmp(argv[i], "symbols") == 0)
			{
				printf("symbols generator\n");
			}
			else if (strcmp(argv[i], "words") == 0)
			{
				printf("words generator\n");
			}
			else if (strcmp(argv[i], "mixed") == 0)
			{
				printf("mixed generator\n");
			}

			if (!(i++ < argc - 1)) break;

			if (sscanf(argv[i], "%dx%d", &r, &c))
			{
				printf("row: %d\n", r);
				printf("col: %d\n", r);
			}
		}
		else if (strcmp(argv[i], "help") == 0)
		{
			printf("help page\n");
			break;
		}
		else
		{
			fprintf(stderr, "wrong argument\n");
			exit(-1);
		}
	}

	return 0;

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
				comove(row, col--);
				putchar(*ps--);
				comove(row, col);
				putchar(*ps);
				comove(row, col);

				if (*ps == '\n')
				{
					row = row > 0 ? row - 1 : row;
					col = pop();
					printf("\033[0m");
					comove(row, col--);
					putchar(*ps--);
					comove(row, col);
					putchar(*ps);
					comove(row, col);
				}
				continue;
			}
			else if (ch == '\b' && ps - sbuf == 0)
			{
				continue;
			}

			ch == *ps
				? printf("\033[32m")
				: printf("\033[31m");

			putchar(*(ps++));
			comove(row, ++col);

			if (*ps == '\n')
			{
				push(col);
				comove(++row, col=0);
			}
		}
	}

	printf("\033[0m");
	return 0;
}

#define BUF_LEN 255
struct {
	size_t curr;
	size_t buf[BUF_LEN];
} indices;

void push(size_t val)
{
	if (indices.curr > BUF_LEN - 1) exit(-1);
	indices.buf[indices.curr++] = val;
}

int pop(void)
{
	if (indices.curr < 1) exit(-1);
	return indices.buf[--indices.curr];
}

