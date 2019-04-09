int ans1;
long int ans2;

int test1(int a, int b)
{
    int ret;
    ret=a-b;
    return ret;
}

int test2(int a, int b, int c)
{
    int ret;
    ret=a-b-(c-1);
    return ret;
}

long int test3(long int a, long int b)
{
    long int ret;
    ret=a-b;
    return ret;
}

long int test4(long int a, long int b, long int c)
{
    long int ret;
    ret=a-b-(c-1);
    return ret;
}

int main(void)
{
    ans1=test1(0x123,0x456);
    ans1=test2(0x123,0x456,0x789);
    ans2=test3(0x123,0x456);
    ans2=test4(0x123,0x456,0x789);
}