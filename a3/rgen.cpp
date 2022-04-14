#include <iostream>
#include <sstream>
#include <vector>

#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>

#include <unistd.h>
// #include <sys/wait.h>

#include "rgen_source_files/node.hpp"
#include "rgen_source_files/street.hpp"
#include "rgen_source_files/rgen_processes.hpp"

#include "a3_source_files/a3_processes.hpp"




/* ******************************************************************************** */
//              Function to Remove Streets
/* ******************************************************************************** */
void clearStreets (std::vector<Street> &streets) {
    for (int i = 0; i < ((int) streets.size()); i++) {
        std::string removeCmd = "rm \"" + streets.at(i).getName() + "\"";
        std::cout << removeCmd << std::endl;
    }

    streets.clear();
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                          Main Function
/* ******************************************************************************** */
int main(int argc, char** argv) {
    // Maximum number of failed attempts allowed - to get the right specification
    int maxAllowedFailures = 25; // By default = 25

    // Variable to keep track of failed attempts to get the right specification
    int failedCaseCount = 0;    // Initially = 0

    // Stores current streets
    std::vector<Street> streets;

    // Variables to store rangeValues
    int minStreets, maxStreets;
    int minLines, maxLines;
    int minWait, maxWait;
    int minCoordRange, maxCoordRange;


    try {
        // Setting range for - noStreets, noLines, noWait, noCoordRange */
        parseArguments(argc, argv, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
        
        // Initialize failedCaseCount to 0
        failedCaseCount = 0;

        // Keep generating random specifications
        while (1) {
            std::string errorMessage;
            int noStreets, noLines, waitTime;
            
            /* Remove the previous specification of streets (if any) */
            clearStreets(streets);

            
            /* Random number for Streets */
            noStreets = findRandomNumber(minStreets, maxStreets);
            
            /* Generating random streets (count = noStreets) */
            int street = 0;
            while (street < noStreets) {
                // Random Street Name
                std::string streetName = findRandomString() + " " + findRandomString();

                // Add as a failure and regenerate, if a street with this name already exists
                if (streetWithNameExists (streets, streetName)) {
                    //  throw error if maxAllowedFailures is reached
                    if (++failedCaseCount  >  maxAllowedFailures) {
                        errorMessage = "Failed ro generate valid input for " + std::to_string(maxAllowedFailures) + " simultaneous attempts";
                        throw errorMessage;
                    }

                    continue;
                }


                // Random number of Lines
                noLines = findRandomNumber(minLines, maxLines);

                // Random Coordinates
                std::vector<Node> coords;
                for (int coord = 0; coord < (noLines + 1); coord++) {
                    int x = findRandomCoordindate(maxCoordRange);     // Generate  random 'x' coordinate
                    int y = findRandomCoordindate(maxCoordRange);     // Generate  random 'y' coordinate
                    
                    coords.push_back(Node(x,y));
                }

                // Add as a failure, if an invalid street has been generated
                if (multipleNodeInstancesInStreet(coords)  ||  intersectionExistsInStreet(coords)  ||  overlapExists(streets, coords)) {
                    //  throw error if maxAllowedFailures is reached
                    if (++failedCaseCount  >  maxAllowedFailures) {
                        errorMessage = "Failed to generate valid input for " + std::to_string(maxAllowedFailures) + " simultaneous attempts";
                        throw errorMessage;
                    }

                    continue;
                }
                
                streets.push_back(Street(streetName, coords));
                street++;
            }


            // Add as a failure, if the generated specification leads to an empty graph
            if (!intersectionExistsBetweenStreets(streets)) {
                //  throw error if maxAllowedFailures is reached
                if (++failedCaseCount  >  maxAllowedFailures) {                    
                    errorMessage = "Failed to generate valid input for " + std::to_string(maxAllowedFailures) + " simultaneous attempts";
                    throw errorMessage;
                }

                // Clear the specification (if any)
                streets.clear();

                continue;
            }


            /* Add streets */
            for (int i = 0; i < ((int) streets.size()); i++) {
                std::string addCmd = "add " + streets.at(i).toString();
                std::cout << addCmd << std::endl;
            }

            /* gg - Generate Graph */
            std::cout << "gg" << std::endl;

            /* Random Wait Time */
            waitTime = findRandomNumber(minWait, maxWait);
            sleep(waitTime);

            // Reset failedCaseCount to 0, on succesfull specification
            failedCaseCount = 0;
        }

    } catch (std::string exc) {
        std::cerr << "Error: " << exc << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
/* ******************************************************************************** */
/* ******************************************************************************** */