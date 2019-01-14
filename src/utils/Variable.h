#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>

using namespace std;

class Variable{
public:
  // Data for reckognizing
  bool isArr;
  bool isNum;
  bool isVar;
  bool isRes;

  // Base data about variable
  string name;
  long long int index;

  // If is array
  long long int start;
  long long int end;
  long long int size;
  vector<Variable*> cells;

  // If is array returns cell of given index (accounting for array size, start and end)
  Variable* getCell(long long int index);

  Variable(string name, long long int index); // Constructor
};

Variable* Variable::getCell(long long int index){
  return nullptr;
}

Variable::Variable(string name, long long int index)
{
  this->name = name;
  this->index = index;
}


#endif /* end of include guard: VARIABLE_H */
