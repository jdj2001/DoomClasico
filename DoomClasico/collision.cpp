#include "collision.h"
#include <cmath>

bool checkCollision(float x1, float y1, float x2, float y2, float radius) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < radius;
}