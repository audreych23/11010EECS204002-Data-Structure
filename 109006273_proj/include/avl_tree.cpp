#include "avl_tree.hpp"

std::ostream& operator<< (std::ostream& out, Data const& data)
{
  out
  << "("
  << data.user_id << ","
  << data.bike_type << ","
  << data.station_id << ","
  << data.begin_time << ","
  << data.bike_id
  << ")";
  return out;
}

Data* TreeNode::GetData () const { return data_; }

std::ostream& operator<< (std::ostream& out, TreeNode const& node)
{
  out << *(node.data_);
  return out;
}

TreeNode* AvlTree::Search (uint64_t user_id)
{
  TreeNode *node {root_};
  while (node)
  {
    if (user_id < node->data_->user_id) { node = node->left_; }
    else if (user_id > node->data_->user_id) { node = node->right_; }
    else { break; }
  }
  return node;
}

void AvlTree::Insert
(
  uint64_t user_id,
  std::string bike_type,
  uint64_t station_id,
  uint64_t begin_time,
  uint64_t bike_id
)
{
  root_ = Insert(root_, user_id, bike_type, station_id, begin_time, bike_id);
}

void AvlTree::Delete (uint64_t user_id) { root_ = Delete(root_, user_id); }

void AvlTree::PreOrder (Vector<Data>& preorder) const { PreOrder(preorder, root_); }
void AvlTree::InOrder (Vector<Data>& inorder) const { InOrder(inorder, root_); }
void AvlTree::PostOrder (Vector<Data>& postorder) const { PostOrder(postorder, root_); }

/* private member functions */

TreeNode* AvlTree::Insert
(
  TreeNode* node,
  uint64_t user_id,
  std::string bike_type,
  uint64_t station_id,
  uint64_t begin_time,
  uint64_t bike_id
)
{
  if (node == nullptr) { return new TreeNode(user_id, bike_type, station_id, begin_time, bike_id); }
  if (user_id == node->data_->user_id) return node;
  if (user_id < node->data_->user_id)
  {
		node->left_ = Insert(node->left_, user_id, bike_type, station_id, begin_time, bike_id);
	}
  else
  {
		node->right_ = Insert(node->right_, user_id, bike_type, station_id, begin_time, bike_id);
	}
  node->height_ = 1 + Max(Height(node->left_), Height(node->right_));
	int64_t balance_factor {BalanceFactor(node)};
  if (balance_factor == 2)
  {
    if (user_id > node->left_->data_->user_id) { node->left_ = LeftRotate(node->left_);}
    return RightRotate(node);
  }
  else if (balance_factor == -2)
  {
    if (user_id < node->right_->data_->user_id) { node->right_ = RightRotate(node->right_); }
    return LeftRotate(node);
  }
	return node;
}

TreeNode* AvlTree::Delete (TreeNode* node, uint64_t user_id)
{
  if (node)
  {
    if (user_id < node->data_->user_id)
    {
      node->left_ = Delete(node->left_, user_id);
    }
    else if (user_id > node->data_->user_id)
    {
      node->right_ = Delete(node->right_, user_id);
    }
    else
    {
      if (node->left_ && node->right_)
      {
        TreeNode *successor {node->right_};
        while (successor->left_) { successor = successor->left_; }
        Swap(*node, *successor);
        node->right_ = Delete(node->right_, user_id);
      }
      else if (node->left_ || node->right_)
      {
        TreeNode *child {(node->left_) ? node->left_ : node->right_};
        node->left_ = node->right_ = nullptr;
        delete node;
        node = child;
      }
      else
      {
        delete node;
        return nullptr;
      }
    }
    node->height_ = 1 + Max(Height(node->left_), Height(node->right_));
  	int64_t balance_factor {BalanceFactor(node)};
    if (balance_factor == 2)
    {
      if (BalanceFactor(node->left_) == -1) { node->left_ = LeftRotate(node->left_); }
      return RightRotate(node);
    }
    else if (balance_factor == -2)
    {
      if (BalanceFactor(node->right_) == 1) { node->right_ = RightRotate(node->right_); }
      return LeftRotate(node);
    }
  }
  return node;
}

void AvlTree::PreOrder (Vector<Data>& preorder, TreeNode* node) const
{
  if (node)
  {
    preorder.PushBack(*(node->data_));
    PreOrder(preorder, node->left_);
    PreOrder(preorder, node->right_);
  }
  return;
}

void AvlTree::InOrder (Vector<Data>& inorder, TreeNode* node) const
{
  if (node)
  {
    InOrder(inorder, node->left_);
    inorder.PushBack(*(node->data_));
    InOrder(inorder, node->right_);
  }
  return;
}

void AvlTree::PostOrder (Vector<Data>& postorder, TreeNode* node) const
{
  if (node)
  {
    PostOrder(postorder, node->left_);
    PostOrder(postorder, node->right_);
    postorder.PushBack(*(node->data_));
  }
  return;
}

std::ostream& operator<< (std::ostream& out, AvlTree const& avl_tree)
{
  Vector<Data> inorder;
  avl_tree.InOrder(inorder);
  out << inorder;
  return out;
}

/* private member functions */

/*
*     z  O          O y
*       / \        / \
*   y  O   O  =>  O   O z
*     / \            / \
*    O   O x      x O   O
*/
TreeNode* AvlTree::RightRotate (TreeNode *z)
{
  TreeNode* y {z->left_};
	TreeNode* x {y->right_};
  z->left_ = x;
  y->right_ = z;
  z->height_ = Max(Height(z->left_), Height(z->right_)) + 1;
  y->height_ = Max(Height(y->left_), Height(y->right_)) + 1;
	return y;
}

/*
*     y  O          O z
*       / \        / \
*   z  O   O  <=  O   O y
*     / \            / \
*    O   O x      x O   O
*/
TreeNode* AvlTree::LeftRotate (TreeNode *z)
{
  TreeNode* y {z->right_};
	TreeNode* x {y->left_};
  z->right_ = x;
	y->left_ = z;
  z->height_ = Max(Height(z->left_), Height(z->right_)) + 1;
	y->height_ = Max(Height(y->left_), Height(y->right_)) + 1;
	return y;
}

uint64_t AvlTree::Max (uint64_t lhs, uint64_t rhs) const { return ((lhs < rhs) ? rhs : lhs); }

uint64_t AvlTree::Height (TreeNode* node) { return ((node) ? node->height_ : 0); }

int64_t AvlTree::BalanceFactor (TreeNode *node) { return ((node) ? (Height(node->left_) - Height(node->right_)) : 0); }

void AvlTree::Swap (TreeNode& lhs, TreeNode& rhs) { Data* temp {lhs.data_}; lhs.data_ = rhs.data_; rhs.data_ = temp; }
