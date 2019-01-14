#ifndef OPER_GEN_H
#define OPER_GEN_H

#include <string>
#include <vector>
#include "Variable.h"
#include "Inserter.h"

using namespace std;

class OperationGenerator{
private:
  // Pointers for improved accesibility
  vector<string>* assemblyCode;
  long long int* currLine;
  Inserter* inserter;

public:
  // Inserts var1 and var2 to needed registers
  void prepareVariables(Variable* var1, Variable* var2);

  // Conditional statements generators
  void getEQ(Variable* var1, Variable* var2);
  void getNEQ(Variable* var1, Variable* var2);
  void getLT(Variable* var1, Variable* var2);
  void getGT(Variable* var1, Variable* var2);
  void getLE(Variable* var1, Variable* var2);
  void getGE(Variable* var1, Variable* var2);

  // Arythmetic expressions generators
  void getADD(Variable* var1, Variable* var2);
  void getSUB(Variable* var1, Variable* var2);
  void getMUL(Variable* var1, Variable* var2);
  void getDIV(Variable* var1, Variable* var2);
  void getMOD(Variable* var1, Variable* var2);

  // Constructor
  OperationGenerator(vector<string>* assemblyCode, long long int* currLine, Inserter* inserter);
};

void OperationGenerator::prepareVariables(Variable* var1, Variable* var2){}

void OperationGenerator::getEQ(Variable* var1, Variable* var2){}

void OperationGenerator::getNEQ(Variable* var1, Variable* var2){}

void OperationGenerator::getLT(Variable* var1, Variable* var2){}

void OperationGenerator::getGT(Variable* var1, Variable* var2){}

void OperationGenerator::getLE(Variable* var1, Variable* var2){}

void OperationGenerator::getGE(Variable* var1, Variable* var2){}

void OperationGenerator::getADD(Variable* var1, Variable* var2){}

void OperationGenerator::getSUB(Variable* var1, Variable* var2){}

void OperationGenerator::getMUL(Variable* var1, Variable* var2){}

void OperationGenerator::getDIV(Variable* var1, Variable* var2){}

void OperationGenerator::getMOD(Variable* var1, Variable* var2){}

OperationGenerator::OperationGenerator(vector<string>* assemblyCode, long long int* currLine, Inserter* inserter){
  this->assemblyCode = assemblyCode;
  this->currLine = currLine;
  this->inserter = inserter;
}

#endif /* end of include guard: OPER_GEN_H */
