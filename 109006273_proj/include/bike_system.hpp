#ifndef BIKE_SYSTEM_HPP_
#define BIKE_SYSTEM_HPP_

#include "avl_tree.hpp"
#include "graph.hpp"
#include "station.hpp"

struct Fee
{
  Fee ();

  uint64_t discounted_electric_bike_fee;
  uint64_t regular_electric_bike_fee;
  uint64_t discounted_lady_bike_fee;
  uint64_t regular_lady_bike_fee;
  uint64_t discounted_road_bike_fee;
  uint64_t regular_road_bike_fee;
  // uint64_t waiting_fee {};
  // double bike_switching_rate {};
  // uint64_t transfer_fee {};

  friend std::ostream& operator<< (std::ostream& out, Fee const& fee);

};

class BikeSystem
{
public:

  BikeSystem ();

  void Run ();
  void AccumulateRevenue (std::string const& bike_type, uint64_t begin_time, uint64_t end_time, uint64_t from, uint64_t to);

private:

  uint64_t revenue_;
  Stations stations_;
  Graph map_;
  AvlTree users_;
  Fee fee_;

};

#endif
