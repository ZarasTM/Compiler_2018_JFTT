#ifndef MAIN_H
#define MAIN_H

#include "Variable.h"
#include "Inserter.h"
#include "Labeler.h"
#include "OperationGenerator.h"

extern int yylineno;
extern bool DEBUG;
long long int currMemIdx;

using namespace std;

// Data used in compiler
vector<string> assemblyCode;
long long int currLine = 0;

// Pointer to objects used in compiling
Inserter* varInserter = new Inserter(assemblyCode);
OperationGenerator* operationGen = new OperationGenerator(assemblyCode, currLine, varInserter);
Labeler* labeler = new Labeler(assemblyCode, currLine);


// Function user for testing
void tester(){
  cout << "RUNNING TESTER" << endl;
}

#endif /* end of include guard: MAIN_H */
