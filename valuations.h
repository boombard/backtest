#ifndef VALUATIONS_H
#define VALUATIONS_H

#include <iostream>
#include <vector>

struct Command {
  int index;
  char cmd;
};

struct Bollinger {
  std::vector<double> mean;
  std::vector<double> upper_sd;
  std::vector<double> lower_sd;
  std::vector<double> stdev;
};

class Valuations {
  public:
    std::vector<double> values;
    std::vector<std::tm> index;
    Bollinger boll;
    Valuations () {};
    void print ();
    Valuations query (std::string begin, std::string end);
    double apply(std::vector<Command>);
};

std::vector<Command> bollinger_buy_sell(Bollinger, Valuations);

Bollinger moving_average(Valuations, int, double K = 1.0);

#endif
