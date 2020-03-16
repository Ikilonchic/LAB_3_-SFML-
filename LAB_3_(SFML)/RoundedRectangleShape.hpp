#pragma once

#ifndef ROUNDEDRECTANGLESHAPE_HPP
#define ROUNDEDRECTANGLESHAPE_HPP

#include "Settings.hpp"

class RoundedRectangleShape : public sf::Shape
{
private:
    sf::Vector2f mySize;
    float myRadius;
    unsigned int myCornerPointCount;

public:
    explicit RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0)
    {
        mySize = size;
        myRadius = radius;
        myCornerPointCount = cornerPointCount;
        update();
    }

    void setSize(const sf::Vector2f& size)
    {
        mySize = size;
        update();
    }

    const sf::Vector2f& getSize() const
    {
        return mySize;
    }

    void setCornersRadius(float radius)
    {
        myRadius = radius;
        update();
    }

    float getCornersRadius() const
    {
        return myRadius;
    }

    void setCornerPointCount(unsigned int count)
    {
        myCornerPointCount = count;
        update();
    }

    virtual std::size_t getPointCount() const
    {
        return myCornerPointCount * 4;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        if (index >= myCornerPointCount * 4)
        {
            return sf::Vector2f(0, 0);
        }

        float deltaAngle = 90.0f / (myCornerPointCount - 1);
        sf::Vector2f center;
        unsigned int centerIndex = index / myCornerPointCount;
        static const float pi = 3.141592654f;

        switch (centerIndex)
        {
            case 0: center.x = mySize.x - myRadius; center.y = myRadius; break;
            case 1: center.x = myRadius; center.y = myRadius; break;
            case 2: center.x = myRadius; center.y = mySize.y - myRadius; break;
            case 3: center.x = mySize.x - myRadius; center.y = mySize.y - myRadius; break;
        }

        return sf::Vector2f(myRadius * cos(deltaAngle * (index - centerIndex) * pi / 180) + center.x, -myRadius * sin(deltaAngle * (index - centerIndex) * pi / 180) + center.y);
    }
};

#endif