#include <iostream>
using namespace std;

int main()
{
    int matriz[10][10];

    int maiorL = 0;
    int maiorC = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cin >> matriz[i][j];
        }
    }

    // procura maior
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (matriz[i][j] > matriz[maiorL][maiorC])
            {
                maiorL = i;
                maiorC = j;
            }
        }
    }

    int lMenor = maiorL;
    int cMenor = maiorC;

    // procura menor da linha
    for (int j = 0; j < 10; j++)
    {
        if (matriz[lMenor][j] < matriz[lMenor][cMenor])
        {
            cMenor = j;
        }
    }

    cout << matriz[lMenor][cMenor] << endl;
    cout << lMenor << " " << cMenor;

    return 0;
}
