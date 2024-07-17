#include <iostream>

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

    void removeTodos();
    void imprimeReversoAux(noh *umNoh);
    void printValores(equipe elenco);
    inline bool vazia();

public:
    // construtores e destrutor
    lista();
    lista(const lista &umaLista);
    ~lista();

    // sobrecarga do operador de atribuição
    lista &operator=(const lista &umaLista);

    // inserção, remoção e procura
    void insereVazia(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);

    void removeNoFim();
    void removeNoInicio();

    int procura(string valor); // retorna a posição do nó com va

    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
};

// constrói uma lista inicialmente vazia
lista::lista()
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
lista::lista(const lista &umaLista)
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;

    *this = umaLista;
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista()
{
    removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos()
{
    while (primeiro != NULL)
    {
        removeNoInicio();
    }

    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// sobrecarga do operador de atribuição
lista &lista::operator=(const lista &umaLista)
{
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh *aux = umaLista.primeiro;

    while (aux != NULL)
    {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}

void lista::insereVazia(equipe elenco)
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
        insereVazia(elenco);
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
        insereVazia(elenco);
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
        throw runtime_error("Posição Inexistente!");
    }

    if (vazia())
    {
        insereVazia(elenco);
    }

    else if (posicao == 0)
    {
        insereNoInicio(elenco);
    }

    else if (posicao == tamanho)
    {
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
        throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = primeiro;
    primeiro = aux->proximo;

    if (primeiro == NULL)
    {
        ultimo = NULL;
    }

    tamanho--;

    delete aux;
}

void lista::removeNoFim()
{
    if (vazia())
    {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = primeiro;
    noh *anterior = NULL;

    while (aux->proximo != NULL)
    {
        anterior = aux;
        aux = aux->proximo;
    }

    if (anterior != NULL)
    {
        anterior->proximo = NULL;
    }

    else
    {
        primeiro = NULL;
    }

    ultimo = anterior;
    tamanho--;

    delete aux;
}

// procura a posição de um determinado elemento
int lista::procura(string valor)
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }

    noh *aux = primeiro;
    int posAux = 0;

    while (aux != NULL)
    {
        if (aux->elenco.nomeEquipe == valor)
        {
            return posAux;
        }

        aux = aux->proximo;
        posAux++;
    }

    throw runtime_error("Nao encontrado");
}

void lista::printValores(equipe elenco)
{

    printf("(%s, %s, %s, %d)\n", elenco.nomeEquipe.c_str(), elenco.lider.c_str(), elenco.linguagem.c_str(), elenco.qtdMembros);
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
        printValores(aux->elenco);
        aux = aux->proximo;
    }
}

void lista::imprimeReverso()
{
    imprimeReversoAux(primeiro);
}

void lista::imprimeReversoAux(noh *umNoh)
{
    if (umNoh != NULL)
    {
        imprimeReversoAux(umNoh->proximo);
        printValores(umNoh->elenco);
    }
}

// verifica se a lista está vazia
inline bool lista::vazia()
{
    return (primeiro == NULL);
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
            case 's': // remover
                cin >> nomeEquipe;
                cout << minhaLista.procura(nomeEquipe) << endl;
                break;
            case 'r': // remover
                minhaLista.removeNoInicio();
                break;
            case 'a': // remover
                minhaLista.removeNoFim();
                break;
            case 'p': // limpar tudo
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
