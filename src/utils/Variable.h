#ifndef VARIABLE_H
#define VARIABLE_H

using namespace std;

extern void error(string msg);

/*
 *  If Variable is tab(const1:const2) name = tab and index = first table cell in memory
 *  If Variable is tab(const1) name = tab, isNum = truth and varIndex = const1
 *  If Variable is tab(var1) name = tab, isVar = truth and varIndex = var1
 */

class Variable{
public:
  // Data for reckognizing
  bool isArr = false;
  bool isNum = false;
  bool isVar = false;
  bool isRes = false;

  // Base data about variable
  string name;
  long long int index;

  // If is array
  long long int start;
  long long int end;
  long long int size;

  // If using tab(var): varIndex = var->name, if using tab(const): varIndex = const
  string varIndex;

  void setArray(long long int start, long long int end);

  Variable(string name, long long int index); // Constructor
  ~Variable(); // Destructor
};

void Variable::setArray(long long int start, long long int end){
  this->start = start;
  this->end = end;
  this->size = end - start + 1;
  if(size<1){
    error("Incorrect array size");
  }
}

Variable::Variable(string name, long long int index)
{
  this->name = name;
  this->index = index;
}

Variable::~Variable()
{
  free(this);
}

#endif /* end of include guard: VARIABLE_H */
