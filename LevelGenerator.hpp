#ifndef _LEVEL_GENERATOR_HPP_
#define _LEVEL_GENERATOR_HPP_

#include "GameObject.hpp"

class LevelGenerator{
    vector<GameObject> objects_;
public:
    LevelGenerator();
    //If after the scroll an object isn't visible, delete it
    void scroll_up();
    void scroll_down();
    void draw_level(SDL_Renderer* renderer);
    //Deallocation
    ~LevelGenerator();
};

#endif
