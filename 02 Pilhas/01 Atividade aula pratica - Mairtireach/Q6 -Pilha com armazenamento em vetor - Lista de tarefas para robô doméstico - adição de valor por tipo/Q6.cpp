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
    // Constrói pilha vazia.
    Pilha();
    // Destrutor que desaloca memória.
    ~Pilha();
    // Retira e retorna o valor que estiver no topo da pilha.
    Dado Desempilhar();
    // Insere um elemento na pilha.
    void Empilhar(const Dado &d);
    // Apagar todos os dados da pilha.
    void LimparTudo();
    // Imprime o valor que está no topo sem desempilhar.
    inline void Topo();
    // Informa se a pilha está Vazia.
    inline bool Vazia();
    // Informa se a pilha está Cheia.
    inline bool Cheia();
    //
    inline void soma(char t);
};

Pilha::Pilha()
{
    mPilha = new Dado[TAMANHOPILHA];
    posTopo = PILHAVAZIA;
}

Pilha::~Pilha()
{
    delete[] mPilha;
}

void Pilha::Empilhar(const Dado &d)
{
    if (this->Cheia())
    {
        throw runtime_error("Erro: pilha cheia!");
    }
    else
    {
        posTopo++;
        mPilha[posTopo] = d;
    }
}

Dado Pilha::Desempilhar()
{
    if (this->Vazia())
    {
        throw runtime_error("Erro: pilha vazia!");
    }

    Dado topo = mPilha[posTopo];
    posTopo--;
    return topo;
}

void Pilha::soma(char t)
{
    int soma = 0;
    Dado dadoAux;
    Pilha *pilhaAux = new Pilha;

    while (!this->Vazia())
    {
        dadoAux = this->Desempilhar();

        if (dadoAux.tipo == t)
        {
            soma += dadoAux.valor;
        }
    }

    while (!pilhaAux->Vazia())
    {
        this->Empilhar(pilhaAux->Desempilhar());
    }

    delete pilhaAux;

    cout << soma << endl;
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
    if (posTopo == PILHAVAZIA)
    {
        return true;
    }

    return false;
}

bool Pilha::Cheia()
{
    if (posTopo == TAMANHOPILHA - 1)
    {
        return true;
    }

    return false;
}

int main()
{
    Pilha pilha;
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
            case 's':
                char tipo;
                cin >> tipo;
                pilha.soma(tipo);
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