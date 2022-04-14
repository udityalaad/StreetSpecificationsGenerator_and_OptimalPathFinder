#pragma once

#include <string>
#include <vector>



/* ******************************************************************************** */
//          Functions to find different types of random data
/* ******************************************************************************** */
/* Function to convert Integers to Alphabets (Using ASCII Representation) */
std::string convertIntegersToAlphabets (int num);

/* Function to find a random number in the given range */
int findRandomNumber (int min, int max);

/* Function to find a random coordinate (+/-) in the given range [-k,k] */
int findRandomCoordindate (int k);

/* Function to find a random Alphabetical String */
std::string findRandomString ();
/* ******************************************************************************** */
/* ******************************************************************************** */





/* ******************************************************************************** */
//          Function to Check whether streetName already exists
/* ******************************************************************************** */
bool streetWithNameExists (std::vector<Street> streets, std::string newName);
/* ******************************************************************************** */
/* ******************************************************************************** */






/* ******************************************************************************** */
//          Functions to Check Overlap Between Line Segments
/* ******************************************************************************** */
/* Function to find distance between 2 nodes (Coordinates) */
float distanceBetweenNodes (Node node1, Node node2);

/* Function to check whether a Node lies on a given line */
bool nodeLiesOnLine (Node line_Src, Node line_Dest, Node checkNode);

/* Function to check only for cases where a node lies on the line
    and [(is not just a connecting point and its other node lies on the lines)]  */
bool overlapsAndNotJustConnect (Node line1_Src, Node line1_Dest, Node line2_checkPoint, Node line2_otherPoint);

/* Function to check whether the given lines (2) overlap at any point */
bool linesOverlap (Node line1_Src, Node line1_Dest, Node line2_Src, Node line2_Dest);

/* Function to check whether the new line segments overlap among themselves
    or overlap with any lineSegment of Other Streets (existing) */
bool overlapExists (std::vector<Street> streets, std::vector<Node> newCoords);
/* ******************************************************************************** */
/* ******************************************************************************** */





/* ******************************************************************************** */
/*      Function to check for existence of:
           i] a line segement between same node, i.e.: (a,b) -> (a,b)
           ii] a circular loop (between 2 line-endpoints) in the street */
/* ******************************************************************************** */
bool multipleNodeInstancesInStreet (std::vector<Node> coords);
/* ******************************************************************************** */
/* ******************************************************************************** */





/* ******************************************************************************** */
//                  Functions to Check for Intersections
/* ******************************************************************************** */
/* Function to check if intersection exists between 2 lines (using their Coordinates) */
bool intersectionExistsBetweenLines (Node line1_Src, Node line1_Dest, Node line2_Src, Node line2_Dest);

/* Function to check if intersection exists between 2 lines within a street (except for connecting points between lines) */
// i.e.: To check for circular loop within a street
bool intersectionExistsInStreet (std::vector<Node> coords);

/* Function to check if intersection exists between 2 lines on different streets */
// i.e.: To check whether it will lead to a non-empty graph
bool intersectionExistsBetweenStreets (std::vector<Street> streets);
/* ******************************************************************************** */
/* ******************************************************************************** */



