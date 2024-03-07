#include <iostream>

using namespace std;

void insereNaOrdem(int vetor[], int &tam, int numero)
{
    int posAtual = tam - 1;
    while (posAtual >= 0 && vetor[posAtual] > numero)
    {
        vetor[posAtual + 1] = vetor[posAtual];
        posAtual--;
    }

    vetor[posAtual + 1] = numero;
    tam++;
}

int main()
{
    int vetor[8];
    int tamAtual = 0;

    int numero;
    while (cin >> numero)
    {
        insereNaOrdem(vetor, tamAtual, numero);
        for (int i = 0; i < tamAtual; i++)
        {
            cout << vetor[i] << " ";
        }
        cout << endl;
    }
}
