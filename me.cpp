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
#include <chrono>
#include "CircularDynamicArray.cpp"

bool testQuickSort() {
    std::cout << "Starting Quick Sort Test" << std::endl;
    CircularDynamicArray<int> list;

    for (int j=1;j<16;j++) {
        for (int k=10;k<1000000;k=k*10) {

            for (int h=0;h<k;h+=2) {
                list.addEnd(h);
                list.addFront(h+1);
            }
            
            list.randomize();
            list.quickSort();

            for (int i=0;i<k;i++) {
                if (i!=list[i]) return false;
            }

            list.clear();
        }
    }
    std::cout << "Finished Quick Sort Test With No Errors" << std::endl;
    return true;
}

bool testStableSort() {
    std::cout << "Starting Stable Sort Test" << std::endl;
    CircularDynamicArray<int> list;

    for (int j=1;j<16;j++) {
        for (int k=10;k<1000000;k=k*10) {

            for (int h=0;h<k;h+=2) {
                list.addEnd(h);
                list.addFront(h+1);
            }
            
            list.randomize();
            list.stableSort();

            for (int i=0;i<k;i++) {
                if (i!=list[i]) return false;
            }

            list.clear();
        }
    }
    std::cout << "Finished Stable Sort Test With No Errors" << std::endl;
    return true;
}

bool testRadixSort() {
    std::cout << "Starting Radix Sort Test" << std::endl;
    CircularDynamicArray<int> list;

    for (int j=1;j<16;j++) {
        for (int k=10;k<1000000;k=k*10) {

            for (int h=0;h<k;h+=2) {
                list.addEnd(h);
                list.addFront(h+1);
            }
            
            list.randomize();
            list.radixSort(j);

            for (int i=0;i<k;i++) {
                if (i!=list[i]) return false;
            }

            list.clear();
        }
    }
    std::cout << "Finished Radix Sort Test With No Errors" << std::endl;
    return true;
}

bool testWCSelect() {
    std::cout << "Starting WCSelect Test" << std::endl;
    CircularDynamicArray<int> list;
    int total=500;
    
    for (int j=0;j<total;j++) list.addEnd(j);
    
    
    for (int j=1;j<total+1;j++) {
        if (list.WCSelect(j) != j-1) {
            return false;
        }
    }
    
    for (int j=1;j<total+1;j++) {
        list.randomize();
        if (list.WCSelect(j) != j-1) {
            return false;
        }
    }
    
    
    
    std::cout << "Fished WCSelect Test With No Errors" << std::endl;
    return true;
}

void timeWCSelect() {
    CircularDynamicArray<int> list;
    
    auto total = std::chrono::high_resolution_clock::now();
    
    for (int numElements=49;numElements<50;numElements*=2) {
        
        for (int h=0;h<numElements;h++) list.addEnd(h);
            for (int j=0;j<numElements;j++) list.addFront(j);
                for (int k=0;k<numElements;k++) list.addEnd(k);
                    for (int i=0;i<numElements;i+=2) {
                        list.addEnd(i);
                        list.addFront(i+1);
                    }
        //This should be *4
        
        using namespace std::chrono;
        list.randomize();
        auto start = high_resolution_clock::now();
        for (int i=1;i<=list.length();i++)
            if (list.WCSelect(i) != (i-1)/4) std::cout << "FUCK";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << numElements << "," << duration.count() << std::endl;
    }
}

void timeSorts() {
    CircularDynamicArray<int> list;
    
    for (int numElements=1;numElements<50;numElements*=2) {
        
        for (int h=0;h<numElements;h++) list.addEnd(h);
            for (int j=0;j<numElements;j++) list.addFront(j);
                for (int k=0;k<numElements;k++) list.addEnd(k);
                    for (int i=0;i<numElements;i+=2) {
                        list.addEnd(i);
                        list.addFront(i+1);
                    }
        //This should be *4
        
        using namespace std::chrono;
        list.randomize();
        auto start = high_resolution_clock::now();
        list.quickSort();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << numElements << "," << duration.count() << std::endl;
    }
}

int main(int argc, char const *argv[]) {
	std::cout << "Hello World!\n" << std::endl;
    
    timeWCSelect();
    
    if (!testWCSelect()) {
        std::cout << "WCSelect Failed" << std::endl;
    }
    if (!testQuickSort()) {
        std::cout << "Quick Sort Failed" << std::endl;
    }
    if (!testStableSort()) {
        std::cout << "Stable Sort Failed" << std::endl;
    }
    if (!testRadixSort()) {
        std::cout << "Radix Sort Failed" << std::endl;
    }
    
    return 0;
}
