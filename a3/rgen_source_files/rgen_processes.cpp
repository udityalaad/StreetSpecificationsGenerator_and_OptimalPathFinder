#include <iostream>
#include <sstream>
#include <vector>

#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

#include <unistd.h>
// #include <sys/wait.h>

#include "node.hpp"
#include "street.hpp"
#include "rgen_processes.hpp"



/* ******************************************************************************** */
//          Functions to find different types of random data
/* ******************************************************************************** */
/* Function to convert Integers to Alphabets (Using ASCII Representation) */
std::string convertIntegersToAlphabets (int num) {
    std::string result = "";

    while (num != 0) {
        int curr = num % 100;

        if ((curr % 26) != 0) {
            char c = char(('A' - 1) + (curr % 26));
            result = c + result;
        }
        
        num = num / 100;
    }

    return result;
}



/* Function to find a random number in the given range */
int findRandomNumber (int min, int max) {
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::string errorMessage = "Cannot open /dev/urandom";
        throw errorMessage;
    }

    // read a random 8-bit value.
    // Have to use read() method for low-level reading
    char ch = 'a';

    urandom.read(&ch, 1);
    int temp = std::abs((int) ch);
    int randomNumber = temp % max;

    while (randomNumber < min) {
        randomNumber++;
    }
    while (randomNumber > max) {
        randomNumber--;
    }

    urandom.close();
    return randomNumber;
}



/* Function to find a random coordinate (+/-) in the given range [-k,k] */
int findRandomCoordindate (int k) {
    int num = findRandomNumber(0, k);
    int signDecider = findRandomNumber(0, 10);

    int finalVal = num;
    if (signDecider % 2 != 0) {
        finalVal = -num;
    }

    return finalVal;
}



/* Function to find a random Alphabetical String */
std::string findRandomString () {
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::string errorMessage = "Cannot open /dev/urandom";
        throw errorMessage;
    }

    // read a random integer
    // Have to use read() method for low-level reading
    int num = 2421;

    urandom.read((char *) &num, sizeof(int));
    int randomNumber = std::abs(num);

    std::string result = convertIntegersToAlphabets((int)randomNumber);

    urandom.close();
    return result;
}
/* ******************************************************************************** */
/* ******************************************************************************** */





/* ******************************************************************************** */
//          Function to Check whether streetName already exists
/* ******************************************************************************** */
bool streetWithNameExists (std::vector<Street> streets, std::string newName) {
    for (int i = 0; i < ((int) streets.size()); i++) {
        if (streets.at(i).getName() == newName) {
            return true;
        }
    }

    return false;
}
/* ******************************************************************************** */
/* ******************************************************************************** */






/* ******************************************************************************** */
//          Functions to Check Overlap Between Line Segments
/* ******************************************************************************** */
/* Function to find distance between 2 nodes (Coordinates) */
float distanceBetweenNodes (Node node1, Node node2) {
    // Using Pythagoras Theorem
    float horDist = ((float) node2.getX()) - ((float) node1.getX());
    float vertDist = ((float) node2.getY()) - ((float) node1.getY());

    float result = std::sqrt((horDist * horDist)  +  (vertDist * vertDist));

    return result;
}



/* Function to check whether a Node lies on a given line */
bool nodeLiesOnLine (Node line_Src, Node line_Dest, Node checkNode) {    
    if (distanceBetweenNodes(line_Src, line_Dest)  ==  (distanceBetweenNodes(line_Src, checkNode) + distanceBetweenNodes(checkNode, line_Dest))) {
        return true;
    }

    return false;
}

/* Function to check only for cases where a node lies on the line
    and [(is not just a connecting point and its other node lies on the lines)]  */
bool overlapsAndNotJustConnect (Node line1_Src, Node line1_Dest, Node line2_checkPoint, Node line2_otherPoint) {
    if (nodeLiesOnLine(line1_Src, line1_Dest, line2_checkPoint)) {                                                  // if line2_checkPoint lies on line1
        if ((line2_checkPoint.getX() == line1_Src.getX()  &&  line2_checkPoint.getY() == line1_Src.getY())
               ||  (line2_checkPoint.getX() == line1_Dest.getX()  &&  line2_checkPoint.getY() == line1_Dest.getY())) {   // 1] if line2_checkPoint is a connecting point
            if (nodeLiesOnLine(line1_Src, line1_Dest, line2_otherPoint)) {                                              // and line2_otherPoint lies on line1 
                return true;                                                                                            // THEN: overlaps
            }
        } else {                                                                                                        // 2] else if line2_checkPoint is not a connecting point
            return true;                                                                                                // THEN: overlaps
        }
    }

    return false;
}


