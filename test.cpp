#include <iostream>
#include <string>
#include "consume.h"
#include "valuations.h"

using namespace std;

int main () {

  Valuations result = read_historical("data/bitcoinity_data_coinfloor.csv");
  // result.print();
  Bollinger boll = moving_average(result, 20, 2);
  int length = result.index.size();

  vector<Command> commands = bollinger_buy_sell(boll, result);

  int i;
  for (i = 0; i < commands.size(); i++) {
    cout << commands[i].index << " " << commands[i].cmd << endl;
  }

  cout << "Total: " << result.apply(commands) << endl;

  return 0;
}
