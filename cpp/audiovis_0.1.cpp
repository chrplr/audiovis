// basic example of priority queue
// Time-stamp: <2021-04-18 13:43:22 christophe@pallier.org>

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <string>


#include <SDL.h>
#include <SDL_image.h>

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


SDL_Window *g_sdlWindow;
SDL_Renderer *g_sdlRenderer;


int main(int argc, char* argv[])
{

  action_queue pq = action_queue();
  pq.read_events_from_csv("stimulations.csv");

  

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);

  sdlWindow = SDL_CreateWindow("Streaming",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
  SDL_RenderClear(sdlRenderer);
  SDL_RenderPresent(sdlRenderer);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
  SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  a= get_ticks();
  while (!pq.empty()) {
    time_action a = pq.pop()

  }



  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);

  IMG_Quit();
  SDL_Quit();

  return 0;

}

