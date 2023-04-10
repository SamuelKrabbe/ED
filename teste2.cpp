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
    Vizinho *novoVizinho = new Vizinho;
    novoVizinho->ip = conexao;
    novoVizinho->custo = custo;
    novoVizinho->prox = NULL;
    
    while (p->prox != NULL)
        p = p->prox;
    p->prox = novoVizinho;
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

int pai(int i)
{
    return (i - 1) / 2;
}

int filhoEsq(int i)
{
    return 2 * (i + 1) - 1;
}

int filhoDir(int i)
{
    return 2 * (i + 1);
}

void sobe(Vizinho **minHeap, int i)
{
    Vizinho *aux, *p, *f;
    aux = *minHeap;
    p = aux + pai(i);
    f = aux + i;

    while (p->custo > f->custo)
    {
        troca(&p, &f);
        i = pai(i);
        p = aux + pai(i);
        f = aux + i;
    }
}

void desce(Vizinho **minHeap, int tamanhoHeap, int i)
{
    Vizinho *p, *q, *r;
    p = *minHeap;
    int e, d, menor, n;
    n = tamanhoHeap;

    if (i != (n - 1))
    {
        e = filhoEsq(i);
        d = filhoDir(i);

        if (e < n && (p + e)->custo < (p + i)->custo)
            menor = e;
        else
            menor = i;

        if (d < n && (p + d)->custo < (p + menor)->custo)
            menor = d;

        if (menor != i)
        {
            q = p + i;
            r = p + menor;
            troca(&q, &r);
            desce(minHeap, n, i);
        }
    }
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

    for (int i = tamanhoRede / 2; i > 0; i--)
        desce(&minHeap, tamanhoRede, i);
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

// int estaNoHeap(Vizinho *minHeap, Vizinho *vizinhoDeP, int tamanhoRede)
// {
//     cout << "entrou na funcao estaNoHeap..." << endl;
//     Vizinho *p, *q;
//     p = minHeap;
//     q = vizinhoDeP;

//     for (int i = 0; i < tamanhoRede; i++)
//     {
//         cout << "entrou no for i da funcao estaNoHeap..." << endl;
//         if (comparaStr((p + i)->ip, q->ip) == 1)
//         {
//             cout << "entrou no if da funcao estaNoHeap..." << endl;
//             return 1;
//         }
//     }
//     cout << "saiu do for i da funcao estaNoHeap..." << endl;
//     return 0;
// }

void diminuiPrioridade(Vizinho **minHeap, Vizinho *vizinhoDeP, int tamanhoHeap)
{
    int index;
    Vizinho *p;
    p = *minHeap;

    for (int i = 0; i < tamanhoHeap; i++)
    {
        if (comparaStr((p + i)->ip, vizinhoDeP->ip) == 1)
        {
            index = i;
            break;
        }
    }
    (p + index)->custo = vizinhoDeP->custo;
    sobe(minHeap, index);
}

int redeCustoMinimo(Vizinho **rede, int tamanhoRede)
{
    int custoMinimo = 0, j = 0;
    Vizinho *p, *vizinhoDeP, minimoValor;
    p = *rede;
    p->custo = 0;

    for (int i = 1; i < tamanhoRede; i++)
        (p + i)->custo = MAX;

    Vizinho *minHeap = constroiMinHeap(rede, tamanhoRede);

    while (tamanhoRede > 0)
    {
        minimoValor = extraiMinimo(&minHeap, &tamanhoRede);
        custoMinimo += minimoValor.custo;

        if (j < tamanhoRede)
        {
            vizinhoDeP = (p + j)->prox;
            while (vizinhoDeP != NULL)
            {
                for (int k = 0; k < tamanhoRede; k++)
                {
                    if (comparaStr(vizinhoDeP->ip, (minHeap + k)->ip) == 1)
                    {
                        if (vizinhoDeP->custo < (minHeap + k)->custo)
                        {
                            diminuiPrioridade(&minHeap, vizinhoDeP, tamanhoRede);
                        }
                        break;
                    }
                }
                vizinhoDeP = vizinhoDeP->prox;
            }
            j++;
        }
        else    
            break;
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
