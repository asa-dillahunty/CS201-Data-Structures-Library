all : testDixon testMe

testCDA : CircularDynamicArray.cpp
	g++ -o testCDA CircularDynamicArray.cpp

testDixon : CircularDynamicArray.cpp 201MainPhase1.cpp
	g++ -o testDixon 201MainPhase1.cpp 

testMe : CircularDynamicArray.cpp me.cpp
	g++ -o testMe me.cpp -std=c++14

dixon: testDixon
	./testDixon

test: testMe
	./testMe

clean :
	rm testMe testDixon
