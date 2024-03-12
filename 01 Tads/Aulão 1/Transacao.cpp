#include <iostream>

using namespace std;

class Transacao
{
private:

    //Atributos
    string nome;
    string telefone;
    char tipo;
    float valor;
    int dia;

public:

    //Metodos
    Transacao()
    {
        nome = "-";
        telefone = "-";
        tipo = '-';
        valor = 0.0;
        dia = 0;
    }

    ~Transacao()
    {
        nome = "0";
        telefone = "0";
        tipo = '0';
        valor = 0.0;
        dia = 0;
    }

    void atualizarTransacao(string nome, string telefone, char tipo, float valor, int dia)
    {
        this->nome = nome;
        this->telefone = telefone;
        this->tipo = tipo;
        this->valor = valor;
        this->dia = dia;
    }

    void calcularMovimentacao(float &totalCompra, float totalVenda, char tipo, float valor)
    {
        //if ((this->tipo ==))
    }

    // int diaVendas(char);

    int getDia() { return dia; }
};

