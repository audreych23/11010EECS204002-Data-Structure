#include <iostream>
#include "rentalhistory.hpp"
/* public methods */

RentalHistory::RentalHistory () { root = nullptr; }

RentalHistory::~RentalHistory () { Clear_ (root); }

void RentalHistory::Insert (int key, int bike_type, int station_id, int time_begin, int bike_id){ root = Insert_ (root, key, bike_type, station_id, time_begin, bike_id); }

void RentalHistory::Delete (int key){ root = Delete_ (root, key); }

UserNode* RentalHistory::Find (int key) { return Find_ (root, key); } // find from key?

void RentalHistory::PreOrder () { PreOrder_ (root); }

void RentalHistory::InOrder () { InOrder_ (root); }

/* private methods */

void RentalHistory::Clear_ (UserNode* node)
{
  if(node != nullptr)
  {
    Clear_ (node->left);
    Clear_ (node->right);
    delete node;
  }
}

UserNode* RentalHistory::Insert_ (UserNode* node, int key, int bike_type, int station_id, int time_begin, int bike_id)
{
  // recursive definiton in class??
  if (node == nullptr) { return new UserNode(key, bike_type, station_id, time_begin, bike_id); }

	if (key < node->key)
  {
		node->left = Insert_(node->left, key, bike_type, station_id, time_begin, bike_id);
	}
  else if (key > node->key)
  {
		node->right = Insert_(node->right, key, bike_type, station_id, time_begin, bike_id);
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

UserNode* RentalHistory::Delete_ (UserNode* node, int key)
{
  if (node == nullptr) { return node; }
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
    // node with only one child or no child
    if((node->left == nullptr) || (node->right == nullptr) )
    {
      UserNode *temp = node->left ? node->left : node->right;
      if (temp == nullptr)
      {
          temp = node;
          node = nullptr;
      }
      else
      {
        *node = *temp; // Copy the contents
      }
      delete temp;
    }
    else
    {
      UserNode* temp = MinValueNode(node->right);
      node->key = temp->key;
      node->right = Delete_(node->right, temp->key);
    }
  }
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
    return LeftRotate(node);
  }
  else if (balance < -1 && GetBalance(node->right) > 0) // Right Left
  {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

UserNode* RentalHistory::Find_ (UserNode* node, int key) // invalid when return nullptr
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

void RentalHistory::PreOrder_ (UserNode* node)
{
  if (node != nullptr)
  {
    std::cout << node->key << " ";
    PreOrder_(node->left);
    PreOrder_(node->right);
  }
  return;
}

void RentalHistory::InOrder_ (UserNode* node)
{
  if (node != nullptr)
  {
    InOrder_(node->left);
    std::cout << node->key << " ";
    InOrder_(node->right);
  }
  return;
}

UserNode* RentalHistory::RightRotate (UserNode *z)
{
  UserNode* y = z->left;
	UserNode* temp = y->right;

	y->right = z;
	z->left = temp;

  z->height = max(GetHeight(z->left), GetHeight(z->right)) + 1;
  y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

	return y;
}

UserNode* RentalHistory::LeftRotate (UserNode *z)
{
  UserNode* y = z->right;
	UserNode* temp = y->left;

	y->left = z;
	z->right = temp;

  z->height = max(GetHeight(z->left), GetHeight(z->right)) + 1;
	y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

	return y;
}

int RentalHistory::GetBalance (UserNode *node)
{
  if (node == nullptr) { return 0; }
  return (GetHeight(node->left) - GetHeight(node->right));
}


UserNode* RentalHistory::MinValueNode(UserNode* node)
{
  UserNode* current = node;

  /* loop down to find the leftmost leaf */
  while (current->left != nullptr) { current = current->left; }

  return current;
}

int RentalHistory::max (int a, int b)
{
  if (a < b) { return b; }
  return a;
}

int RentalHistory::GetHeight(UserNode* node)
{
  if(node == nullptr) { return 0; }
  return node->height;
}
