/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <cctype>

#include "rgen_source_files/node.hpp"
#include "rgen_source_files/street.hpp"
#include "rgen_source_files/rgen_processes.hpp"




TEST_CASE("findRandomNumber - Success") {
    int iterations = 10;
    std::vector<std::vector<int>> ranges;

    // Default Ranges
    ranges.push_back(std::vector<int>{2,10});
    ranges.push_back(std::vector<int>{1,5});
    ranges.push_back(std::vector<int>{5,5});
    ranges.push_back(std::vector<int>{0,20});


    // Range = 0
    ranges.push_back(std::vector<int>{2,2});
    ranges.push_back(std::vector<int>{1,1});
    ranges.push_back(std::vector<int>{5,5});
    ranges.push_back(std::vector<int>{10,10});
    ranges.push_back(std::vector<int>{20,20});

    // Range = 1
    ranges.push_back(std::vector<int>{2,3});
    ranges.push_back(std::vector<int>{1,6});
    ranges.push_back(std::vector<int>{5,6});
    ranges.push_back(std::vector<int>{1,21});


    // Changed Defaults to Boundary Points - 1 (Increased)
    ranges.push_back(std::vector<int>{2,11});
    ranges.push_back(std::vector<int>{1,6});
    ranges.push_back(std::vector<int>{5,6});
    ranges.push_back(std::vector<int>{0,21});

    // Changed Defaults to Boundary Points - 1 (Decreased)
    ranges.push_back(std::vector<int>{2,9});
    ranges.push_back(std::vector<int>{1,4});
    ranges.push_back(std::vector<int>{5,5});    // No scope to descrese
    ranges.push_back(std::vector<int>{0,19});


    // Changed Defaults to Wayword point - 1 (Increased)
    ranges.push_back(std::vector<int>{2,72});
    ranges.push_back(std::vector<int>{1,31});
    ranges.push_back(std::vector<int>{5,42});
    ranges.push_back(std::vector<int>{0,125});

    // Changed Defaults to Wayword point - 2 (Decreased)
    ranges.push_back(std::vector<int>{2,7});
    ranges.push_back(std::vector<int>{1,3});
    ranges.push_back(std::vector<int>{5,5});   // No scope to descrese
    ranges.push_back(std::vector<int>{0,14});


    // Changed Min and Max to Wayword points - 1
    ranges.push_back(std::vector<int>{15,288});
    ranges.push_back(std::vector<int>{67,124});
    ranges.push_back(std::vector<int>{39,75});
    ranges.push_back(std::vector<int>{0,112});

    // Changed Min and Max to Wayword points - 2
    ranges.push_back(std::vector<int>{117,2888});
    ranges.push_back(std::vector<int>{617,1224});
    ranges.push_back(std::vector<int>{379,7335});
    ranges.push_back(std::vector<int>{0,11442});

    // Test each case in vector
    for (int caseNo = 0; caseNo < ((int) ranges.size()); caseNo++) {
        int min = ranges.at(caseNo).at(0);
        int max = ranges.at(caseNo).at(1);

        // Finding 'n'( = iterations) random numbers from min to max
        for (int i = 0; i < iterations; i++) {
            int randomNumber = findRandomNumber(min, max);
            
            bool testResult = (randomNumber >= min)   &&   (randomNumber <= max);
            CHECK(testResult);
        }
    }
}



TEST_CASE("findRandomCoordindate - Success") {
    int iterations = 10;
    std::vector<int> ranges;

    ranges.push_back(20);   // Default
    ranges.push_back(19);   // Default - 1
    ranges.push_back(19);   // Default + 1

    ranges.push_back(1);    // Min Required
    ranges.push_back(2);   // MinRequired + 1
    
    ranges.push_back(15);
    ranges.push_back(35);
    ranges.push_back(100);
    ranges.push_back(37);
    ranges.push_back(83);

    // Test each case in vector
    for (int caseNo = 0; caseNo < ((int) ranges.size()); caseNo++) {
        int k = ranges.at(caseNo);

        // Finding 'n'( = iterations) random coordinate values (+/-) from -k to k
        for (int i = 0; i < iterations; i++) {
            int randomCoordinateValue = findRandomCoordindate(k);
            
            bool testResult = (randomCoordinateValue >= -k)   &&   (randomCoordinateValue <= k);
            CHECK(testResult);
        }
    }
}



