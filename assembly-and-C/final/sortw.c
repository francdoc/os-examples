#include "sortw.h"


int array[] = {4, 6, 1, 23, 66, 29, 37, 58, 8, 22};

void print_array(int a[], int n)
{
    int i;

    for(i=0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    print_array(array, sizeof(array)/sizeof(int));
    sorta(array, sizeof(array)/sizeof(int));
    print_array(array, sizeof(array)/sizeof(int));
}
