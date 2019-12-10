/**
 * @Author Asa Dillahunty
 *
 * CS201 Programming Project Phase 3
 *
 * This program is written to implement
 * learned algorithms in CS201
 *
 * It's a binomial heap
 */
#include <iostream>
#include "CDA.cpp"
using namespace std;

template<class K,class V>
class BHeap {
  	private:

	struct node {
		K key;
		V val;
		int degree;
		node *child;
		node *sibling;
		node *parent;
	};

	node *newNode(K key, V value) {
		node *newnode = new node;
		newnode->key = key;
		newnode->val = value;
		newnode->degree = 0;
		newnode->child = NULL;
		newnode->sibling = NULL;
		newnode->parent = NULL;
		return newnode;
	}

	node *mergeTree(node *x, node *y) {
		if (x->key < y->key) {
			y->parent = x;
			y->sibling = x->child;
			x->child = y;
			x->degree++;
			return x;
		}
		else {
			x->parent = y;
			x->sibling = y->child;
			y->child = x;
			y->degree++;
			return y;
		}
	}

	void preorder(node *curr) {
		if (curr == NULL) return;

		cout << curr->key << " ";
		preorder(curr->child);
		preorder(curr->sibling);
	}

	void deleteTree(node *curr) {
		if (curr == NULL) return;

		deleteTree(curr->child);
		deleteTree(curr->sibling);
		free(curr);
		return;
	}

	node* copyTree(node *curr) {
		if (curr == NULL) return NULL;

		node *r = newNode(curr->key, curr->val);
		r->degree = curr->degree;
		r->child = copyTree(curr->child);
		r->sibling = copyTree(curr->sibling);
		return r;
	}

	CDA<node*> BinHeap;

	public:
		BHeap() {
			BinHeap = CDA<node*> ();
		}

		BHeap(K keys[], V values[], int s) {
			BinHeap = CDA<node*> ();
			for (int i = 0; i < s; i++) {
				insert(keys[i], values[i]);
			}
		}

		BHeap(CDA<node*> curr) {
			BinHeap = curr;
		}

		~BHeap() {
			for (int i=0;i<BinHeap.length();i++)
				deleteTree(BinHeap[i]);
		}

		BHeap(BHeap &other) {
			for (int i = 0; i < other.BinHeap.length(); i++) {
				BinHeap.addEnd(copyTree(other.BinHeap[i]));
			}
		}

		BHeap& operator=(BHeap& other) {
			if (this != &other) {
				for (int i = 0; i < other.BinHeap.length(); i++) {
					BinHeap.addEnd(copyTree(other.BinHeap[i]));
				}
			}
			return *this;
		}

		void insert(K key, V value) {
			bool inserted = false;
			node *curr = newNode(key, value);
			for (int i = 0; i < BinHeap.length(); i++) {
				if (BinHeap[i] == NULL) {
					BinHeap[i] = curr;
					inserted = true;
					break;
				}
				else {
					curr = mergeTree(curr, BinHeap[i]);
					BinHeap[i] = NULL;
				}
			}
			if (!inserted)
				BinHeap.addEnd(curr);
		}

		K peakKey() {
			bool minStarted = false;
			K minn;

			for (int i = 0; i < BinHeap.length(); i++) {
				if (BinHeap[i] == NULL)
					continue;
				if (!minStarted)
					minn = BinHeap[i]->key;
				else if (BinHeap[i]->key < minn)
					minn = BinHeap[i]->key;
			}
			return minn;
		}

			V peakValue() {
			bool minStarted = false;
			K minn;
			V minnVal;
			for (int i = 0; i < BinHeap.length(); i++) {
				if (BinHeap[i] == NULL)
					continue;
				if (!minStarted) {
					minn = BinHeap[i]->key;
					minnVal = BinHeap[i]->val;
				}
				else if (BinHeap[i]->key < minn) {
					minn = BinHeap[i]->key;
					minnVal = BinHeap[i]->val;
				}
			}
			return minnVal;
		}

		void merge(BHeap H2) {
			node *carry = NULL;
			for (int i = 0; i < H2.BinHeap.length(); i++) {
				if (i >= this->BinHeap.length()) {
					if (carry == NULL && H2.BinHeap[i] == NULL)
						this->BinHeap.addEnd(NULL);
					else if (carry == NULL)
						this->BinHeap.addEnd(H2.BinHeap[i]);
					else if (H2.BinHeap[i] == NULL) {
						this->BinHeap.addEnd(carry);
						carry = NULL;
					}
					else {
						carry = mergeTree(carry, H2.BinHeap[i]);
					}
				}
				if (H2.BinHeap[i] == NULL && this->BinHeap[i] == NULL && carry == NULL)
					continue;
				else if (H2.BinHeap[i] == NULL && this->BinHeap[i] == NULL) {
					this->BinHeap[i] = carry;
					carry = NULL;
				}
				else if (H2.BinHeap[i] == NULL && carry == NULL)
					continue;
				else if (this->BinHeap[i] == NULL && carry == NULL)
					this->BinHeap[i] = H2.BinHeap[i];
				else if (carry == NULL)  {
					carry = mergeTree(this->BinHeap[i], H2.BinHeap[i]);
					this->BinHeap[i] = NULL;
				}
				else if (this->BinHeap[i] == NULL) {
					carry = mergeTree(carry, H2.BinHeap[i]);
				}
				else if (H2.BinHeap[i] == NULL) {
					carry = mergeTree(carry, this->BinHeap[i]);
					this->BinHeap[i] = NULL;
				}
				else {
					carry = mergeTree(carry, H2.BinHeap[i]);
				}
			}
			if (carry != NULL && H2.BinHeap.length() >= this->BinHeap.length()) {
				this->BinHeap.addEnd(carry);
				carry = NULL;
			}
			else if (carry != NULL) {
				for (int i = H2.BinHeap.length(); i < this->BinHeap.length(); i++) {
					if (this->BinHeap[i] == NULL) {
						this->BinHeap[i] = carry;
						carry = NULL;
						break;
					}
					else {
						carry = mergeTree(carry, this->BinHeap[i]);
						this->BinHeap[i] = NULL;
					}
				}
				if (carry != NULL) this->BinHeap.addEnd(carry);
			}
		}

		K extractMin() {
		bool minStarted = false;
		K minn;
		int minnIndex = 0;
		for (int i = 0; i < BinHeap.length(); i++) {
			if (BinHeap[i] == NULL) continue;
			if (!minStarted) {
				minn = BinHeap[i]->key;
				minnIndex = i;
			}
			else if (BinHeap[i]->key < minn) {
				minn = BinHeap[i]->key;
				minnIndex = i;
			}
		}
		if (minnIndex != 0) {
			CDA<node*> tempCDA(BinHeap[minnIndex]->degree);
			node *start = BinHeap[minnIndex]->child;
			tempCDA[BinHeap[minnIndex]->degree - 1] = start;
			int k = BinHeap[minnIndex]->degree - 2;

			while (start->sibling != NULL) {
				start = start->sibling;
				tempCDA[k] = start;
				k--;
			}
			for (int i = 0; i < tempCDA.length(); i++) {
				tempCDA[i]->sibling = NULL;
			}
			BinHeap[minnIndex] = NULL;
			BHeap temp(tempCDA);
			merge(temp);
		}
		else
				BinHeap[minnIndex] = NULL;
			return minn;
		}

		void printKey() {
			for (int i = 0; i < BinHeap.length(); i++) {
				if (BinHeap[i] == NULL)
				continue;
				cout << "B" << BinHeap[i]->degree << endl;
				preorder(BinHeap[i]);
				cout << endl << endl;
			}
		}
};