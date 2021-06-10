int main(void)
{
    int *a,*b;
    a = (int *)0x5566;
    b = (int *)0x5570;
    printf("%d %d %d %d %d\n", a, b, (int)a+(int)b, a+(int)b, sizeof(int *));
    printf("%d\n", a - b);
    printf("%d\n", ((int)b - (int)a)/sizeof(int *));
    return 0;
}