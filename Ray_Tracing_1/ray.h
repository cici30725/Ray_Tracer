//
//  ray.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/8/31.
//

#ifndef ray_h
#define ray_h

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const point3 &origin, const vec3 &direction): orig(origin), dir(direction) {}
    
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    
    point3 at(double t) const {
        return orig + t*dir;
    }
    
private:
    point3 orig;
    vec3 dir;
};

#endif /* ray_h */
