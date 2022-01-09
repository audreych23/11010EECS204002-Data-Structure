#ifndef STATION_HPP_
#define STATION_HPP_

#include <fstream>

#include "min_heap.hpp"
#include "vector.hpp"

class Station
{
public:

  Station () = default;
  Station
  (
    uint64_t station_id,
    uint64_t electric_bike_size,
    uint64_t lady_bike_size,
    uint64_t road_bike_size
  );

  bool IsEmpty (std::string const& bike_type) const;
  void InsertBike (std::string const& bike_type, uint64_t const bike_id);
  uint64_t RetrieveBike (std::string const& bike_type);

  friend std::ostream& operator<< (std::ostream& out, Station const& station);

private:

  MinHeap electric_bikes;
  MinHeap lady_bikes;
  MinHeap road_bikes;

};

class Stations
{
public:

  Stations ();

  uint64_t Size () const;
  Station& operator[] (uint64_t index);

  friend std::ostream& operator<< (std::ostream& out, Stations const& stations);

private:

  Vector<Station> stations_;

};

#endif
