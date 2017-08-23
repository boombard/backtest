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
  for (i = 0; i < data.size(); i++) {
    cout << put_time(&data[i].time, "%Y-%m-%d") << ", " << data[i].value << endl;
  }
}

Valuations Valuations::query (string begin, string end) {
  Valuations result;

  return result;
}

vector<double> Valuations::get_values() {
  int i;
  vector<double> result;
  result.resize(data.size());
  for (i = 0; i < data.size(); i++) {
    result[i] = data[i].value;
  }

  return result;
}

vector<tm> Valuations::get_index() {
  int i;
  vector<tm> result;
  result.resize(data.size());
  for (i = 0; i < data.size(); i++) {
    result[i] = data[i].time;
  }

  return result;
}


Bollinger moving_average (Valuations vals, int interval) {

  Bollinger result;
  vector<double> values = vals.get_values();
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
    double sq_sum;
    int k;
    for (k = begin; k < i; k++) {
      sq_sum += pow((values[k] - mean), 2.0);
    }
    double stdev = sqrt(sq_sum / (interval - 1));
    result.mean[i] = mean;
    result.upper_sd[i] = mean + stdev;
    result.lower_sd[i] = mean - stdev;
    result.stdev[i] = stdev;
  }

  return result;
}
