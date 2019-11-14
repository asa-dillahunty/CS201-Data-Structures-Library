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
using namespace std;

template<typename K,typename V>
class RBTree
{
	private:
		
		/**
		 * Struct for the node class
		 * used in left-leaning red black trees
		 */
		struct RBNode {
			RBNode *left, *right;
			K key;
			V val;
			bool color;
			int size;
		};

		bool red;
		bool black;
		RBNode* root;

		/**
		 * Returns a pointer to a new node
		 * Mimics a constructor
		 *
		 * @param key: used for ordering the nodes
		 * @param val: the value stored at each node
		 * @param color: the color of the node, used for balancing the nodes (defaults to red)
		 * @return: returns a pointer to a new node with key K, value V
		 */
		RBNode* newNode(K key, V val, bool color=true) { // color = true is color = red
			RBNode *newnode = new RBNode;
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->key = key;
			newnode->val = val;
			newnode->color = color;
			newnode->size = 1;
			return newnode;
		}

		/**
		 * Clears the memory?
		 * Doesn't look like it does anything honestly
		 * I don't understand structs or pointers.
		 */
		void clearMemory(RBNode *curr) {
			if (curr == NULL) return;

			clearMemory(curr->left);
			if (curr->left != NULL) free(curr->left);
			clearMemory(curr->right);
			if (curr->right != NULL) free(curr->right);
		}
		
		/**
		 * Returns a pointer to the node's key
		 * Kind of a pointless function
		 * 
		 * @param curr: pointer to the node whose key we want
		 * @return: returns a pointer to the node's key
		 */
		K* getKey(RBNode *curr) {
			if (curr == NULL) return NULL;
			return &(curr->key);
		}

		/**
		 * Returns a pointer to the node's value
		 * Kind of a pointless function
		 * 
		 * @param curr: pointer to the node whose value we want
		 * @return: returns a pointer to the node's value
		 */
		V* getVal(RBNode *curr) {
			if (curr == NULL) return NULL;
			return &(curr->val);
		}

		/**
		 * Returns if the node is red or not
		 *
		 * @param curr: the node whose color is in question
		 * @return: true if red, false if black
		 */
		bool isRed(RBNode *curr) {
			if (curr == NULL) return black;
			return (curr->color);
		}

		/**
		 * Returns the size of the node
		 *
		 * Size is the number of nodes "below" it, plus 1 (itself)
		 *
		 * @param curr: the node whose size is in question
		 * @return: the size of the node
		 */
		int nodeSize(RBNode *curr){
			if (curr == NULL) return 0;
			return curr->size;
		}

		/**
		 * "Rotates" the node curr to become the left child of
		 * its current right child.
		 *
		 * @param curr: the node to be rotated
		 * @return: the node on "top" after the rotation.
		 */
		RBNode* rotateLeft(RBNode *curr) {
			RBNode *x = curr->right;
			curr->right = x->left;
			x->left = curr;
			x->color = x->left->color;
			x->left->color = red; // Implies x was red?

			/** UPDATE SIZE **/
			curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
			x->size = nodeSize(x->left) + nodeSize(x->right) + 1;
			return x;
		}

		/**
		 * "Rotates" the node curr to become the right child of
		 * its current left child.
		 *
		 * @param curr: the node to be rotated
		 * @return: the node on "top" after the rotation
		 */
		RBNode* rotateRight(RBNode *curr) {
			RBNode *x = curr->left;
			curr->left = x->right;
			x->right = curr;
			x->color = x->right->color;
			x->right->color = red; //Implies x was red?

			/** UPDATE SIZE **/
			curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
			x->size = nodeSize(x->left) + nodeSize(x->right) + 1;
			return x;
		}

		/**
		 * Inverts the colors of the node and its children
		 *
		 * @param curr: the node to have its color flipped.
		 */
		 // does this imply both children exist??
		void colorFlip(RBNode *curr) {
			curr->color = !curr->color;
			curr->left->color = !curr->left->color;
			curr->right->color = !curr->right->color;
		}

