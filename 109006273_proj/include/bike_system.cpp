#include <sstream>

#include "bike_system.hpp"

Fee::Fee ()
{
  std::ifstream fin {"test_case/fee.txt"};
  std::string buffer;
  fin >> buffer >> discounted_electric_bike_fee >> regular_electric_bike_fee;
  fin >> buffer >> discounted_lady_bike_fee >> regular_lady_bike_fee;
  fin >> buffer >> discounted_road_bike_fee >> regular_road_bike_fee;
  // fin >> waiting_fee >> bike_switching_rate >> transfer_fee;
}

std::ostream& operator<< (std::ostream& out, Fee const& fee)
{
  out
  << "electric bike fee: {" << "discounted: " << fee.discounted_electric_bike_fee
  << ", regular: " << fee.regular_electric_bike_fee << "}\n"
  << "lady bike fee: {" << "discounted: " << fee.discounted_lady_bike_fee
  << ", regular: " << fee.regular_lady_bike_fee << "}\n"
  << "road bike fee: {" << "discounted: " << fee.discounted_road_bike_fee
  << ", regular: " << fee.regular_road_bike_fee << "}\n";
  return out;
}

BikeSystem::BikeSystem (): revenue_ {}
{
  map_ = Graph(stations_.Size());
}

void BikeSystem::Run ()
{
  {
    std::ifstream fin {"test_case/user.txt"};
    std::ofstream response_1 {"part1_response.txt"};
    bool is_first_line {true};
    while (fin)
    {
      std::string line;
      std::getline(fin, line);
      if (!line.empty())
      {
        if (is_first_line) { is_first_line = false; }
        else { response_1 << "\n"; }
        response_1 << line;
        std::stringstream ss;
        ss << line;
        std::string instruction;
        ss >> instruction;
        if (instruction == "rent")
        {
          uint64_t station_id {};
          std::string bike_type;
          uint64_t user_id {};
          uint64_t begin_time {};
          ss >> station_id >> bike_type >> user_id >> begin_time;
          if (!stations_[station_id].IsEmpty(bike_type))
          {
            response_1 << "\naccept";
            uint64_t bike_id {stations_[station_id].RetrieveBike(bike_type)};
            users_.Insert(user_id, bike_type, station_id, begin_time, bike_id);
          }
          else
          {
            response_1 << "\nreject";
          }
        }
        else
        {
          uint64_t station_id {};
          uint64_t user_id {};
          uint64_t end_time {};
          ss >> station_id >> user_id >> end_time;
          TreeNode* node {users_.Search(user_id)};
          if (node)
          {
            Data data {*(node->GetData())};
            users_.Delete(user_id);
            stations_[station_id].InsertBike(data.bike_type, data.bike_id);
            AccumulateRevenue(data.bike_type, data.begin_time, end_time, data.station_id, station_id);
          }
        }
      }
    }
  }
  {
    std::ofstream status_1 {"part1_status.txt"};
    status_1 << stations_;
    status_1 << revenue_;
  }
  {
    std::ifstream response_1 {"part1_response.txt"};
    std::ofstream response_2 {"part2_response.txt"};
    response_2 << response_1.rdbuf();
  }
  {
    std::ifstream status_1 {"part1_status.txt"};
    std::ofstream status_2 {"part2_status.txt"};
    status_2 << status_1.rdbuf();
  }
}

void BikeSystem::AccumulateRevenue (std::string const& bike_type, uint64_t begin_time, uint64_t end_time, uint64_t from, uint64_t to)
{
  uint64_t shortest_duration {map_.Distance(from, to)};
  uint64_t duration {end_time - begin_time};
  if (bike_type[0] == 'e')
  {
    revenue_ += duration * ((duration <= shortest_duration) ? fee_.discounted_electric_bike_fee : fee_.regular_electric_bike_fee);
  }
  else if (bike_type[0] == 'l')
  {
    revenue_ += duration * ((duration <= shortest_duration) ? fee_.discounted_lady_bike_fee : fee_.regular_lady_bike_fee);
  }
  else
  {
    revenue_ += duration * ((duration <= shortest_duration) ? fee_.discounted_road_bike_fee : fee_.regular_road_bike_fee);
  }
  return;
}
