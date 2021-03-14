#include <stdio.h>

int main(int argc, char const *argv[])
{

	char buf[80];

	printf("Enter your first name: ");
	scanf("%79s\n", buf);

	printf("Hello %s\n", buf);

	return 0;
}