TEST_CASE("findRandomString - Success") {
    int totalCases = 100;

    for (int caseNo = 0; caseNo < totalCases; caseNo++) {
        bool validString = true;

        std::string randomString = findRandomString();

        for (int i = 0; i < ((int) randomString.size()); i++) {
            if (!std::isalpha(randomString[i])) {
                validString = false;
                break;
            }
        }

        CHECK(validString);
    }
}





TEST_CASE("multipleNodeInstancesInStreet, intersectionExistsInStreet, overlapExists - false (Success)   +   intersectionExistsBetweenStreets - true (Success)") {
    std::vector<Street> streets;
    std::vector<Node> newCoords;

    // ---------------------------------------------------
    // ------------------- Example 1 ---------------------
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(3, 8));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(4, 2));
    newCoords.push_back(Node(4, 8));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(1, 4));
    newCoords.push_back(Node(5, 8));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Davenport Road", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 2 ---------------------
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(-2, 2));
    newCoords.push_back(Node(1, 0));
    newCoords.push_back(Node(1, -3));
    newCoords.push_back(Node(-3, -3));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(1, -1));
    newCoords.push_back(Node(4, -1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(7, 5));
    newCoords.push_back(Node(1, 3));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(2, 6));
    newCoords.push_back(Node(5, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Davenport Road", newCoords));


    // Street 4
    newCoords.clear();
    newCoords.push_back(Node(1, -3));
    newCoords.push_back(Node(6, -6));
    newCoords.push_back(Node(6, -3));
    newCoords.push_back(Node(4, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Fourth Road", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 3 ---------------------
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(8, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(6, 2));
    newCoords.push_back(Node(8, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 4 ---------------------
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(9, 0));
    newCoords.push_back(Node(12, -2));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 5 ---------------------
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(3, 3));
    newCoords.push_back(Node(4, 0));
    newCoords.push_back(Node(4, -3));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(8, 4));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Davenport Road", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 6 ---------------------
    //  Streets with vertical and horizontal lines
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(3, 3));
    newCoords.push_back(Node(4, 0));
    newCoords.push_back(Node(4, -3));
    newCoords.push_back(Node(-2, -3));
    newCoords.push_back(Node(-2, -6));
    newCoords.push_back(Node(4, -6));
    newCoords.push_back(Node(4, -4));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-2, -1));
    newCoords.push_back(Node(-8, -1));
    newCoords.push_back(Node(-8, 6));
    newCoords.push_back(Node(-5, 6));
    newCoords.push_back(Node(-4, 7));
    newCoords.push_back(Node(-4, 13));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Davenport Road", newCoords));

    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(8, 4));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 7 ---------------------
    //      Streets with connecting end-points
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(3, 3));
    newCoords.push_back(Node(4, 0));
    newCoords.push_back(Node(4, -3));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(8, 4));
    newCoords.push_back(Node(4, -3));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(0, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Davenport Road", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 8 ---------------------
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(5,1));
    newCoords.push_back(Node(2,2));
    newCoords.push_back(Node(9,6));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Street One", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(9,12));
    newCoords.push_back(Node(6,8));
    newCoords.push_back(Node(5,8));
    newCoords.push_back(Node(14,20));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Street Two", newCoords));

    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(3,4));
    newCoords.push_back(Node(3,3));
    newCoords.push_back(Node(3,2));
    newCoords.push_back(Node(3,1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Street Three", newCoords));


    // Street 4
    newCoords.clear();
    newCoords.push_back(Node(2,4));
    newCoords.push_back(Node(2,9));
    newCoords.push_back(Node(11,4));
    newCoords.push_back(Node(11,1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Street Four", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // // ---------------------------------------------------
    // // ------------------- Example Template ---------------------
    // // ---------------------------------------------------
    // streets.clear();

    // // Street 1
    // newCoords.clear();
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());

    // CHECK(!multipleNodeInstancesInStreet(newCoords));
    // CHECK(!intersectionExistsInStreet(newCoords));
    // CHECK(!overlapExists(streets, newCoords));
    // streets.push_back(Street("", newCoords));

    // // Street 2
    // newCoords.clear();
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());

    // CHECK(!multipleNodeInstancesInStreet(newCoords));
    // CHECK(!intersectionExistsInStreet(newCoords));
    // CHECK(!overlapExists(streets, newCoords));
    // streets.push_back(Street("", newCoords));

    // // Street 3
    // newCoords.clear();
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());

    // CHECK(!multipleNodeInstancesInStreet(newCoords));
    // CHECK(!intersectionExistsInStreet(newCoords));
    // CHECK(!overlapExists(streets, newCoords));
    // streets.push_back(Street("", newCoords));


    // // Street 4
    // newCoords.clear();
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());
    // newCoords.push_back(Node());

    // CHECK(!multipleNodeInstancesInStreet(newCoords));
    // CHECK(!intersectionExistsInStreet(newCoords));
    // CHECK(!overlapExists(streets, newCoords));
    // streets.push_back(Street("", newCoords));
    // // ---------------------------------------------------
    // // ---------------------------------------------------
}









