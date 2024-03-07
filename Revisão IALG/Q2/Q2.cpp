#include <iostream>

using namespace std;

int main()
{
    int tamA, tamB, tamC;
    int *conjuntoA, *conjuntoB, *conjuntoC;

    // preenche conjunto A
    cin >> tamA;
    conjuntoA = new int[tamA];
    for (int i = 0; i < tamA; i++)
    {
        cin >> conjuntoA[i];
    }

    // preenche conjunto A
    cin >> tamB;
    conjuntoB = new int[tamB];
    for (int i = 0; i < tamB; i++)
    {
        cin >> conjuntoB[i];
    }

    // Copia cojunto A para conjunto C
    tamC = tamA;
    conjuntoC = new int[tamC];
    for (int i = 0; i < tamC; i++)
    {
        conjuntoC[i] = conjuntoA[i];
    }

    for (int i = 0; i < tamB; i++)
    {
        // verifica se o elemento i do conjuto C é igual algum do C
        bool Diferente = true;
        for (int j = 0; j < tamC; j++)
        {
            if (conjuntoB[i] == conjuntoC[j])
            {
                Diferente = false;
            }
        }

        if (Diferente)
        {
            int *vetorAux = new int[tamC];
            for (int j = 0; j < tamC; j++)
            {
                vetorAux[j] = conjuntoC[j];
            }

            // desaloca conjuntoC
            delete[] conjuntoC;
            tamC++;
            conjuntoC = new int[tamC];

            // copia
            for (int j = 0; j < tamC - 1; j++)
            {
                conjuntoC[j] = vetorAux[j];
            }

            conjuntoC[tamC - 1] = conjuntoB[i];
        }
    }

    for (int i = 0; i < tamC; i++)
    {
        cout << conjuntoC[i] << " ";
    }

    return 0;
}