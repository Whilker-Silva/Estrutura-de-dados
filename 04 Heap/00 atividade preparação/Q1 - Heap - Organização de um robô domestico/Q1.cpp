/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    alterado em 2023 by Renato
*/

#include <iostream>
#include <utility>   // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado
{
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2)
{
    return d1.energiaGasta > d2.energiaGasta;
}

bool operator<(dado d1, dado d2)
{
    return d1.energiaGasta < d2.energiaGasta;
}

ostream &operator<<(ostream &output, const dado &d)
{
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade << "]";
    return output;
}

class MaxHeap
{
private:
    dado *heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);

public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
};

MaxHeap::MaxHeap(int cap)
{
    capacidade = cap;
    heap = new dado[capacidade];
    tamanho = 0;
}

MaxHeap::~MaxHeap()
{
    delete[] heap;
}

int MaxHeap::pai(int i)
{
    return (i - 1) / 2;
}

int MaxHeap::esquerdo(int i)
{
    return 2 * i + 1;
}

int MaxHeap::direito(int i)
{
    return 2 * i + 2;
}

void MaxHeap::corrigeDescendo(int i)
{
    int esq = this->esquerdo(i);
    int dir = this->direito(i);
    int maior = i;

    if ((esq < tamanho) && (heap[esq] > heap[maior]))
    {
        maior = esq;
    }
    if ((dir < tamanho) && (heap[dir] > heap[maior]))
    {
        maior = dir;
    }
    if (maior != i)
    {
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i)
{
    int pai = this->pai(i);

    if (heap[i] > heap[pai])
    {
        swap(heap[i], heap[pai]);
        corrigeSubindo(pai);
    }
}

dado MaxHeap::retiraRaiz()
{
    if (tamanho < 1)
    {
        throw runtime_error("Erro ao retirar raiz");
    }

    dado aux = heap[0];
    swap(heap[0], heap[tamanho - 1]);
    tamanho--;
    corrigeDescendo(0);

    return aux;
}

void MaxHeap::insere(dado d)
{
    if (tamanho == capacidade)
    {
        throw runtime_error("Erro ao inserir");
    }

    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

void MaxHeap::imprime()
{
    if (tamanho < 1)
    {
        throw runtime_error("Heap vazia!");
    }
    
    for (int i = 0; i < tamanho; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}

int main()
{
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    MaxHeap meuHeap(capacidade);

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                meuHeap.insere(info);
                break;
            case 'r': // remover
                cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                break;
            case 'p': // limpar tudo
                meuHeap.imprime();
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
    cout << endl;
    return 0;
}