#ifndef EX1_POINT_H
#define EX1_POINT_H

/**
 * class point.
 */

class Point {
private:
    int x, y;

public:
    Point() {};

    Point(int newX, int newY) : x(newX), y(newY) {};

    int getX();

    int getY();

    bool operator==(Point point);
};

#endif //EX1_POINT_H
