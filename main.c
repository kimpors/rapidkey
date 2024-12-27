#include <stdio.h>
#include "cmdio.h"

int main(void)
{
	while (1)
	{
		if (cokbhit())
		{
			printf("ch: %c\n", cogetch());
		}
	}
	return 0;
}
