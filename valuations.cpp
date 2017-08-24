#include "valuations.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <numeric>
#include <cmath>
#include <tuple>

using namespace std;

void Valuations::print () {
  int i;
  for (i = 0; i < index.size(); i++) {
    cout << put_time(&index[i], "%Y-%m-%d") << ", " << values[i] << endl;
  }
}

Valuations Valuations::query (string begin, string end) {
  Valuations result;

  return result;
}

double Valuations::apply(vector<Command> commands) {
  double returns = 0.0;
  double bought = 0.0;
  int i;
  for (i = 0; i < commands.size(); i++) {
    if (commands[i].cmd == 'b') {
      bought = values[commands[i].index];
    }
    else if (commands[i].cmd == 's') {
      double profit = values[commands[i].index] - bought;
      returns += profit;
      bought = 0.0;
    }
  }
  return returns;
}

Bollinger moving_average (Valuations vals, int interval, double K) {

  Bollinger result;
  vector<double> values = vals.values;
  result.mean.resize(values.size());
  result.upper_sd.resize(values.size());
  result.lower_sd.resize(values.size());
  result.stdev.resize(values.size());

  double window[interval];

  int i;
  for (i = 0; i < values.size(); i++) {
    double *begin_ptr;
    double begin;
    double denominator;
    if (i < interval) {
      begin_ptr = &values[0];
      begin = 0;
      denominator = i + 1;
    }
    else {
      begin_ptr = &values[i - interval] + 1;
      begin = i - interval + 1;
      denominator = interval;
    }
    double sum = accumulate(begin_ptr, &values[i + 1], 0.0);
    double mean = sum / denominator;
    double sq_sum = 0.0;
    int k;
    for (k = begin; k < i; k++) {
      sq_sum += pow((values[k] - mean), 2.0);
    }
    double stdev = K * sqrt(sq_sum / (denominator - 1));
    result.mean[i] = mean;
    result.upper_sd[i] = mean + stdev;
    result.lower_sd[i] = mean - stdev;
    result.stdev[i] = stdev;
  }

  return result;
}

vector<Command> bollinger_buy_sell (Bollinger boll, Valuations vals) {
  int i;
  char state = 'n';
  vector<Command> commands;
  for (i = 0; i <= boll.mean.size(); i++) {
    double mean = boll.mean[i];
    double upper = boll.upper_sd[i];
    double lower = boll.lower_sd[i];
    double value = vals.values[i];
    if (value > upper) {
      if (state == 'n') {
        Command command = {i, 'b'};
        commands.push_back(command);
        state = 'b';
      }
    }
    if (value < mean) {
      if (state == 'b') {
        Command command = {i, 's'};
        commands.push_back(command);
        state = 'n';
      }
    }
  }
  return commands;
}
