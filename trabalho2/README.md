================= Cálculo de Tempo de Execução de Algoritmos =================

Descrição do Projeto:

    Este projeto consiste em um código que realiza o cálculo do tempo de execução de três algoritmos de ordenação diferentes: 

        Algoritmo A = imprime em pré-ordem a árvore binária de busca;
        Algoritmo B = imprime em pré-ordem a árvore AVL;
        Algoritmo C = Heapsort;

    O objetivo é fornecer uma medida precisa do tempo necessário para executar cada um dos algoritmos, permitindo uma comparação de desempenho.

Requisitos do Sistema:

    Para executar o programa, o usuário precisa ter instalados os seguintes requisitos:

    make: Utilizado para automatizar o processo de compilação e execução do código.
    gnuplot: Uma ferramenta para criação de gráficos e visualização dos resultados.

Instalação:

    Siga as instruções abaixo para instalar e executar o programa:

    -> Verifique se o make está instalado executando o seguinte comando no terminal:
        make --version

    -> Se o make estiver instalado, você verá a versão instalada sendo exibida. Caso contrário, você precisará instalá-lo antes de prosseguir.

    -> Verifique se o gnuplot está instalado executando o seguinte comando no terminal:
        gnuplot --version

    -> Se o gnuplot estiver instalado, você verá a versão instalada sendo exibida. Caso contrário, você precisará instalá-lo antes de prosseguir.

    -> Abra o terminal e navegue até o diretório onde o código-fonte está.

    -> Execute o seguinte comando para compilar o código:
        make

Após a execução, você encontrará os resultados do tempo de execução no arquivo de saída "plorTrab2.txt".
Para visualizar os resultados em um gráfico, abra o arquivo "AlgoritmosDeOrdenacao.png".

Configuração dos Algoritmos:

    Os algoritmos A, B e C podem ser encontrados no código-fonte do projeto. Cada um desses algoritmos está implementado em uma função separada, que pode ser chamada para executar o algoritmo individualmente.

Saída:

    Após a execução do programa, as médias aritméticas dos tempos de execução dos algoritmos serão imprimidos no terminal/console e armazenados no arquivo "plotTrab2.txt". Este arquivo conterá as médias aritméticas dos tempos de execução registrados para cada algoritmo para cada tamanho de entrada n dado.

Visualização dos Resultados:

    Os resultados dos tempos de execução podem ser visualizados em um gráfico utilizando o gnuplot. Após a execução do programa, você pode vizualizar o gráfico abrindo o arquivo "AlgoritmosDeOrdenacao.png". Isso abrirá uma janela com o gráfico contendo os tempos de execução dos algoritmos A, B e C.

Considerações Finais:

    Este projeto fornece uma maneira fácil e conveniente de calcular e comparar as médias aritméticas dos tempos de execução de diferentes algoritmos. Certifique-se de ter o make e o gnuplot instalados antes de executar o programa. Para mudar as variáveis de entrada inc, max, stp e rpt entre no arquivo "makefile" e altere os valores da variável ENTRA respectivamente.