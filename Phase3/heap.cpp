/**
 * @Author Asa Dillahunty
 *
 * CS201 Programming Project Phase 3
 *
 * This program is written to implement
 * learned algorithms in CS201
 *
 * It's a heap
 */

#ifndef Included_CDA
#define Included_CDA
#include "CDA.cpp"
#endif

#include <iostream>
using namespace std;

template<class K,class V>
class Heap {

  private:
	struct node {
		K key;
		V val;
	};

	CDA<node> minHeap;

	void swap(node &a, node &b) {
		node temp = a;
		a = b;
		b = temp;
	}

	void heapify(node arr[], int n, int i) {
		int min = i;
		int lChild = 2*i + 1;
		int rChild = 2*i + 2;

		if (lChild < n && arr[lChild].key < arr[min].key)
			min = lChild;
		if (rChild < n && arr[rChild].key < arr[min].key)
			min = rChild;
		if (min != i) {
			swap(arr[i], arr[min]);
			heapify(arr, n, min);
		}
	}

	void fixUp(int index) {
		//if parent smaller, swap
		int parent = (index-1)/2;

		//if parent == index this will not be called, no worries
		if (minHeap[parent].key < minHeap[index].key) { //swap
			node swap = minHeap[parent];
			minHeap[parent] = minHeap[index];
			minHeap[index] = swap;

			//check if still broke
			fixUp(parent);
		}
	}
	

  public:
	Heap() {
		minHeap = CDA<node> ();
	}

	Heap(K k[], V v[], int s) {
	  	node *list = new node[s];
	  	for (int i = 0; i < s; i++) {
			node *a = new node;
			a->key = k[i];
			a->val = v[i];
			list[i] = *a;
		}

		for (int i = (s/2) - 1; i >= 0; i--) {
			heapify(list, s, i);
		}

		minHeap = CDA<node> ();
		for (int i = 0; i < s; i++) {
			minHeap.addEnd(list[i]);
		}
	}

	~Heap() {
	}

	K peakKey() {
	  	return minHeap[0].key;
	}

	V peakValue() {
	  	return minHeap[0].val;
	}

	K extractMin() {
			K key = minHeap[0].key;

			//check both kids
			int index = 0;
			int size = minHeap.length() - 1; // to fix index + 1
			while(index < size) {
				if (minHeap[index].key < minHeap[index+1].key) { //index becomes new parent
					minHeap[(index-1)/2] = minHeap[index];
					//index = next index
					index = index*2 + 1;
				}
				else {
					minHeap[(index-1)/2] = minHeap[index + 1];
					index = (index + 1)*2 + 1;
				}
				//what if index+1 !< size
			}

			index = (index-1)/2; //go back to parent
			minHeap[index] = minHeap[size]; // size is size - 1
			fixUp(index);

			minHeap.delEnd();
			return key;
		}

	void insert(K key, V value) {
		node *newnode = new node;
		newnode->key = key;
		newnode->val = value;

		minHeap.addEnd(*newnode);
		fixUp(minHeap.length()-1);
	}

	void printKey() {
		for (int i = 0; i < minHeap.length(); i++)
			cout << minHeap[i].key << " ";
		cout << endl;
	}
};