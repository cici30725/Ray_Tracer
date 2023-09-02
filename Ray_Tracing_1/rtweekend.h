//
//  rtweekend.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/9/1.
//

#ifndef rtweekend_h
#define rtweekend_h

#include <cmath>
#include <memory>
#include <limits>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double random_double() {
    // Return number between [0, 1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + random_double() * (max-min);
}

// Common Headers

#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif /* rtweekend_h */
