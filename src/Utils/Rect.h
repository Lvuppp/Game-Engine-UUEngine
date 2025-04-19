#pragma once
#include "Vectors.h"

struct cRect
{
    cRect() = default;
    cRect(float x, float y, const sVec2& size);
    cRect(const sVec2& position, const sVec2& size);
    cRect(float x1, float y1, float x2, float y2);

    void setPosition(const sVec2& pos);
    void setSize(const sVec2& size);

    sVec2 getPosition() const;
    sVec2 getSize() const;

    bool contains(const sVec2& point) const;
    bool intersects(const cRect& other) const;
    void move(const sVec2& delta);

    float x1 = 0.0f;
    float y1 = 0.0f;
    float x2 = 0.0f;
    float y2 = 0.0f;
};
