#include <iostream>
#include <cassert>
#include <string>
#include "Part1.h"
#include "Part2.h"

using namespace std;

int main(int argc, char* argv[])
{
    assert(argc == 4);
    string inputFile = argv[1];
    string outputFileI = argv[2];
    string outputFileII = argv[3];

    SolverBase* solver_1 = new Part1();
    solver_1->read(inputFile);
    solver_1->solve();
    solver_1->write(outputFileI);
    delete solver_1;

    SolverBase* solver_2 = new Part2();
    solver_2->read(inputFile);
    solver_2->solve();
    solver_2->write(outputFileII);
    delete solver_2;

    cout << "Solved." << endl;
}
