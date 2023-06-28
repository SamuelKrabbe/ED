# Makefile para o trabalho

PROG = ordenacao
# A entrada (ENTRA) são as variáveis inc, max, stp, rpt respectivamente
ENTRA = 100 1000 100 10

CPPFLAGS = -Wall -pedantic -std=c++11

default :
	@echo ""
	g++ $(CPPFLAGS) $(PROG).cpp -o $(PROG)
	@echo ""
	@echo "___________________________________________"
	./$(PROG) $(ENTRA)
	@echo ""
	gnuplot geraGraficoTrab2.gnuplot