int globalsum=0;

void test1(void)
{
    int localsum=0;
    int i;
    for (i=1;i<=10;i++) {
        localsum+=i;
    }
}
	int test2(void)
{
    int localsum=0;
    int i;
    for (i=1;i<=10;i++) {
        localsum+=i;
    }
    return localsum;
}
void test3(void)
{
    static int staticsum;
    int i;
    for (i=1;i<=10;i++) {
        staticsum+=i;
    }
}

void test4(void)
{
    int i;
    for (i=1;i<=10;i++) {
        globalsum+=i;
    }
}
