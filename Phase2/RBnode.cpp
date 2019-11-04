/**
 * @Author Asa Dillahunty
 *
 * CS201 Programming Project Phase 2
 *
 * This program is written to implement
 * learned algorithms in CS201
 *
 * These nodes are used to implement left-leaning
 * Red Black Trees
 */

#include <iostream>
#include <string>
using namespace std;

bool red = true;
bool black = false;

/**
 * Struct for the node class
 * used in left-leaning red black trees
 */
template <class K,class V>
struct rbnode {
	rbnode *left, *right;
	K key;
	V val;
	int size;
	bool color;
};

/**
 * Returns a pointer to a new node
 * Mimics a constructor
 * 
 * @param key: key is used for ordering the nodes
 * @param val: val is the value stored at each node
 * @return: returns a pointer to a new node with key K, value V
 */
template<class K, class V>
rbnode<K,V>* newrbnode(K key, V val) {

	rbnode<K,V> *newnode = new rbnode<K,V>;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->key = key;
	newnode->val = val;
	newnode->color = red;
	newnode->size = 1;

	return newnode;
}

/**
 * Returns a pointer to a new node
 * Mimics a constructor
 * 
 * @param key: used for ordering the nodes
 * @param val: the value stored at each node
 * @param color: the color of the node, used for balancing the nodes
 * @return: returns a pointer to a new node with key K, value V
 */
template<class K, class V>
rbnode<K,V>* newrbnode(K key, V val, bool color) {

	rbnode<K,V> *newnode = new rbnode<K,V>;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->key = key;
	newnode->val = val;
	newnode->color = color;
	newnode->size = 1;

	return newnode;
}

/**
 * "Rotates" the node h to become the left child of
 * its current right child.
 * 
 * @param h: the node to be rotated
 * @return: the node on "top" after the rotation.
 */
template<class K, class V>
rbnode<K,V>* rotateLeft(rbnode<K,V> *h) {

	rbnode<K,V> *x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = x->left->color;
	x->left->color = red;

	/***************
	 * update size *
	 ***************/
	h->size = nodeSize(h->left) + nodeSize(h->right) + 1; // h is below x
	x->size = nodeSize(x->left) + nodeSize(x->right) + 1;

	return x;
}

/**
 * "Rotates" the node h to become the right child of
 * its current left child.
 * 
 * @param h: the node to be rotated
 * @return: the node on "top" after the rotation
 */
template<class K, class V>
rbnode<K,V>* rotateRight(rbnode<K,V> *h) {

	rbnode<K,V> *x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = x->right->color;
	x->right->color = red;

	/***************
	 * update size *
	 ***************/
	h->size = nodeSize(h->left) + nodeSize(h->right) + 1; // h is below x
	x->size = nodeSize(x->left) + nodeSize(x->right) + 1;

	return x;
}

/**
 * Inverts the colors of the node and its children
 * 
 * @param h: the node to have its color flipped.
 */
template<class K, class V> // does this imply both children exist??
void colorFlip(rbnode<K,V> *h) {

	h->color = !h->color;
	h->left->color = !h->left->color;
	h->right->color = !h->right->color;
}

/**
 * Returns if the node is red or not
 * 
 * @param h: the node whose color is in question
 * @return: true if red, false if black
 */
template<class K, class V>
bool isRed(rbnode<K,V> *h) {
	if (h == NULL) return black;
	else return h->color; //red is true
}

/**
 * Returns the size of the node
 * 
 * Size is the number of nodes "below" it, plus 1 (itself)
 * 
 * @param h: the node whose size is in question
 * @return: the size of the node
 */
template<class K, class V>
int nodeSize(rbnode<K,V> *h) {
	if (h == NULL) return 0;
	else return h->size; // assume we update this (safe?)
}

/**
 * Inserts a node into the branching nodes below
 * 
 * @param h: the current node in the branches being looked at
 * @param key: the key of the node to be inserted
 * @param val: the value of the node to be inserted
 * @return: the updated node on top after the insert
 */
