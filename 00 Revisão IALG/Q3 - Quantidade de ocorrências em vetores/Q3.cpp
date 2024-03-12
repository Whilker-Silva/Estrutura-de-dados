#include <iostream>

using namespace std;

int main()
{
    int tam1, tam2, tam3;

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

    cin >> tam3;
    string *lista3 = new string[tam3];
    for (int i = 0; i < tam3; i++)
    {
        cin >> lista3[i];
    }

    for (int i = 0; i < tam3; i++)
    {
        int qtd = 0;

        for (int j = 0; j < tam1; j++)
        {
            if (lista3[i] == lista1[j])
            {
                qtd++;
            }
        }

        for (int j = 0; j < tam2; j++)
        {
            if (lista3[i] == lista2[j])
            {
                qtd++;
            }
        }

        cout << qtd << " ";
    }

    return 0;
}