TEST_CASE("multipleNodeInstancesInStreet - true (Failure)") {
    std::vector<Node> newCoords;

    // ---------------------------------------------------
    // ------------------- true (Failures) ---------------------
    // a line segement between same node, i.e.: (a,b) -> (a,b)
    // ---------------------------------------------------

    // true (Failure) - a line segement between same node, i.e.: (a,b) -> (a,b)
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(3, 8));
    CHECK(multipleNodeInstancesInStreet(newCoords));

    // true (Failure) - a line segement between same node, i.e.: (a,b) -> (a,b)
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(3, 8));
    CHECK(multipleNodeInstancesInStreet(newCoords));

    // true (Failure) - a line segement between same node, i.e.: (a,b) -> (a,b)
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(3, 8));
    newCoords.push_back(Node(3, 8));
    CHECK(multipleNodeInstancesInStreet(newCoords));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- true (Failures) ---------------------
    // a circular loop in the street
    // ---------------------------------------------------

    // true (Failure) - a circular loop in the street
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(3, 8));
    newCoords.push_back(Node(2, -1));
    CHECK(multipleNodeInstancesInStreet(newCoords));

    // true (Failure) - a circular loop in the street
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(3, 8));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(3, 8));
    CHECK(multipleNodeInstancesInStreet(newCoords));

    // true (Failure) - a circular loop in the street
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(3, 8));
    CHECK(multipleNodeInstancesInStreet(newCoords));


    // true (Failure) - a circular loop in the street
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(5, 6));
    newCoords.push_back(Node(5, 5));
    newCoords.push_back(Node(3, 8));
    CHECK(multipleNodeInstancesInStreet(newCoords));
}






TEST_CASE("intersectionExistsInStreet - true (Failure)") {
    std::vector<Node> newCoords;

    // ---------------------------------------------------
    // ------------------- true (Failures) ---------------------
    //      - 1st line intersects with other lines
    // ---------------------------------------------------

    // true (Failure) - 1st line intersect with 3rd line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, -1));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-5, -3));
    newCoords.push_back(Node(2, -4));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - 1st line intersect with any line in the middle
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-5, -3));
    newCoords.push_back(Node(2, -4));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - 1st line intersect with last line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(-3, 5));
    CHECK(intersectionExistsInStreet(newCoords));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- true (Failures) ---------------------
    //      - Last line intersects with other lines
    // ---------------------------------------------------

    // true (Failure) - Last line intersect with 3rd last line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(2, -4));
    newCoords.push_back(Node(-5, 0));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - Last line intersect with any line in the middle
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-3, 0));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(2, -4));
    newCoords.push_back(Node(-3, 5));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - Last line intersect with 1st line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(-3, 5));
    CHECK(intersectionExistsInStreet(newCoords));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- true (Failures) ---------------------
    //      - 2nd line and 2nd last lines intersects with other lines
    // ---------------------------------------------------

    // true (Failure) - 2nd line intersects with closest intersectable line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-3, 7));
    newCoords.push_back(Node(1, 7));
    newCoords.push_back(Node(2, -4));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - 2nd last line intersects with closest intersectable line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-3, 5));
    newCoords.push_back(Node(1, 5));
    newCoords.push_back(Node(2, -4));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - 2nd line intersect with last line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-2, 0));
    newCoords.push_back(Node(-3, 5));
    newCoords.push_back(Node(-3, 7));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - 2nd last line intersects with first line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-2, 0));
    newCoords.push_back(Node(-3, 5));
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, 0));
    CHECK(intersectionExistsInStreet(newCoords));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- true (Failures) ---------------------
    //      - Any line (in the middle) intersects with other lines
    // ---------------------------------------------------

    // true (Failure) - Any line (in the middle) intersects with closest intersectable line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-3, 0));
    newCoords.push_back(Node(0, 2));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - Any line (in the middle) intersects with Any other line (in the middle)
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(2, -4));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(4, 0));
    newCoords.push_back(Node(4, -3));
    newCoords.push_back(Node(6, 6));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - Any line (in the middle) intersect with last line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(2, -4));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(0, 2));
    CHECK(intersectionExistsInStreet(newCoords));

    // true (Failure) - 2nd last line intersects with first line
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(-1, -1));
    newCoords.push_back(Node(-6, -3));
    newCoords.push_back(Node(-3, 5));
    newCoords.push_back(Node(-3, 0));
    newCoords.push_back(Node(-4, -1));
    newCoords.push_back(Node(-5, -2));
    CHECK(intersectionExistsInStreet(newCoords));
    // ---------------------------------------------------
    // ---------------------------------------------------

}




