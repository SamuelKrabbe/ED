#include <iostream>

using namespace std;

typedef struct vizinho{
    string ip;
    int custo;
    Vizinho *prox;
}Vizinho;

typedef struct rede{
    string ip;
    int prioridade;
    Vizinho *vizinho;
}Rede;

void setVizinho(Vizinnho **vizinho, ipConexao){

}


int main(){
    int quantIps, quantConexoes, custo;
    string ip, ipConexao, conexao;

    cin >> quantIps;

    Rede *rede = new Rede[quantIps];
    
    for (int i = 0; i < quantIps; i++){
        cin >> ip;
        (&rede)[i]->ip = ip;
        (&rede)[i]->prioridade = INT_MAX;
        (&rede)[i]->vizinho = NULL;
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++){
        cin >> ipConexao >> conexao >> custo;
        for (int j = 0; j < quantIps; j++){
            if ((&rede)[j]->ip == ipConexao){
                setVizinho(&((&rede)[j]->vizinho), ipConexao);
            }
        }
    }

    return 0;
}