/**
 * @Author Asa Dillahunty
 *
 * CS201 Programming Project
 *
 * This program is written to implement
 * learned algorithms in CS201
 *
 * CDA stands for Circular Dynamic Array
 */
#include <iostream>
#include <string>
#include <math.h>
#include "CircularDynamicArray.cpp"

int main(int argc, char const *argv[]) {
	std::cout << "Hello World!\n" << std::endl;


	CircularDynamicArray<int> list;
	int numElements=60;

	for (int i=0;i<numElements;i+=2) {
		list.addEnd(i);
		list.addFront(i+1);
	}

	list.printList();
	list.clear();
	list.printList();

	for (int i=0;i<numElements;i+=2) {
		list.addEnd(i);
		list.addFront(i+1);
	}

	list.printList();

	list.quickSort();
	list.printList();

	/*
	CircularDynamicArray<double> listD;
	listD.addFront(.1);
	listD.addFront(.01);
	listD.addFront(.001);
	listD.addFront(.0001);
	listD.addFront(.2);
	listD.printList();
	listD.stableSort();
	listD.printList();
	listD.radixSort(4);
	listD.printList();
	*/

	/*
	CircularDynamicArray<std::string> listS;
	listS.addFront("A Hello");
	listS.addFront("B This");
	listS.addFront("C Message");
	listS.addFront("D Is");
	listS.addFront("E Backwards");
	listS.printList();
	listS.stableSort();
	listS.printList();
	listS.radixSort(4);
	listS.printList();
    */
   /*
   CircularDynamicArray<char> listC;
   for (char i='A';i<'Y';i+=2) {
		listC.addEnd(i);
		listC.addFront(i+1);
	}

	std::cout << "********************" << std::endl;
	listC.printList();
	listC.stableSort();
	listC.printList();

	int ndex = listC.linearSearch('C');
	std::cout << listC.linearSearch('C') << std::endl;
	std::cout << listC[ndex] << std::endl;

	int ndex2 = listC.binarySearch('C');
	std::cout << listC.binarySearch('C') << std::endl;
	std::cout << listC[ndex2] << std::endl;
	std::cout << "********************" << std::endl;


	list.printList();
	int dex = list.linearSearch(5);
	std::cout << list.linearSearch(5) << std::endl;
	std::cout << list[dex] << std::endl;

	list.stableSort();
	list.printList();
	int dex2 = list.binarySearch(3);
	std::cout << list.binarySearch(3) << std::endl;
	std::cout << list[dex2] << std::endl;



	for (int j=1;j<16;j++) {
		CircularDynamicArray<int> list2;

		for (int k=10;k<10000000;k=k*10) {

			for (int h=0;h<k;h+=2) {
				list2.addEnd(h);
				list2.addFront(h+1);
			}

			list2.radixSort(j);

			for (int i=0;i<k;i++) {
				if (i!=list2[i]) std::cout << "YOU SUCK" << std::endl;
			}

			list2.clear();
		}
	}
	*/
}