#include <iostream>
#include "fee.hpp"

/*public members*/
Fee::Fee (int read_fee_data[3][2], int waiting_fee, double bike_switch, int transfer_rate)
{
  for (int i {}; i < 3; ++i)
  {
    for (int j {}; j < 2; ++j)
    {
      bike_fee_[i][j] = read_fee_data[i][j];
    }
  }
  waiting_fee_ = waiting_fee;
  bike_switch_ = bike_switch;
  transfer_rate_ = transfer_rate;
}

int Fee::GetFeeDiscount (int bike_type) { return bike_fee_[bike_type][0]; }

int Fee::GetFeeRegular (int bike_type) { return bike_fee_[bike_type][1]; }

int Fee::GetWaitFee () { return waiting_fee_; }

int Fee::GetBikeSwitch () { return bike_switch_; }

int Fee::GetTransferRate () { return transfer_rate_; }
