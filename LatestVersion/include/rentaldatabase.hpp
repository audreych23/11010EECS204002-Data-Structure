#ifndef RENTALDATABASE_HPP_
#define RENTALDATABASE_HPP_

class RentalDatabase
{
public:

  RentalDatabase () = default;
  RentalDatabase ();
  ~RentalDatabase () = default;

  //void ReadFile (); //our constructor?
  int GetTotalRevenues ();
  void RentBike ();
  void ReturnBike ();
  int CalculateRevenue ();

private:

  Station stations; // TODO might need copy assignment for each class because I need to copy them in read file
  Graph map;
  RentalHistory rental_histories;
  Fee fees;

  int total_revenues;

};

int RentalDatabase::GetTotalRevenues () { return total_revenues; }

void RentalDatabase::RentBike (int station_id_rent, int bike_type, int user_id, int time_begin)
{
  int bike_id = stations.GetFromInventory (station_id_rent, bike_type);
  rental_histories.Insert(user_id, bike_type, station_id_rent, time_begin, bike_id);

  return;
}

void RentalDatabase::ReturnBike (int station_id_return, int user_id, int time_return)
{
  if(rental_histories.Find(user_id) != nullptr){
    station_id_rent = GetStationId(rental_histories.Find(user_id));
    bike_type = GetBikeType(rental_histories.Find(user_id));
    time_rent = GetTimeBegin(rental_histories.Find(user_id));
    bike_id = GetBikeId(rental_histories.Find(user_id)); // do one function call? //TODO
  } else { return; } //invalid

  rental_histories.Delete(user_id);

  Stations.UpdateInventory(bike_type, station_id_return, bike_id);

  CalculateRevenue(time_rent, time_return, station_id_rent, station_id_return);

  return;
}

int RentalDatabase::CalculateRevenue (int time_rent, int time_return, int station_id_rent, int station_id_return)
{
  //TODO continue
  time_diff = time_return - time_rent;
  shortest_dist = map.GetShortestDistance(station_id_rent, station_id_return); // from to
  if (time_diff == lowerbound)
  {

  }
  else
  {

  }
  total_revenues += ;
}


#endif