		/**
		 * Inserts a node into the branching nodes below
		 *
		 * @param curr: the current node in the branches being looked at
		 * @param key: the key of the node to be inserted
		 * @param val: the value of the node to be inserted
		 * @return: the updated node on top after the insert
		 */
		RBNode* insertNode(RBNode *curr, K key, V val) {
			if (curr == NULL) return newNode(key, val);

			if (isRed(curr->left) && isRed(curr->right))
				colorFlip(curr);

			if (key < curr->key)
				curr->left = insertNode(curr->left, key, val);
			else if (key > curr->key)
				curr->right = insertNode(curr->right, key, val);
			else if (key == curr->key)
				curr->val = val;

			if (isRed(curr->right))
				curr = rotateLeft(curr);
				
			if (isRed(curr->left) && isRed(curr->left->left))
				curr = rotateRight(curr);

			/** UPDATE SIZE **/
			//why is this necessary when it was just done in the rotates?
			//it may not rotate
			curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
			return curr;
		}

		/**
		 * Prints an in order traversal of the tree
		 *
		 * @param curr: the current node in the branches being looked at
		 */
		void printInOrder(RBNode *curr) {
			if (curr == NULL) return;

			printInOrder(curr->left);
			cout << curr->key << " ";
			printInOrder(curr->right);
		}

		/**
		 * Prints a post-order traversal of the tree
		 *
		 * @param curr: the current node in the branches being looked at
		 */
		void printPostOrder(RBNode *curr) {
			if (curr == NULL) return;

			printPostOrder(curr->left);
			printPostOrder(curr->right);
			cout << curr->key << " ";
		}

		/**
		 * Prints a pre-order traversal of the tree
		 *
		 * @param curr: the current node in the branches being looked at
		 */
		void printPreOrder(RBNode *curr) {
			if (curr == NULL) return;

			cout << curr->key << " ";
			printPreOrder(curr->left);
			printPreOrder(curr->right);
		}

		/**
		 * Prints a pre-order traversal of the tree with colors listed beside values
		 *
		 * @param curr: the current node in the branches being looked at
		 */
		void printColors(RBNode *curr) {
			if (curr == NULL) return;

			if (curr->color) cout << curr->val << ": Red" << endl;
			else cout << curr->val << ": Black" << endl;
			printColors(curr->left);
			printColors(curr->right);
		}

		
		RBNode* fixUp(RBNode *curr) {
			if (isRed(curr->right))
				curr = rotateLeft(curr);

			if (isRed(curr->left) && isRed(curr->left->left))
				curr = rotateRight(curr);

			if (isRed(curr->left) && isRed(curr->right))
				colorFlip(curr);

			/** UPDATE SIZE **/
			curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
			return curr;
		}

		
		RBNode* moveRedRight(RBNode *curr) {
			colorFlip(curr);
			if (isRed(curr->left->left)) {
				curr = rotateRight(curr);
				colorFlip(curr);
			}
			return curr;
		}

		
		RBNode* moveRedLeft(RBNode *curr) {
			colorFlip(curr);
			if (isRed(curr->right->left)) {
				curr->right = rotateRight(curr->right);
				curr = rotateLeft(curr);
				colorFlip(curr);
			}
			return curr;
		}

		/**
		 * Deletes the smallest key value in the tree
		 *
		 * @param curr: the node currently being looked at in the tree
		 * @return: the node on top after the deletion
		 */
		RBNode* deleteMin(RBNode *curr) {
			if (curr->left == NULL)
				return NULL;

			if (!isRed(curr->left) && !isRed(curr->left->left))
				curr = moveRedLeft(curr);

			curr->left = deleteMin(curr->left);
			return fixUp(curr);
		}

		/**
		 * Removes the node with key value "key" from the tree
		 *
		 * @param curr: the node currently being looked at in the tree
		 * @param key: the key value of the node to be deleted
		 * @return: returns the node on top after the deletion
		 */
		RBNode* removeNode(RBNode *curr, K key) {
			if (key < curr->key) {
				if (!isRed(curr->left) && !isRed(curr->left->left))
					curr = moveRedLeft(curr);

				curr->left = removeNode(curr->left, key);
			}
			else {
				// leanRight() in sedgewick
				if (isRed(curr->left))
					curr = rotateRight(curr);

				if (key == curr->key && curr->right == NULL) {
					return NULL;
				}

				if (!isRed(curr->right) && !isRed(curr->right->left))
					curr = moveRedRight(curr);

				if (key == curr->key) {
					RBNode *x = curr->right;

					while (x->left != NULL) x = x->left; // get sucessor

					curr->key = x->key;
					curr->val = x->val;
					curr->right = deleteMin(curr->right); // essentially removeNode(curr->right, curr->key);
				}
				else {
					curr->right = removeNode(curr->right, key);
				}
			}

			//fixUp fixes size
			return fixUp(curr);
		}

