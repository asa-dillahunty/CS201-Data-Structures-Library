all : treeTest dixonCompile

treeTest : RBTree.cpp treeTest.cpp
	g++ -o treeTest treeTest.cpp

test : treeTest
	./treeTest

dixonCompile: 201MainPhase2.cpp RBTree.cpp
	g++ -o phase2 201MainPhase2.cpp

dixon: dixonCompile
	./phase2

clean :
	rm -f treeTest phase2
