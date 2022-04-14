#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "node.hpp"

Node :: Node (int newX, int newY) {
    x = newX;
    y = newY;
}


int Node :: getX()  {
    return x;
}

void Node :: setX(int newX)  {
    x = newX;
}


int Node :: getY()  {
    return y;
}

void Node :: setY(int newY)  {
    y = newY;
}



std::string Node :: toString() {
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

bool Node :: equals (Node node2) {
    return (x == node2.getX()   &&   y == node2.getY());
}