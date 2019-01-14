#ifndef INSERTER_H
#define INSERTER_H

#include <string>
#include <vector>
#include "Variable.h"

using namespace std;

class Inserter{
private:
  // Pointer to assemblyCode for improved accesibility
  vector<string>* assemblyCode;

public:
  // Inserting to register non array variables
  void insertToReg(Variable* var, string reg);

  // Inserting to register array varaibles
  void insertToReg(Variable* var, long long int index, string reg);

  // Insert functions for specific variable types
  void insertArr();
  void insertVar();
  void insertNum();

  // Constructor
  Inserter(vector<string>* assemblyCode);
};

void Inserter::insertToReg(Variable* var, string reg){}

void Inserter::insertToReg(Variable* var, long long int index, string reg){}

void Inserter::insertArr(){}

void Inserter::insertVar(){}

void Inserter::insertNum(){}

Inserter::Inserter(vector<string>* assemblyCode){
  this->assemblyCode = assemblyCode;
}

#endif /* end of include guard: INSERTER_H */
