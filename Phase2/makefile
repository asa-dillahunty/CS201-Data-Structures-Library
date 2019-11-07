all : treeTest dixonCompile

treeTest : RBTree.cpp 
	g++ -o treeTest treeTest.cpp

test : treeTest
	./treeTest

dixonCompile: 201MainPhase2.cpp
	g++ -o phase2 201MainPhase2.cpp

dixon: dixonCompile
	./phase2

clean :
	rm -f treeTest phase2
