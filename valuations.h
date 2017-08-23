#ifndef VALUATIONS_H
#define VALUATIONS_H

#include <iostream>
#include <vector>

struct Bollinger {
  std::vector<double> mean;
  std::vector<double> upper_sd;
  std::vector<double> lower_sd;
  std::vector<double> stdev;
};

struct DataPoint {
  double value;
  std::tm time;
};

class Valuations {
  public:
    std::vector<DataPoint> data;
    Valuations () {};
    std::vector<double> get_values ();
    std::vector<tm> get_index ();
    void print ();
    Valuations query (std::string begin, std::string end);
};

Bollinger moving_average(Valuations, int);

#endif
