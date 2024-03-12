#include <iostream>
using namespace std;

int main()
{

    int l, c;
    int **matriz;

    cin >> l >> c;

    // cria matriz
    matriz = new int *[l];
    for (int i = 0; i < l; i++)
    {
        matriz[i] = new int[c];
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> matriz[i][j];
        }
    }

    for (int j = 0; j < c; j++)
    {
        for (int i = 0; i < l; i++)
        {
            cout << matriz[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}