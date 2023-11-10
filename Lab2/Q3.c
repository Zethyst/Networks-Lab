#include <stdio.h>
#include <string.h>

void swap(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}
int main(int argc, char *argv[])
{

    if (argc == 1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name\n");

    if (argc != 3)
    {
        printf("Please provide exactly two strings as command-line arguments.\n");
        return 1;
    }

    char *str1 = argv[1];
    char *str2 = argv[2];

    printf("Before swapping: str1 = %s, str2 = %s\n", str1, str2);

    swap(&str1, &str2);

    printf("After swapping: str1 = %s, str2 = %s\n", str1, str2);

    return 0;
}
