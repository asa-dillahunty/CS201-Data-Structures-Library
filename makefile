all : testCDA

testCDA : cda.cpp
	g++ -o testCDA cda.cpp

test : testCDA
	./testCDA

clean :
	rm testCDA
