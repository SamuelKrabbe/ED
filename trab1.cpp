/**************************************************
*
* Samuel de Oliveira Krabbe e Leonardo de Moraes Perin
* Trabalho 1
* Professor(a): Fabio Henrique Viduani Martinez
*
*/


#include <iostream>
#include <cstdio>

using namespace std;

typedef struct conexao {
    string ip;
    int custo;
    struct conexao *prox;
}Conexao;

typedef struct minHeapVertice {
    string ip;
    int prioridade;
}MinHeapVertice;

class Rede {
    public:
        Rede();
        ~Rede();
        string ip;
        Conexao *conexoes;
        int redeCustoMinimo(Rede R[], string ip);
        
    private:

        int prioridade;
        void diminuiPrioridade(MinHeap Q, string ip, int custo);
};

class MinHeap
{
    public:
    MinHeap(int n, Rede rede[]);
    ~MinHeap();
    void insere(int p);
    int extrai_min();
    void altera_prioridade(int i, int p);
    int consultaMinHeap(string ip);
    
    private:
    vector<MinHeapVertice> S;

    int pai(int i);
    int esquerdo(int i);
    int direito(int i);
    void troca(int i, int j);
    void desce(int i);
    void sobe(int i);
};

//**************************************
//** IMPLEMENTAÇÕES DA CLASSE MinHeap **
//**************************************


MinHeap::MinHeap(int n, Rede rede[]) :
  S(rede, rede + n) {
  for (int i = n / 2; i > 0; i--)
    desce(i);
}

MinHeap::~MinHeap() {
}

int MinHeap::pai(int i) {
  return (i - 1) / 2;
}

int MinHeap::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

int MinHeap::direito(int i) {
  return 2 * (i + 1);
}

void MinHeap::troca(int i, int j) {
  int aux = S[i].prioridade;
  S[i].prioridade = S[j].prioridade;
  S[j].prioridade = aux;
}

void MinHeap::desce(int i) {
    int e, d, menor, n;
    n = S.size();

    if (i != (n - 1)){
        e = esquerdo(i);
        d = direito(i);

        if (e < n && S[e].prioridade < S[i].prioridade)
            menor = e;
        else
            menor = i;

        if (d < n && S[d].prioridade < S[menor].prioridade)
            menor = d;

        if (menor != i){
            troca(i, menor);
            desce(i);
        }
    }
}

void MinHeap::sobe(int i) {
  while (S[pai(i)].prioridade > S[i].prioridade) {
    troca(i, pai(i));
    i = pai(i);
  }
}

// void MinHeap::insere(int p) {
//   S..push_back(p);
//   sobe(S.size()-1);
// }

int MinHeap::extrai_min() {
  int n, minimo;
  n = S.size();
  minimo = S[0].prioridade;

  troca(0, n - 1);
  S.resize(n - 1);

  return minimo;
}

void MinHeap::altera_prioridade(int i, int p) {

  if (p < S[i].prioridade){
    S[i].prioridade = p;
    sobe(i);
  }
  else{
    S[i].prioridade = p;
    desce(i);
  }
}

int MinHeap::consultaMinHeap(string ip){
    int i = 0;

    while (ip != S[i].ip){
        i++;
    }
    return i;
}

//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE Rede ***
//*************************************

Rede::Rede(){
}

// int Rede::redeCustoMinimo(Rede R[], string ip){
//     return custo;
// }

void Rede::diminuiPrioridade(MinHeap Q, string ip, int custo){
    int index = Q.consultaMinHeap(ip);
    Q.altera_prioridade(index, custo);
}

int main(){
    int quantidadeIps;
    string ip;
    scanf("%d", &quantidadeIps);

    Rede vertice;
    vector<Rede> rede;
    
    for (int i = 0; i < quantidadeIps; i++){
        scanf("%s", ip);
        vertice.ip = ip;
        rede.push_back(vertice);
    }

    return 0;
}