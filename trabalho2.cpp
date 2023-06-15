/**************************************************
 *
 * Samuel de Oliveira Krabbe e Leonardo de Moraes Perin
 * Trabalho 1
 * Professor(a): Fabio Henrique Viduani Martinez
 *
 */

#include <iostream>
#include <random>

using namespace std;

int *geraEntradaAleatoria(int tamanhoEntrada)
{
    int *entrada = new int[tamanhoEntrada];
    // Função para gerar um conjunto de dados de entrada aleatório com base nos parâmetros fornecidos
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 100); // Intervalo dos números aleatórios (0 a 100)

    for (int i = 0; i < tamanhoEntrada; ++i)
        entrada[i] = dis(gen); // Gera um número aleatório e o adiciona ao conjunto de entrada
    return entrada;
}

//*************************************
//*********** STRUCT String ***********
//*************************************

typedef struct string
{
    /* Como não podemos usar a biblioteca string
        criamos nossa própria estrutura
    */
    char nome[22];
} String;

//*************************************
//**** FUNÇÕES PARA O STRUCT String ***
//*************************************
int getComprimentoStr(String str)
{
    // Recebe uma String e retorna o comprimento dela
    int i = 0;
    while (str.nome[i] != '\0')
        i++;
    return i + 1;
}

int comparaStr(String str1, String str2)
{
    /* Recebe duas Strings, as compara e retorna 1 se forem iguais,
        caso sejam diferentes retorna 0
    */
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

class NoABB
{
    // Nó da árvore binária de busca
    friend class ABB;

public:
    NoABB(const int chave);
    void escreve(const char *sep = "");

private:
    int chave;
    NoABB *pai;
    NoABB *esq;
    NoABB *dir;
};

class ABB
{
public:
    ABB();
    ~ABB();

    void escreve_ordenado(); // escreve em percurso em-ordem
    void insere(int chave);  // insere a chave na árvore binária de busca
    void limpa();            // remove todos elementos da árvore

private:
    NoABB *raiz;

    void escreve_ordenado(NoABB *x); // escreve em percurso em-ordem
    void insere(NoABB *z);           // insere a chave na árvore binária de busca
    void limpa(NoABB *x);            // dado um nó x, remove recursivamente elementos abaixo e deleta x
};

class NoAVL
{
    // Nó da árvore AVL
    friend class AVL;

public:
    NoAVL(const int chave);

    void escreve(const char *sep = "");
    inline bool eh_raiz();         // devolve true se o nó é raiz
    inline bool eh_direito();      // devolve true se o nó é filho direito do seu pai
    inline bool eh_esquerdo();     // devolve true se o nó é filho esquerdo do seu pai
    inline int bal();              // calcula e devolve o fator de balanceamento
    inline void atualiza_altura(); // recalcula a altura a partir das alturas dos filhos

private:
    int chave;
    int altura; // consideramos que a altura das folhas é 0
    NoAVL *pai;
    NoAVL *esq;
    NoAVL *dir;
};

class AVL
{
public:
    AVL();
    ~AVL();

    void escreve_ordenado();  // escreve em percurso em-ordem
    NoAVL *get_raiz();        // devolve a raiz
    void insere(int chave);   // insere uma chave
    void limpa();             // remove todos elementos da árvore
    void rotacao_dir();       // Rotação à direita: p e p->esq
    void rotacao_esq();       // Rotação à esquerda: p e p->dir
    void rotacao_dupla_dir(); // Rotação dupla à direita: p->esq e p->esq->dir à esquerda, então p e p->esq à direita
    void rotacao_dupla_esq(); // Rotação dupla à esquerda: p->dir e p->dir->esq à direita, então p e p->dir à esquerda

private:
    NoAVL *raiz;

    void escreve_ordenado(NoAVL *x); // escreve em percurso em-ordem

    // recalcula balanceamento e rotaciona, se necessário, devolvendo o
    // ponteiro para o nó que ocupou a posição de p na árvore (caso uma
    // rotação tenha sido realizada)
    NoAVL *ajusta_balanceamento(NoAVL *p);
    void transplante(NoAVL *u, NoAVL *v); // transplante de v para u, não altera filhos
    void insere(NoAVL *z);                // insere um nó z na árvore
    void limpa(NoAVL *x);                 // dado um nó x, remove recursivamente todos elementos abaixo e deleta x
    void rotacao_dir(NoAVL *p);           // Rotação à direita: p e p->esq
    void rotacao_esq(NoAVL *p);           // Rotação à esquerda: p e p->dir
    void rotacao_dupla_dir(NoAVL *p);     // Rotação dupla à direita: p->esq e p->esq->dir à esquerda, então p e p->esq à direita
    void rotacao_dupla_esq(NoAVL *p);     // Rotação dupla à esquerda: p->dir e p->dir->esq à direita, então p e p->dir à esquerda
};

class Heap
{
public:
    Heap();
    Heap(int n, int **vetorEntrada);
    ~Heap();
    void heapSort();

private:
    int *S;
    int tamanhoDeS; // tamanho do vetor de entrada

    int pai(int i);
    int esquerdo(int i);
    int direito(int i);
    void troca(int i, int j);
    void desce(int i);
    void sobe(int i);
};

int main()
{
    int inc;      // Valor inicial
    int max;      // Valor final
    int stp;      // Intervalo entre dois tamanhos
    int rpt;      // Quantidade de repetições
    int *entrada; // Vetor de entrada
    time_t start, end;
    double timeTaken;

    cin >> inc >> max >> stp >> rpt;
    cout << "n          ABB           AVl          Heapsort     " << endl;
    cout << "---------------------------------------------------" << endl;

    for (int n = inc; n <= max; n += stp)
    {
        double totalABB = 0.000000f;
        double totalAVL = 0.000000f;
        double totalHEAP = 0.000000f;
        double mediaABB = 0.000000f;
        double mediaAVL = 0.000000f;
        double mediaHEAP = 0.000000f;

        for (int i = 0; i < rpt; i++)
        {
            entrada = geraEntradaAleatoria(n);

            // ABB
            ABB arvoreBinBusca;
            for (const auto &x : entrada)
                arvoreBinBusca.insere(x);
            // AVL
            AVL arvoreAVL;
            for (const auto &y : entrada)
                arvoreAVL.insere(y);
            // HEAP
            Heap maxHeap(n, &entrada);
            time(&start);
            maxHeap.heapSort();
            time(&end);
            timeTaken = double(end - start);
            totalHEAP += timeTaken;

            delete[] entrada; // Liberar a memória alocada para o vetor
        }
        double mediaABB = totalABB / rpt;
        double mediaAVL = totalAVL / rpt;
        double mediaHEAP = totalHEAP / rpt;
        cout << n << "     " << mediaABB << "     " << mediaAVL << "     " << mediaHEAP << endl;
    }
    return 0;
}

//***********************************
//* IMPLEMENTAÇÕES DA CLASSE NoABB **
//***********************************

NoABB::NoABB(const int chave) : chave(chave),
                                pai(NULL),
                                esq(NULL),
                                dir(NULL)
{
}

void NoABB::escreve(const char *sep)
{
    printf("%2d%s", chave, sep);
}

//********************************************
//*** IMPLEMENTAÇÃO DA CLASSE ABB ****
//********************************************

ABB::ABB()
{
    raiz = NULL;
}

ABB::~ABB()
{
    limpa();
}

void ABB::escreve_ordenado()
{
    escreve_ordenado(raiz);
    putchar('\n');
}

void ABB::escreve_ordenado(NoABB *x)
{
    if (x == NULL)
        return;

    escreve_ordenado(x->esq);
    x->escreve(" ");
    escreve_ordenado(x->dir);
}

void ABB::insere(int chave)
{
    NoABB *z = new NoABB(chave);
    insere(z);
}

void ABB::insere(NoABB *z)
{
    NoABB *y = NULL;
    NoABB *x = raiz;

    while (x != NULL)
    {
        y = x;
        if (z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if (y == NULL)
        raiz = z;
    else if (z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;
}

void ABB::limpa()
{
    limpa(raiz);
    raiz = NULL;
}

void ABB::limpa(NoABB *x)
{
    // limpa a árvore em pós-ordem
    if (x == NULL)
        return;

    limpa(x->esq);
    limpa(x->dir);
    delete x;
}

//***********************************
//** IMPLEMENTAÇÃO DA CLASSE NoAVL **
//***********************************

NoAVL::NoAVL(const int chave) : chave(chave),
                                altura(0),
                                pai(NULL),
                                esq(NULL),
                                dir(NULL)
{
}

void NoAVL::escreve(const char *sep)
{
    printf("%2d(%d)%s", chave, bal(), sep);
}

bool NoAVL::eh_raiz()
{
    return pai == NULL;
}

bool NoAVL::eh_direito()
{
    return !eh_raiz() and pai->dir == this;
}

bool NoAVL::eh_esquerdo()
{
    return !eh_raiz() and pai->esq == this;
}

int NoAVL::bal()
{
    int altEsq = esq ? esq->altura : -1;
    int altDir = dir ? dir->altura : -1;
    int fb = altEsq - altDir;
    return fb;
}

void NoAVL::atualiza_altura()
{
    int altEsq = esq ? esq->altura : -1;
    int altDir = dir ? dir->altura : -1;
    altura = 1 + (altEsq > altDir ? altEsq : altDir);
}

//************************************
//*** IMPLEMENTAÇÃO DA CLASSE AVL ****
//************************************

AVL::AVL()
{
    raiz = NULL;
}

AVL::~AVL()
{
    limpa();
}

NoAVL *AVL::get_raiz()
{
    return raiz;
}

void AVL::escreve_ordenado()
{
    escreve_ordenado(raiz);
    putchar('\n');
}

void AVL::escreve_ordenado(NoAVL *x)
{
    if (x == NULL)
        return;

    escreve_ordenado(x->esq);
    x->escreve(" ");
    escreve_ordenado(x->dir);
}

NoAVL *AVL::ajusta_balanceamento(NoAVL *p)
{

    p->atualiza_altura();

    if (p->bal() == 2)
    {                           // Caso 1
        if (p->esq->bal() >= 0) // Caso 1.1
            rotacao_dir(p);
        else // Caso 1.2
            rotacao_dupla_dir(p);
        p = p->pai; // após a rotação p desceu 1 nível, precisamos subir de volta
    }
    else if (p->bal() == -2)
    {                           // Caso 2
        if (p->dir->bal() <= 0) // Caso 2.1
            rotacao_esq(p);
        else // Caso 2.2
            rotacao_dupla_esq(p);
        p = p->pai; // após a rotação p desceu 1 nível, precisamos subir de volta
    }

    return p;
}

void AVL::insere(int chave)
{
    NoAVL *z = new NoAVL(chave);
    insere(z);
}

void AVL::insere(NoAVL *z)
{
    NoAVL *y = NULL;
    NoAVL *x = raiz;

    while (x != NULL)
    {
        y = x;
        x = z->chave < x->chave ? x->esq : x->dir;
    }
    z->pai = y;
    if (y == NULL)
        raiz = z;
    else if (z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;

    // Atualização das alturas/fatores de balanceamento
    if (z->eh_raiz())
        return;

    do
    { // o laço inicia subindo imediatamente para o pai do nó inserido
        z = z->pai;
        z = ajusta_balanceamento(z);
    } while (!z->eh_raiz() and z->bal() != 0);
}

void AVL::transplante(NoAVL *u, NoAVL *v)
{
    if (u->eh_raiz())
        raiz = v;
    else if (u->eh_esquerdo())
        u->pai->esq = v;
    else
        u->pai->dir = v;

    if (v != NULL)
        v->pai = u->pai;
}

void AVL::limpa()
{
    limpa(raiz);
    raiz = NULL;
}

void AVL::limpa(NoAVL *x)
{
    if (x == NULL)
        return;

    limpa(x->esq);
    limpa(x->dir);
    delete x;
}

void AVL::rotacao_dir()
{
    NoAVL *raiz = this->get_raiz();
    rotacao_dir(raiz);
}

void AVL::rotacao_dir(NoAVL *p)
{
    NoAVL *u = p->esq;

    transplante(p, u);
    p->pai = u;
    p->esq = u->dir;
    u->dir = p;

    if (p->esq)
        p->esq->pai = p;

    p->atualiza_altura();
    u->atualiza_altura();
}

void AVL::rotacao_esq()
{
    NoAVL *raiz = this->get_raiz();
    rotacao_esq(raiz);
}

void AVL::rotacao_esq(NoAVL *p)
{
    NoAVL *u = p->dir;

    transplante(p, u);
    p->pai = u;
    p->dir = u->esq;
    u->esq = p;

    if (p->dir)
        p->dir->pai = p;

    p->atualiza_altura();
    u->atualiza_altura();
}

void AVL::rotacao_dupla_dir()
{
    NoAVL *raiz = this->get_raiz();
    rotacao_dupla_dir(raiz);
}

void AVL::rotacao_dupla_dir(NoAVL *p)
{
    rotacao_esq(p->esq);
    rotacao_dir(p);
}

void AVL::rotacao_dupla_esq()
{
    NoAVL *raiz = this->get_raiz();
    rotacao_dupla_esq(raiz);
}

void AVL::rotacao_dupla_esq(NoAVL *p)
{
    rotacao_dir(p->dir);
    rotacao_esq(p);
}

//************************************
//*** IMPLEMENTAÇÃO DA CLASSE Heap ***
//************************************

Heap::Heap(int n, int **vetorEntrada)
{
    S = *vetorEntrada;
    tamanhoDeS = n;
    Heap();
}

Heap::Heap()
{
    for (int i = tamanhoDeS / 2 - 1; i >= 0; i--)
        desce(i);
}

Heap::~Heap()
{
}

void Heap::heapSort()
{
    for (int i = tamanhoDeS - 1; i > 0; i--)
    {
        troca(S[0], S[i]);
        tamanhoDeS--;
        desce(0);
    }
}

int Heap::pai(int i)
{
    return (i - 1) / 2;
}

int Heap::esquerdo(int i)
{
    return 2 * (i + 1) - 1;
}

int Heap::direito(int i)
{
    return 2 * (i + 1);
}

void Heap::troca(int i, int j)
{
    int aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

void Heap::desce(int i)
{
    int e, d, maior;

    if (i != (tamanhoDeS - 1))
    {
        e = esquerdo(i);
        d = direito(i);

        if (e < tamanhoDeS && S[e] > S[i])
            maior = e;
        else
            maior = i;

        if (d < tamanhoDeS && S[d] > S[maior])
            maior = d;

        if (maior != i)
        {
            troca(i, maior);
            desce(maior);
        }
    }
}

void Heap::sobe(int i)
{
    while (S[pai(i)] < S[i])
    {
        troca(i, pai(i));
        i = pai(i);
    }
}
