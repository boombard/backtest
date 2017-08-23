#include <iostream>
#include <string>
#include "consume.h"
#include "valuations.h"

using namespace std;

int main () {

  Valuations result = read_historical("data/bitcoinity_data_coinfloor.csv");
  // result.print();
  Bollinger boll = moving_average(result, 5);
  int length = result.data.size();
  int i;
  for (i = length - 10; i <= length; i++) {
    cout << boll.lower_sd[i] << endl;
  }

  cout << "***" << endl;

  for (i = length - 10; i <= length; i++) {
    cout << boll.upper_sd[i] << endl;
  }
  cout << "***" << endl;

  for (i = length - 10; i <= length; i++) {
    cout << result.get_values()[i] << endl;
  }

  return 0;
}
