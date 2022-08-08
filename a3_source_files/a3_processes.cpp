#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

#include "a3_processes.hpp"



/* ******************************************************************************** */
//          Function to Parse Arguments and check them for Semantic Errors
/* ******************************************************************************** */
void parseArguments (int argc, char **argv, int &minStreets, int &maxStreets, int &minLines, int &maxLines, int &minWait, int &maxWait, int &minCoordRange, int &maxCoordRange) {
    /* Default range for noStreets, noLines, waitTime, coordRange */
    minStreets = 2;
    maxStreets = 10;

    minLines = 1;
    maxLines = 5;

    minWait = 5;
    maxWait = 5;

    minCoordRange = -20;
    maxCoordRange = 20;


    /* Changing max. of each Range depending on command-line arguments, that are passed */
    for (int i = 1; i < argc; i = i + 2) {
        if (strcmp(argv[i], "-s") == 0) {
            int val = std::stoi(argv[i + 1]);

            if (val < minStreets) {
                std::string errorMessage = "Invalid maxStreets: should be >= " + std::to_string(minStreets);
                throw errorMessage;
            }

            maxStreets = val;

        } else if (strcmp(argv[i], "-n") == 0) {
            int val = std::stoi(argv[i + 1]);

            if (val < minLines) {
                std::string errorMessage = "Invalid maxLines: should be >= " + std::to_string(minLines);
                throw errorMessage;
            }
            
            maxLines = val;

        } else if (strcmp(argv[i], "-l") == 0) {
            int val = std::stoi(argv[i + 1]);

            if (val < minWait) {
                std::string errorMessage = "Invalid maxWait: should be >= " + std::to_string(minWait);
                throw errorMessage;
            }

            maxWait = val;

        } else if (strcmp(argv[i], "-c") == 0) {
            int val = std::stoi(argv[i + 1]);
            
            int minRequiredValue = 1;
            if (val < minRequiredValue) {
                std::string errorMessage = "Invalid maxCoordRange: should be >= " + std::to_string(minRequiredValue);
                throw errorMessage;
            }

            minCoordRange = -val;
            maxCoordRange = val;
        }
    }
}
/* ******************************************************************************** */
/* ******************************************************************************** */
