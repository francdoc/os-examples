// This implements the example on p. 385 in PLP

#include <stdio.h>
#include <string.h>

#define DEBUG (0)

void globalfunct_A(void)
{

    void localfunct_E_in_A(void)
    {
        if(DEBUG) printf("local function: E nested in A\n");
    }

    void localfunct_B_in_A(void)
    {

        void localfunct_C_in_B(void)
        {
            if(DEBUG) printf("local function: C nested in B nested in A\n");
        }

        void localfunct_D_in_B(void)
        {
            if(DEBUG) printf("local function: D nested in B nested in A\n");
        }

        if(DEBUG) printf("local function: B nested in A\n");
   
        // B can see everything it contains and that contains it - A,B,C,D,E

        // recurses if called
        // if(DEBUG) globalfunct_A();
        // if(DEBUG) localfunct_B_in_A();

        if(DEBUG) localfunct_C_in_B();
        if(DEBUG) localfunct_D_in_B();
        if(DEBUG) localfunct_E_in_A();

    }

    if(DEBUG) printf("global function: A\n");
    if(DEBUG) localfunct_B_in_A();

}

void main(void)
{
    // main can only see A
    if(DEBUG) globalfunct_A();
}
