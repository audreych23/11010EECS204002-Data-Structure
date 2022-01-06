#include <iostream>
#include "users.hpp"

UserNode::UserNode (int user_id, int bike_type, int station_id, int time_begin, int bike_id)
{
  key = user_id;
  left = nullptr;
  right = nullptr;
  height = 1;

  this->bike_type = bike_type;
  this->station_id = station_id;
  this->time_begin = time_begin;
  this->bike_id = bike_id;
}

// UserNode::UserNode (const UserNode& users) // ???
// {
//   key = users.user_id;
//   left = users->left;
//   right = users->right;
//   height = users->height;
//
//   bike_type = users.bike_type;
//   station_id = users.station_id;
//   time_begin = users.time_begin;
//   bike_id = users.bike_id;
// }

int UserNode::GetBikeType ()
{
  return bike_type;
}

int UserNode::GetStationId ()
{
  return station_id;
}

int UserNode::GetTimeBegin ()
{
  return time_begin;
}

int UserNode::GetBikeId ()
{
  return bike_id;
}
