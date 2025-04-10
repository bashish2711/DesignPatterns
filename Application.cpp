#include<iostream>
#include<conio.h>
using namespace std;
typedef uint8_t U8;
typedef uint32_t U32;

U8     homeScreen[] = "__________________________________________________|    Welcome to ABC pizza center                 || What would you like to try today ?             ||1. Special pizza                                ||2. Onion Pizza                                  ||3. Capsicum Pizza                               ||4. Cheese Pizza                                 ||                 press number to select item    ||________________________________________________|";
U8 quantityScreen[] = "__________________________________________________|    Special Pizza        <ESC> for previous menu|| Select Size of Pizza                           ||1. Small             -  0  +                    ||2. Medium            -  0  +                    ||3. Large             -  0  +                    ||                          <ENT> to confirm      ||press number to select item + and - for quantity||________________________________________________|";
U8    orderScreen[] = "__________________________________________________|    Your Order Details   <ESC> for previous menu||                                                ||1. Small Special pizza: 2 Nos.                  ||2. Medium Onion pizza : 1 Nos.                  ||3. Large Cheeese pizza: 1 Nos.                  ||                          <ENT> for Order       ||                                                ||________________________________________________|";

void display(U8* str)
{
    for(U32 i=0; str[i] != 0;i++)
    {
        if((i%50) == 0)
        {
            putchar('\n');
        }
        putchar(str[i]);
    }
}
int main(void)
{
    U8 key = 0;
    display(homeScreen);
    cin >> key;
    if(key == '1')
    {
        display(quantityScreen);
    }
    cin >> key;
    if(key == '1')
    {
        display(orderScreen);
    }
    return 0;
}
