//
//  sphere.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/9/1.
//

#ifndef sphere_h
#define sphere_h

#include "hittable.h"

class sphere: public hittable {
public:
    sphere(point3 _center, double _radius, shared_ptr<material> _material): center(_center), radius(_radius), mat(_material) {}
    
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto a = r.direction().length_squared();
        vec3 oc = r.origin() - center;
        auto half_b = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        
        auto determinant = half_b*half_b - a*c;
        if(determinant < 0) return false;
        auto sqrtd = sqrt(determinant);

        auto root = (-half_b - sqrtd)/ a;
        if(!ray_t.surrounds(root)) {
            root = (-half_b + sqrtd)/ a;
            if(!ray_t.surrounds(root))
                return false;
        }
        
        rec.t = root;
        rec.p = r.at(root);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        
        return true;
    }
    
private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif /* sphere_h */
