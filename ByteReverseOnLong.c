#include <stdio.h>
unsigned long BitReverse(unsigned long Kx);
int main()
{
    unsigned long seed = 0x12345678;
    unsigned long key;
    
    unsigned char* seed_ptr;
    seed_ptr = &seed;
    
    key = (unsigned long)(((*seed_ptr) << 24)|(*(seed_ptr+1) << 16)|(*(seed_ptr+2) << 8)|*(seed_ptr+3)); 
    printf("seed = %x key = %x", seed , key);
    key = (seed >> 24) | (seed << 24); 
    printf("seed = %x key = %x", seed , key);

    return 0;
}