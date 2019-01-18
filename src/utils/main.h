#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include "utility.h"
#include "Variable.h"
#include "SymbolTable.h"
#include "Inserter.h"
#include "OperationGenerator.h"
#include "Labeler.h"

using namespace std;

extern int yylineno;
extern bool DEBUG;
long long int currMemIdx = 0;

using namespace std;

// Data used in compiler
vector<string> assemblyCode;
long long int currLine = 0;

// Pointer to objects used in compiling
SymbolTable* symTab = new SymbolTable(assemblyCode, currMemIdx);
Inserter* varInserter = new Inserter(assemblyCode, symTab);
OperationGenerator* operationGen = new OperationGenerator(assemblyCode, currLine, varInserter);
Labeler* labeler = new Labeler(assemblyCode, currLine);

void assign(Variable* var1, Variable* var2){
  // Error handling 1
  if(symTab->lookup(var1->name) != 0){
    error("Variable "+var1->name+" not declared");
  }else if(symTab->lookup(var2->name) != 0 && !var2->isNum && !var2->isRes){
    error("Variable "+var2->name+" not declared");
  }

  Variable* trueVar1 = symTab->getVariable(var1->name);
  Variable* trueVar2 = symTab->getVariable(var2->name);

  // Error handling 2
  if(trueVar2 == nullptr && !var2->isNum  && !var2->isRes){
    error("Variable "+var2->name+" not initialized");
  }

  // If var1 is not initialized do it
  if(trueVar1 == nullptr){
    trueVar1 = new Variable(var1->name, currMemIdx++);
    symTab->initialize(trueVar1);
  }

  if(var2->isRes){
    varInserter->insertIndex(var1);
    addLine("STORE F");
  }else{
    varInserter->insertToReg(var2, "B");
    varInserter->insertIndex(var1);
    addLine("STORE B");
  }
}

void getWrite(Variable* var){
  varInserter->insertToReg(var, "B");
  addLine("PUT B");
}

void getRead(Variable* var){
  var->index = currMemIdx++;
  symTab->initialize(var);
  varInserter->insertIndex(var);
  addLine("GET B");
  addLine("STORE B");
}

void finish(){
  addLine("HALT");
  for(int i=0; i<assemblyCode.size(); i++){
    if(DEBUG) cout << i << "\t|";
    cout << assemblyCode.at(i);
  }
}

// Function user for testing
void tester(){
  cout << "RUNNING TESTER" << endl;
}

#endif /* end of include guard: MAIN_H */
