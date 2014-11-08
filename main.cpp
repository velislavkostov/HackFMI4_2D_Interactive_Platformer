#include <iostream>
using namespace std;
//#include "GameObject.hpp"
#include "Physics.hpp"
#include <vector>
#include <iterator>
using std::vector;

int main(){
    SDL_Window* window = (SDL_Window*)nullptr;
    SDL_Renderer* renderer = (SDL_Renderer*)nullptr;
    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    bool running = false;
    if(window != (SDL_Window*)nullptr && renderer != (SDL_Renderer*)nullptr){
        running = true;
    }
    SDL_Event event;
    
    vector<GameObject> objects_;
    for(int a = 0; a < 25; ++a){
        GameObject obj(rand() % 1440, rand() % 768, "");
        obj.load_texture(renderer, "platform.png");
        obj.set_width(rand() % 250 + 100);
        obj.set_height(rand() % 200 + 100);
        obj.set_rotation(rand() % 90);
        objects_.push_back(obj);
    }
    
    int i = 1;
    while(running){
        if(SDL_PollEvent(&event)){
            if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                running = false;
        }
        SDL_RenderClear(renderer);
        if(i < 360){
            i++;
        }
        else{
            i = 1;
        }
        for(vector<GameObject>::iterator it = objects_.begin(); it != objects_.end(); ++it){
            if((*it).get_y() > 768)
                (*it).set_y(0);
            (*it).set_rotation(i);
            Physics::apply_gravity((*it));
            (*it).draw(renderer);
        }
        
        SDL_RenderPresent(renderer);
    };
    return 0;
};