template<class K, class V>
rbnode<K,V>* insertNode(rbnode<K,V> *h, K key, V val) {

	if (h == NULL) {
		return newrbnode(key, val);
	}

	if (isRed(h->left) && isRed(h->right)) colorFlip(h);

	if (key < h->key)
		h->left = insertNode(h->left, key, val);
	else if (key > h->key)
		h->right = insertNode(h->right, key, val);
	else if (key == h->key)
		h->val = val;

	if (isRed(h->right))
		h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);

	/***************
	 * update size *
	 ***************/
	//why is this necessary when it was just done in the rotates?
	//it may not rotate
	h->size = nodeSize(h->left) + nodeSize(h->right) + 1;
	return h;
}

/**
 * Returns a string representation of an in order traversal of the tree
 * 
 * @param h: the current node in the branches being looked at
 * @return: a string representation of an in order traversal of the tree
 */
template<class K, class V>
string printInOrder(rbnode<K,V> *h) {
	string output="";

	if (h!=NULL) {
		output += printInOrder(h->left);
		output += to_string(h->val) + " ";
		output += printInOrder(h->right);
	}

	return output;
}

/**
 * Returns a string representation of a post-order traversal of the tree
 * 
 * @param h: the current node in the branches being looked at
 * @return: a string representation of a post-order traversal of the tree
 */
template<class K, class V>
string printPostOrder(rbnode<K,V> *h) {
	string output="";

	if (h!=NULL) {
		output += printPostOrder(h->left);
		output += printPostOrder(h->right);
		output += to_string(h->val) + " ";
	}

	return output;
}

/**
 * Returns a string representation of a pre-order traversal of the tree
 * 
 * @param h: the current node in the branches being looked at
 * @return: a string representation of a pre-order traversal of the tree
 */
template<class K, class V>
string printPreOrder(rbnode<K,V> *h) {
	string output="";

	if (h!=NULL) {
		output += to_string(h->val) + " ";
		output += printPreOrder(h->left);
		output += printPreOrder(h->right);
	}

	return output;
}

/**
 * Prints a pre-order traversal of the tree with colors listed beside values
 * 
 * @param h: the current node in the branches being looked at
 */
template<class K, class V>
void printColors(rbnode<K,V> *h) {
	if (h == NULL) return;

	if (h->color) cout << h->val << ": Red" << endl;
	else cout << h->val << ": Black" << endl;

	printColors(h->left);
	printColors(h->right);
}

template<class K, class V>
rbnode<K,V>* fixUp(rbnode<K,V> *h) {
	if (isRed(h->right))
		h = rotateLeft(h);

	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);

	if (isRed(h->left) && isRed(h->right))
		colorFlip(h);

	/***************
	 * update size *
	 ***************/
	h->size = nodeSize(h->left) + nodeSize(h->right) + 1;

	return h;
}

template<class K, class V>
rbnode<K,V>* moveRedRight(rbnode<K,V> *h) {
	colorFlip(h);

	if (isRed(h->left->left)) {
		h = rotateRight(h);
		colorFlip(h);
	}

	return h;
}

template<class K, class V>
rbnode<K,V>* moveRedLeft(rbnode<K,V> *h) {
	colorFlip(h);

	if (isRed(h->right->left)) {
		h->right = rotateRight(h->right);
		h = rotateLeft(h);
		colorFlip(h);
	}

	return h;
}

/**
 * Deletes the smallest key value in the tree
 * 
 * @param h: the node currently being looked at in the tree
 * @return: the node on top after the deletion
 */
template<class K, class V>
rbnode<K,V>* deleteMin(rbnode<K,V> *h) {
	if (h->left == NULL) return NULL; // do we not care about right? //free memory?

	if (!isRed(h->left) && !isRed(h->left->left))
		h = moveRedLeft(h);

	h->left = deleteMin(h->left);

	return fixUp(h);
}

/**
 * Removes the node with key value "key" from the tree
 * 
 * @param h: the node currently being looked at in the tree
 * @param key: the key value of the node to be deleted
 * @return: returns the node on top after the deletion
 */
