#ifndef FEE_HPP_
#define FEE_HPP_

class Fee
{
public:

  Fee () = default;
  Fee (int[3][2], int, double, int);
  Fee (const Fee&) = default;
  Fee& operator= (const Fee&) = default;
  ~Fee () = default;

  int GetFeeDiscount (int);
  int GetFeeRegular (int);
  int GetWaitFee ();
  int GetBikeSwitch ();
  int GetTransferRate ();

private:

  int bike_fee_[3][2]; // first array denotes the type
  int waiting_fee_;
  int bike_switch_;
  int transfer_rate_;

};

#endif
