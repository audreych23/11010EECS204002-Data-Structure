#include <iostream>
#include <fstream>
#include "input.hpp"

void CalculateRevenue (Graph& map, Fee& fee, int& revenues, int time_rent, int time_return, int station_id_rent, int station_id_return, int bike_type)
{
  int shortest_time = map.GetDistance(station_id_rent, station_id_return);
  int time_difference = time_return - time_rent;
  if (time_difference <= shortest_time)
  {
    revenues += time_difference * fee.GetFeeDiscount(bike_type);
  }
  else
  {
    revenues += time_difference * fee.GetFeeRegular(bike_type);
  }
}

std::vector<std::vector<int>> ParseInputStation()
{
  std::string line;
  /* read station input */
  std::ifstream file("test_case/station.txt");
  std::vector<std::vector<int>> read_station_input;
  if (file.is_open())
  {
    while (getline (file,line))
    {
      int j = 10;
      int x = 0;
      std::vector<int> temp;
      for(int i {}; i != line.length(); ++i)
      {
        if (line[i] != ' ')
        {
          x = j * x + line[i] - '0';
        }
        else
        {
          temp.push_back (x);
          x = 0;
        }
      }
      temp.push_back(x);
      //x = 0;
      read_station_input.push_back(temp);
      //std::cout << line << '\n';
    }
    file.close();
  }
  else { std::cerr << "Unable to open file"; }

  return read_station_input;
}

std::vector<std::vector<int>> ParseInputMap ()
{
  std::string line;

  std::ifstream file("test_case/map.txt");
  std::vector<std::vector<int>> read_map_input;
  if (file.is_open())
  {
    while ( getline (file,line) )
    {
      int j = 10;
      int x = 0;
      std::vector<int> temp;
      for(int i {}; i != line.length(); ++i)
      {
        if (line[i] != ' ')
        {
          x = j * x + line[i] - '0';
        }
        else
        {
          temp.push_back (x);
          x = 0;
        }
      }
      temp.push_back(x);
      read_map_input.push_back(temp);
      //std::cout << line << '\n';
      //line[0] src, line[2] dest, line[4] length
    }
    file.close();
  }
  else { std::cerr << "Unable to open file"; }
  return read_map_input;

}

std::vector<std::vector<std::string>> ParseInputFee ()
{
  std::string line;

  std::ifstream file("test_case/fee.txt");
  std::vector<std::vector<std::string>> read_fee_input;
  if (file.is_open())
  {
    while ( getline (file,line) )
    {
      std::string buf = "";

      std::vector<std::string> temp;
      for (int i {}; i != line.length(); ++i)
      {
        if (line[i] != ' ')
        {
          buf += line[i];
        }
        else
        {
          temp.push_back(buf);
          buf = "";
        }
      }
      temp.push_back(buf);
      read_fee_input.push_back(temp);
      //std::cout << line << '\n';
    }
    file.close();
  }
  else { std::cerr << "Unable to open file"; }
  return read_fee_input;
}

std::vector<std::vector<std::string>> ParseInputUser ()
{
  std::string line;

  std::ifstream file("test_case/user.txt");
  std::vector<std::vector<std::string>> read_user_input;
  if (file.is_open())
  {
    while ( getline (file,line) )
    {
      std::string buf = "";

      std::vector<std::string> temp;
      for (int i {}; i != line.length(); ++i)
      {
        if (line[i] != ' ')
        {
          buf += line[i];
        }
        else
        {
          temp.push_back(buf);
          buf = "";
        }
      }
      temp.push_back(buf);
      read_user_input.push_back(temp);
      //std::cout << line << '\n';
      //line[0] src, line[2] dest, line[4] length
    }
    file.close();
  } else { std::cerr << "Unable to open file"; }

  return read_user_input;
}

void InitializeInventory (std::vector<Inventory>& station, std::vector<std::vector<int>>& read_station_input)
{
  for (int i {}; i < read_station_input.size(); ++i)
  {
    Inventory inventory(read_station_input[i][0], read_station_input[i][1], read_station_input[i][2], read_station_input[i][3]);
    station.push_back(inventory);
  }
}

void InitializeGraph (Graph& map, std::vector<std::vector<int>>& read_map_input)
{
  for (int i {}; i < read_map_input.size(); ++i)
  {
    map.Insert(read_map_input[i][0], read_map_input[i][1], read_map_input[i][2]);
  }
  map.InitializeDistance();
}

