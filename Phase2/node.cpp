#include <iostream>
using namespace std;

bool red = true;
bool black = false;
bool removed = false;
bool inserted = false;
int rankCounter = 1;

struct node {
  node *left, *right;
  int key;
  int val;
  bool color;
};

node* createNode(int key, int val, bool color) {
//  cout << "createNode called" << endl;
  node *newNode = new node;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->key = key;
  newNode->color = color;
  newNode->val = val;
//  cout << "createNode finished" << endl;
  return newNode;
}

node* rotateLeft(node *h) {
//  cout << "rotateLeft called" << endl;
  node *x = h->right;
  h->right = x->left;
  x->left = h;
  x->color = x->left->color;
  x->left->color = red;
//  cout << "rotateLeft finished" << endl;
  return x;
}

node* rotateRight(node *h) {
//  cout << "rotateRight called" << endl;
  node *x = h->left;
  h->left = x->right;
  x->right = h;
  x->color = x->right->color;
  x->right->color = red;
//  cout << "rotateRight finished" << endl;
  return x;
}

void colorFlip(node *h) {
//  cout << "colorFlip called" << endl;
  h->color = !h->color;
  h->left->color = !h->left->color;
  h->right->color = !h->right->color;
//  cout << "colorFlip finished" << endl;
}

bool isRed(node *h) {
//  cout << "isRed called" << endl;
  if (h == NULL)
    return black;
//  cout << "isRed finished" << endl;
  return (h->color);
}

node* insert(node *h, int key, int val) {
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

  return h;
}

node* insertFix(node *h, int key, int val) {
  if (h == NULL) {
    return createNode(key, val, black);
  }
  else
    return insert(h, key, val);
}

void printInOrder(node *h) {
  if (h == NULL)
    return;
  printInOrder(h->left);
  cout << h->val << " ";
  printInOrder(h->right);
}

void printPostOrder(node *h) {
  if (h == NULL)
    return;
  printPostOrder(h->left);
  printPostOrder(h->right);
  cout << h->val << " ";
}

void printPreOrder(node *h) {
  if (h == NULL)
    return;
  cout << h->val << " ";
  printPreOrder(h->left);
  printPreOrder(h->right);
}

void printColors(node *h) {
  if (h == NULL)
    return;
  if (h->color)
    cout << h->val << ": Red" << endl;
  else
    cout << h->val << ": Black" << endl;
  printColors(h->left);
  printColors(h->right);
}

node* fixUp(node *h) {
  if (isRed(h->right))
    h = rotateLeft(h);
  if (isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if (isRed(h->left) && isRed(h->right))
    colorFlip(h);
  return h;
}

node* moveRedRight(node *h) {
  colorFlip(h);
  if (isRed(h->left->left))
  {
    h = rotateRight(h);
    colorFlip(h);
  }
  return h;
}

node* moveRedLeft(node *h) {
  colorFlip(h);
  if (isRed(h->right->left))
  {
    h->right = rotateRight(h->right);
    h = rotateLeft(h);
    colorFlip(h);
  }
  return h;
}

node* deleteMin(node *h) {
  if (h->left == NULL)
    return NULL;
  if (!isRed(h->left) && !isRed(h->left->left))
    h = moveRedLeft(h);
  h->left = deleteMin(h->left);
  return fixUp(h);
}

node* removeFix(node *h, int key) {
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
      removed = true;
      return NULL;
    }
    if (!isRed(h->right) && !isRed(h->right->left))
      h = moveRedRight(h);
    if (key == h->key) {
      removed = true;
      node *x = h->right;
      while (x->left != NULL)
        x = x->left;
      h->key = x->key;
      h->val = x->val;
      h->right = deleteMin(h->right);
    }
    else{
      cout << h->key << endl;
      h->right = removeFix(h->right, key);
    }
  }
  return fixUp(h);
}

void clearMemory(node *h) {
  if (h == NULL)
    return;
  clearMemory(h->left);
  clearMemory(h->right);
  free(h);
}

void copy(node *h, node *old) {
  if (old->left != NULL) {
    h->left = new node;
    h->left->key = old->left->key;
    h->left->val = old->left->val;
    h->left->color = old->left->color;
    h->left->left = NULL;
    h->left->right = NULL;
    copy(h->left, old->left);
  }
  if (old->right != NULL) {
    h->right = new node;
    h->right->key = old->right->key;
    h->right->val = old->right->val;
    h->right->color = old->right->color;
    h->right->left = NULL;
    h->right->right = NULL;
    copy(h->right, old->right);
  }
  return;
}

int* findVal(int k, node *h) {
  if (h == NULL)
    return NULL;
  else if (h->key == k)
    return &h->val;
  else if (h->key > k)
    return findVal(k, h->right);
  else if (h->key < k)
    return findVal(k, h->left);
  return NULL;
}

int getRank(int k, node *h, int count, bool keyFound) {
  if (h == NULL)
    return 0;
}