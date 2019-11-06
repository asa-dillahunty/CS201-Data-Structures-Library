all : treeTest dixon

treeTest : RBnode.cpp RBTree.cpp 
	g++ -o treeTest treeTest.cpp

test : treeTest
	./treeTest

dixon: 201MainPhase2.cpp
	g++ -o phase2 201MainPhase2.cpp
	./phase2

clean :
	rm -f treeTest phase2
