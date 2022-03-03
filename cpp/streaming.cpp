/* */
/* Time-stamp: <2021-03-28 19:14:47 christophe@pallier.org> */

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

# include "csv.h"


using namespace std;


const char * const pics[] =
    {
        "lizzie_1024x768.jpg",
        "rainbow_1024x768.jpg"
    };




const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

double get_delta_time(Uint64 time1, Uint64 time2)
{
  return (time2 - time1) * 1000 / (double)SDL_GetPerformanceFrequency();
}




int main()
{
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    SDL_Surface *image1, *image2;
    SDL_Texture *texture1, *texture2;

    bool quit = false;
    SDL_Event event;
    Uint64 time1, time2, time3;

    vector<int> onsets;
    vector<int> offsets;
    vector<string> fnames;

    io::CSVReader<3> in("pics.csv");
    in.read_header(io::ignore_extra_column, "onset", "offset", "filename");
    int onset; int offset; string filename;
    while(in.read_row(onset, offset, filename)){
      cout << onset << " " << offset << " " << filename << endl;
      onsets.push_back(onset);
      offsets.push_back(offset);
      fnames.push_back(filename);
    }

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

    image1 = IMG_Load(pics[0]);
    image2 = IMG_Load(pics[1]);

    /* sdlTexture = SDL_CreateTexture(sdlRenderer, */
    /*                                SDL_PIXELFORMAT_ARGB8888, */
    /*                                SDL_TEXTUREACCESS_STREAMING, */
    /*                                SCREEN_WIDTH, SCREEN_HEIGHT); */

    texture1 = SDL_CreateTextureFromSurface(sdlRenderer, image1);
    texture2 = SDL_CreateTextureFromSurface(sdlRenderer, image2);

    while (!quit)
        {
            SDL_WaitEvent(&event);

            switch (event.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    quit = true;
                    break;
                }

            //SDL_Rect dstrect = { 5, 5, 320, 240 };
            //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            time1 = SDL_GetPerformanceCounter();
            SDL_RenderCopy(sdlRenderer, texture1, NULL, NULL);
            SDL_RenderPresent(sdlRenderer);
            time2 = SDL_GetPerformanceCounter();

            SDL_WaitEvent(&event);

            switch (event.type)
              {
              case SDL_QUIT:
                quit = true;
                break;
              case SDL_KEYDOWN:
                quit = true;
                break;
              }



            SDL_RenderCopy(sdlRenderer, texture2, NULL, NULL);
            SDL_RenderPresent(sdlRenderer);
            time3 = SDL_GetPerformanceCounter();
            wcout << get_delta_time(time1, time2) << " " << get_delta_time(time2, time3) << endl;
        }

    /* SDL_UpdateTexture(sdlTexture, NULL, myPixels, 640 * sizeof (Uint32)); */
    /* SDL_RenderClear(sdlRenderer); */
    /* SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL); */
    /* SDL_RenderPresent(sdlRenderer); */
    SDL_DestroyTexture(texture1);
    SDL_FreeSurface(image1);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(image2);

    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
