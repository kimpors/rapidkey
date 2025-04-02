#include <stdio.h>
#include "cmdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int pop(void);
void push(size_t val);
char *generate(char *s, int row, int col);

static char *sbuf = "this is a test\nthis is also test\nAnd this is also test";
static char *nums = "0123456789";
static char *chrs = "abcdefghijklmnopqrstuvwxyz";
static char *syms = "!@#$5^&*()";
static char *mixes = "0123456789abcdefghijklmnopqrstuvwxyz!@#$5^&*()";

int main(int argc, char *argv[])
{
	srand(time(NULL));
	char *option;
	int r, c;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "generate") == 0)
		{
			i = i < argc ? i + 1 : i;

			if (strcmp(argv[i], "numbers") == 0)
			{
				option = nums;
			}
			else if (strcmp(argv[i], "characters") == 0)
			{
				option = chrs;
			}
			else if (strcmp(argv[i], "symbols") == 0)
			{
				option = syms;
			}
			else if (strcmp(argv[i], "words") == 0)
			{
				printf("words generator\n");
				break;
			}
			else if (strcmp(argv[i], "mixed") == 0)
			{
				option = mixes;
			}

			if (!(i++ < argc - 1))
			{
				sbuf = generate(option, 10, 10);
			}
			else if (sscanf(argv[i], "%dx%d", &r, &c))
			{
				printf("row: %d\n", r);
				printf("col: %d\n", r);

				sbuf = generate(option, r, c);
				break;
			}
		}
		else if (strcmp(argv[i], "help") == 0)
		{
			printf("help page\n");
			exit(-1);
		}
		else
		{
			fprintf(stderr, "wrong argument\n");
			exit(-1);
		}
	}

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

#define TEXT_LEN 4096
char tbuf[TEXT_LEN];

int rand_range(int min, int max)
{
	return min + rand() % (max - min + 1);
}

char *generate(char *s, int row, int col)
{
	size_t len = strlen(s);

	if (row > 60) row = 60;
	if (col > 60) col = 60;

	int j = 0;
	int offset = 0;

	tbuf[row * col] = '\0';

	for (int i = 1; i <= row; i++)
	{
		while (j < col * i + offset)
		{
			tbuf[j++] = s[rand_range(0, len - 1)];
		}

		offset++;
		tbuf[j++] = '\n';
	}

	return tbuf;
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

