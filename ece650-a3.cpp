#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <sstream>

#include "a3_source_files/a3_processes.hpp"



/* ******************************************************************************** */
//              Functions to execute concurrent programs
/* ******************************************************************************** */
/* Function to execute 'rgen' (Random Input Generator) */
int handle_rgen (int argc, char **argv) {
    argv[0] = (char *) "rgen";

    char *args[argc + 1];
    int i;
    for (i = 0; i < argc; i++) {
        args[i] = argv[i];
    }
    args[i] = NULL;

    auto status = execv("./rgen", args);

    std::cerr << "Error: " << strerror(errno) << "; Status = " << status << std::endl;

    return 1;
}


/* Function to execute 'ece650-a1.py' (Graph Generator) */
int handle_graphGenerator (void) {
    char *args[] = {(char *) "ece650-a1.py", NULL};
    auto status = execv("./ece650-a1.py", args);

    std::cerr << "Error: " << strerror(errno) << "; Status = " << status << std::endl;

    return 1;
}

/* Function to execute 'ece650-a2' (Shortest Path Generator) */
int handle_shortestPathGenerator (void) {
    char *args[] = {(char *) "ece650-a2", NULL};
    auto status = execv("./ece650-a2", args);

    std::cerr << "Error: " << strerror(errno) << "; Status = " << status << std::endl;

    return 1;
}
/* ******************************************************************************** */
/* ******************************************************************************** */





/* ******************************************************************************** */
//                          Main Function
/* ******************************************************************************** */
int main (int argc, char **argv) {
    // Checking arguments for semantic errors
    // try {
    //     int minStreets, maxStreets;
    //     int minLines, maxLines;
    //     int minWait, maxWait;
    //     int minCoordRange, maxCoordRange;

    //     parseArguments(argc, argv, minStreets, maxStreets, minLines, maxLines, minWait, maxWait, minCoordRange, maxCoordRange);

    // } catch (std::string exc) {
    //     std::cerr << "Error: " << exc << std::endl;
    //     exit(0);

    // } catch (const std::exception &e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     exit(0);
    // }
    

    // Pipe 1
    int CtoP1[2];
    if (pipe(CtoP1) == -1) {
        std::cerr << "Error: " << "Failed to create the pipe!" << std::endl;
        return 1;
    }

    // Create child-1
    auto fid1_handle_rgen = fork();
    if (fid1_handle_rgen == 0) {
        // Writing output of - rgen (cpp - Random Street-input)  --to-->  pipe1
        dup2(CtoP1[1], STDOUT_FILENO);
        close(CtoP1[0]);
        close(CtoP1[1]);
        
        handle_rgen(argc, argv);

        return 1;

    } else if (fid1_handle_rgen > 0) {
        // Go ahead

    } else {
        std::cerr << "Error: " << "Failed to start a child-1 process!" << std::endl;
        return 1;
    }


    // Pipe 2
    int CtoP2[2];
    if (pipe(CtoP2) == -1) {
        std::cerr << "Error: " << "Failed to create the pipe!" << std::endl;
        return 1;
    }

    // Create child-2
    auto fid2_handle_graphGenerator = fork();
    if (fid2_handle_graphGenerator == 0) {
        // Reading input of - a1 (py - Graph Generator)  --from-->  pipe1
        dup2(CtoP1[0], STDIN_FILENO);
        close(CtoP1[0]);
        close(CtoP1[1]);

        // Writing output of - a1 (py - Graph Generator)  --to-->  pipe2
        dup2(CtoP2[1], STDOUT_FILENO);
        close(CtoP2[0]);
        close(CtoP2[1]);

        handle_graphGenerator();

        return 1;

    } else if (fid2_handle_graphGenerator > 0) {
        // Go ahead

    } else {
        std::cerr << "Error: " << "Failed to start a child-2 process!" << std::endl;
        return 1;
    }



    // Create child-3
    auto fid3_handle_shortestPathGenerator = fork();
    if (fid3_handle_shortestPathGenerator == 0) {
        // Close unsed pipe ends
        close(CtoP1[0]);
        close(CtoP1[1]);

        // Reading input of - a2 (cpp - Shortest Path Generator)  --from-->  pipe2
        dup2(CtoP2[0], STDIN_FILENO);
        close(CtoP2[0]);
        close(CtoP2[1]);

        handle_shortestPathGenerator();

        return 1;

    } else if (fid3_handle_shortestPathGenerator > 0) {
        // Go Ahead

    } else {
        std::cerr << "Error: " << "Failed to start a child-3 process!" << std::endl;
        return 1;
    }



    // Create child-4
    auto fid4_take_user_input = fork();
    if (fid4_take_user_input == 0) {
        // Close unused pipe ends
        close(CtoP1[0]);
        close(CtoP1[1]);

        // Close unused pipe ends
        close(CtoP2[0]);

        // read input from the stdin and write to pipe-2 - [To be read by a2 (cpp - Shortest Path Generator)]
        while (!std::cin.eof()) {
            std::string line;
            std::getline(std::cin, line);
            
            std::stringstream stream1;
            stream1 << line << "\n";
            stream1.flush();
            
            write(CtoP2[1], stream1.str().c_str(), ((int) line.length()) + 1);
        }

        // Close remaining - (open) pipe ends
        close(CtoP2[1]);

        // Terminate rgen (Random Generator), on receiving EOF on stdin
        kill(fid1_handle_rgen, SIGTERM);

        return 0;

    } else if (fid4_take_user_input > 0) {
        // Close unused pipe ends
        close(CtoP1[0]);
        close(CtoP1[1]);

        // Close unused pipe ends
        close(CtoP2[0]);
        close(CtoP2[1]);

        // Go Ahead

    } else {
        std::cerr << "Error: " << "Failed to start a child-3 process!" << std::endl;
        return 1;
    }

    


    /* ---- Wait for the child-1 (rgen) to terminate
        i.e.: when either - error is thrown by rgen
                    or - eof is encountered on stdin ---- */
    int status1_handle_rgen;
    waitpid(fid1_handle_rgen, &status1_handle_rgen, 0);
    /* --------------------------------------------------- */


    /* ---- Then terminate remaining children ---- */
    kill(fid2_handle_graphGenerator, SIGTERM);
    kill(fid3_handle_shortestPathGenerator, SIGTERM);
    kill(fid4_take_user_input, SIGTERM);
    /* --------------------------------------------------- */


    /* ---- Wait for the signalled child processes to terminate ---- */
    // Wait for the child-2 to terminate
    int status2_handle_graphGenerator;
    waitpid(fid2_handle_graphGenerator, &status2_handle_graphGenerator, 0);

    // Wait for the child-3 to terminate
    int status3_handle_shortestPathGenerator;
    waitpid(fid3_handle_shortestPathGenerator, &status3_handle_shortestPathGenerator, 0);

    // Wait for the child-4 to terminate
    int status4_take_user_input;
    waitpid(fid4_take_user_input, &status4_take_user_input, 0);
    /* --------------------------------------------------- */

    return 0;
}
/* ******************************************************************************** */
/* ******************************************************************************** */