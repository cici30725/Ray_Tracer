//
//  material.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/9/2.
//

#ifndef material_h
#define material_h

#include "rtweekend.h"

class hit_record;

class material {
public:
    virtual ~material() = default;
    
    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian : public material {
public:
    lambertian(const color& a): albedo(a) {}
    
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.p + random_unit_vector();
        
        if(scatter_direction.near_zero())
            scatter_direction = rec.normal;
        
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        
        return true;
    }
    
private:
    color albedo;
};

class metal : public material {
public:
    metal(const color& a, double f): albedo(a), fuzz(f < 1 ? f : 1) {}
    
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        
        attenuation = albedo;
        scattered = ray(rec.p, reflected + fuzz*random_unit_vector());
        return dot(scattered.direction(), rec.normal) > 0;
    }
    
private:
    color albedo;
    double fuzz;
};

#endif /* material_h */
