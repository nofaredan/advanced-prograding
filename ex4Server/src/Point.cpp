#include "Point.h"

/**
 * get x.
 * @return x.
 */
int Point::getX(){
    return x;
}

/**
 * get y.
 * @return y.
 */
int Point::getY(){
    return y;
}

/**
* Operator to compare between points.
**/
bool Point::operator==(Point point) {
    return (x==point.getX() && y  == point.getY());
}