Fee InitializeFee (std::vector<std::vector<std::string>>& read_fee_input)
{
  int k {10};
  int for_input[3][2] = {};
  for (int i {}; i < read_fee_input.size() - 3; ++i)
  {
    if (read_fee_input[i][0] == "electric" || read_fee_input[i][0] == "lady" || read_fee_input[i][0] == "road")
    {
      int k {10};
      auto g {read_fee_input[i]};
      for (int j {}; j < g[1].length(); ++j)
      {
        for_input[i][0] = k * for_input[i][0] + g[1][j] - '0';
      }

      for (int j {}; j < g[2].length(); ++j)
      {
        for_input[i][1] = k * for_input[i][1] + g[2][j] - '0';
      }
    }
  }

  int waiting_fee {};
  for (int i {}; i < read_fee_input[3][0].length(); ++i)
  {
    waiting_fee = waiting_fee * k + read_fee_input[3][0][i] - '0';
  }

  double bike_switch {};
  double temp_coma {};
  int counter {};
  int after_coma {};
  for (int i {}; i < read_fee_input[4][0].length(); ++i)
  {
    if (read_fee_input[4][0][i] == '.' )
    {
      after_coma = 1;
    }
    else
    {
      if (after_coma == 1)
      {
        temp_coma = temp_coma * k + read_fee_input[4][0][i] - '0';
        counter++; // 10^1
      }
      else
      {
        bike_switch = bike_switch * k + read_fee_input[4][0][i] - '0';
      }
    }
  }
  for (int m {}; m < counter; ++m) {temp_coma /= 10;}
  bike_switch += temp_coma;

  int transfer_rate {};

  for (int i {}; i < read_fee_input[5][0].length(); ++i)
  {
    waiting_fee = waiting_fee * k + read_fee_input[5][0][i] - '0';
  }

  Fee fee (for_input, waiting_fee, bike_switch, transfer_rate);
  return fee;
}


void InitializeRentalHistory(RentalHistory& rental_history, std::vector<std::vector<std::string>>& read_user_input, Fee& fee, Graph& map, std::vector<Inventory> &station, int& revenues)
{
  // bike is 5 digit
  //int counter {1};
  for (int i {}; i < read_user_input.size(); ++i)
  {
    //std::cout << counter++ << '\n';
    auto g {read_user_input[i]}; // vector<string>
    // parse the string
    int k {10};
    int station_id {0};
    for (int j {}; j < g[1].length(); ++j)
    {
      station_id = k * station_id + g[1][j] - '0'; // rent/return doesn't matter
    }
    if (g[0] == "rent")
    {
      int bike_type {};
      if (g[2] == "electric") { bike_type = 0; }
      else if (g[2] == "lady") { bike_type = 1; }
      else { bike_type = 2; }

      int user_id {};
      for (int j {}; j < g[3].length(); ++j)
      {
        user_id = k * user_id + g[3][j] - '0';
      }

      int time_begin {};
      for (int j {}; j < g[4].length(); ++j)
      {
        time_begin = k * time_begin + g[4][j] - '0';
      }

      // user_id, bike type, station_id, time, bike_id
      //std::cout << "station_id" << " " << station_id << '\n';
      //std::cout << "bike_type" << " " << bike_type << '\n';
      int bike_id = station[station_id - 1].GetBike(bike_type);
      if(bike_id == -1) // means empty
      {
        std::cout << "reject" << '\n';
        continue;
      }
      else
      {
        std::cout << "accept" << '\n';
      }
      //UserNode users(user_id, bike_type, station_id, time, bike_id);
      rental_history.Insert(user_id, bike_type, station_id, time_begin, bike_id);
      //========debug
      // std::cout << "Inorder : " << '\n';
      // std::cout << "=========" << '\n';
      // rental_history.InOrder();
      // std::cout << '\n';
      // std::cout << "==========="<< '\n';
    }
    else if (g[0] == "return")
    {
      int user_id {};
      for (int j {}; j < g[2].length(); ++j)
      {
        user_id = k * user_id + g[2][j] - '0';
      }

      int time_return {};
      for (int j {}; j < g[3].length(); ++j)
      {
        time_return = k * time_return + g[3][j] - '0';
      }

      UserNode* node_find = rental_history.Find(user_id);
      int station_id_rent {}, bike_type {}, time_rent {}, bike_id {};
      if(node_find != nullptr){
        station_id_rent = node_find->GetStationId();
        bike_type = node_find->GetBikeType();
        time_rent = node_find->GetTimeBegin();
        bike_id = node_find->GetBikeId(); // do one function call? //TODO
      }
      else { std::cout << "not found" << '\n'; continue; } //invalid // to debug
      // but apparently if we reject it can be not found so np

      rental_history.Delete(user_id);
      // std::cout << "Inorder delete: " << '\n';
      // std::cout << "=========" << '\n';
      // rental_history.InOrder();
      // std::cout << '\n';
      // std::cout << "==========="<< '\n';

      station[station_id - 1].SetBike(bike_type, bike_id);

      CalculateRevenue(map, fee, revenues, time_rent, time_return, station_id_rent, station_id, bike_type);
    }
    // map.Insert(read_user_input[0], read_user_input[1], read_user_input[2], read_user_input[3]);

  }
}

// TODO : print and debug the AVL tree
// TODO : check off by one error
// TODO : check whether to reject or accept
