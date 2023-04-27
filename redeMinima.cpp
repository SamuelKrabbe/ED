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
//****** STRUCT VIZINHO & STRING ******
//*************************************

typedef struct string
{
    char nome[22];
} String;

typedef struct vizinho
{
    String ip;
    int custo;
    struct vizinho *prox;
} Vizinho;

//*************************************
//**** FUNÇÕES PARA O STRUCT STRING ***
//*************************************
int getComprimentoStr(String str)
{
    int i = 0;
    while (str.nome[i] != '\0')
        i++;
    return i + 1;
}

int comparaStr(String str1, String str2)
{
    for (int i = 0; i < getComprimentoStr(str1) || i < getComprimentoStr(str2); i++)
    {
        if (str1.nome[i] != str2.nome[i])
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
    ~Rede();
    void setVerticeRede(String ip, int posicaoIp);
    void adicionaVizinho(String ip, String conexao, int custoConexao);
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
    ~MinHeap();
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
//*************** MAIN ****************
//*************************************

int main()
{
    int quantIps, quantConexoes, custo;
    String ip, ipConexao, conexao;

    cin >> quantIps;
    Rede rede(quantIps);

    for (int i = 0; i < quantIps; i++)
    {
        cin >> ip.nome;
        rede.setVerticeRede(ip, i);
    }

    cin >> quantConexoes;

    for (int j = 0; j < quantConexoes; j++)
    {
        cin >> ipConexao.nome >> conexao.nome >> custo;
        rede.adicionaVizinho(ipConexao, conexao, custo);
    }

    cout << rede.redeCustoMinimo() << endl;
    return 0;
}

//*************************************
//**** IMPLEMENTANDO A CLASSE REDE ****
//*************************************

Rede::Rede(int quantIps)
{
    tamanhoRede = quantIps;
    rede = new Vizinho[quantIps];
}

Rede::~Rede()
{
    Vizinho *aux1, *aux2;

    for (int i = 0; i < tamanhoRede; i++)
    {
        aux1 = rede[i].prox;
        if (aux1 != NULL)
            aux2 = aux1->prox;
        else
            aux2 = NULL;

        while (aux1 != NULL)
        {
            delete aux1;
            aux1 = aux2;
            if (aux1 != NULL)
                aux2 = aux1->prox;
        }
    }
    delete[] rede;
}

void Rede::setVerticeRede(String ip, int posicaoIp)
{   //Essa função define o que cada nó da rede tem no inicio do programa

    rede[posicaoIp].ip = ip;
    rede[posicaoIp].custo = MAX;
    rede[posicaoIp].prox = NULL;
}

void Rede::adicionaVizinho(String ip, String conexao, int custoConexao)
{   //Adiciona para cada IP da rede as suas possíveis conexões

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
        }

        conexaoVizinha = rede[j].prox;

        while (conexaoVizinha != NULL)
        {
            for (int k = 0; k < minHeap.tamanhoMinHeap; k++)
                if (comparaStr(conexaoVizinha->ip, minHeap.minHeap[k].ip) == 1)
                {
                    if (conexaoVizinha->custo < minHeap.minHeap[k].custo)
                        minHeap.diminuiPrioridade(conexaoVizinha);
                    break;
                }
            conexaoVizinha = conexaoVizinha->prox;
        }
    }
    return custoMinimo;
}

// Deixei essa função imprimeRede aqui caso queira imprimir a rede...
// void Rede::imprimeRede()
// {
//     Vizinho *aux;
//     for (int i = 0; i < tamanhoRede; i++)
//     {
//         cout << "IP e CUSTO: " << endl;
//         cout << endl;
//         cout << rede[i].ip.nome << ", " << rede[i].custo << endl;
//         cout << endl;

//         cout << "CONEXÕES: " << endl;
//         cout << endl;
//         aux = rede[i].prox;
//         while (aux != NULL)
//         {
//             cout << aux->ip.nome << ", " << aux->custo << endl;
//             aux = aux->prox;
//         }
//         cout << "===========================================" << endl;
//         cout << endl;
//     }
// }

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

MinHeap::~MinHeap()
{
    delete[] minHeap;
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

// Deixei essa função imprimeMinHeap aqui caso queira imprimir o minHeap...
// void MinHeap::imprimeMinHeap()
// {
//     for (int i = 0; i < tamanhoMinHeap; i++)
//     {
//         cout << minHeap[i].ip.nome << ", " << minHeap[i].custo << endl;
//     }
//     cout << "===========================================" << endl;
//     cout << endl;
// }