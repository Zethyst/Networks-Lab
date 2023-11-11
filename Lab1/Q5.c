#include <stdio.h>

// Function to check endianness of the host machine
int isLittleEndian() {
    int num = 1;
    return *((char*)&num);
}

// Function to swap endianness of an integer
int swapEndianness(int num) {
    return ((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) |
           ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000);
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("The host machine is %s endian.\n", isLittleEndian() ? "Little" : "Big");

    printf("Content of each byte location:\n");
    for (int i = 0; i < sizeof(int); i++) {
        unsigned char byte = (num >> (i * 8)) & 0xFF;
        printf("Byte %d: %02X\n", i, byte);
    }

    int swappedNum = swapEndianness(num);
    printf("Converted number with swapped endianness: %d\n", swappedNum);

    return 0;
}
 