/* Function to check whether the given lines (2) overlap at any point */
bool linesOverlap (Node line1_Src, Node line1_Dest, Node line2_Src, Node line2_Dest) {
    // slope = infinity (N.D.)  =>  Vertical line 
    if ((line1_Src.getX() - line1_Dest.getX())  ==  0
            &&  (line2_Src.getX() - line2_Dest.getX()) == 0) {      // Both are vertical lines
        if (line1_Src.getX() == line2_Src.getX()) {         // + Both have same x-coordinate (=> Same vertical path - But, may or may not be overlapping)
            if (overlapsAndNotJustConnect(line1_Src, line1_Dest, line2_Src, line2_Dest)
                || overlapsAndNotJustConnect(line1_Src, line1_Dest, line2_Dest, line2_Src)
                || overlapsAndNotJustConnect(line2_Src, line2_Dest, line1_Src, line1_Dest)
                || overlapsAndNotJustConnect(line2_Src, line2_Dest, line1_Dest, line1_Src)) {
                    return true;
            }
        } else {
            return false;
        }
    } else if ((line1_Src.getX() - line1_Dest.getX())  ==  0
        ||  (line2_Src.getX() - line2_Dest.getX()) == 0) {      // Any one is a vertical line
            return false;
    }

    float slope1 = ((float) line1_Src.getY() - (float) line1_Dest.getY())   /   (float) (line1_Src.getX() - (float) line1_Dest.getX());
    float slope2 = ((float) line2_Src.getY() - (float) line2_Dest.getY())   /   ((float) line2_Src.getX() - (float) line2_Dest.getX());

    if (slope1 == slope2) {
        if (overlapsAndNotJustConnect(line1_Src, line1_Dest, line2_Src, line2_Dest)
            || overlapsAndNotJustConnect(line1_Src, line1_Dest, line2_Dest, line2_Src)
            || overlapsAndNotJustConnect(line2_Src, line2_Dest, line1_Src, line1_Dest)
            || overlapsAndNotJustConnect(line2_Src, line2_Dest, line1_Dest, line1_Src)) {
                return true;
        }
    }

    return false;
}



/* Function to check whether the new line segments overlap among themselves
    or overlap with any lineSegment of Other Streets (existing) */
bool overlapExists (std::vector<Street> streets, std::vector<Node> newCoords) {
    // Checking among nodes in the new set
    for (int i = 0; i < ((int) newCoords.size()) - 1; i++) {
        for (int j = 0; j < ((int) newCoords.size()) - 1; j++) {
            if (i == j) {
                continue;
            }

            if (linesOverlap (newCoords.at(i), newCoords.at(i + 1), newCoords.at(j), newCoords.at(j + 1))) {
                return true;
            }
        }
    }


    // Check with already added (and existing) streets
    for (int streetNo = 0; streetNo < ((int) streets.size()); streetNo++) {
        std::vector<Node> streetCoords = streets.at(streetNo).getCoordinates();

        for (int i = 0; i < ((int) streetCoords.size()) - 1; i++) {
            for (int j = 0; j < ((int) newCoords.size()) - 1; j++) {
                if (linesOverlap (streetCoords.at(i), streetCoords.at(i + 1), newCoords.at(j), newCoords.at(j + 1))) {
                    return true;
                }
            }
        }
    }

    return false;
}
/* ******************************************************************************** */
/* ******************************************************************************** */





/* ******************************************************************************** */
/*      Function to check for existence of:
           i] a line segement between same node, i.e.: (a,b) -> (a,b)
           ii] a circular loop (between 2 line-endpoints) in the street */
/* ******************************************************************************** */
bool multipleNodeInstancesInStreet (std::vector<Node> coords) {
    for (int i = 0; i < ((int) coords.size()); i++) {
        for (int j = 0; j < ((int) coords.size()); j++) {
            if (i == j) {
                continue;
            }

            Node node1 = coords.at(i);
            Node node2 = coords.at(j);

            if (node1.getX() == node2.getX()  &&  node1.getY() == node2.getY()) {
                return true;
            }
        }
    }

    return false;

}
/* ******************************************************************************** */
/* ******************************************************************************** */



