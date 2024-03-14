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
    // Constrói pilha vazia.
    Pilha();
    // Destrutor que desaloca memória.
    ~Pilha();
    // Retira e retorna o valor que estiver no mPtTopo da pilha.
    // Escreve uma mensagem de erro se não for possível desempilhar.
    Dado Desempilhar(); // retorna o mPtTopo da Pilha.
    void RemocaoEspecial(int limIferior);
    void Ordernar();
    // Insere um valor na pilha.
    void Empilhar(const Dado &d);
    // Apagar todos os dados da pilha.
    void LimparTudo();
    // Imprime o valor que está no mPtTopo sem desempilhar.
    inline void
    Topo();
    // Informa se a pilha está Vazia.
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

    else
    {
        Noh *aux = mPtTopo;
        Dado d = aux->mDado;
        mPtTopo = mPtTopo->mProx;
        tamanho--;
        return d;
    }
}

void Pilha::RemocaoEspecial(int limIferior)
{
    Pilha *aux = new Pilha();

    while (!this->Vazia())
    {
        aux->Empilhar(this->Desempilhar());
        if (aux->mPtTopo->mDado.valor < limIferior)
        {
            imprimir_dado(aux->Desempilhar());
        }
    }

    while (!aux->Vazia())
    {
        this->Empilhar(aux->Desempilhar());
    }
    delete aux;
}

void Pilha::Ordernar()
{
    Pilha *aux = new Pilha();
    Dado dAux;

    while (!this->Vazia())
    {
        dAux = this->Desempilhar();

        if (aux->Vazia())
        {
            aux->Empilhar(dAux);
        }
        else
        {
            if (dAux.nome <= aux->mPtTopo->mDado.nome)
            {
                aux->Empilhar(dAux);
            }

            else
            {
                while (!aux->Vazia() && dAux.nome > aux->mPtTopo->mDado.nome)
                {
                    this->Empilhar(aux->Desempilhar());
                }
            }
        }
    }

    while (!aux->Vazia())
    {
        this->Empilhar(aux->Desempilhar());
    }
    delete aux;
}

void Pilha::LimparTudo()
{
    mPtTopo = NULL;
    tamanho = 0;
}

void Pilha::Topo()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }

    else
    {
        imprimir_dado(mPtTopo->mDado);
    }
}

bool Pilha::Vazia()
{
    if (tamanho == 0)
    {
        return true;
    }

    return false;
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
            case 'i': // inserir
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
            case 'o': // espiar
                pilha.Ordernar();
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