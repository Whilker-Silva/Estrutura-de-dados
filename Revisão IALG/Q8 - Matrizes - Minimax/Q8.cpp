#include <iostream>
using namespace std;

int main()
{
    int matriz[10][10];
    int lMaior = 0;
    int cMaior = 0;

    int lMenor = 0;
    int cMenor = 0;

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
            if (matriz[i][j] > matriz[lMaior][cMaior])
            {
                lMaior = i;
                cMaior = j;
            }
        }
    }

    lMenor = lMaior;
    cMenor = cMaior;
    // procura menor da linha
    for (int i = 0; i < 10; i++)
    {
        if (matriz[lMenor][i] < matriz[lMenor][cMenor])
        {
            lMenor = i;
        }
    }

    cout << matriz[lMenor][cMenor] << endl;

    return 0;
}
