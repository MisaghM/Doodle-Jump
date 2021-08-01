#ifndef CALC_HPP_INCLUDE
#define CALC_HPP_INCLUDE

class Point;
class GameObject;

bool collided(const Point& mousePos, const GameObject* a);
bool collided(const GameObject* a, const GameObject* b);

#endif //CALC_HPP_INCLUDE