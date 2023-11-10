#include <stdio.h>

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    char byte1 = (num >> 24) & 0xFF;
    char byte2 = (num >> 16) & 0xFF;
    char byte3 = (num >> 8) & 0xFF;
    char byte4 = num & 0xFF;

    printf("Displaying the bytes in LITTLE ENDIAN\n");
    printf("Byte 1: %01X\n", byte4);
    printf("Byte 2: %01X\n", byte3);
    printf("Byte 3: %01X\n", byte2);
    printf("Byte 4: %01X\n", byte1);

    return 0;
}
