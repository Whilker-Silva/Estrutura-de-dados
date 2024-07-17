#include <iostream>
// #include <cstdlib>

using namespace std;

struct equipe
{
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class noh
{
    friend class lista;

private:
    equipe elenco; // poderia ser outro tipo de variável
    noh *proximo;

public:
    // noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d)
{
    elenco = d;
    proximo = NULL;
}

// lista dinamicamente encadeada
class lista
{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;

    void insereVazio(equipe elenco);
    bool vazia();

public:
    // construtores e destrutor
    lista();
    ~lista();

    void insereNoInicio(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);

    void removeNoFim();
    void removeNoInicio();

    void imprime();
    string procura(string valor);
};

// constrói uma lista inicialmente vazia
lista::lista()
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista()
{
    while (!vazia())
    {
        removeNoInicio();
    }

    delete primeiro;
    delete ultimo;
}

void lista::insereVazio(equipe elenco)
{
    noh *novo = new noh(elenco);

    primeiro = novo;
    ultimo = novo;

    tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco)
{
    if (vazia())
    {
        insereVazio(elenco);
    }

    else
    {
        noh *novo = new noh(elenco);

        novo->proximo = primeiro;
        primeiro = novo;

        tamanho++;
    }
}

// insere no final da lista
void lista::insereNoFim(equipe elenco)
{
    if (vazia())
    {
        insereVazio(elenco);
    }

    else
    {
        noh *novo = new noh(elenco);

        ultimo->proximo = novo;
        ultimo = novo;

        tamanho++;
    }
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco)
{
    if (posicao > tamanho)
    {
        throw runtime_error("Posicao Inexistente!");
    }

    if (vazia())
    {
        insereVazio(elenco);
    }

    else if (posicao = 0)
    {

        insereNoInicio(elenco);
    }

    else if (posicao == tamanho)
    {
        cout << posicao;
        insereNoFim(elenco);
    }

    else
    {

        noh *novo = new noh(elenco);

        noh *aux = primeiro;
        int posAux = 0;

        while (posAux < (posicao - 1))
        {
            aux = aux->proximo;
            posAux++;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;

        tamanho++;
    }
}

void lista::removeNoInicio()
{

    if (vazia())
    {
        throw runtime_error("Remocao em lista vazia!");
    }

    noh *aux = primeiro;
    primeiro = aux->proximo;
    delete aux;
    tamanho--;

    if (vazia())
    {
        ultimo = NULL;
    }
}

void lista::removeNoFim()
{
    if (vazia())
    {
        throw runtime_error("Remocao em lista vazia!");
    }

    noh *aux = primeiro;
    noh *anterior = NULL;

    while (aux->proximo != NULL)
    {
        anterior = aux;
        aux = aux->proximo;
    }

    if (anterior == NULL)
    {
        primeiro = NULL;
    }

    else
    {
        anterior->proximo = NULL;
    }

    delete ultimo;
    ultimo = anterior;
    tamanho--;
}

// verifica se a lista está vazia
bool lista::vazia()
{
    return (primeiro == NULL);
}

// procura a posição de um determinado elemento
string lista::procura(string valor)
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }

    noh *aux = primeiro;

    while (aux != NULL)
    {
        if (aux->elenco.nomeEquipe == valor)
        {
            equipe time = aux->elenco;
            return "(" + time.nomeEquipe + ", " + time.lider + ", " + time.linguagem + ", " + to_string(time.qtdMembros) + ")";
        }

        aux = aux->proximo;
    }

    return "Nao encontrado";
}

// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime()
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }

    noh *aux = primeiro;

    while (aux != NULL)
    {
        equipe time = aux->elenco;
        printf("(%s, %s, %s, %d)\n", time.nomeEquipe.c_str(), time.lider.c_str(), time.linguagem.c_str(), time.qtdMembros);
        aux = aux->proximo;
    }
}

int main()
{
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoInicio(info);
                break;

            case 'h': // inserir
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoFim(info);
                break;

            case 'm': // inserir
                cin >> posicao;
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNaPosicao(posicao, info);
                break;

            case 's': // procura
                cin >> nomeEquipe;

                cout << minhaLista.procura(nomeEquipe) << endl;
                break;

            case 'r': // remover
                minhaLista.removeNoInicio();
                break;

            case 'a': // remover
                minhaLista.removeNoFim();
                break;

            case 'p': // imprime tudo
                minhaLista.imprime();
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
