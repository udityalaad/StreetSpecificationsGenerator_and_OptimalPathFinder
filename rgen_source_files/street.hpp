#pragma once

#include <string>
#include <vector>


// CLASS AND FUNCTION DECLARATIONS GO HERE

class Street {
    std::string name;
    std::vector<Node> coordinates;

    public:
        Street(std::string newName, std::vector<Node> newCoordinates);
        
        std::string getName();
        void setName(std::string newName);
        std::vector<Node> getCoordinates();
        void setCoordinates(std::vector<Node> newCoordinates);

        std::string toString();
        bool equals (Street street2);
};


// Function to check if 2 'Node Vectors' are equal
bool nodeVectorEquals (std::vector<Node> nodes1, std::vector<Node> nodes2);

