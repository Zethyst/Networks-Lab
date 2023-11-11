#include <stdio.h> 
int main()
{
    int num = 0x12345678;   // Sample integer
    unsigned char lsb, msb; // Variables to store extracted bytes // Extract LSB (Least Significant Byte)
    lsb = num & 0xFF;       // Bitwise AND with 0xFF (0x000000FF) to isolate the last 8 bits // Extract MSB
    // (Most Significant Byte)
        msb = (num >> 24) & 0xFF; // Right shift by 24 bits to move the MSB to the least significant position
    printf("Number: 0x%08X\n", num);
    printf("LSB: 0x%02X\n", lsb);
    printf("MSB: 0x%02X\n", msb);
    return 0;
}