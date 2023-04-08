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

//*************************************
//********** STRUCT VIZINHO ***********
//*************************************

typedef struct vizinho
{
    string ip;
    int custo;
    struct vizinho *prox;
} Vizinho;

//*************************************
//************* FUNÇÕES ***************
//*************************************

int comparaStr(string str1, string str2)
{
    for (long unsigned int i = 0; i < str1.length() || i < str2.length(); i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;
}

void adicionaVizinho(Vizinho **vizinho, string conexao, int custo)
{
    Vizinho *p = *vizinho;

    Vizinho novoVizinho;
    novoVizinho.ip = conexao;
    novoVizinho.custo = custo;
    novoVizinho.prox = NULL;

    while (p->prox != NULL)
        p = p->prox;

    p->prox = &novoVizinho;
}

void troca(Vizinho **i, Vizinho **j)
{
    Vizinho aux, *p, *q;
    p = *i;
    q = *j;

    aux.ip = p->ip;
    p->ip = q->ip;
    q->ip = aux.ip;

    aux.custo = p->custo;
    p->custo = q->custo;
    q->custo = aux.custo;

    aux.prox = p->prox;
    p->prox = q->prox;
    q->prox = aux.prox;
}

Vizinho *constroiMinHeap(Vizinho **rede, int tamanhoRede)
{
    Vizinho *p = *rede;
    Vizinho *minHeap = new Vizinho[tamanhoRede];

    for (int i = 0; i < tamanhoRede; i++)
    {
        (minHeap + i)->ip = (p + i)->ip;
        (minHeap + i)->custo = (p + i)->custo;
        (minHeap + i)->prox = NULL;
    }
    return minHeap;
}

Vizinho extraiMinimo(Vizinho **minHeap, int *tamanhoRede)
{
    Vizinho *p, *aux, minimo;
    int *n = tamanhoRede;
    p = *minHeap;
    aux = p + (*n - 1);

    minimo.ip = p->ip;
    minimo.custo = p->custo;
    minimo.prox = NULL;

    troca(&p, &aux);
    (*n)--;

    return minimo;
}

int redeCustoMinimo(Vizinho **rede, int tamanhoRede)
{
    int custoMinimo = 0;
    Vizinho *p = *rede, minimoValor;
    p->custo = 0;

    for (int i = 1; i < tamanhoRede; i++)
        (p + i)->custo = MAX;

    Vizinho *minHeap = constroiMinHeap(rede, tamanhoRede);

    // imprimindo o minHeap
    for (int h = 0; h < tamanhoRede; h++)
        cout << (minHeap + h)->ip << ", " << (minHeap + h)->custo << endl;

    while (tamanhoRede > 0){
        minimoValor = extraiMinimo(&minHeap, &tamanhoRede);
        custoMinimo += minimoValor.custo;

        for (int t = 0; t < tamanhoRede; t++)
            cout << (minHeap + t)->ip << ", " << (minHeap + t)->custo << endl;

        // for (int j = 1; j < tamanhoRede; j++)
        // {
        //     if (comparaStr((p + j)->ip, minimoValor.ip) == 1)
        //     {
        //         for (int k = 0; k < tamanhoRede; k++)
        //         {
        //         }
        //     }
        // }
    }

    return custoMinimo;
}

//*************************************
//*************** MAIN ****************
//*************************************

int main()
{
    int quantIps, quantConexoes, custo, custoMinimo;
    string ip, ipConexao, conexao;
    Vizinho *aux = NULL;

    cin >> quantIps;

    Vizinho *rede = new Vizinho[quantIps];

    for (int i = 0; i < quantIps; i++)
    {
        cin >> ip;
        (rede + i)->ip = ip;
        (rede + i)->custo = MAX;
        (rede + i)->prox = NULL;
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++)
    {
        cin >> ipConexao >> conexao >> custo;

        for (int k = 0; k < quantIps; k++)
        {
            if (comparaStr((rede + k)->ip, ipConexao) == 1)
            {
                aux = (rede + k);
                adicionaVizinho(&aux, conexao, custo);
                break;
            }
        }
    }

    custoMinimo = redeCustoMinimo(&rede, quantIps);
    cout << custoMinimo << endl;
    return 0;
}