template<class K, class V>
rbnode<K,V>* removeNode(rbnode<K,V> *h, K key) {
	if (key < h->key) { // I feel like this does not imply a left
				// possible null pointer exception when data is not in tree
		if (!isRed(h->left) && !isRed(h->left->left))
			h = moveRedLeft(h);
		h->left = removeNode(h->left, key);
	}
	else {
		// leanRight() in sedgewick
		if (isRed(h->left))
			h = rotateRight(h);
		if (key == h->key && h->right == NULL) {
			//removed = true;
			return NULL;
		}
		if (!isRed(h->right) && !isRed(h->right->left))
			h = moveRedRight(h);
		if (key == h->key) {
			//removed = true;
			rbnode<K,V> *x = h->right;
			while (x->left != NULL)
				x = x->left;
			h->key = x->key;
			h->val = x->val;
			h->right = deleteMin(h->right); //lol what? shouldn't this be x
		}
		else{
			//cout << h->key << endl; //what?
			h->right = removeNode(h->right, key);
		}
	}

	/***************
	 * update size *
	 ***************/
	//h->size = nodeSize(h->left) + nodeSize(h->right) + 1;

	return fixUp(h);
}

/**
 * Clears the memory?
 * Doesn't look like it does anything honestly
 * I don't understand structs.
 */
template<class K, class V>
void clearMemory(rbnode<K,V> *h) {
	if (h == NULL) return;
	clearMemory(h->left);
	clearMemory(h->right);
	free(h);
}

/**
 * Creates a deep copy of the node
 * 
 * @param h: the node being copied
 * @return: the copy of the node
 */
template<class K, class V>
rbnode<K,V>* copy(rbnode<K,V> *h) {
	rbnode<K,V> *newnode = newrbnode(h->key, h->val, h->color);
	if (h->right!=NULL) newnode->right = copy(h->right);
	if (h->left!=NULL) newnode->left = copy(h->left);
	newnode->size = h->size;

	return newnode;
}

/**
 * Finds the value of a node with the specified key, k
 * 
 * @param h: the node currently being looked at
 * @param k: the key of the node being searched for
 * @return: returns the value stored in the node with key value k
 */
template<class K, class V>
V findVal(rbnode<K,V> *h, K k) {
	if (h == NULL) return NULL;
	else if (h->key == k) return h->val;
	else if (h->key > k) return findVal(h->right, k);
	else if (h->key < k) return findVal(h->left, k);
	else return NULL;
}

/**
 * Gets the rank of a node
 * 
 * Rank is something I don't understand at the moment
 * 
 * @param h: the current node being looked at
 * @return: the rank of the node;
 */
template<class K, class V>
int getRank(rbnode<K,V> *h, K key, bool found=false) {
	if (h == NULL) return 0;

	if (found)
		if (h->color) return getRank(h->right,key,found);// right path should be shorter
		else return getRank(h->right,key,found)+1;

	else if (h->key == key)
		if (h->color) return getRank(h->right,key,!found);// right path should be shorter
		else return getRank(h->right,key,!found)+1;

	else if (h->key > key) //go right
		return getRank(h->right,key,found);

	else return getRank(h->left,key,found);
}

template<class K, class V>
V getVal(rbnode<K,V> *h) {
	if (h == NULL) {
		V val;
		return val;
	}
	else return h->val;
}

template<class K, class V>
rbnode<K,V>* getPosition(rbnode<K,V> *h, int k) {
	//get node at position k?? yeah
	/*
	say I am the root, my size is 17, left is 8 and right is 8,
	my order is 9.

	if I'm looking for 10, I tell my right, I'm looking for 1, 
	or k - my order, which is left->size + 1

	if I'm looking for 3, I tell left I'm looking for 3
	*/
	if (h == NULL) return NULL;
	int order = nodeSize(h->left) + 1;

	if (k == order) return h;
	else if (k < order) return getPosition(h->left, k);
	else return getPosition(h->right, k - order);
}