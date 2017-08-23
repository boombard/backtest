#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <locale>
#include "consume.h"

using namespace std;

vector<string> splitline(const string &s, char delim) {
  stringstream ss;
  ss.str(s);
  vector<string> elements;

  string item;
  while (getline(ss, item, delim)) {
    *(back_inserter(elements)++) = item;
  }
  return elements;
}

Valuations read_historical (string filename) {
  Valuations data;
  ifstream file_handle (filename);

  if (file_handle.is_open()) {
    cout << "Opened " << filename << endl;
    string line;
    int file_length = 0;
    while (getline(file_handle, line)) {
      ++file_length;
    }
    cout << "File length: " << file_length << endl;
    data.data.resize(file_length);
    file_handle.clear();
    file_handle.seekg(0, ios::beg);
    int line_number = 0;
    while (getline(file_handle, line)) {
      if (line_number != 0) {
        DataPoint point = {};
        vector<string> elements = splitline(line, ',');
        istringstream timepoint(elements[0]);
        timepoint >> get_time(&point.time, "%Y-%m-%d %H:%M:%S UTC");
        istringstream value(elements[1]);
        value >> point.value;
        // double value = atof(elements[1].c_str());
        data.data[line_number] = point;
      }
      ++line_number;
    }
    file_handle.close();
  }

  return data;
}
