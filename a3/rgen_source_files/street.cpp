#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>


#include "node.hpp"
#include "street.hpp"


Street :: Street (std::string newName, std::vector<Node> newCoordinates) {
    name = newName;
    coordinates = newCoordinates;
}


std::string Street :: getName()  {
    return name;
}

void Street :: setName(std::string newName) {
    name = newName;
}


std::vector<Node> Street :: getCoordinates() {
    return coordinates;
}

void Street :: setCoordinates(std::vector<Node> newCoordinates) {
    coordinates = newCoordinates;
}



std::string Street :: toString() {
    std::string result = "\"" + name + "\" ";
    
    for (int i = 0; i < ((int) coordinates.size()); i++) {
        if (i != 0) {
            result += " ";
        }

        result += coordinates.at(i).toString();
    }

    return result;
}

bool Street :: equals (Street street2) {
    return (name == street2.getName()   &&   nodeVectorEquals(coordinates, street2.getCoordinates()));
}




// Function to check if 2 'Node Vectors' are equal
bool nodeVectorEquals (std::vector<Node> nodes1, std::vector<Node> nodes2) {
    if (nodes1.size() != nodes2.size()) {
        return false;
    }

    for (int i =0; i < ((int) nodes1.size()); i++) {
        if (!nodes1.at(i).equals(nodes2.at(i))) {
            return false;
        }
    }

    return true;
}