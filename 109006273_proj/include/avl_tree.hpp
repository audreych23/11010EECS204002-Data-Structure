#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <fstream>

#include "vector.hpp"

struct Data
{
  Data () = default;
  Data
  (
    uint64_t user_id,
    std::string bike_type,
    uint64_t station_id,
    uint64_t begin_time,
    uint64_t bike_id
  )
  : user_id {user_id},
    bike_type {bike_type},
    station_id {station_id},
    begin_time {begin_time},
    bike_id {bike_id}
  {
  }

  friend std::ostream& operator<< (std::ostream& out, Data const& data);

  uint64_t user_id;
  std::string bike_type;
  uint64_t station_id;
  uint64_t begin_time;
  uint64_t bike_id;
};

class TreeNode
{
public:

  TreeNode () = default;

  TreeNode
  (
    uint64_t user_id,
    std::string bike_type,
    uint64_t station_id,
    uint64_t begin_time,
    uint64_t bike_id
  )
  : height_ {1},
    left_ {nullptr},
    right_ {nullptr},
    data_ {new Data{user_id, bike_type, station_id, begin_time, bike_id}}
  {
  }

  ~TreeNode ()
  {
    delete data_;
    delete left_;
    delete right_;
  }

  Data* GetData () const;

  friend std::ostream& operator<< (std::ostream& out, TreeNode const& node);
  friend class AvlTree;

private:

  uint64_t height_;
  TreeNode *left_;
  TreeNode *right_;
  Data *data_;

};

class AvlTree
{
public:

  AvlTree (): root_ {nullptr} {}
  ~AvlTree () { delete root_; }

  TreeNode* Search (uint64_t user_id);
  void Insert
  (
    uint64_t user_id,
    std::string bike_type,
    uint64_t station_id,
    uint64_t begin_time,
    uint64_t bike_id
  );
  void Delete (uint64_t user_id);

  void PreOrder (Vector<Data>& preorder) const;
  void InOrder (Vector<Data>& inorder) const;
  void PostOrder (Vector<Data>& postorder) const;

  friend std::ostream& operator<< (std::ostream& out, AvlTree const& avl_tree);

private:

  TreeNode* Insert
  (
    TreeNode* node,
    uint64_t user_id,
    std::string bike_type,
    uint64_t station_id,
    uint64_t begin_time,
    uint64_t bike_id
  );
  TreeNode* Delete (TreeNode* node, uint64_t user_id);

  TreeNode* RightRotate (TreeNode* z);
  TreeNode* LeftRotate (TreeNode* z);

  uint64_t Max (uint64_t lhs, uint64_t rhs) const;
  uint64_t Height (TreeNode* node);
  int64_t BalanceFactor (TreeNode* node);
  void Swap (TreeNode& lhs, TreeNode& rhs);

  void PreOrder (Vector<Data>& preorder, TreeNode* node) const;
  void InOrder (Vector<Data>& inorder, TreeNode* node) const;
  void PostOrder (Vector<Data>& postorder, TreeNode* node) const;

  TreeNode* root_;

};

#endif
