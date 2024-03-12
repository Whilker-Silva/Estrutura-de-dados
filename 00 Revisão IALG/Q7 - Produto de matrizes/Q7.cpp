#include <iostream>
using namespace std;

int main()
{

    int matrizA[4][5];
    int matrizB[5][2];
    int matrizC[4][2];

    // preenche matriz A
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> matrizA[i][j];
        }
    }

    // preenche matriz B
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> matrizB[i][j];
        }
    }

    // inicializa matriz c = 0
    // preenche matriz B
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrizC[i][j] = 0;
        }
    }

    // Realzai multiplicação das matrizes
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int x = 0; x < 5; x++)
            {
                matrizC[i][j] += matrizA[i][x] * matrizB[x][j];
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << matrizC[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}