		/**
		 * Creates a deep copy of the node
		 *
		 * @param curr: the node being copied
		 * @return: the copy of the node
		 */
		RBNode* copy(RBNode *curr) {
			RBNode* newnode = newNode(curr->key,curr->val,curr->color);
			if (curr->left != NULL) newnode->left = copy(curr->left);
			if (curr->right != NULL) newnode->right = copy(curr->right);
			newnode->size = curr->size;
			return newnode;
		}

		/**
		 * Finds the value of a node with the specified key, k
		 *
		 * @param curr: the node currently being looked at
		 * @param k: the key of the node being searched for
		 * @return: returns the value stored in the node with key value k
		 */
		V* findVal(RBNode *curr, K key) {
			if (curr == NULL) return NULL;
			else if (curr->key == key) return &(curr->val);
			else if (key > curr->key) return findVal(curr->right, key);
			else if (key < curr->key) return findVal(curr->left, key);
			return NULL;
		}

		/**
		 * Gets the rank of a node
		 *
		 * Rank is something I don't understand at the moment
		 *
		 * @param curr: the current node being looked at
		 * @return: the rank of the node;
		 */
		int getRank(RBNode *curr, K key) {
			if (curr==NULL) return 0;
			else if (key > curr->key) return nodeSize(curr->left) + 1 + getRank(curr->right, key);
			else if (key < curr->key) return getRank(curr->left, key);
			else if (key == curr->key) return curr->size - nodeSize(curr->right);
			else return 0;
		}
		
		K getPos(RBNode *curr, int k) {
			//get node at position k?? yeah
			/*
			say I am the root, my size is 17, left is 8 and right is 8,
			my order is 9.

			if I'm looking for 10, I tell my right, I'm looking for 1,
			or k - my order, which is left->size + 1

			if I'm looking for 3, I tell left I'm looking for 3
			*/
			int place = nodeSize(curr->left) + 1;
			if (k == place) return curr->key;
			else if (k < place) return getPos(curr->left, k);
			else return getPos(curr->right, k - place);
		}

		RBNode* findNode(RBNode* curr, K key) {
			if (curr == NULL) return NULL;
			else if (key == curr->key) return curr;
			else if (key > curr->key) return findNode(curr->right, key);
			else if (key < curr->key) return findNode(curr->left, key);
			else return NULL;
		}

		/******************************************************************************
		 * * * * * * * * * * * * * * * End of Node Struct * * * * * * * * * * * * * * *
		 ******************************************************************************/

	public:

		RBTree() {
			root = NULL;
			red = true;
			black = false;
		}

		RBTree(K k[], V v[], int s) {
			root = NULL;
			red = true;
			black = false;

			for (int i = 0; i < s; i++) {
				root = insertNode(root, k[i], v[i]);
				root->color = black;
			}
		}

		RBTree(RBNode* root) {
			this->root = root;
			this->root->color = black;
			red = true;
			black = false;
		}

		~RBTree() {
			clearMemory(root);
			free(root);
		}

		RBTree(const RBTree &other) {
			root = copy(other.root);
		}

		RBTree& operator=(const RBTree& other) {
			root = copy(other.root);
			return *this;
		}

		void setRoot(RBNode* root) {
			this->root = root;
		}

		void insert(K k, V v) {
			root = insertNode(root, k, v);
			root->color = black;
		}

		int remove(K k) {
			if (search(k) == NULL) return 0;

			int s = nodeSize(root);
			root = removeNode(root, k);

			return s - nodeSize(root); // Better than below?
			/*
			if (nodeSize(this->root) != s) return 1;
			else return 0;
			*/
		}

		V* search(K key) {
			return findVal(root, key);
		}

		int rank(K k) {
			return getRank(root, k);
		}

		K select(int pos) {
			if (pos > nodeSize(root) || pos < 1) {
				cout << "Error: param should be between 1 and the size of the tree." << endl;
				K error;
				return error;
			}
			return getPos(root, pos);
		}

		int size() {
			return nodeSize(root);
		}

		void preorder() {
			printPreOrder(root);
			cout << endl;
		}

		void inorder() {
			printInOrder(root);
			cout << endl;
		}

		void postorder() {
			printPostOrder(root);
			cout << endl;
		}

		void printTree() {
			printColors(root);
		}

		/**
		 * I have no idea how this is supposed to work
		 */
		void split(K key, RBTree& T1, RBTree& T2) {
			
		}
};