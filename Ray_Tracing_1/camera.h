//
//  camera.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/9/2.
//

#ifndef camera_h
#define camera_h

#include "color.h"
#include "material.h"

class camera {
public:
    int samples_per_pixel = 10;
    int max_depth = 10;
    double aspect_ratio = 1.0;
    double image_width = 100;
    
    void render(const hittable& world) {
        initialize();
        
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        
        for(int j=0; j<image_height; j++){
            std::clog << "\rScanlines remaining " << (image_height-j) << std::flush;
            for(int i=0; i<image_width; i++){
                color pixel_color(0, 0, 0);
                for(int sample = 0; sample<samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }

                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
        
        std::clog << "\rDone                   \n";
    }
    
private:
    int image_height;
    point3 camera_center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    
    void initialize() {
        // Calculate image height and make sure it is atleast 1
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = image_height < 1 ? 1 : image_height;
        
        // Camera
        camera_center = point3(0, 0, 0);
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
        
        // Viewport
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);
        
        auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;
        
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    
    ray get_ray(int i, int j) {
        auto pixel_center = pixel00_loc + (j*pixel_delta_v) + (i*pixel_delta_u);
        auto pixel_sample = pixel_center + pixel_sample_square();
        
        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }
    
    vec3 pixel_sample_square() {
        double px = -0.5 + random_double();
        double py = -0.5 + random_double();
        return pixel_delta_u * px + pixel_delta_v * py;
    }
    
    color ray_color(const ray& r, int depth, const hittable& world) {
        if(depth <= 0)
            return color(0, 0, 0);
        
        hit_record rec;
        if(world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth-1, world);
            return color(0, 0, 0);
        }
        
        auto unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};


#endif /* camera_h */
