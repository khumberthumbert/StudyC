#include <stdio.h>

int main(void)
{
	int a = 0, b = 0;
	scanf_s("%d %d", &a, &b);
	printf("%d", a - b);

	return 0;
}