#include <iostream>
#include <string>

using namespace std;

const int UMPRIMO = 7;

// Um nó guarda um par (chave / valor)
class noh
{
    friend class lista;
    friend class tabelaHash;

private:
    string chave;
    char tipo;
    int valor;
    noh *proximo;
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = NULL) : chave(c), tipo(t), valor(v), proximo(prox) {}
};

// Uma lista guarda todos os Nós cuja chave foi mapeada na mesma posição.
class lista
{
    friend class tabelaHash;

private:
    noh *primeiro;               // primeiro nó da lista
    unsigned short numElementos; // quantidade de valores na lista
public:
    lista() : primeiro(NULL), numElementos(0) {}      // Construtor
    ~lista() {}                                       // Destrutor
    unsigned short tamanho() { return numElementos; } // Consulta do Tamanho
    // Adiciona um novo par (chave, valor) na lista
    // Insere no início, para não precisar de ponteiro para o fim
    void insere(const string &c, const char &t, const int &v)
    {
        noh *novoNoh = new noh(c, t, v, primeiro);
        primeiro = novoNoh;
        numElementos++;
    }
    // Remove o nó com dada chave da lista.
    // Se a chave não existe, retorna informação.
    bool remove(const string &c)
    {
        if (primeiro == NULL)
            return false; // lista vazia

        noh *atual = primeiro;
        noh *anterior = NULL;

        while (atual != NULL && atual->chave != c)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual == NULL)
            return false; // chave não encontrada

        if (anterior == NULL)
            primeiro = atual->proximo;
        else
            anterior->proximo = atual->proximo;

        delete atual;
        numElementos--;
        return true;
    }
    // Busca um elemento na lista, retorna falso se não encontrado
    // o valor buscado é retornado por passagem por referência
    // na variável valorBuscado
    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            if (atual->chave == c)
            {
                tipoBuscado = atual->tipo;
                valorBuscado = atual->valor;
                return true; // encontrado
            }
            atual = atual->proximo;
        }
        return false; // não encontrado
    }
    // Verifica se já tem algum dado na lista com
    // uma dada chave
    bool verificaOcorrencia(const string &c)
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            if (atual->chave == c)
                return true; // encontrado
            atual = atual->proximo;
        }
        return false; // não encontrado
    }
    // Imprime o conteúdo da lista, para fins de depuração
    void imprime()
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]";
            atual = atual->proximo;
        }
    }
};

class tabelaHash
{
private:
    // vetor de ponteiros para lista
    lista *tabela;
    // quantidade de posições na tabela hash
    unsigned numPosicoes;
    // converte uma chave (string) num endereço da tabela
    // - versão simples
    unsigned funcaoHash(const string &s)
    {
        return funcaoHash(s, numPosicoes);
    }
    // converte uma chave (string) num endereço da tabela
    // - versão para redimensionamento
    unsigned funcaoHash(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

public:
    // construtor padrão
    tabelaHash(unsigned cap)
    {
        numPosicoes = cap;
        tabela = new lista[numPosicoes];
    }
    ~tabelaHash()
    {
        delete[] tabela;
    }
    

    bool insere(const string &c, char &t, const int &v)
    {
        unsigned posicao = funcaoHash(c);
        
        if (!tabela[posicao].verificaOcorrencia(c))
        {
            tabela[posicao].insere(c, t, v);
            cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
            return true;
        }
        else
        {
            cout << "Erro na inserção: chave já existente!" << endl;
            return false;
        }
    }
    
    // Retorna um valor associado a uma dada chave.
    // Se a chave não existe, retorna "NÃO ENCONTRADO!".
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].busca(c, tipoBuscado, valorRetorno))
            return true; // encontrado
        else
        {
            cout << "Elemento inexistente!" << endl;
            return false; // não encontrado
        }
    }
    // Retira do hash um nó com dada chave.
    bool remove(const string &c)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].remove(c))
            return true; // removido
        else
        {
            cout << "Elemento inexistente!" << endl;
            return false; // não removido
        }
    }
    // Imprime o conteúdo interno do hash (para fins de depuração)
    void imprime()
    {
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            cout << i << ": ";
            tabela[i].imprime();
            cout << endl;
        }
    }
};

int main()
{
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;
    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> chave >> tipo >> valor;
                tabela.insere(chave, tipo, valor);
                break;
            case 'r': // remover
                cin >> chave;
                tabela.remove(chave);
                break;
            case 'l': // remover
                cin >> chave;
                tabela.valor(chave, tipo, valor);
                break;
            case 'p': // mostrar estrutura
                tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}
