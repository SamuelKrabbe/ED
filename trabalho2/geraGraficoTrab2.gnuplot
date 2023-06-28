# Set the terminal type and output file format
set terminal png
set output 'AlgoritmosDeOrdenacao.png'

# Set the plot title and axis labels
set title 'Algoritmos de Ordenação'
set xlabel 'Tamanho da entrada'
set ylabel 'Tempo(s)'

# Set the plot style and line colors
set style data linespoints
set style line 1 lc rgb '#E41A1C' pt 7  # Linha vermelha com marcadores quadrados
set style line 2 lc rgb '#377EB8' pt 9  # Linha azul com marcadores estrela
set style line 3 lc rgb '#4DAF4A' pt 5  # Linha verde com marcadores de cruz

# Specify the data file and columns to plot
plot 'plotTrab2.txt' using 1:2 with linespoints ls 1 title 'ABB', \
     'plotTrab2.txt' using 1:3 with linespoints ls 2 title 'AVL', \
     'plotTrab2.txt' using 1:4 with linespoints ls 3 title 'Heapsort'
