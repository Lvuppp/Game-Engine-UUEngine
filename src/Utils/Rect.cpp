#include "Rect.h"

cRect::cRect(float x, float y, const sVec2& size)
    : x1(x)
    , y1(y)
    , x2(x + size.x)
    , y2(y + size.y)
{
}

cRect::cRect(const sVec2& position, const sVec2& size)
    : x1(position.x)
    , y1(position.y)
    , x2(position.x + size.x)
    , y2(position.y + size.y)
{
}

cRect::cRect(float x1, float y1, float x2, float y2)
    : x1(x1)
    , x2(x2)
    , y1(y1)
    , y2(y2)
{
}

void cRect::setPosition(const sVec2& pos)
{
    sVec2 size = getSize();
    x1 = pos.x;
    y1 = pos.y;
    x2 = x1 + size.x;
    y2 = y1 + size.y;
}

void cRect::setSize(const sVec2& size)
{
    x2 = x1 + size.x;
    y2 = y1 + size.y;
}

sVec2 cRect::getPosition() const
{
    return sVec2(x1, y1);
}

sVec2 cRect::getSize() const
{
    return sVec2(x2 - x1, y2 - y1);
}

bool cRect::contains(const sVec2& point) const
{
    return point.x >= x1 && point.x <= x2 &&
           point.y >= y1 && point.y <= y2;
}

bool cRect::intersects(const cRect& other) const
{
    return !(other.x2 < x1 || other.x1 > x2 ||
             other.y2 < y1 || other.y1 > y2);
}

void cRect::move(const sVec2& delta)
{
    x1 += delta.x;
    y1 += delta.y;
    x2 += delta.x;
    y2 += delta.y;
}
