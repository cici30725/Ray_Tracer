//
//  color.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/8/31.
//

#ifndef color_h
#define color_h

#include "vec3.h"

using color = vec3;

inline double linear_to_gamma(double linear_component) {
    return sqrt(linear_component);
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel){
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();
    
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;
    
    // Apply the linear to gamma transform.
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    
    // Write the color in [0, 255] range
    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif /* color_h */
