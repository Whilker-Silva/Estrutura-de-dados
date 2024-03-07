#include <iostream>
using namespace std;

void imprimeMatriz(int **matriz)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void voltaMatriz(int **matrizOriginal, int **matrizAlterada)
{

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrizAlterada[i][j] = matrizOriginal[i][j];
            matrizAlterada[i][j] = matrizOriginal[i][j];
        }
    }
}

int main()
{
    int **matrizAux = new int *[10];
    for (int i = 0; i < 10; i++)
    {
        matrizAux[i] = new int[10];
    }

    int **matriz = new int *[10];
    for (int i = 0; i < 10; i++)
    {
        matriz[i] = new int[10];
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cin >> matriz[i][j];
            matrizAux[i][j] = matriz[i][j];
        }
    }

    cout << "1." << endl;
    for (int j = 0; j < 10; j++)
    {
        matriz[1][j] = matriz[7][j];
        matriz[7][j] = matrizAux[1][j];
    }
    imprimeMatriz(matriz);
    voltaMatriz(matrizAux, matriz);

    cout << "2." << endl;
    for (int i = 0; i < 10; i++)
    {
        matriz[i][3] = matriz[i][9];
        matriz[i][9] = matrizAux[i][3];
    }
    imprimeMatriz(matriz);
    voltaMatriz(matrizAux, matriz);

    cout << "3." << endl;
    int j = 9;
    for (int i = 0; i < 10; i++)
    {
        matriz[i][i] = matriz[i][j];
        matriz[i][j] = matrizAux[i][i];
        j--;
    }
    imprimeMatriz(matriz);
    voltaMatriz(matrizAux, matriz);

    cout << "4." << endl;
    for (int j = 0; j < 10; j++)
    {
        matriz[4][j] = matriz[j][9];
        matriz[j][9] = matrizAux[4][j];
    }
    imprimeMatriz(matriz);

    return 0;
}
