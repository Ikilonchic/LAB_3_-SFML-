#pragma once

#ifndef ROUNDEDRECTANGLESHAPE_HPP
#define ROUNDEDRECTANGLESHAPE_HPP

#include "Settings.hpp"

//----------------------------------------------------------------------------------------------------
//                                     Rounded rectangle shape
//----------------------------------------------------------------------------------------------------

class RoundedRectangleShape : public sf::Shape
{
private:
    // Size //
    sf::Vector2f _size;
    // Radius //
    float _radius;
    // Count of points //
    unsigned int _count_point;

public:
    explicit RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0) {
        _size = size;
        _radius = radius;
        _count_point = cornerPointCount;
        update();
    }

    void setSize(const sf::Vector2f& size) {
        _size = size;
        update();
    }

    const sf::Vector2f& getSize() const {
        return _size;
    }

    void setCornersRadius(float radius) {
        _radius = radius;
        update();
    }

    float getCornersRadius() const {
        return _radius;
    }

    void setCornerPointCount(unsigned int count) {
        _count_point = count;
        update();
    }

    virtual std::size_t getPointCount() const {
        return _count_point * 4;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const {
        if (index >= _count_point * 4) {
            return sf::Vector2f(0, 0);
        }

        float deltaAngle = 90.0f / (_count_point - 1);
        sf::Vector2f center;
        unsigned int centerIndex = index / _count_point;
        static const float pi = 3.141592654f;

        switch (centerIndex) {
            case 0: center.x = _size.x - _radius; center.y = _radius; break;
            case 1: center.x = _radius; center.y = _radius; break;
            case 2: center.x = _radius; center.y = _size.y - _radius; break;
            case 3: center.x = _size.x - _radius; center.y = _size.y - _radius; break;
        }

        return sf::Vector2f(_radius * cos(deltaAngle * (index - centerIndex) * pi / 180) + center.x, -_radius * sin(deltaAngle * (index - centerIndex) * pi / 180) + center.y);
    }
};

#endif