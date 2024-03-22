/* Classe pilha estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

struct Dado
{
    string nome;
    char tipo;
    int valor;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado &umDado)
{
    cout << "Nome: " << umDado.nome << " ";
    cout << "Tipo: " << umDado.tipo << " ";
    cout << "Valor: " << umDado.valor << endl;
}

class Pilha
{
private:
    Dado *mPilha;
    int posTopo;

public:
    Pilha();
    ~Pilha();

    Dado Desempilhar();
    void Empilhar(const Dado &d);
    void LimparTudo();
    inline void Topo();
    inline bool Vazia();
    inline bool Cheia();
};

Pilha::Pilha()
{
    mPilha = new Dado[TAMANHOPILHA];
    posTopo = PILHAVAZIA;
}

Pilha::~Pilha()
{
    this->LimparTudo();
    delete[] mPilha;
}

void Pilha::Empilhar(const Dado &d)
{
    if (this->Cheia())
    {
        Pilha *pAux = new Pilha;
        Dado dAux;

        // transfere todos itens da pilha principal para a auxiliar
        while (!this->Vazia())
        {
            pAux->Empilhar(this->Desempilhar());
        }

        // imprime dado mais antigo
        dAux = pAux->Desempilhar();
        imprimir_dado(dAux);

        // volta dados para pilha principal
        while (!pAux->Vazia())
        {
            this->Empilhar(pAux->Desempilhar());
        }

        delete pAux;
    }

    posTopo++;
    mPilha[posTopo] = d;
}

Dado Pilha::Desempilhar()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }

    Dado dadoAux = mPilha[posTopo];
    posTopo--;
    return dadoAux;
}

void Pilha::LimparTudo()
{
    while (!Vazia())
    {
        Desempilhar();
    }
}

void Pilha::Topo()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }
    imprimir_dado(mPilha[posTopo]);
}

bool Pilha::Vazia()
{
    return (posTopo == PILHAVAZIA) ? true : false;
}

bool Pilha::Cheia()
{
    return (posTopo == TAMANHOPILHA - 1) ? true : false;
}

int main()
{
    Pilha pilha;
    Dado info;
    char comando;
    char somaTipo;
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
            case 'r': // remover
                imprimir_dado(pilha.Desempilhar());
                break;
            case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
            case 'e': // espiar
                if (!pilha.Vazia())
                    pilha.Topo();
                else
                    cout << " Pilha vazia!" << endl;
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