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
    cout << "nome: " << umDado.nome;
    cout << " assunto: " << umDado.assunto;
    cout << " tipo: " << umDado.tipo;
    cout << " numero do processo: " << umDado.nProcesso << endl;
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
    delete[] mFila;
}

void Fila::Enfileirar(const Dado &d)
{
    if (this->Cheia())
    {
        throw runtime_error("Erro: fila cheia!");
    }

    if (this->Vazia())
    {
        posPrimeiro++;
    }

    posUltimo = (posUltimo + 1) % CAPACIDADE_FILA;
    mFila[posUltimo] = d;
}

Dado Fila::Desenfileirar()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: fila vazia!");
    }

    Dado aux = mFila[posPrimeiro];

    if (posPrimeiro == posUltimo)
    {
        posPrimeiro = FILAVAZIA;
        posUltimo = FILAVAZIA;
    }
    else
    {
        posPrimeiro = (posPrimeiro + 1) % CAPACIDADE_FILA;
    }

    return aux;
}

void Fila::LimparTudo()
{
    while (!this->Vazia())
    {
        this->Desenfileirar();
    }
}

void Fila::PrimeiroDaFila()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: fila vazia!");
    }

    imprimir_dado(mFila[posPrimeiro]);
}

bool Fila::Vazia()
{
    return (posPrimeiro == FILAVAZIA) ? true : false;
}

bool Fila::Cheia()
{
    return (((posUltimo + 1) % CAPACIDADE_FILA) == posPrimeiro) ? true : false;
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
                fila.PrimeiroDaFila();
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