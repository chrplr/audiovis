// basic example of priority queue
// Time-stamp: <2021-04-16 13:44:25 christophe@pallier.org>

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
  string parameters;
  time_action(int time,  string act, string param): onset(time), action(act), parameters(param) {};
  friend ostream& operator<<(ostream &out, const time_action &ta);
};

struct compare_onsets {
    bool operator()(time_action const & p1, time_action const & p2) {
        // return "true" if "p1" is ordered before "p2", for example:
        return p1.onset > p2.onset;
    }
};

ostream& operator<< (ostream &out, const time_action &ta)  {
  out << ta.action << "(" << ta.parameters << ")" << endl;
  return out;
};



class action_queue {
public:
  priority_queue<time_action, vector<time_action>, compare_onsets> pq;

  void add_event(time_action const &a) {
    (this -> pq).push(a);
  }

  void read_events_from_csv(string fname) {
    io::CSVReader<4> in(fname);
    in.read_header(io::ignore_extra_column, "onset", "duration", "action", "filename");
    int onset; int duration; string action; string filename;
    while(in.read_row(onset, duration, action, filename)){
      time_action a = time_action(onset, action, filename);
      this -> add_event(a);
      time_action b =  time_action(onset + duration, "clear_screen", filename);
      this -> add_event(b);
    }
  }

  bool empty() { return (this -> pq).empty(); };
  time_action top() { return (this -> pq).top(); };
  void pop() { (this -> pq).pop(); };
};



int main(int argc, char* argv[])
{
  time_action a = time_action(10, "print", " Bonjour!");
  time_action b = time_action(20, "print", " ca va?");
  time_action c = time_action(30, "print", " Au revoir!");

  priority_queue<time_action, vector<time_action>, compare_onsets> pq;

  pq.push(b);
  pq.push(c);
  pq.push(a);



  while (!pq.empty()) {
    cout << pq.top();  // Print highest priority string
    pq.pop();          // Remmove highest priority string
  }



  action_queue pq2 = action_queue();
  pq2.read_events_from_csv("stimulations.csv");

  while (!pq2.empty()) {
    cout << pq2.top();  // Print highest priority string
    pq2.pop();          // Remmove highest priority string
  }


  return 0;
}

