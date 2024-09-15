#include "../include/misc.h"

using std::string;

string temp(const CellType &type) {
    string s;
    switch (type) {
    case CellType::Empty:
        s = "Empty";
        break;
    case CellType::Obstacle:
        s = "Obstacle";
        break;
    case CellType::Start:
        s = "Start";
        break;
    case CellType::Finish:
        s = "Finish";
        break;
    default:
        s = "Unknown";
        break;
  }
  return s;
}