#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "GameObject.hpp"

class Physics{
    static constexpr double gravity_ = 9.8f;
public:
    static void apply_gravity(GameObject& obj){
        obj.set_y(obj.get_y() + gravity_);
    }
};

#endif
