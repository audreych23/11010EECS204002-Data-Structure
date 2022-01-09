#include "station.hpp"

/* public member functions */

Station::Station
(
  uint64_t station_id,
  uint64_t electric_bike_size,
  uint64_t lady_bike_size,
  uint64_t road_bike_size
)
{
  uint64_t prefix {station_id * 100};
  for (uint64_t i {}; i != electric_bike_size; ++i) { electric_bikes.Push(prefix + i); }
  for (uint64_t i {}; i != lady_bike_size; ++i) { lady_bikes.Push(prefix + i); }
  for (uint64_t i {}; i != road_bike_size; ++i) { road_bikes.Push(prefix + i); }
}

bool Station::IsEmpty (std::string const& bike_type) const
{
  if (bike_type[0] == 'e') { return electric_bikes.IsEmpty(); }
  if (bike_type[0] == 'l') { return lady_bikes.IsEmpty(); }
  return road_bikes.IsEmpty();
}

void Station::InsertBike (std::string const& bike_type, uint64_t const bike_id)
{
  if (bike_type[0] == 'e') { electric_bikes.Push(bike_id); }
  else if (bike_type[0] == 'l') { lady_bikes.Push(bike_id); }
  else { road_bikes.Push(bike_id); }
  return;
}

uint64_t Station::RetrieveBike (std::string const& bike_type)
{
  uint64_t bike_id {};
  if (bike_type[0] == 'e')
  {
    bike_id = electric_bikes.Top();
    electric_bikes.Pop();
  }
  else if (bike_type[0] == 'l')
  {
    bike_id = lady_bikes.Top();
    lady_bikes.Pop();
  }
  else
  {
    bike_id = road_bikes.Top();
    road_bikes.Pop();
  }
  return bike_id;
}

std::ostream& operator<< (std::ostream& out, Station const& station)
{
  out << "electric: " << station.electric_bikes;
  out << "lady: " << station.lady_bikes;
  out << "road: " << station.road_bikes;
  return out;
}

Stations::Stations ()
{
  std::ifstream fin {"test_case/station.txt"};
  while (fin)
  {
    uint64_t station_id {};
    uint64_t electric_bike_size {};
    uint64_t lady_bike_size {};
    uint64_t road_bike_size {};
    fin >> station_id >> electric_bike_size >> lady_bike_size >> road_bike_size;
    if (station_id)
    {
      stations_.PushBack(Station{station_id, electric_bike_size, lady_bike_size, road_bike_size});
    }
  }
}

uint64_t Stations::Size () const { return stations_.Size(); }

Station& Stations::operator[] (uint64_t index)
{
  return stations_[index - 1];
}

std::ostream& operator<< (std::ostream& out, Stations const& stations)
{
  for (uint64_t station_id {}; station_id != stations.stations_.Size(); ++station_id)
  {
    out << (station_id + 1) << ":\n";
    out << stations.stations_[station_id];
  }
  return out;
}