TEST_CASE("overlapExists - true (Failure)  +  false (Success)") {
    std::vector<Street> streets;
    std::vector<Node> newCoords;

    // ---------------------------------------------------
    // ---------- true (Failure) ------------
    //      Overlap exists within the street
    // ---------------------------------------------------

    //* ---------------------------------------------------*/
    /* -------- Overlap exists within the street (between vertical streets) ---------*/
    streets.clear();

    // Case 1 - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(6, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(6, 0));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 2 - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(6, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 3a - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(6, 0));
    newCoords.push_back(Node(6, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 3b - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(6, 2));
    newCoords.push_back(Node(6, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 4a - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(6, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(6, -4));
    newCoords.push_back(Node(6, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 4b - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(6, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(6, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));




    /* ---------------------------------------------------*/
    /* -------- Overlap exists within the street (between horizontal streets) ---------*/
    streets.clear();

    // Case 1 - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, -2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 2 - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, -2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(-3, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 3a - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-3, -2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(0, -2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 3b - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-3, -2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(0, -2));
    newCoords.push_back(Node(3, -2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 4a - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, -2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(8, -2));
    newCoords.push_back(Node(3, -2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 4b - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, -2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(-3, -2));
    newCoords.push_back(Node(3, -2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    /* ---------------------------------------------------*/
    /* -------- Overlap exists within the street ---------*/
    streets.clear();

    // Case 1 - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(3, 0));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 2 - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(-3, 4));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(3, -5));
    newCoords.push_back(Node(3, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 3a - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-3, 4));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(0, 2));
    newCoords.push_back(Node(3, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 3b - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-3, 4));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(3, 0));
    newCoords.push_back(Node(0, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 4a - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(11, -3));
    newCoords.push_back(Node(9, -4));
    newCoords.push_back(Node(3, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 4b - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(0, 2));
    newCoords.push_back(Node(6, -2));
    newCoords.push_back(Node(9, 2));
    newCoords.push_back(Node(11, 1));
    newCoords.push_back(Node(-3, 4));
    newCoords.push_back(Node(3, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // ---------------------------------------------------
    // ---------------------------------------------------







    // ---------------------------------------------------
    // ---------- false (Success) + true (Failure) ------------
    //      Overlap exists among the streets
    //      - Done using Example 5
    // ---------------------------------------------------

    /* ---------------------------------------------------*/
    /* -------- false (Success) ---------*/
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(3, 3));
    newCoords.push_back(Node(4, 0));
    newCoords.push_back(Node(4, -3));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, -2));
    newCoords.push_back(Node(6, 4));
    newCoords.push_back(Node(8, 4));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));



    /* ---------------------------------------------------*/
    /* -------- true (Failure) - Overlap exists among the streets (between vertical lines) ---------*/

    // Case 1a - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 1b - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(-7, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 2a - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 3));
    newCoords.push_back(Node(-7, -2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 2b - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(-7, 6));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 3a - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 1));
    newCoords.push_back(Node(-7, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 3b - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 2));
    newCoords.push_back(Node(-7, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 4a - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 1));
    newCoords.push_back(Node(-7, 4));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 4b - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 2));
    newCoords.push_back(Node(-7, -6));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));



    /* -------- true (Failure) - Overlap exists among the streets (between horizontal lines) ---------*/

    // Case 1a - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(-5, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 1b - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(-6, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 2a - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-7, 0));
    newCoords.push_back(Node(3, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 2b - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(-18, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 3a - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-6, 0));
    newCoords.push_back(Node(-2, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 3b - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-2, 0));
    newCoords.push_back(Node(-6, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 4a - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-9, 0));
    newCoords.push_back(Node(-3, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 4b - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(-5, 0));
    newCoords.push_back(Node(7, 0));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));





    /* ---------------------------------------------------*/
    /* -------- true (Failure) - Overlap exists among the streets ---------*/

    // Case 1a - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(3, 3));
    newCoords.push_back(Node(2, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 1b - One common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(2, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 2a - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(3, 3));
    newCoords.push_back(Node(-2, -2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 2b - One common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(0, 0));
    newCoords.push_back(Node(4, 4));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 3a - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(1, 1));
    newCoords.push_back(Node(2, 2));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 3b - No common point + fully lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(1, 1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));


    // Case 4a - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));
    newCoords.push_back(Node(4, 4));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));

    // Case 4b - No common point + some part lies on other line
    newCoords.clear();
    newCoords.push_back(Node(-4, 1));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(1, 1));
    newCoords.push_back(Node(-1, -1));
    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(overlapExists(streets, newCoords));




    /* ---------------------------------------------------*/
    /* -------- false (success) ---------*/
    // Street 3
    newCoords.clear();
    newCoords.push_back(Node(-4, 0));
    newCoords.push_back(Node(-4, 6));
    newCoords.push_back(Node(-2, 6));
    newCoords.push_back(Node(2, 2));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Davenport Road", newCoords));
    // ---------------------------------------------------
    // ---------------------------------------------------
}




