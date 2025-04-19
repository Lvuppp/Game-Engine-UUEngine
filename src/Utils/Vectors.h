#pragma once

#include <QSize>

struct sVec2
{
    sVec2() = default;
    explicit sVec2(const QSize& size)
        : x(size.width())
        , y(size.height())
        {}

    sVec2(float x, float y)
        : x(x)
        , y(y)
        {}

    static const sVec2 One;
    static const sVec2 Zero;

    float x = 0.0f;
    float y = 0.0f;
};
