#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>

using namespace std;

struct dado {
    string assunto;
    string nomeInteressado;
    char tipo;
    int numeroProcesso;
};

const dado INVALIDO = {"", "", '1', -1};
const dado REMOVIDO = {"", "", '2', -2};
const int POSINVALIDA = -1;

bool operator==(const dado& d1, const dado& d2) {
    return d1.nomeInteressado == d2.nomeInteressado;
}

bool operator!=(const dado& d1, const dado& d2) {
    return d1.nomeInteressado != d2.nomeInteressado;
}

class hashEA {
private:
    unsigned capacidade;
    dado* vetDados;
    unsigned tamanho;

    unsigned posicao(const string& chave) {
        unsigned pos = 1;
        for (char ch : chave) {
            pos = 13 * pos + ch;
        }
        return pos % capacidade;
    }

    int buscarChave(const string& chave) {
        if (tamanho == 0) {
            return POSINVALIDA;
        }

        unsigned pos = posicao(chave);
        unsigned posFinal = pos;
        
        do {
            if (vetDados[pos] == INVALIDO) {
                return POSINVALIDA;
            }
            if (vetDados[pos].nomeInteressado == chave) {
                return pos;
            }
            pos = (pos + 1) % capacidade;
        } while (pos != posFinal);

        return POSINVALIDA;
    }

public:
    hashEA(unsigned cap = 6) {
        capacidade = cap;
        vetDados = new dado[capacidade];
        for (unsigned i = 0; i < capacidade; ++i) {
            vetDados[i] = INVALIDO;
        }
        tamanho = 0;
    }

    ~hashEA() {
        delete[] vetDados;
    }

    void inserir(const string& assunto, const string& interessado, char tipo, int numero) {
        if (interessado.empty()) {
            throw invalid_argument("Chave inválida.");
        }
        if (tamanho == capacidade) {
            throw runtime_error("Erro: hash cheia!");
        }

        if (buscarChave(interessado) != POSINVALIDA) {
            throw runtime_error("Inserção de chave que já existe.");
        }

        unsigned pos = posicao(interessado);
        while ((vetDados[pos] != INVALIDO) && (vetDados[pos] != REMOVIDO)) {
            pos = (pos + 1) % capacidade;
        }

        vetDados[pos] = {assunto, interessado, tipo, numero};
        tamanho++;
    }

    void remover(const string& chave) {
        if (tamanho == 0) {
            throw runtime_error("Erro: hash vazia!");
        }

        int pos = buscarChave(chave);
        if (pos == POSINVALIDA) {
            throw runtime_error("Elemento inexistente!");
        }

        vetDados[pos] = REMOVIDO;
        tamanho--;
    }

    int consultar(const string& chave) {
        if (tamanho == 0) {
            throw runtime_error("Erro: hash vazia!");
        }

        int pos = buscarChave(chave);
        if (pos == POSINVALIDA) {
            throw runtime_error("Elemento inexistente!");
        }

        return vetDados[pos].numeroProcesso;
    }

    void imprimir() {
        for (unsigned i = 0; i < capacidade; ++i) {
            cout << '[' << i << ":";
            if (vetDados[i] == INVALIDO) {
                cout << "";
            } else if (vetDados[i] == REMOVIDO) {
                cout << "REMOVIDO";
            } else {
                cout << vetDados[i].nomeInteressado << '/' << vetDados[i].numeroProcesso;
            }
            cout << "] ";
        }
        cout << endl;
    }
};

int main() {
    hashEA tabela(6);
    char operacao;

    string assunto, interessado;
    char tipo;
    int valor;

    while (true) {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> assunto >> interessado >> tipo >> valor;
                    tabela.inserir(assunto, interessado, tipo, valor);
                    break;
                case 'r': // remover
                    cin >> interessado;
                    tabela.remover(interessado);
                    break;
                case 'l': // consultar
                    cin >> interessado;
                    valor = tabela.consultar(interessado);
                    cout << valor << endl;
                    break;
                case 'p': // debug (mostrar estrutura)
                    tabela.imprimir();
                    break;
                case 'f': // finalizar
                    tabela.imprimir();
                    return 0;
                default:
                    cerr << "Operação inválida" << endl;
            }
        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
