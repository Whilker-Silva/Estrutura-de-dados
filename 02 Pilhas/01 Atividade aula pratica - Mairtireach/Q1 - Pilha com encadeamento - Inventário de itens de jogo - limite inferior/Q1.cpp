/* Classe pilha encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado
{
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado &umDado)
{
    cout << "Nome: " << umDado.nome << " Tipo: " << umDado.tipo << " Valor: " << umDado.valor << endl;
}

class Noh
{
    friend class Pilha;

private:
    Dado mDado; // poderia ser outro tipo de variável
    Noh *mProx;

public:
    Noh(Dado v)
    {
        mDado = v;
        mProx = NULL;
    }
};

class Pilha
{
public:
    Pilha();
    ~Pilha();

    void Empilhar(const Dado &d);
    Dado Desempilhar(); // retorna o mPtTopo da Pilha.
    void RemocaoEspecial(int limIferior);
    void LimparTudo();
    inline void Topo();
    inline bool Vazia();

private:
    Noh *mPtTopo;
    int tamanho;
};

Pilha::Pilha()
{
    mPtTopo = NULL;
    tamanho = 0;
}

Pilha::~Pilha()
{
    this->LimparTudo();
    delete mPtTopo;
}

void Pilha::Empilhar(const Dado &d)
{
    Noh *novoNoh = new Noh(d);
    novoNoh->mProx = mPtTopo;
    mPtTopo = novoNoh;
    tamanho++;
}

Dado Pilha::Desempilhar()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }

    Noh *nAux = mPtTopo;
    Dado dAux = nAux->mDado;

    mPtTopo = mPtTopo->mProx;
    tamanho--;

    delete nAux;
    return dAux;
}

void Pilha::RemocaoEspecial(int limIferior)
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }

    Pilha *pAux = new Pilha();
    Dado dAux;

    while (!this->Vazia())
    {
        dAux = this->Desempilhar();
        if (dAux.valor < limIferior)
        {
            imprimir_dado(dAux);
        }

        else
        {
            pAux->Empilhar(dAux);
        }
    }

    while (!pAux->Vazia())
    {
        this->Empilhar(pAux->Desempilhar());
    }

    delete pAux;
}

void Pilha::LimparTudo()
{
    while (!this->Vazia())
    {
        this->Desempilhar();
    }
}

void Pilha::Topo()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }

    imprimir_dado(mPtTopo->mDado);
}

bool Pilha::Vazia()
{
    return (tamanho == 0) ? 1 : 0;
}

int main()
{
    Pilha pilha;
    Dado info;
    int limInferior;
    char comando;
    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserira
                cin >> info.nome >> info.tipo >> info.valor;
                pilha.Empilhar(info);
                break;
            case 'x':
                cin >> limInferior;
                pilha.RemocaoEspecial(limInferior);
                break;
            case 'r': // remover
                imprimir_dado(pilha.Desempilhar());
                break;
            case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
            case 'e': // espiar
                pilha.Topo();
                break;
            case 'f': // finalizar
                // checado no do-while
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução

    while (!pilha.Vazia())
    {
        imprimir_dado(pilha.Desempilhar());
    }
    return 0;
}