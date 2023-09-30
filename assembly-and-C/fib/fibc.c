unsigned int fibc(unsigned int n)
{
    unsigned int f=0, f0=0, f1=1, i=1;

    do
    {
        i++;
        f = f0 + f1; /* This is f(2), f(3), f(n-1) */
        f0 = f1;
        f1 = f;
    } while(i < n);

    return f;
}
