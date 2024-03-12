#include <iostream>
using namespace std;

struct Familia
{
    string nome;
    int pai, mae, filho;
};

Familia *aumentaVetor(Familia *vetor, int &tam, int plus)
{
    Familia *aux;
    aux = new Familia[tam + plus];

    for (int i = 0; i < tam; i++)
    {
        aux[i] = vetor[i];
    }

    delete[] vetor;
    tam += plus;

    return aux;
}

int main()
{

    int tamVetorFamilia = 3;
    int qtdFamilias = 0;
    Familia *vetorFamilias;
    vetorFamilias = new Familia[tamVetorFamilia];

    int tamVetoriguais = 0;
    int qtdIguais = 0;
    Familia *idadesRepitidas;
    idadesRepitidas = new Familia[qtdIguais];

    string nomeAux;
    cin >> nomeAux;

    while (nomeAux != "FIM")
    {
        vetorFamilias[qtdFamilias].nome = nomeAux;
        cin >> vetorFamilias[qtdFamilias].pai;
        cin >> vetorFamilias[qtdFamilias].mae;
        cin >> vetorFamilias[qtdFamilias].filho;
        qtdFamilias++;

        cin >> nomeAux;

        if (nomeAux != "FIM" && qtdFamilias == tamVetorFamilia)
        {
            vetorFamilias = aumentaVetor(vetorFamilias, tamVetorFamilia, 3);
            cout << tamVetorFamilia << endl;
        }
    }

    for (int i = 0; i < qtdFamilias; i++)
    {
        bool naoRepitdo = true;

        // verifica se ja foi encontrado
        for (int j = 0; j < qtdIguais; j++)
        {
            if (vetorFamilias[i].nome == idadesRepitidas[j].nome)
            {
                naoRepitdo = false;
            }
        }

        if (naoRepitdo)
        {
            bool repetiu = false;

            for (int j = i + 1; j < qtdFamilias; j++)
            {
                if (vetorFamilias[i].filho == vetorFamilias[j].filho)
                {
                    if (!repetiu)
                    {
                        idadesRepitidas = aumentaVetor(idadesRepitidas, qtdIguais, 1);
                        idadesRepitidas[qtdIguais - 1] = vetorFamilias[i];

                        idadesRepitidas = aumentaVetor(idadesRepitidas, qtdIguais, 1);
                        idadesRepitidas[qtdIguais - 1] = vetorFamilias[j];

                        repetiu = true;
                    }

                    else
                    {
                        idadesRepitidas = aumentaVetor(idadesRepitidas, qtdIguais, 1);
                        idadesRepitidas[qtdIguais - 1] = vetorFamilias[j];
                    }
                }
            }
        }
    }

    if (qtdIguais > 0)
    {
        for (int i = 0; i < qtdIguais; i++)
        {
            cout << idadesRepitidas[i].nome << endl;
        }
    }
    else
    {
        cout << "NENHUM";
    }

    return 0;
}