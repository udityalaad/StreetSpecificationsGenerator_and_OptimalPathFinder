#pragma once

#include <string>
#include <vector>


// CLASS AND FUNCTION DECLARATIONS GO HERE

class Node {
    int x;
    int y;

    public:
        Node(int newX, int newY);
        
        int getX();
        void setX(int newX);
        int getY();
        void setY(int newY);

        std::string toString();
        bool equals (Node node2);
};