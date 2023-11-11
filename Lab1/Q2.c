#include <stdio.h>

struct pkt
{
    char ch1;
    char ch2[2];
    char ch3;
};

int main()
{
    struct pkt myStruct;
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    char byte1 = (num >> 24) & 0xFF;
    char byte2 = (num >> 16) & 0xFF;
    char byte3 = (num >> 8) & 0xFF;
    char byte4 = num & 0xFF;

    myStruct.ch1 = byte4;
    myStruct.ch2[0] = byte3;
    myStruct.ch2[1] = byte2;
    myStruct.ch3 = byte1;
    // myStruct.ch1 = num % 10 + '0';
    // num /= 10;

    // myStruct.ch2[0] = num % 10 + '0';
    // num /= 10;
    // myStruct.ch2[0] = num % 10 + '0';

    // myStruct.ch3 = num % 10 + '0';

    printf("Digit in the 1st Sturcture: %01X\n", myStruct.ch1);
    printf("Digit in the 2nd & 3rd Sturcture:: %01X,%01X\n", myStruct.ch2[0], myStruct.ch2[1]);
    printf("Digit in the 4th Sturcture:: %01X\n", myStruct.ch3);

    int result=0;
    result |= myStruct.ch1;
    result |= myStruct.ch2[0] << 8;
    result |= myStruct.ch2[1] <<16;
    result |= myStruct.ch3 <<24;

    printf("\nRegenerated Number: %u\n", result);

    // char originalNum[3] = myStruct.ch1 + myStruct.ch2[0] + myStruct.ch3;
    // int originalNum =
    //     (myStruct.ch3 - '0') * 100 + (myStruct.ch2[0] - '0') * 10 + myStruct.ch1 - '0';
    // printf("Original number formed from the structure members: %s\n", originalNum);

    return 0;
}
