int div(int a, int b)
{
    int d;

    d=a/b;

    return d;
}

int lcmc(int a, int b)
{
    int lcm;

    lcm = (a * b) / (gcdc(a,b));

    return lcm;
}

int gcdc(int a, int b)
{
    while(a != b) 
    {
        if(a > b)
            a = a - b;
        else
            b = b - a; 
    }

    return a;
}