/* ******************************************************************************** */
//                  Functions to Check for Intersections
/* ******************************************************************************** */
/* Function to check if intersection exists between 2 lines (using their Coordinates) */
bool intersectionExistsBetweenLines (Node line1_Src, Node line1_Dest, Node line2_Src, Node line2_Dest) {
    float x1 = (float) line1_Src.getX();
    float y1 = (float) line1_Src.getY();
    
    float x2 = (float) line1_Dest.getX();
    float y2 = (float) line1_Dest.getY();

    float x3 = (float) line2_Src.getX();
    float y3 = (float) line2_Src.getY();

    float x4 = (float) line2_Dest.getX();
    float y4 = (float) line2_Dest.getY();

    
    float xNum = ((x1*y2 - y1*x2) * (x3 - x4))  -  ((x1 - x2) * (x3*y4 - y3*x4));
    float xDen = ((x1 - x2) * (y3 - y4))  -  ((y1 - y2) * (x3 - x4));
    
    // Intersection point = Infinity
    if (xDen == 0) {
        return false;
    }
        
    
    float yNum = ((x1*y2 - y1*x2) * (y3 - y4))  - ((y1 - y2) * (x3*y4 - y3*x4));
    // yDen is same as xDen
    float yDen = ((x1 - x2) * (y3 - y4))  -  ((y1 - y2) * (x3 - x4));
    
    float x = xNum / xDen;
    float y = yNum / yDen;
    
    // // *********************************
    // // Do not consider the intersection, when intersection point is equal to one of the end points
    // // Usefull when comparing lines on the same street
    // // if not((x >= std::min(x1, x2) and x <= std::max(x1, x2))  and  (y >= std::min(y1, y2) and y <= std::max(y1, y2))  and  (x >= std::min(x3, x4) and x <= std::max(x3, x4))  and  (y >= std::min(y3, y4) and  y <= std::max(y3, y4)))      or    (((x == x1 and y == y1) and (x == x3 and y == y3))  or  ((x == x1 and y == y1)  and  (x == x4 and y == y4))  or  ((x == x2 and y == y2) and (x == x3 and y == y3))  or  ((x == x2 and y == y2)  and  (x == x4 and y == y4))):
    // //	return None, None
    
    // // Consider the intersection, when intersection point is equal to one of the end points
    // // Usefull when not comparing lines on the same street
    // if not((x >= std::min(x1, x2) and x <= std::max(x1, x2))  and  (y >= std::min(y1, y2) and y <= std::max(y1, y2))  and  (x >= std::min(x3, x4) and x <= std::max(x3, x4))  and  (y >= std::min(y3, y4) and  y <= std::max(y3, y4))):
    // 	return None, None
    // // *************************************

    // If the intersection point lies on both lines, only then - it is an intersection point between the 2 lines
    if (((x >= std::min(x1, x2) and x <= std::max(x1, x2))  and  (y >= std::min(y1, y2) and y <= std::max(y1, y2))  and  (x >= std::min(x3, x4) and x <= std::max(x3, x4))  and  (y >= std::min(y3, y4) and  y <= std::max(y3, y4)))) {
        return true;
    } else {
        return false;
    }
}

/* Function to check if intersection exists between 2 lines within a street (except for connecting points between lines) */
// i.e.: To check for circular loop within a street
bool intersectionExistsInStreet (std::vector<Node> coords) {
    for (int i = 0; i < ((int) coords.size()) - 1; i++) {
        for (int j = 0; j < ((int) coords.size()) - 1; j++) {
            if ((j == i)  ||  (j == i - 1)  ||  (j == i + 1)) {
                continue;
            }

            if (intersectionExistsBetweenLines(coords.at(i), coords.at(i+1), coords.at(j), coords.at(j+1))) {
                return true;
            }
        }
    }

    return false;
}


/* Function to check if intersection exists between 2 lines on different streets */
// i.e.: To check whether it will lead to a non-empty graph
bool intersectionExistsBetweenStreets (std::vector<Street> streets) {
    for (int i = 0; i < ((int) streets.size()); i++) {
        for (int j = 0; j < ((int) streets.size()); j++) {
            if (i == j) {
                continue;
            }

            std::vector<Node> scI = streets.at(i).getCoordinates();
            std::vector<Node> scJ = streets.at(j).getCoordinates();
            
            for (int m = 0; m < ((int) scI.size()) - 1; m++) {
                for (int n = 0; n < ((int) scJ.size()) - 1; n++) {
                    if (intersectionExistsBetweenLines(scI.at(m), scI.at(m+1), scJ.at(n), scJ.at(n+1))) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
/* ******************************************************************************** */
/* ******************************************************************************** */