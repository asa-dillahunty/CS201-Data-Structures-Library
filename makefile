all : testDixon testMe

testCDA : CircularDynamicArray.cpp
	g++ -o testCDA CircularDynamicArray.cpp

testDixon : CircularDynamicArray.cpp dixon.cpp
	g++ -o testDixon dixon.cpp

testMe : CircularDynamicArray.cpp me.cpp
	g++ -o testMe me.cpp

dixon: testDixon
	./testDixon

test: testMe
	./testMe

clean :
	rm testMe testDixon
