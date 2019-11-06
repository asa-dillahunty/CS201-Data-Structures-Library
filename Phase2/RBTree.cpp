/**
 * @Author Asa Dillahunty
 *
 * CS201 Programming Project Phase 2
 *
 * This program is written to implement
 * learned algorithms in CS201
 *
 * Red Black Trees implemented are left-leaning
 */

#include <iostream>
#include <string>
#include "RBnode.cpp"
using namespace std;

template <class K,class V>
class RBTree {
	public:
		rbnode<K,V>* root;

		RBTree() {
			this->root = NULL;
		}

		RBTree(K k[], V v[], int s) {
			this->root = NULL;
			for (int i = 0; i < s; i++) {
				this->root = insertNode(root, k[i], v[i]);
			}
    	}

		/*
		RBTree(K *k[], int v[], int s) {
			root = NULL;
			for (int i = 0; i < s; i++) {
			root = insert(root, k[i], v[i]);
			if (root->color)
				root->color = black;
			cout << "Insert #" << i+1 << endl;
			cout << "Inorder: ";
			inorder();
			cout << endl << "Preorder: ";
			preorder();
			cout << endl;
			printColors(root);
			}
			treeSize = s;
		}
		*/

		~RBTree() {
			clearMemory(this->root);
		}

		/*
		RBTree(const RBTree &other) {
			treeSize = other.treeSize;
			root = new node;
			root->key = other.root->key;
			root->val = other.root->val;
			root->color = other.root->color;
			copy(root, other.root);
		}
		*/
		/*
		RBTree& operator=(const RBTree& other) {
			if (this != &other) {
				treeSize = other.treeSize;
				root = new node;
				root->key = other.root->key;
				root->val = other.root->val;
				root->color = other.root->color;
				copy(root, other.root);
			}
			return *this;
		}
		*/

		V* search(K k) {
			return findVal(root,k);
		}

		void insert(K k, V v) {
			root = insertNode(root, k, v);
		}

		int remove(K k) {
			int s = nodeSize(this->root);
			this->root = removeNode(root, k);
			if (nodeSize(this->root) != s) return 1;
			else return 0;
		}

		int size() {
			return nodeSize(this->root);
		}

		string preorder() {
			return printPreOrder(root);
		}

		string inorder() {
			return printInOrder(root);
		}

		string postorder() {
			return printPostOrder(root);
		}

		K select(int k) {
			return getPosition(root,k);
		}

		V rank(K k) {
			return rankNode(root,k);
		}
};