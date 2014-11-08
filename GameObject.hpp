#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using std::string;

//TODO: Enumerate GameObjectErrors

class GameObjectError{};

class GameObject{
    SDL_Rect rect_;
    SDL_Texture* texture_;
    double scale_;
    double rotation_;
    string filepath_;
protected:
    //Must be protected method, in order to preserve the GameObject invariant
    SDL_Rect* get_rectangle(){return &rect_;}
public:
    GameObject(int x, int y, string filepath): rect_{x, y, 0, 0}, filepath_(filepath.c_str()){}
    GameObject(int x, int y): rect_{x, y, 0, 0}{}    
    
    void draw(SDL_Renderer* renderer){
        if(renderer == (SDL_Renderer*)nullptr)
            throw GameObjectError();
        if(texture_ == (SDL_Texture*)nullptr)
            throw GameObjectError();
        if(rotation_ != 0){
            SDL_RenderCopyEx(renderer,texture_, (SDL_Rect*)nullptr, &rect_, rotation_, (SDL_Point*)nullptr, SDL_FLIP_NONE);
        }
        else{
            SDL_RenderCopy(renderer, texture_, (SDL_Rect*)nullptr, &rect_);
        }
    }
    
    SDL_Point get_position() const {
        SDL_Point p;
        p.x = rect_.x;
        p.y = rect_.y;
        return p;
    }
    int get_x() const {return rect_.x;}
    int get_y() const {return rect_.y;}
    void set_x(int x) {rect_.x = x;}
    void set_y(int y) {rect_.y = y;}
    
    SDL_Point get_size() const {SDL_Point size; 
        size.x = rect_.w; 
        size.y = rect_.h; 
        return size;
    }
    int get_width() const {return rect_.w;}
    int get_height() const {return rect_.h;}
    void set_width(int w){rect_.w = w;}
    void set_height(int h){rect_.h = h;}
    
    double get_scale() const {return scale_;}
    void set_scale(double factor){scale_ = factor;}
    
    double get_rotation() const {return rotation_;}
    void set_rotation(double angle){rotation_ = angle;}
    
    void set_filepath(string path){filepath_ = path;}
    void load_texture(SDL_Renderer* renderer, string path){
        if(renderer == (SDL_Renderer*)nullptr)
            throw GameObjectError();
        SDL_Surface* surface = IMG_Load(path.c_str());
        if(surface == (SDL_Surface*)nullptr)
            throw GameObjectError();
        filepath_ = path;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if(texture == (SDL_Texture*)nullptr)
            throw GameObjectError();
        if(texture_ != (SDL_Texture*)nullptr){
            SDL_DestroyTexture(texture_);
        }
        texture_ = texture;
    }
    
    bool colliding(GameObject& other)const{
        return (SDL_HasIntersection(&rect_, other.get_rectangle()));
    }
};

#endif
