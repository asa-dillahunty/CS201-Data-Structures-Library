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

#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;

template<typename K,typename V>
class Heap {
    private:

        struct node {
			K key;
			V val;
		};

        node* newNode(K key, V value) {
            node *newNode = new node;
            newNode->key = key;
            newNode->value = value;
            return newNode;
        }

        CircularDynamicArray<node> CDA;

    public:

        Heap() {
			CDA = new CircularDynamicArray<node>();
		}

        ~Heap() {
        }

        /**
         * Returns the minimum key in the heap without modifying the heap
         */
        K peakKey() {

        }

        /**
         * Returns the value associated with the minimum key in the heap
         * without modifying the heap
         */
        V peakValue() {

        }

        /**
         * Removes the minimum key in the heap and returns the key
         */
        K extractMin() {

        }

        /**
         * inserts the key and value pair into the heap
         */
        void insert(K key, V value) {
        }

        /**
         * Writes the keys stored in the array starting at the root
         */
        void printKey() {

        }
};