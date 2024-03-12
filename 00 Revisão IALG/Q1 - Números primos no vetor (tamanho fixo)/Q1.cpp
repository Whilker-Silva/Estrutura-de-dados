#include <iostream>

using namespace std;

bool ePrimo(int num);

int main()
{
    int algarismos[9];

    for (int i = 0; i < 9; i++)
    {
        cin >> algarismos[i];
    }

    for (int i = 0; i < 9; i++)
    {
        if (ePrimo(algarismos[i]))
        {
            cout << algarismos[i] << " " << i << endl;
        }
    }

    return 0;
}

bool ePrimo(int num)
{
    int div = 0;
    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            div++;
        }
    }

    if (div == 2)
    {
        return true;
    }

    return false;
}
