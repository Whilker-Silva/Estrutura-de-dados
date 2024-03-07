#include <iostream>
using namespace std;

int main()
{

    int tam1, tam2;

    cin >> tam1;
    string *lista1 = new string[tam1];
    for (int i = 0; i < tam1; i++)
    {
        cin >> lista1[i];
    }

    cin >> tam2;
    string *lista2 = new string[tam2];
    for (int i = 0; i < tam2; i++)
    {
        cin >> lista2[i];
    }

    bool nada = true;
    for (int i = 0; i < tam1; i++)
    {
        bool achou = false;
        for (int j = 0; j < tam2; j++)
        {
            if (lista1[i] == lista2[j])
            {
                achou = true;
            }
        }

        if (!achou)
        {
            cout << lista1[i] << endl;
            nada = false;
        }
    }

    if (nada)
    {
        cout << "NADA";
    }

    return 0;
}