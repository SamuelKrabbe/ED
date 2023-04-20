Rede::~Rede()
{
    Vizinho *aux1, *aux2;

    for (int i = 0; i < tamanhoRede; i++)
    {
        aux1 = (rede + i)->prox;
        aux2 = aux1->prox;

        while (aux1 != NULL)
        {
            delete aux1;
            aux1 = aux2;
            aux2 = aux1->prox;
        }
    }

    for (int j = 0; j < tamanhoOriginal; j++)
        delete rede[j];
    delete rede;
}

MinHeap::~MinHeap()
{
    for (int i = 0; i < tamanhoOriginal; i++)
        delete minHeap[i];
}