TEST_CASE("Boundry Checks - intersectionExistsBetweenStreets - true (Success)") {
    std::vector<Street> streets;
    std::vector<Node> newCoords;


    // ---------------------------------------------------
    // ------------------- Example 1 ---------------------
    //  End-point to End-point intersection
    // ---------------------------------------------------

    /* ----- Case 1a - S1L1 to SnL1----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(1, 0));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(8, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(1, 0));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));



    /* ----- Case 1b - S1L1 to SnLn----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(1, 0));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(6, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(8, -1));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));


    /* ----- Case 1c - S1Ln to SnL1----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(8, 1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(1, 0));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));


    /* ----- Case 1d - S1Ln to SnLn----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(8, 1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(8, -1));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 2 ---------------------
    //  End-point to Line intersection
    // ---------------------------------------------------

    /* ----- Case 2a - S1L1 to SnL1----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(8, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(1, 0));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));



    /* ----- Case 2b - S1L1 to SnLn----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(6, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(8, -1));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));


    /* ----- Case 2c - SnL1 to S1Ln ----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(8, 1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(2, 1));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));


    /* ----- Case 2d - SnLn to S1Ln ----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(8, 1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(1, 0));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(8, -1));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(2, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 3 ---------------------
    //  Line to Line intersection
    // ---------------------------------------------------

    /* ----- Case 3a - S1L1 to SnL1----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, -1));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(8, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(0, 1));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));



    /* ----- Case 3b - S1L1 to SnLn----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(0, -1));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(6, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(8, -1));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(0, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));


    /* ----- Case 3c - SnL1 to S1Ln ----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(8, 1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(0, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(0, 1));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));


    /* ----- Case 3d - SnLn to S1Ln ----- */
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(8, 1));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(0, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(8, -1));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(0, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------
}



TEST_CASE("intersectionExistsBetweenStreets - false (Failure)") {
    std::vector<Street> streets;
    std::vector<Node> newCoords;


    // ---------------------------------------------------
    // ------------------- Example 1 ---------------------
    //          Nowhere close to intersection
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(2, 1));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(8, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(2, -1));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(!intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 2 ---------------------
    //          Very close to intersection
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(-3, -1));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(8, 1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-10, 0));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -1));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(!intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 3 ---------------------
    //          Parallel Streets (Horizontal)
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(-3, 2));
    newCoords.push_back(Node(3, 2));
    newCoords.push_back(Node(7, 2));
    newCoords.push_back(Node(8, 2));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-10, -2));
    newCoords.push_back(Node(3, -2));
    newCoords.push_back(Node(7, -2));
    newCoords.push_back(Node(8, -2));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(!intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 4 ---------------------
    //          Parallel Streets (Vertical)
    // ---------------------------------------------------
    streets.clear();

    // Street 1
    newCoords.clear();
    newCoords.push_back(Node(2, -3));
    newCoords.push_back(Node(2, 3));
    newCoords.push_back(Node(2, 7));
    newCoords.push_back(Node(2, 8));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("Weber Street", newCoords));

    // Street 2
    newCoords.clear();
    newCoords.push_back(Node(-2, -10));
    newCoords.push_back(Node(-2, 3));
    newCoords.push_back(Node(-2, 7));
    newCoords.push_back(Node(-2, 8));

    CHECK(!multipleNodeInstancesInStreet(newCoords));
    CHECK(!intersectionExistsInStreet(newCoords));
    CHECK(!overlapExists(streets, newCoords));
    streets.push_back(Street("King Street S", newCoords));

    // Check whether this specification would lead to a non-empty graph
    CHECK(!intersectionExistsBetweenStreets(streets));
    // ---------------------------------------------------
    // ---------------------------------------------------
}