#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include <utility>
#include "Texture.h"
#include <cmath>

class Sprite {
public:
    Sprite(std::shared_ptr<Texture> texture, int x, int y)
            : texture(std::move(texture)), x(x), y(y) {}

    void Draw(int offsetX = 0);

    void Move(int addX, int addY) {
        x += addX;
        y += addY;
    }

    int x;
    int y;

    int GetWidth() { return texture->width; }

    int GetHeight() { return texture->height; }

    float DistanceTo(const std::shared_ptr<Sprite> &other, float xOffset) const {
        float distanceX = abs((float) x + xOffset - static_cast<float>(other->x));
        float distanceY = abs((float) y - static_cast<float>(other->y));
        return sqrt(distanceX * distanceX + distanceY * distanceY);
    }

private:
    std::shared_ptr<Texture> texture;
};

#endif