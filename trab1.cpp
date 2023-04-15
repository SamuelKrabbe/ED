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
//************* CLASSES ***************
//*************************************

class Rede
{
    friend class MinHeap;

public:
    Rede(int quantIps);
    void setVerticeRede(string ip, int posicaoIp);
    int comparaStr(string str1, string str2);
    void adicionaVizinho(string ip, string conexao, int custoConexao);
    int redeCustoMinimo();

private:
    int tamanhoRede;
    Vizinho *rede;
};

class MinHeap
{
    friend class Rede;

public:
    MinHeap(Vizinho *rede, int tamanhoRede);

private:
    Vizinho *minHeap;
    int tamanhoMinHeap;
    int pai(int indice);
    int filhoEsq(int indice);
    int filhoDir(int indice);
    void troca(int indice1, int indice2);
    void desce(int indice);
    void sobe(int indice);
};

//*************************************
//**** IMPLEMENTANDO A CLASSE REDE ****
//*************************************

Rede::Rede(int quantIps)
{
    tamanhoRede = quantIps;
    rede = new Vizinho[quantIps];
}

void Rede::setVerticeRede(string ip, int posicaoIp)
{
    rede[posicaoIp].ip = ip;
    rede[posicaoIp].custo = MAX;
    rede[posicaoIp].prox = NULL;
}

int Rede::comparaStr(string str1, string str2)
{
    for (long unsigned int i = 0; i < str1.length() || i < str2.length(); i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;
}

void Rede::adicionaVizinho(string ip, string conexao, int custoConexao)
{
    Vizinho *novoVizinho = new Vizinho;
    novoVizinho->ip = conexao;
    novoVizinho->custo = custoConexao;
    ;
    novoVizinho->prox = NULL;

    for (int i = 0; i < tamanhoRede; i++)
    {
        if (comparaStr(ip, rede[i].ip) == 1)
        {
            rede[i].prox = novoVizinho;
            break;
        }
    }
}

int Rede::redeCustoMinimo()
{
    int custoMinimo = 0;

    rede[0].custo = 0;

    MinHeap minHeap(rede, tamanhoRede);

    // while (tamanhoRede > 0)
    // {
    //     minimoValor = extraiMinimo(&minHeap, &tamanhoRede);
    //     custoMinimo += minimoValor.custo;

    //     for (int j = 0; j < tamanhoRede; j++)
    //     {
    //         vizinhoDeP = (p + j)->prox;
    //         while (vizinhoDeP != NULL)
    //         {
    //             for (int k = 0; k < tamanhoRede; k++)
    //             {
    //                 if (comparaStr(vizinhoDeP->ip, (minHeap + k)->ip) == 1)
    //                 {
    //                     if (vizinhoDeP->custo < (minHeap + k)->custo)
    //                     {
    //                         diminuiPrioridade(&minHeap, vizinhoDeP, tamanhoRede);
    //                     }
    //                 }
    //             }
    //             vizinhoDeP = vizinhoDeP->prox;
    //         }
    //     }
    // }
    return custoMinimo;
}

//*************************************
//**** IMPLEMENTANDO A CLASSE HEAP ****
//*************************************

MinHeap::MinHeap(Vizinho *rede, int tamanhoRede)
{
    minHeap = new Vizinho[tamanhoRede];
    tamanhoMinHeap = tamanhoRede;

    for (int i = 0; i < tamanhoRede; i++)
    {
        minHeap[i].ip = rede[i].ip;
        minHeap[i].custo = rede[i].custo;
        minHeap[i].prox = NULL;
    }

    for (int indice = tamanhoRede / 2; indice > 0; indice--)
        desce(indice);
}

int MinHeap::pai(int i)
{
    return (i - 1) / 2;
}

int MinHeap::filhoEsq(int i)
{
    return 2 * (i + 1) - 1;
}

int MinHeap::filhoDir(int i)
{
    return 2 * (i + 1);
}

void MinHeap::troca(int indice1, int indice2)	
{
    Vizinho aux, p, q;
    p = minHeap[indice1];
    q = minHeap[indice1];

    aux.ip = p.ip;
    p.ip = q.ip;
    q.ip = aux.ip;

    aux.custo = p.custo;
    p.custo = q.custo;
    q.custo = aux.custo;

    aux.prox = p.prox;
    p.prox = q.prox;
    q.prox = aux.prox;
}

void MinHeap::desce(int indice)
{
    int e, d, maior;

    if (indice != (tamanhoMinHeap - 1))
    {
        e = filhoEsq(indice);
        d = filhoDir(indice);

        if (e < tamanhoMinHeap && minHeap[e].custo > minHeap[indice].custo)
            maior = e;
        else
            maior = indice;

        if (d < tamanhoMinHeap && minHeap[d].custo > minHeap[maior].custo)
            maior = d;

        if (maior != indice)
        {
            troca(indice, maior);
            desce(maior);
        }
    }
}

// void MinHeap::sobe(int i)
// {
//     while (S[pai(i)] < S[i])
//     {
//         troca(i, pai(i));
//         i = pai(i);
//     }
// }

//*************************************
//*************** MAIN ****************
//*************************************

int main()
{
    int quantIps, quantConexoes, custo;
    string ip, ipConexao, conexao;

    cin >> quantIps;

    Rede rede(quantIps);

    for (int i = 0; i < quantIps; i++)
    {
        cin >> ip;
        rede.setVerticeRede(ip, i);
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++)
    {
        cin >> ipConexao >> conexao >> custo;

        for (int k = 0; k < quantIps; k++)
        {
            rede.adicionaVizinho(ipConexao, conexao, custo);
        }
    }

    cout << rede.redeCustoMinimo() << endl;
    return 0;
}
