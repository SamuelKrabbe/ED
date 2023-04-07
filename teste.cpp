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

void adicionaVizinho(Rede **rede, string conexao, int custo){
    Rede *p = *rede;
    Vizinho *q = p->vizinho;
    
    Vizinho novoVizinho;
    novoVizinho.ip = conexao;
    novoVizinho.custo = custo;
    novoVizinho.prox = NULL;

    if (q == NULL){
        q = &novoVizinho;
        cout << "\naqui foi if!\n";
    }else{
        while (q->prox != NULL)
        {
            cout << "\naqui foi loop!\n";
            q = q->prox;
        }
    }
        
    q->prox = &novoVizinho;
    cout << "\naqui foi!\n";
}

int main(){
    int quantIps, quantConexoes, custo;
    string ip, ipConexao, conexao;
    Rede *aux = NULL;

    cin >> quantIps;
    
    Rede *rede = new Rede[quantIps];

    for (int i = 0; i < quantIps; i++){
        cin >> ip;
        (*(rede + i)).ip = ip;
        (*(rede + i)).prioridade = MAX;
        (*(rede + i)).vizinho = NULL;
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++){
        cin >> ipConexao >> conexao >> custo;

        for (int j = 0; j < quantIps; j++){
            if ((rede + j)->ip == ipConexao){
                aux = rede + j;
                cout << "\naqui foi if!\n";
                adicionaVizinho(&aux, conexao, custo);
            }
            cout << "\naqui foi loop!\n";
        }
    }
    cout << "\naqui foi!\n";
    return 0;
}