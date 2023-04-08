/**************************************************
 *
 * Samuel de Oliveira Krabbe e Leonardo de Moraes Perin
 * Trabalho 1
 * Professor(a): Fabio Henrique Viduani Martinez
 *
 */

#include <iostream>
#define MAX 1000000000

using namespace std;

typedef struct vizinho{
    string ip;
    int custo;
    struct vizinho *prox;
}Vizinho;

int comparaStr(string str1, string str2){
    for (long unsigned int i = 0; i < str1.length() || i < str2.length(); i++){
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;
}

void adicionaVizinho(Vizinho **vizinho, string conexao, int custo){
    Vizinho *p = *vizinho;
    
    Vizinho novoVizinho;
    novoVizinho.ip = conexao;
    novoVizinho.custo = custo;
    novoVizinho.prox = NULL;
    
    while (p->prox != NULL)
    {
        cout << "\naqui foi loop function!\n";
        p = p->prox;
    }
       
    p->prox = &novoVizinho;
    cout << "\naqui foi funcao!\n";
}

int main(){
    int quantIps, quantConexoes, custo;
    string ip, ipConexao, conexao;
    Vizinho *aux = NULL;

    cin >> quantIps;
    
    Vizinho *rede = new Vizinho[quantIps];

    for (int i = 0; i < quantIps; i++){
        cin >> ip;
        (rede + i)->ip = ip;
        (rede + i)->custo = MAX;
        (rede + i)->prox = NULL;
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++){
        cin >> ipConexao >> conexao >> custo;

        for (int k = 0; k < quantIps; k++){
            if (comparaStr((rede + k)->ip, ipConexao) == 1)
            {
                aux = (rede + k);
                cout << "\naqui foi if!\n";
                adicionaVizinho(&aux, conexao, custo);
                cout << "\naqui foi if!\n";
                break;
            }
            cout << "\naqui foi loop " << k << "x\n";
        }
    }
    cout << "\naqui foi!\n";
    return 0;
}