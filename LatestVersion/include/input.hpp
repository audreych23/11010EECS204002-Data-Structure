#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <iostream>
#include <vector>
#include "graph.hpp"
#include "fee.hpp"
#include "inventory.hpp"
#include "rentalhistory.hpp"

void CalculateRevenue (Graph&, Fee&, int&, int, int, int, int, int);

std::vector<std::vector<int>> ParseInputStation ();

std::vector<std::vector<int>> ParseInputMap ();

std::vector<std::vector<std::string>> ParseInputFee ();

std::vector<std::vector<std::string>> ParseInputUser ();

void InitializeInventory (std::vector<Inventory>& station, std::vector<std::vector<int>>& read_station_input);

void InitializeGraph (Graph& map, std::vector<std::vector<int>>& read_map_input);

Fee InitializeFee (std::vector<std::vector<std::string>>& read_fee_input);

void InitializeRentalHistory(RentalHistory& rental_history, std::vector<std::vector<std::string>>& read_user_input, Fee& fee, Graph& map, std::vector<Inventory>& station, int& revenues);

#endif
