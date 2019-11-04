#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "RBTree.cpp"
using namespace std;

void dumpTree(RBTree<int,int> *tree, string filename, bool rw) { //true for read, false for write
    string line;
    string rline;//read line
    if (rw) {
        ofstream myfile;
        myfile.open (filename);
    }
    else {
        ifstream myfile;
        myfile.open(filename);
    }

	line = "size is : " + to_string(tree->size());

	cout << "inorder is : " << tree->inorder() << endl;
	cout << "preorder is : " << tree->preorder() << endl;
}

bool insertTest(string filename, bool rw) { 

    bool result=true;
    RBTree<int,int> *tree = new RBTree<int,int>();
	for (int i=0;i<10;i++) {
		if (tree->size() != i) cout << "Sux" << endl;
		tree->insert(i,i);
		if (tree->size() != i+1) cout << "Sux" << endl;
	}
	dumpTree(tree);

    return result;
}

int main() {
	RBTree<int,int> *tree = new RBTree<int,int>();
	for (int i=0;i<10;i++) {
		if (tree->size() != i) cout << "Sux" << endl;
		tree->insert(i,i);
		if (tree->size() != i+1) cout << "Sux" << endl;
	}
	dumpTree(tree);
	tree->insert(1,1);
	dumpTree(tree);

	for (int i=0;i<10;i++) {
		if (tree->getOrder(i+1) != i) cout<< tree->getOrder(i+1) << ":" << i <<endl;
	}

	int s=10;
	for (int i=0;i<10;i++) {
		if (tree->size() != s) cout << "Sux" << endl;
		tree->remove(i);
		s--;
		if (tree->size() != s) cout << "Sux" << endl;
	}
}