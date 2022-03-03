// basic example of priority queue
// Time-stamp: <2021-04-16 12:46:57 christophe@pallier.org>

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

# include "csv.h"


using namespace std;

class time_action {
public:
  int onset = 0;
  string action;
  time_action(int time,  string st): onset(time), action(st) {};
  string getaction() { return action; }
  friend ostream& operator<<(ostream &out, const time_action &ta);
};

struct compare_onsets {
    bool operator()(time_action const & p1, time_action const & p2) {
        // return "true" if "p1" is ordered before "p2", for example:
        return p1.onset > p2.onset;
    }
};

ostream& operator<< (ostream &out, const time_action &ta)  {
  out << ta.action << endl;
  return out;
};



int main(int argc, char* argv[])
{
  time_action a = time_action(10, "print Bonjour!");
  time_action b = time_action(20, "print ca va?");
  time_action c = time_action(30, "print Au revoir!");

  priority_queue<time_action, vector<time_action>, compare_onsets> pq;

  pq.push(b);
  pq.push(c);
  pq.push(a);

  while (!pq.empty()) {
    cout << pq.top();  // Print highest priority string
    pq.pop();          // Remmove highest priority string
  }


  io::CSVReader<3> in("pics.csv");
  in.read_header(io::ignore_extra_column, "onset", "offset", "filename");
  int onset; int offset; string filename;
  while(in.read_row(onset, offset, filename)){
    time_action a = time_action(onset, filename);
    pq.push(a);
  }

  while (!pq.empty()) {
    cout << pq.top();  // Print highest priority string
    pq.pop();          // Remmove highest priority string
  }



  return 0;
}

