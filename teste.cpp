#include <iostream>
#define MAX 1000000000

using namespace std;

typedef struct vizinho{
    string ip;
    int custo;
    struct vizinho *prox;
}Vizinho;

typedef struct rede{
    string ip;
    int prioridade;
    Vizinho *vizinho;
}Rede;

void adicionaVizinho(Vizinho **vizinho, string conexao, int custo){
    Vizinho *p = *vizinho;

    Vizinho novoVizinho;
    novoVizinho.ip = conexao;
    novoVizinho.custo = custo;
    novoVizinho.prox = NULL;

    while (p->prox != NULL)
        p = p->prox;
    p->prox = &novoVizinho;
}

int main(){
    int quantIps, quantConexoes, custo;
    string ip, ipConexao, conexao;
    Vizinho **aux = NULL;

    cin >> quantIps;

    Rede *rede = new Rede[quantIps];
    
    for (int i = 0; i < quantIps; i++){
        cin >> ip;
        (&rede)[i]->ip = ip;
        (&rede)[i]->prioridade = MAX;
        (&rede)[i]->vizinho = NULL;
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++){
        cin >> ipConexao >> conexao >> custo;
        for (int j = 0; j < quantIps; j++){
            if ((&rede)[j]->ip == ipConexao){
                aux = &((&rede)[j]->vizinho);
                adicionaVizinho(aux, conexao, custo);
            }
        }
    }

    return 0;
}