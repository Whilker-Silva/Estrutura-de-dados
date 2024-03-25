/* Classe fila estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

const int FILAVAZIA = -1;
const int CAPACIDADE_FILA = 6;

struct Dado
{
    string nome;
    string assunto;
    char tipo;
    int nProcesso;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado &umDado)
{
    cout << "Você já implementou o método para imprimir dados???" << endl;
}

class Fila
{
private:
    Dado *mFila;
    int posPrimeiro, posUltimo;

public:
    Fila();
    ~Fila();

    Dado Desenfileirar();
    void Enfileirar(const Dado &d);
    void LimparTudo();
    inline void PrimeiroDaFila();
    inline bool Vazia();
    inline bool Cheia();
};

Fila::Fila()
{
    mFila = new Dado[CAPACIDADE_FILA];
    posPrimeiro = FILAVAZIA;
    posUltimo = FILAVAZIA;
}

Fila::~Fila()
{
    this->LimparTudo();
    delete[] mFila;
}

void Fila::Enfileirar(const Dado &d)
{
    if (this->Cheia())
    {
        throw runtime_error("Erro: fila cheia!");
    }
    // completar com código necessário caso fila não esteja vazia
}

Dado Fila::Desenfileirar()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: fila vazia!");
    }
    // completar com código necessário caso fila não esteja vazia
}

void Fila::LimparTudo()
{
}

void Fila::PrimeiroDaFila()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: fila vazia!");
    }
    // completar com código necessário caso fila não esteja vazia
}

bool Fila::Vazia()
{
}

bool Fila::Cheia()
{
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
            case 'i':
                cin >> info.nome >> info.assunto >> info.tipo >> info.nProcesso;
                fila.Enfileirar(info);
                break;
            case 'r':
                imprimir_dado(fila.Desenfileirar());
                break;
            case 'l':
                fila.LimparTudo();
                break;
            case 'e':
                if (!fila.Vazia())
                    fila.PrimeiroDaFila();
                else
                    cout << "Erro: fila vazia!" << endl;
                break;
            case 'f':
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