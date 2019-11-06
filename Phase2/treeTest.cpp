#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "RBTree.cpp"
using namespace std;



void dumpTree(RBTree<int,int> *tree) { //true for read, false for write

	cout << "size is : " << tree->size() << endl;
	cout << "inorder is : " << tree->inorder() << endl;
	cout << "preorder is : " << tree->preorder() << endl;
}

void dumpTree(RBTree<int,int> *tree, string filename, bool cat) { //cat:=> concatenate
	ofstream out;

	if (cat) out.open(filename,ios::app);
	else out.open(filename);

	out << "size is : " << tree->size() << endl;
	out << "inorder is : " << tree->inorder() << endl;
	out << "preorder is : " << tree->preorder() << endl;
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
	dumpTree(tree,"testTxt/test.txt",true);
	dumpTree(tree);
	tree->insert(1,1);
	dumpTree(tree);

	int s=10;
	for (int i=0;i<10;i++) {
		if (tree->size() != s) cout << "Sux" << endl;
		tree->remove(i);
		s--;
		if (tree->size() != s) cout << "Sux" << endl;
	}
}