#include <iostream>
using namespace std;

int main()
{
    int tabuleiro[8][8];
    int torreI, torreJ;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> tabuleiro[i][j];
        }
    }

    // procura torre
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tabuleiro[i][j] == 1)
            {
                torreI = i;
                torreJ = j;
            }
        }
    }

    // procura peça para cima
    for (int i = torreI - 1; i >= 0; i--)
    {
        if (tabuleiro[i][torreJ] == 2)
        {
            cout << i << " " << torreJ << endl;
            i = -1;
        }
    }

    // procura peça a esquerda
    for (int j = torreJ - 1; j >= 0; j--)
    {
        if (tabuleiro[torreI][j] == 2)
        {
            cout << torreI << " " << j << endl;
            j = -1;
        }
    }

    // procura peça a direita
    for (int j = torreJ + 1; j < 8; j++)
    {
        if (tabuleiro[torreI][j] == 2)
        {
            cout << torreI << " " << j << endl;
            j = 8;
        }
    }

    // procura peça para baixo
    for (int i = torreI + 1; i < 8; i++)
    {
        if (tabuleiro[i][torreJ] == 2)
        {
            cout << i << " " << torreJ << endl;
            i = 8;
        }
    }

    return 0;
}