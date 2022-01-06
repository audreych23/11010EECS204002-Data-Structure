#ifndef USERS_HPP_
#define USERS_HPP_

class UserNode
{
public:

  UserNode () = default;
  UserNode (int, int, int, int, int);
  UserNode (const UserNode&) = default;
  UserNode& operator= (const UserNode&) = default;


  int GetBikeType ();
  int GetStationId ();
  int GetTimeBegin ();
  int GetBikeId ();

  int key; // key is user_id
  UserNode *left;
  UserNode *right;
  int height;

private:

  int bike_type;
  int station_id;
  int time_begin;
  int bike_id;

};


#endif
