#ifndef AVL_HPP_
#define AVL_HPP_

class Node
{
public:
  Node ();
  Node (int);
  int key; // key is user_id
  Node *left;
  Node *right;
  int height;

};

Node::Node (int key)
{
  this->key = key;
  left = nullptr;
  right = nullptr;
  height = 1;
}

class AVLTree
{
public:

  AVLTree ();
  ~AVLTree ();

  Node* Find(int);
  void Insert (int);
  void Delete (int);
  void PreOrder ();
  void InOrder ();

private:

  void Clear_ (Node*);

  Node* Find_ (Node*, int);
  Node* Insert_ (Node*, int);
  Node* Delete_ (Node*, int);
  void PreOrder_ (Node*);
  void InOrder_ (Node*);

  Node* RightRotate (Node*);
  Node* LeftRotate (Node*);

  int GetBalance (Node*);
  Node* MinValueNode (Node*);
  int max (int, int);
  int GetHeight (Node*);

  Node* root;

};

/* public methods */

AVLTree::AVLTree () { root = nullptr; }

AVLTree::~AVLTree () { Clear_ (root); }

Node* AVLTree::Find (int key) { return Find_ (root, key); } // find from key?

void AVLTree::Insert (int key){ root = Insert_ (root, key); }

void AVLTree::Delete (int key){ root = Delete_ (root, key); }

void AVLTree::PreOrder () { PreOrder_ (root); }

void AVLTree::InOrder () { InOrder_ (root); }

/* private methods */

void AVLTree::Clear_ (Node* node)
{
  if(node != nullptr)
  {
    Clear_ (node->left);
    Clear_ (node->right);
    delete node;
  }
}

Node* AVLTree::Find_ (Node* node, int key)
{
  if(node == nullptr) { return node; }
  if(key < node->key)
  {
    return Find_ (node->left, key);
  }
  else if (key > node->key)
  {
    return Find_ (node->right, key);
  }
  else
  {
    return node;
  }
  return node;
}

Node* AVLTree::Insert_ (Node* node, int key)
{
  // recursive definiton in class??
  if (node == nullptr) { return new Node(key); }

	if (key < node->key)
  {
		node->left = Insert_(node->left, key);
	}
  else if (key > node->key)
  {
		node->right = Insert_(node->right, key);
	}
  else
  {
	  return node;
	}
  /* 2. Update height of this ancestor node */
	node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  /* 3. Get the balance factor of this ancestor
  node to check whether this node became
  unbalanced */

	int balance = GetBalance(node);

	if (balance > 1 && key < node->left->key) // Left Left Case
  {
		return RightRotate(node);
	}
  // Right Right Case
	else if (balance < -1 && key > node->right->key)
  {
		return LeftRotate(node);
	}
	else if (balance > 1 && key > node->left->key)  // Left Right Case
  {
		node->left = LeftRotate(node->left);
		return RightRotate(node);
	}
	else if (balance < -1 && key < node->right->key) // Right Left Case
  {
		node->right = RightRotate(node->right);
		return LeftRotate(node);
	}
  /* return the (unchanged) node pointer */
	return node;
}

Node* AVLTree::Delete_ (Node* node, int key)
{
  if (node == nullptr) { return nullptr; }
  //TODO
  if (key < node->key)
  {
    node->left = Delete_(node->left, key);
  }
  else if (key > node->key)
  {
    node->right = Delete_(node->right, key);
  }
  else
  {
    // 3 case
    if(node->left == nullptr && node->right == nullptr)
    {
      temp = node;
      node = nullptr;
      delete temp;
    }
    else if (node->left == nullptr && node->right != nullptr)
    {
      //  rigth children not empty
      Node* temp = node->right;
      *node = *temp;
      delete temp;
    }
    else if (node->left != nullptr && node->right == nullptr)
    {
      Node* temp = node->left;
      *node = *temp;
      delete temp;
    }
    else
    {
      Node* min_node = MinValueNode(node->right);
      node->key = min_node->key;
      node->right = Delete_(node->right, node->key);
    }
  }

  // if the tree had only one node
  if(node == nullptr) { return node; }

  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));

	int balance = GetBalance(node);

  if (balance > 1 && GetBalance(node->left) >= 0) // Left Left
  {
    return RightRotate(node);
  }
  else if (balance > 1 && GetBalance(node->left) < 0) // Left Right
  {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  else if (balance < -1 && GetBalance(node->right) <= 0) // Right Right
  {
    LeftRotate(node);
  }
  else if (balance < -1 && GetBalance(node->right) > 0) // Right Left
  {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

void AVLTree::PreOrder_ (Node* node)
{
  if (node != nullptr)
  {
    std::cout << node->key << " ";
    PreOrder_(node->left);
    PreOrder_(node->right);
  }
  return;
}

void AVLTree::InOrder_ (Node* node)
{
  if (node != nullptr)
  {
    InOrder_(node->left);
    std::cout << node->key << " ";
    InOrder_(node->right);
  }
  return;
}

Node* AVLTree::RightRotate (Node *z)
{
  Node* y = z->left;
	Node* temp = y->right;

	y->right = z;
	z->left = temp;

  z->height = max(GetHeight(z->left), GetHeight(z->right)) + 1;
  y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

	return y;
}

Node* AVLTree::LeftRotate (Node *z)
{
  Node* y = z->right;
	Node* temp = y->left;

	y->left = z;
	z->right = temp;

  z->height = max(GetHeight(z->left), GetHeight(z->right)) + 1;
	y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

	return y;
}

int AVLTree::GetBalance (Node *node)
{
  if (node == nullptr) { return 0; }
  return (GetHeight(node->left) - GetHeight(node->right));
}


Node* AVLTree::MinValueNode(Node* node)
{
  Node* current = node;

  /* loop down to find the leftmost leaf */
  while (current->left != nullptr) { current = current->left; }

  return current;
}

int AVLTree::max (int a, int b)
{
  if (a < b) { return b; }
  return a;
}

int AVLTree::GetHeight(Node* node)
{
  if (node == nullptr) { return 0; }
  return node->height;
}
#endif
