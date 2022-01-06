#ifndef RENTALHISTORY_HPP_
#define RENTALHISTORY_HPP_

#include "users.hpp"

class RentalHistory //is implemented by an AVLTree
{
public:

  RentalHistory ();
  ~RentalHistory ();

  void Insert (int, int, int, int, int);
  void Delete (int);
  UserNode* Find(int);
  void PreOrder ();
  void InOrder ();

private:

  void Clear_ (UserNode*);

  UserNode* Insert_ (UserNode*, int, int, int, int, int);
  UserNode* Delete_ (UserNode*, int);
  UserNode* Find_ (UserNode*, int);
  void PreOrder_ (UserNode*);
  void InOrder_ (UserNode*);

  UserNode* RightRotate (UserNode*);
  UserNode* LeftRotate (UserNode*);

  int GetBalance (UserNode*);
  UserNode* MinValueNode (UserNode*);
  int max (int, int);
  int GetHeight (UserNode*);

  UserNode* root;

};

#endif
