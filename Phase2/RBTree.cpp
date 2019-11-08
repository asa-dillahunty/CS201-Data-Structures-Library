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
using namespace std;

static bool red = true;
static bool black = false;

template <class K,class V>
class RBTree {
	private:

		/**
		 * Struct for the node class
		 * used in left-leaning red black trees
		 */
		struct rbnode {
			rbnode *left, *right;
			K key;
			V val;
			int size;
			bool color;
		};

		K trashKey;
		V trashVal;
		bool red;
		bool black;
		rbnode* root;


		/**
		 * Returns a pointer to a new node
		 * Mimics a constructor
		 *
		 * @param key: key is used for ordering the nodes
		 * @param val: val is the value stored at each node
		 * @return: returns a pointer to a new node with key K, value V
		 */
		rbnode* newrbnode(K key, V val) {

			rbnode *newnode = new rbnode;
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
		rbnode* newrbnode(K key, V val, bool color) {
			rbnode *newnode = new rbnode;
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->key = key;
			newnode->val = val;
			newnode->color = color;
			newnode->size = 1;

			return newnode;

			//return (newrbnode(key,val)->color = color);
		}

		/**
		 * "Rotates" the node h to become the left child of
		 * its current right child.
		 *
		 * @param h: the node to be rotated
		 * @return: the node on "top" after the rotation.
		 */
		rbnode* rotateLeft(rbnode *h) {

			rbnode *x = h->right;
			h->right = x->left;
			x->left = h;
			x->color = x->left->color;
			x->left->color = red;//impliesx was red

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
		rbnode* rotateRight(rbnode *h) {

			rbnode *x = h->left;
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
		 // does this imply both children exist??
		void colorFlip(rbnode *h) {
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
		bool isRed(rbnode *h) {
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
		int nodeSize(rbnode *h) {
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
		rbnode* insertNode(rbnode *h, K key, V val) {

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
		string printInOrder(rbnode *h) {
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
		string printPostOrder(rbnode *h) {
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
		string printPreOrder(rbnode *h) {
			string output="";

			if (h!=NULL) {
				output += to_string(h->val) + " ";
				output += printPreOrder(h->left);
				output += printPreOrder(h->right);
			}

			return output;
		}

		string printKeyInOrder(rbnode *h) {
			string output="";

			if (h!=NULL) {
				output += printKeyInOrder(h->left);
				output += h->key + " ";
				output += printKeyInOrder(h->right);
			}

			return output;
		}

		/**
		 * Prints a pre-order traversal of the tree with colors listed beside values
		 *
		 * @param h: the current node in the branches being looked at
		 */
		void printColors(rbnode *h) {
			if (h == NULL) return;

			if (h->color) cout << h->val << ": Red" << endl;
			else cout << h->val << ": Black" << endl;

			printColors(h->left);
			printColors(h->right);
		}

		rbnode* fixUp(rbnode *h) {
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

		rbnode* moveRedRight(rbnode *h) {
			colorFlip(h);

			if (isRed(h->left->left)) {
				h = rotateRight(h);
				colorFlip(h);
			}

			return h;
		}

		rbnode* moveRedLeft(rbnode *h) {
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
		rbnode* deleteMin(rbnode *h) {
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
		rbnode* removeNode(rbnode *h, K key) {
			if (key < h->key) {
				if (!isRed(h->left) && !isRed(h->left->left))
					h = moveRedLeft(h);
				h->left = removeNode(h->left, key);
			}
			else {
				// leanRight() in sedgewick
				if (isRed(h->left))
				h = rotateRight(h);

				if (key == h->key && h->right == NULL) {
					return NULL;
				}

				if (!isRed(h->right) && !isRed(h->right->left))
					h = moveRedRight(h);

				if (key == h->key) {
					rbnode *x = h->right;
					while (x->left != NULL)
						x = x->left;

					h->key = x->key;
					h->val = x->val;
					h->right = deleteMin(h->right);
				}
				else {
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
		void clearMemory(rbnode *h) {
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
		rbnode* copy(rbnode *h) {
			rbnode *newnode = newrbnode(h->key, h->val, h->color);
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
		V* findVal(rbnode *h, K key) {
			cout << "key: " << key << " h->key: " << h->key << endl;
			if (h == NULL) return NULL;
			else if (key == h->key) {
				cout << "found key" << endl;
				return &h->val;
			}
			else if (key > h->key) {
				cout << "go right" << endl;
				return findVal(h->right, key);
			}
			else if (key < h->key) {
				cout << "go left" << endl;
				return findVal(h->left, key);
			}
			else {
				cout << "foudn the key" << endl;
				return &h->val;
			}
		}

		/**
		 * Gets the rank of a node
		 *
		 * Rank is something I don't understand at the moment
		 *
		 * @param h: the current node being looked at
		 * @return: the rank of the node;
		 */
		int getRank(rbnode *h, K key, bool found=false) {
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

		V getVal(rbnode *h) {
			if (h == NULL) {
				V val;
				return val;
			}
			else return h->val;
		}

		K getPositionNode(rbnode *h, int k) {
			//get node at position k?? yeah
			/*
			say I am the root, my size is 17, left is 8 and right is 8,
			my order is 9.

			if I'm looking for 10, I tell my right, I'm looking for 1,
			or k - my order, which is left->size + 1

			if I'm looking for 3, I tell left I'm looking for 3
			*/
			if (h == NULL) return trashKey;
			int order = nodeSize(h->left) + 1;

			if (k == order) return h->key;
			else if (k < order) return getPositionNode(h->left, k);
			else return getPositionNode(h->right, k - order);
		}

		int rankNode(rbnode *h, K key) {
			if (h==NULL) return 0;
			else if (key > h->key) return rankNode(h->right, key);
			else if (key < h->key) return rankNode(h->left, key);
			else if (key == h->key) return h->size - nodeSize(h->right);
			else return 0;
		}

		/******************************************************************************
		 * * * * * * * * * * * * * * * End of Node Struct * * * * * * * * * * * * * * *
		 ******************************************************************************/

	public:

		RBTree() {
			this->root = NULL;
			//this->trashKey = (K) NULL; Why does this throw errors
			//this->trashVal = (V) NULL;
			this->red = true;
			this->black = false;
		}

		RBTree(K k[], V v[], int s) {
			this->root = NULL;
			this->red = true;
			this->black = false;

			for (int i = 0; i < s; i++) {
				this->root = insertNode(this->root, k[i], v[i]);
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

		V* search(K key) {
			return findVal(root,key);
		}

		void insert(K k, V v) {
			this->root = insertNode(root, k, v);
			this->root->color=black;
		}

		int remove(K k) {
			int s = nodeSize(this->root);
			this->root = removeNode(this->root, k);

			return s-nodeSize(this->root);// does below, but clever
			/*
			if (nodeSize(this->root) != s) return 1;
			else return 0;
			*/
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

		void printColors() {
			printColors(this->root);
		}

		string keyInOrder() {
			return printKeyInOrder(root);
		}

		K select(int k) {
			return getPositionNode(root,k);
		}

		V rank(K k) {
			return rankNode(root,k);
		}
};