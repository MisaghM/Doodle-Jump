#ifndef RECTANGLE_F_HPP_INCLUDE
#define RECTANGLE_F_HPP_INCLUDE

#include "point_f.hpp"

struct RectangleF {
    RectangleF(float x_, float y_, float w_, float h_)
        : x(x_),
          y(y_),
          w(w_),
          h(h_) {}
    RectangleF(PointF xy_, float w_, float h_)
        : x(xy_.x),
          y(xy_.y),
          w(w_),
          h(h_) {}
    float x, y, w, h;
};

#endif //RECTANGLE_F_HPP_INCLUDE