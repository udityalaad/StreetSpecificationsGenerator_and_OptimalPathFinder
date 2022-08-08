// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "a2_source_files/edge.hpp"
#include "a2_source_files/graph.hpp"
#include "a2_source_files/processes.hpp"


int main(int argc, char** argv) {
    // Test code. Replaced with your code
    
    Graph graph = Graph();

    // read from stdin until EOF
    while (!std::cin.eof()) {
        try {
            // read a line of input until EOL and store in a string
            std::string line;
            std::getline(std::cin, line);

            std::string cmd = "";
            int noVert = 0;
            std::vector<Edge> edges;
            std::vector<std::string> endPoints;

            lineParsing(line, cmd, noVert, edges, endPoints);
            if (cmd == "V") {
                graph.setNoVertices(noVert);

            } else if (cmd == "E") {
                graph.setEdges(edges);

                std::cout << graph.toString() << std::endl;

            } else if (cmd == "s") {
                std::string shorestPathResult = graph.generateShortestPath (endPoints.at(0), endPoints.at(1));
                std::cout << shorestPathResult << std::endl;
            }

        } catch (std::string exc) {
            std::cerr << "Error: " << exc << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}