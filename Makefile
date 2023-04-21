#Makefile para o trabalho

PROG = trab1
ENTRA = entrada.txt

CPPFLAGS = -Wall -pedantic -std=c++11

default :
	@echo "Verificação de vazamnto de memória:"
	valgrind --leak-check=full --show-reachable=yes --track-fds=yes ./$(PROG).cpp
	@echo "-----------------------------------"
	@echo ""
	g++ $(CPPFLAGS) $(PROG).cpp -o $(PROG)
	@echo ""
	@echo "-----------------------------------"
	@echo "Teste:"
	./$(PROG) < $(ENTRA)