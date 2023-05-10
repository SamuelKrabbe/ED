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
//********* FUNÇÃO comparaStr *********
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

//*************************************
//************* CLASSES ***************
//*************************************

class Rede
{
    friend class MinHeap;

public:
    Rede(int quantIps);
    void setVerticeRede(string ip, int posicaoIp);
    void adicionaVizinho(string ip, string conexao, int custoConexao);
    int redeCustoMinimo();
    void imprimeRede();

private:
    int tamanhoRede;
    Vizinho *rede;
};

class MinHeap
{
    friend class Rede;

public:
    MinHeap(Vizinho *rede, int tamanhoRede);
    Vizinho extraiMinimo();
    void diminuiPrioridade(Vizinho *conexao);
    void imprimeMinHeap();

private:
    Vizinho *minHeap;
    int tamanhoOriginal;
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

void Rede::adicionaVizinho(string ip, string conexao, int custoConexao)
{
    Vizinho *novoVizinho = new Vizinho, *aux;
    novoVizinho->ip = conexao;
    novoVizinho->custo = custoConexao;
    novoVizinho->prox = NULL;

    for (int i = 0; i < tamanhoRede; i++)
    {
        if (comparaStr(ip, rede[i].ip) == 1)
        {
            aux = rede + i;
            while (aux->prox != NULL)
                aux = aux->prox;
            aux->prox = novoVizinho;
            break;
        }
    }
}

int Rede::redeCustoMinimo()
{
    int custoMinimo = 0;
    Vizinho *conexaoVizinha, minimoValor;

    rede[0].custo = 0;

    MinHeap minHeap(rede, tamanhoRede);

    for (int j = 0; j < tamanhoRede; j++)
    {
        if (minHeap.minHeap[0].custo != MAX)
        {
            minimoValor = minHeap.extraiMinimo();
            custoMinimo += minimoValor.custo;
            cout << custoMinimo << endl;
            cout << endl;
        }

        conexaoVizinha = rede[j].prox;
        cout << conexaoVizinha->ip << endl;
        cout << endl;

        while (conexaoVizinha != NULL)
        {
            for (int k = 0; k < minHeap.tamanhoMinHeap; k++)
            {
                if (comparaStr(conexaoVizinha->ip, minHeap.minHeap[k].ip) == 1)
                {
                    if (conexaoVizinha->custo < minHeap.minHeap[k].custo)
                    {
                        minHeap.diminuiPrioridade(conexaoVizinha);
                        minHeap.imprimeMinHeap();
                    }
                    break;
                }
            }
            conexaoVizinha = conexaoVizinha->prox;
        }
    }

    return custoMinimo;
}

void Rede::imprimeRede()
{
    Vizinho *aux;
    for (int i = 0; i < tamanhoRede; i++)
    {
        cout << rede[i].ip << ", " << rede[i].custo << endl;
        cout << endl;

        cout << "CONEXÕES: " << endl;
        cout << endl;
        aux = rede[i].prox;
        while (aux != NULL)
        {
            cout << aux->ip << ", " << aux->custo << endl;
            aux = aux->prox;
        }
        cout << "===========================================" << endl;
        cout << endl;
    }
}

//*************************************
//**** IMPLEMENTANDO A CLASSE HEAP ****
//*************************************

MinHeap::MinHeap(Vizinho *rede, int tamanhoRede)
{
    minHeap = new Vizinho[tamanhoRede];
    tamanhoMinHeap = tamanhoRede;
    tamanhoOriginal = tamanhoRede;

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
    Vizinho aux, *p, *q;
    p = minHeap + indice1;
    q = minHeap + indice2;

    aux.ip = p->ip;
    p->ip = q->ip;
    q->ip = aux.ip;

    aux.custo = p->custo;
    p->custo = q->custo;
    q->custo = aux.custo;
}

void MinHeap::desce(int indice)
{
    int e, d, menor;

    if (indice != (tamanhoMinHeap - 1))
    {
        e = filhoEsq(indice);
        d = filhoDir(indice);

        if (e < tamanhoMinHeap && minHeap[e].custo < minHeap[indice].custo)
            menor = e;
        else
            menor = indice;

        if (d < tamanhoMinHeap && minHeap[d].custo < minHeap[menor].custo)
            menor = d;

        if (menor != indice)
        {
            troca(indice, menor);
            desce(menor);
        }
    }
}

void MinHeap::sobe(int indice)
{
    while (minHeap[pai(indice)].custo > minHeap[indice].custo)
    {
        troca(indice, pai(indice));
        indice = pai(indice);
    }

    if (minHeap[pai(indice)].custo == minHeap[indice].custo)
    {
        troca(indice, pai(indice));
        indice = pai(indice);
    }
}

Vizinho MinHeap::extraiMinimo()
{
    Vizinho minimoValor;

    minimoValor.ip = minHeap[0].ip;
    minimoValor.custo = minHeap[0].custo;
    minimoValor.prox = NULL;

    troca(0, tamanhoMinHeap - 1);
    tamanhoMinHeap = tamanhoMinHeap - 1;

    desce(0);
    return minimoValor;
}

void MinHeap::diminuiPrioridade(Vizinho *conexao)
{
    int indice;

    for (int i = 0; i < tamanhoMinHeap; i++)
    {
        if (comparaStr(minHeap[i].ip, conexao->ip) == 1)
        {
            indice = i;
            break;
        }
    }
    minHeap[indice].custo = conexao->custo;
    sobe(indice);
}

void MinHeap::imprimeMinHeap()
{
    for (int i = 0; i < tamanhoMinHeap; i++)
    {
        cout << minHeap[i].ip << ", " << minHeap[i].custo << endl;
    }
    cout << "===========================================" << endl;
    cout << endl;
}

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

        rede.adicionaVizinho(ipConexao, conexao, custo);
    }

    cout << rede.redeCustoMinimo() << endl;
    return 0;
}
