//
//  interval.h
//  Ray_Tracing_1
//
//  Created by 許熙康 on 2023/9/2.
//

#ifndef interval_h
#define interval_h

class interval {
public:
    double min, max;
    
    interval(): min(-infinity), max(+infinity) {}
    interval(double _min, double _max): min(_min), max(_max) {}
    
    bool contains(double x) {
        return min <= x && x <= max;
    }
    
    bool surrounds(double x) {
        return min < x && x < max;
    }
    
    double clamp(double x) const {
        if(x > max)
            return max;
        if(x < min)
            return min;
        return x;
    }
    
    static const interval empty, universe;
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);


#endif /* interval_h */
