#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
using namespace std;

bool red = true;
bool black = false;
bool removed = false;
bool inserted = false;

template<class keytype,class valuetype>
struct node {
  node *left, *right;
  keytype key;
  valuetype val;
  bool color;
  int size;
};

template<class keytype,class valuetype>
int nodeSize(node<keytype,valuetype> *h){
  if (h == NULL)
    return 0;
  return h->size;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* createNode(keytype key, valuetype val, bool color) {
  node<keytype,valuetype> *newNode = new node<keytype,valuetype>;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->key = key;
  newNode->color = color;
  newNode->val = val;
  newNode->size = 1;
  return newNode;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* rotateLeft(node<keytype,valuetype> *h) {
  node<keytype,valuetype> *x = h->right;
  h->right = x->left;
  x->left = h;
  x->color = x->left->color;
  x->left->color = red;
  h->size = nodeSize(h->left) + nodeSize(h->right) + 1;
  x->size = nodeSize(x->left) + nodeSize(x->right) + 1;
  return x;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* rotateRight(node<keytype,valuetype> *h) {
  node<keytype,valuetype> *x = h->left;
  h->left = x->right;
  x->right = h;
  x->color = x->right->color;
  x->right->color = red;
  h->size = nodeSize(h->left) + nodeSize(h->right) + 1;
  x->size = nodeSize(x->left) + nodeSize(x->right) + 1;
  return x;
}

template<class keytype,class valuetype>
void colorFlip(node<keytype,valuetype> *h) {
//  cout << "colorFlip called" << endl;
  h->color = !h->color;
  h->left->color = !h->left->color;
  h->right->color = !h->right->color;
//  cout << "colorFlip finished" << endl;
}

template<class keytype,class valuetype>
bool isRed(node<keytype,valuetype> *h) {
//  cout << "isRed called" << endl;
  if (h == NULL)
    return black;
//  cout << "isRed finished" << endl;
  return (h->color);
}

template<class keytype,class valuetype>
node<keytype,valuetype>* insert(node<keytype,valuetype> *h, keytype key, valuetype val) {
  if (h == NULL){
    inserted = true;
    //cout << "NULL found" << endl;
    return createNode(key, val, red);
  }
  if (isRed(h->left) && isRed(h->right))
    colorFlip(h);

  if (key < h->key)
    h->left = insert(h->left, key, val);
  else if (key > h->key)
    h->right = insert(h->right, key, val);
  else if (key == h->key)
    h->val = val;

  if (isRed(h->right))
    h = rotateLeft(h);
  if (isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  h->size = nodeSize(h->left) + nodeSize(h->right) + 1;
  return h;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* insertFix(node<keytype,valuetype> *h, keytype key, valuetype val) {
  if (h == NULL) {
    inserted = true;
    return createNode(key, val, black);
  }
  else
    return insert(h, key, val);
}

template<class keytype,class valuetype>
void printInOrder(node<keytype,valuetype> *h) {
  if (h == NULL)
    return;
  printInOrder(h->left);
  cout << h->key << " ";
  printInOrder(h->right);
}

template<class keytype,class valuetype>
void printPostOrder(node<keytype,valuetype> *h) {
  if (h == NULL)
    return;
  printPostOrder(h->left);
  printPostOrder(h->right);
  cout << h->key << " ";
}

template<class keytype,class valuetype>
void printPreOrder(node<keytype,valuetype> *h) {
  if (h == NULL)
    return;
  cout << h->key << " ";
  printPreOrder(h->left);
  printPreOrder(h->right);
}

template<class keytype,class valuetype>
void printColors(node<keytype,valuetype> *h) {
  if (h == NULL)
    return;
  if (h->color)
    cout << h->val << ": Red" << endl;
  else
    cout << h->val << ": Black" << endl;
  printColors(h->left);
  printColors(h->right);
}

template<class keytype,class valuetype>
node<keytype,valuetype>* fixUp(node<keytype,valuetype> *h) {
  if (isRed(h->right))
    h = rotateLeft(h);
  if (isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if (isRed(h->left) && isRed(h->right))
    colorFlip(h);
  h->size = nodeSize(h->left) + nodeSize(h->right) + 1;
  return h;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* moveRedRight(node<keytype,valuetype> *h) {
  colorFlip(h);
  if (isRed(h->left->left))
  {
    h = rotateRight(h);
    colorFlip(h);
  }
  return h;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* moveRedLeft(node<keytype,valuetype> *h) {
  colorFlip(h);
  if (isRed(h->right->left))
  {
    h->right = rotateRight(h->right);
    h = rotateLeft(h);
    colorFlip(h);
  }
  return h;
}

template<class keytype,class valuetype>
node<keytype,valuetype>* deleteMin(node<keytype,valuetype> *h) {
  if (h->left == NULL)
    return NULL;
  if (!isRed(h->left) && !isRed(h->left->left))
    h = moveRedLeft(h);
  h->left = deleteMin(h->left);
  return fixUp(h);
}

template<class keytype,class valuetype>
node<keytype,valuetype>* removeFix(node<keytype,valuetype> *h, keytype key) {
  if (key < h->key) {
    if (!isRed(h->left) && !isRed(h->left->left))
      h = moveRedLeft(h);
    h->left = removeFix(h->left, key);
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
      node<keytype,valuetype> *x = h->right;
      while (x->left != NULL)
        x = x->left;
      h->key = x->key;
      h->val = x->val;
      h->right = deleteMin(h->right);
    }
    else{
      h->right = removeFix(h->right, key);
    }
  }
  return fixUp(h);
}

template<class keytype,class valuetype>
void clearMemory(node<keytype,valuetype> *h) {
  if (h == NULL)
    return;
  clearMemory(h->left);
  clearMemory(h->right);
  free(h);
}

template<class keytype,class valuetype>
void copy(node<keytype,valuetype> *h, node<keytype,valuetype> *old) {
  if (old->left != NULL) {
    h->left = new node<keytype,valuetype>;
    h->left->key = old->left->key;
    h->left->val = old->left->val;
    h->left->color = old->left->color;
    h->left->size = old->left->size;
    h->left->left = NULL;
    h->left->right = NULL;
    copy(h->left, old->left);
  }
  if (old->right != NULL) {
    h->right = new node<keytype,valuetype>;
    h->right->key = old->right->key;
    h->right->val = old->right->val;
    h->right->color = old->right->color;
    h->right->size = old->right->size;
    h->right->left = NULL;
    h->right->right = NULL;
    copy(h->right, old->right);
  }
  return;
}

template<class keytype,class valuetype>
valuetype* findVal(keytype k, node<keytype,valuetype> *h) {
  if (h == NULL)
    return NULL;
  else if (h->key == k)
    return &h->val;
  else if (k > h->key)
    return findVal(k, h->right);
  else if (k < h->key)
    return findVal(k, h->left);
  return NULL;
}

template<class keytype,class valuetype>
int getRank(node<keytype,valuetype> *h, keytype key) {
    if (h==NULL) return 0;
    else if (key > h->key) return nodeSize(h->left) + 1 + getRank(h->right, key);
    else if (key < h->key) return getRank(h->left, key);
    else if (key == h->key) return h->size - nodeSize(h->right);
    else return 0;
}

template<class keytype,class valuetype>
keytype getPos(node<keytype,valuetype> *h, int k) {
  int place = nodeSize(h->left) + 1;
  if (k == place)
    return h->key;
  else if (k < place)
    return getPos(h->left, k);
  else
    return getPos(h->right, k - place);
}

template<class keytype,class valuetype>
class RBTree
{
  public:
    node<keytype,valuetype>* root;
    int treeSize;

    RBTree() {
      root = NULL;
      treeSize = 0;
    }

    RBTree(keytype k[], valuetype v[], int s) {
      root = NULL;
      for (int i = 0; i < s; i++) {
        root = insertFix(root, k[i], v[i]);
        if (root->color)
          root->color = black;
      }
      treeSize = s;
    }

    ~RBTree() {
      clearMemory(root);
    }

    RBTree(const RBTree &other) {
treeSize = other.treeSize;
      root = new node<keytype,valuetype>;
root->key = other.root->key;
      root->val = other.root->val;
      root->color = other.root->color;
      copy(root, other.root);
}

    RBTree& operator=(const RBTree& other) {
if (this != &other) {
treeSize = other.treeSize;
        root = new node<keytype,valuetype>;
  root->key = other.root->key;
        root->val = other.root->val;
        root->color = other.root->color;
        copy(root, other.root);
}
return *this;
}

    valuetype* search(keytype k) {
      return findVal(k, root);
    }

    void insert(keytype k, valuetype v) {
      inserted = false;
      root = insertFix(root, k, v);
      if (root->color)
        root->color = black;
      if (inserted)
        treeSize += 1;
    }

    int remove(keytype k) {
      if (search(k) == NULL)
        return 0;
      root = removeFix(root, k);
      treeSize -= 1;
      return 1;
    }

    int rank(keytype k) {
      return getRank(root, k);
    }

    keytype select(int pos) {
      if (pos > treeSize || pos < 1) {
        cout << "Error: param should be between 1 and the size of the tree." << endl;
        keytype error;
        return error;
      }
      return getPos(root, pos);
    }

    int size() {
      return treeSize;
    }

    void preorder() {
      printPreOrder(root);
    }

    void inorder() {
      printInOrder(root);
    }

    void postorder() {
      printPostOrder(root);
    }

    void printTree() {
      printColors(root);
    }
};