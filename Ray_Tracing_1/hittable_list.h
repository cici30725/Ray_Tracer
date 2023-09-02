//
//  hittable_list.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/9/1.
//

#ifndef hittable_list_h
#define hittable_list_h

#include "hittable.h"

#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects;
    
    hittable_list() {}
    hittable_list(shared_ptr<hittable> obj) { add(obj); }
    
    void add(shared_ptr<hittable> obj) {
        objects.push_back(obj);
    }
    
    void clear() {
        objects.clear();
    }
    
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record tmp_rec;
        bool hit_anything = false;
        double closest_so_far = ray_t.max;
        
        for(const auto& obj : objects) {
            if(obj->hit(r, interval(ray_t.min, closest_so_far), tmp_rec)) {
                hit_anything = true;
                closest_so_far = tmp_rec.t;
                rec = tmp_rec;
            }
        }
        
        return hit_anything;
    }
    
};

#endif /* hittable_list_h */
