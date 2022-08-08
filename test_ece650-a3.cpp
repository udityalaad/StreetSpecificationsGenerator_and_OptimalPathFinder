/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <cctype>

#include "a3_source_files/a3_processes.hpp"



bool checkIfExceptionRaisedInParseArguments (int argc, char **argv, int &minStreets, int &maxStreets, int &minLines, int &maxLines, int &minWait, int &maxWait, int &minCoordRange, int &maxCoordRange) {
    bool result = false;

    try {
        parseArguments(argc, argv, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    } catch (std::string  e) {
        result = true;
    } catch (const std::exception &e) {
        result = true;
    }

    return result;
}



TEST_CASE("parseArguments - Success") {
    int defaultMinStreets = 2, defaultMaxStreets = 10;
    int defaultMinLines = 1, defaultMaxLines = 5;
    int defaultMinWait = 5, defaultMaxWait = 5;
    int defaultMinCoordRange = -20, defaultMaxCoordRange = 20;

    int minStreets, maxStreets;
    int minLines, maxLines;
    int minWait, maxWait;
    int minCoordRange, maxCoordRange;

    int argc;


    /* ------------------------------------------------------ */
    //              Test 0: No Arguments (Pass)
    /* ------------------------------------------------------ */
    argc = 1;

    char *argv0[] = {(char *) "ece650-a3"};
    parseArguments(argc, argv0, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);

    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == defaultMaxCoordRange);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */


    /* ------------------------------------------------------ */
    //              Test 1 - All 4 Arguments
    /* ------------------------------------------------------ */
    argc = 1 + (2*4);

    // Case 1a - In Order-a
    char *argv1a[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv1a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 1b - In Order-b
    char *argv1b[] = {(char *) "ece650-a3", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50", (char *) "-s", (char *) "20"};

    parseArguments(argc, argv1b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 1c - In Order-c
    char *argv1c[] = {(char *) "ece650-a3", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50", (char *) "-n", (char *) "30", (char *) "-s", (char *) "20"};

    parseArguments(argc, argv1c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 1d - In Order-d
    char *argv1d[] = {(char *) "ece650-a3", (char *) "-c", (char *) "50", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-s", (char *) "20"};

    parseArguments(argc, argv1d, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    /* ------------------------------------------------------ */
    //              Test 2 - 3 Arguments
    /* ------------------------------------------------------ */
    argc = 1 + (2*3);

    // Case 2a - Missing -s
    char *argv2a[] = {(char *) "ece650-a3",  (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 2b - Missing -n
    char *argv2b[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 30);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 2c - Missing -l
    char *argv2c[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30", (char *) "-n", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 30);
    CHECK(maxLines == 40);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == 50);


    // Case 2d - Missing -c
    char *argv2d[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30", (char *) "-n", (char *) "40", (char *) "-l", (char *) "50"};

    parseArguments(argc, argv2d, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == 30);
    CHECK(maxLines == 40);
    CHECK(maxWait == 50);
    CHECK(maxCoordRange == defaultMaxCoordRange);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    /* ------------------------------------------------------ */
    //              Test 3 - 2 Arguments
    /* ------------------------------------------------------ */
    argc = 1 + (2*2);

    // Case 3a - With only -s and -n
    char *argv3a[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30", (char *) "-n", (char *) "40"};

    parseArguments(argc, argv3a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == 30);
    CHECK(maxLines == 40);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == defaultMaxCoordRange);


    // Case 3b - With only -s and -l
    char *argv3b[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30", (char *) "-l", (char *) "40"};

    parseArguments(argc, argv3b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == 30);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == defaultMaxCoordRange);


    // Case 3c - With only -s and -c
    char *argv3c[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30", (char *) "-c", (char *) "40"};

    parseArguments(argc, argv3c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -40);

    CHECK(maxStreets == 30);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == 40);


    // Case 3d - With only -n and -l
    char *argv3d[] = {(char *) "ece650-a3",  (char *) "-n", (char *) "30", (char *) "-l", (char *) "40"};

    parseArguments(argc, argv3d, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == defaultMaxCoordRange);


    // Case 3e - With only -n and -c
    char *argv3e[] = {(char *) "ece650-a3",  (char *) "-n", (char *) "30", (char *) "-c", (char *) "40"};

    parseArguments(argc, argv3e, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -40);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == 30);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == 40);


    // Case 3f - With only -l and -c
    char *argv3f[] = {(char *) "ece650-a3",  (char *) "-l", (char *) "30", (char *) "-c", (char *) "40"};

    parseArguments(argc, argv3f, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -40);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == 30);
    CHECK(maxCoordRange == 40);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    /* ------------------------------------------------------ */
    //              Test 4 - 1 Argument
    /* ------------------------------------------------------ */
    argc = 1 + (2*1);

    // Case 4a - With only -s
    char *argv4a[] = {(char *) "ece650-a3",  (char *) "-s", (char *) "30"};

    parseArguments(argc, argv4a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == 30);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == defaultMaxCoordRange);


    // Case 4b - With only -n
    char *argv4b[] = {(char *) "ece650-a3",  (char *) "-n", (char *) "30"};

    parseArguments(argc, argv4b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == 30);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == defaultMaxCoordRange);


    // Case 4c - With only -l
    char *argv4c[] = {(char *) "ece650-a3",  (char *) "-l", (char *) "30"};

    parseArguments(argc, argv4c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == 30);
    CHECK(maxCoordRange == defaultMaxCoordRange);


    // Case 4d - With only -n
    char *argv4d[] = {(char *) "ece650-a3",  (char *) "-c", (char *) "30"};

    parseArguments(argc, argv4d, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -30);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == 30);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */
}



TEST_CASE("parseArguments - Success + Failure") {
    int defaultMinStreets = 2, defaultMaxStreets = 10;
    int defaultMinLines = 1, defaultMaxLines = 5;
    int defaultMinWait = 5, defaultMaxWait = 5;
    int defaultMinCoordRange = -20, defaultMaxCoordRange = 20;

    int minStreets, maxStreets;
    int minLines, maxLines;
    int minWait, maxWait;
    int minCoordRange, maxCoordRange;

    int argc;


    /* ------------------------------------------------------ */
    //              Test 0: No Arguments (Pass)
    /* ------------------------------------------------------ */
    argc = 1;

    char *argv0[] = {(char *) "ece650-a3"};
    parseArguments(argc, argv0, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);

    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == defaultMinCoordRange);

    CHECK(maxStreets == defaultMaxStreets);
    CHECK(maxLines == defaultMaxLines);
    CHECK(maxWait == defaultMaxWait);
    CHECK(maxCoordRange == defaultMaxCoordRange);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    argc = 1 + (2*4);

    /* ------------------------------------------------------ */
    //              Test 1: -s
    /* ------------------------------------------------------ */
    // Case 1a - -s = -20 (Fail)
    char *argv1a[] = {(char *) "ece650-a3", (char *) "-s", (char *) "-20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv1a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 1b - -s = -1 (Fail)
    char *argv1b[] = {(char *) "ece650-a3", (char *) "-s", (char *) "-1", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv1b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 1c - -s = 0 (Fail)
    char *argv1c[] = {(char *) "ece650-a3", (char *) "-s", (char *) "0", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv1c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));


    // Case 1d - -s = 1 (Fail)
    char *argv1d[] = {(char *) "ece650-a3", (char *) "-s", (char *) "1", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv1d, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));


    // Case 1e - -s = defaultMinStreets = 2 (Pass)
    char *argv1e[] = {(char *) "ece650-a3", (char *) "-s", (char *) "2", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv1e, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 2);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 1f - -s = 3 (Pass)
    char *argv1f[] = {(char *) "ece650-a3", (char *) "-s", (char *) "3", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv1f, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 3);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 1g - -s = defaultMaxStreets = 10 (Pass)
    char *argv1g[] = {(char *) "ece650-a3", (char *) "-s", (char *) "10", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv1g, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 10);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 1h - -s = 11 (Pass)
    char *argv1h[] = {(char *) "ece650-a3", (char *) "-s", (char *) "11", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv1h, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 11);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    /* ------------------------------------------------------ */
    //              Test 2: -n
    /* ------------------------------------------------------ */
    // Case 2a - -n = -20 (Fail)
    char *argv2a[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "-20", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv2a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 2b - -n = -1 (Fail)
    char *argv2b[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "-1", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv2b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 2c - -n = 0 (Fail)
    char *argv2c[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "0", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv2c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));


    // Case 2e - -n = defaultMinStreets = 1 (Pass)
    char *argv2e[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "1", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2e, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 1);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 2f - -n = 2 (Pass)
    char *argv2f[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "2", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2f, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 2);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 2g - -n = defaultMaxStreets = 5 (Pass)
    char *argv2g[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "5", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2g, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 5);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);


    // Case 2h - -n = 6 (Pass)
    char *argv2h[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "6", (char *) "-l", (char *) "40", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv2h, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 6);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 50);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    /* ------------------------------------------------------ */
    //              Test 3: -l
    /* ------------------------------------------------------ */
    // Case 3a - -l = -20 (Fail)
    char *argv3a[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "-20", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv3a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 3b - -l = -1 (Fail)
    char *argv3b[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "-1", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv3b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 3c - -l = 0 (Fail)
    char *argv3c[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "0", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv3c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));


    // Case 3d - -l = 4 (Fail)
    char *argv3d[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "4", (char *) "-c", (char *) "50"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv3d, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));


    // Case 3e - -l = defaultMinStreets = defaultMaxStreets = 5 (Pass)
    char *argv3e[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "5", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv3e, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 5);
    CHECK(maxCoordRange == 50);


    // Case 3f - -l = 6 (Pass)
    char *argv3f[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "6", (char *) "-c", (char *) "50"};

    parseArguments(argc, argv3f, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -50);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 6);
    CHECK(maxCoordRange == 50);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */



    /* ------------------------------------------------------ */
    //              Test 4: -c
    /* ------------------------------------------------------ */
    // Case 4a - -c = -20 (Fail)
    char *argv4a[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "-20"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv4a, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 4b - -c = -1 (Fail)
    char *argv4b[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "-1"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv4b, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));

    // Case 4c - -c = 0 (Fail)
    char *argv4c[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "0"};
    CHECK(checkIfExceptionRaisedInParseArguments(argc, argv4c, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange));


    // Case 4e - -c = minimumRequired = 1 (Pass)
    char *argv4e[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "1"};

    parseArguments(argc, argv4e, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -1);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 1);


    // Case 4f - -c = 2 (Pass)
    char *argv4f[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "2"};

    parseArguments(argc, argv4f, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -2);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 2);


    // Case 4g - -c = defaultMaxStreets = 20 (Pass)
    char *argv4g[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "20"};

    parseArguments(argc, argv4g, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -20);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 20);


    // Case 4h - -c = 21 (Pass)
    char *argv4h[] = {(char *) "ece650-a3", (char *) "-s", (char *) "20", (char *) "-n", (char *) "30", (char *) "-l", (char *) "40", (char *) "-c", (char *) "21"};

    parseArguments(argc, argv4h, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);
    CHECK(minStreets == defaultMinStreets);
    CHECK(minLines == defaultMinLines);
    CHECK(minWait == defaultMinWait);
    CHECK(minCoordRange == -21);

    CHECK(maxStreets == 20);
    CHECK(maxLines == 30);
    CHECK(maxWait == 40);
    CHECK(maxCoordRange == 21);
    /* ------------------------------------------------------ */
    /* ------------------------------------------------------ */
}




