all:
	g++ -o phase3 201MainPhase3.cpp
	g++ -o asaTest me.cpp

asaTest:
	g++ -o asaTest me.cpp

asa: asaTest
	./asaTest
	rm asaTest

test: all
	./phase3

clean:
	rm phase3
