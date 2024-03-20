/* Classe Fila encadeada
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
    string premio;
    char tipo;
    int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado &umDado)
{
    cout << "Nome: " << umDado.nome;
    cout << " Premio: " << umDado.premio;
    cout << " Tipo: " << umDado.tipo;
    cout << " tempo: " << umDado.tempo << endl;
}

class Noh
{
    friend class Fila;

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

class Fila
{
public:
    // Constrói Fila vazia.
    Fila();
    // Destrutor que desaloca memória.
    ~Fila();
    // Retira e retorna o elemento que estiver na frente da Fila.
    // Escreve uma mensagem de erro se não for possível desenfileirar.
    Dado Desenfileirar();
    // Insere um elemento na Fila.
    void Enfileirar(const Dado &d);
    // Apagar todos os dados da Fila.
    void LimparTudo();
    // Retorna o elemento que está na frente da Fila, sem desenfileirar.
    inline void Primeiro();
    // Informa se a Fila está Vazia.
    inline bool Vazia();

private:
    Noh *mPtPrimeiro;
    Noh *mPtrUltimo;
    int tamanho;
};

Fila::Fila()
{
    mPtPrimeiro = NULL;
    mPtrUltimo = NULL;
    tamanho = 0;
}

Fila::~Fila()
{
    this->LimparTudo();
    delete mPtPrimeiro;
    delete mPtrUltimo;
}

void Fila::Enfileirar(const Dado &d)
{
    Noh *novo = new Noh(d);

    if (this->Vazia())
    {
        mPtPrimeiro = novo;
    }
    else
    {
        mPtrUltimo->mProx = novo;
    }

    mPtrUltimo = novo;
    tamanho++;
}

Dado Fila::Desenfileirar()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: Fila vazia!");
    }
    else
    {
        Noh *auxNoh = this->mPtPrimeiro;
        Dado auxDado = auxNoh->mDado;

        mPtPrimeiro = mPtPrimeiro->mProx;
        delete auxNoh;
        tamanho--;

        if (this->Vazia())
        {
            mPtrUltimo = NULL;
        }
        return auxDado;
    }
}

void Fila::LimparTudo()
{
    while (!this->Vazia())
    {
        this->Desenfileirar();
    }
}

void Fila::Primeiro()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: Fila vazia!");
    }
    else
    {
        imprimir_dado(this->mPtPrimeiro->mDado);
    }
}

bool Fila::Vazia()
{
    if (tamanho == 0)
    {
        return true;
    }
    return false;
}

int main()
{
    Fila fila;
    Dado info;
    char comando;
    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                fila.Enfileirar(info);
                break;
            case 'r': // remover
                imprimir_dado(fila.Desenfileirar());
                break;
            case 'l': // limpar tudo
                fila.LimparTudo();
                break;
            case 'e': // espiar
                fila.Primeiro();
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
    while (!fila.Vazia())
    {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}