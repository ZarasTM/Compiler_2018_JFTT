#ifndef OPER_GEN_H
#define OPER_GEN_H

#include "Labeler.h"

using namespace std;

class OperationGenerator{
private:
  // Pointers for improved accesibility
  vector<string>* assemblyCode;
  long long int* currLine;
  Inserter* varInserter;
  Labeler* labeler;

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
  OperationGenerator(vector<string>& assemblyCode, long long int& currLine, Inserter* varInserter);
};

void OperationGenerator::prepareVariables(Variable* var1, Variable* var2){
  varInserter->insertToReg(var1, "B");
  varInserter->insertToReg(var2, "C");
}

// LOGICAL OPERATIONS

void OperationGenerator::getEQ(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("COPY D B\t\t# Checking EQ");
  addLine("SUB D C");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b<=c
  addLine("JUMP "+to_string(*currLine+3));
  addLine("COPY D C");
  addLine("SUB D B");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b=c
  addLine("JUMP "+to_string(0));

}

void OperationGenerator::getNEQ(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("COPY D B\t\t# Checking NEQ");
  addLine("SUB D C");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b>=c
  addLine("JUMP "+to_string(*currLine+3));
  addLine("COPY D C");
  addLine("SUB D B");
  addLine("JZERO D "+to_string(0)); // If zero b=c
}

void OperationGenerator::getLT(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("COPY D C\t\t# Checking LT");
  addLine("SUB D B");
  addLine("JZERO D "+to_string(*currLine+4)); // If zero b>=c
  addLine("COPY D B");
  addLine("SUB D C");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b=c
  addLine("JUMP "+to_string(0));
}

void OperationGenerator::getGT(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("COPY D B\t\t# Checking GT");
  addLine("SUB D C");
  addLine("JZERO D "+to_string(*currLine+4)); // If zero b<=c
  addLine("COPY D C");
  addLine("SUB D B");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b=c
  addLine("JUMP "+to_string(0));
}

void OperationGenerator::getLE(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("COPY D B\t\t# Checking LE");
  addLine("SUB D C");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b<=c
  addLine("JUMP "+to_string(0));
}

void OperationGenerator::getGE(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("COPY D C\t\t# Checking GE");
  addLine("SUB D B");
  addLine("JZERO D "+to_string(*currLine+2)); // If zero b>=c
  addLine("JUMP "+to_string(0));
}

// ARYTHMETIC OPERATIONS

void OperationGenerator::getADD(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("ADD B C\t\t# Adding");
  addLine("COPY F B");
}

void OperationGenerator::getSUB(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("SUB B C\t\t# Subdividing");
  addLine("COPY F B");
}

void OperationGenerator::getMUL(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("SUB F F\t\t# Multiplying");
  addLine("JZERO C " + to_string(*currLine+7));
  addLine("JODD C " + to_string(*currLine+4));
  addLine("ADD B B");
  addLine("HALF C");
  addLine("JUMP " + to_string(*currLine-4));
  addLine("ADD F B");
  addLine("JUMP " + to_string(*currLine-4));
}

void OperationGenerator::getDIV(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);

  // Handle dividing by powers of 2
  if(var2->isNum && !var2->isArr){
    for(long long int i=2; i<=stoll(var2->name); i=i*2){
      if(stoll(var2->name) == i){
        for(int j=i; j>=2; j=j/2){
          addLine("HALF B");
        }
        addLine("COPY F B");
        return;
      }
    }
  }

  addLine("SUB F F\t\t# Dividing");
  addLine("SUB E E");
  addLine("JZERO C "+to_string(*currLine+18)); // If C == 0 jump @do_1_end
  addLine("INC E");
  addLine("COPY A B"); // @while_1
  addLine("SUB A C");
  addLine("JZERO A "+to_string(*currLine+4)); // If divisor is smaller than dividient jump @while_1_end
  addLine("ADD C C");
  addLine("ADD E E");
  addLine("JUMP "+to_string(*currLine-5)); // Jump @while_1
  addLine("COPY A C"); // @if_1, @while_1_end, @do_1_start
  addLine("SUB A B");
  addLine("JZERO A "+to_string(*currLine+2));
  addLine("JUMP "+to_string(*currLine+3)); // Jump @if_1_end
  addLine("SUB B C");
  addLine("ADD F E");
  addLine("HALF C"); // @if_1_end
  addLine("HALF E");
  addLine("JZERO E "+to_string(*currLine+2)); // @do_1_cond, If D != 0 jump @do_1_end
  addLine("JUMP "+to_string(*currLine-9)); // Jump @do_1_start
  // @do_1_end
}

void OperationGenerator::getMOD(Variable* var1, Variable* var2){
  prepareVariables(var1, var2);
  addLine("SUB D D\t\t# Performing modulo operation");
  addLine("SUB E E");
  addLine("JZERO C "+to_string(*currLine+18)); // If C == 0 jump @do_1_end
  addLine("INC E");
  addLine("COPY A B"); // @while_1
  addLine("SUB A C");
  addLine("JZERO A "+to_string(*currLine+4)); // If divisor is smaller than dividient jump @while_1_end
  addLine("ADD C C");
  addLine("ADD E E");
  addLine("JUMP "+to_string(*currLine-5)); // Jump @while_1
  addLine("COPY A C"); // @if_1, @while_1_end, @do_1_start
  addLine("SUB A B");
  addLine("JZERO A "+to_string(*currLine+2));
  addLine("JUMP "+to_string(*currLine+3)); // Jump @if_1_end
  addLine("SUB B C");
  addLine("ADD D E");
  addLine("HALF C"); // @if_1_end
  addLine("HALF E");
  addLine("JZERO E "+to_string(*currLine+2)); // @do_1_cond, If D != 0 jump @do_1_end
  addLine("JUMP "+to_string(*currLine-9)); // Jump @do_1_start
  addLine("COPY F B"); // @do_1_end (this line needs to be here cuz we load numbers to B)
}

OperationGenerator::OperationGenerator(vector<string>& assemblyCode, long long int& currLine, Inserter* varInserter){
  this->assemblyCode = &assemblyCode;
  this->currLine = &currLine;
  this->varInserter = varInserter;
}

#endif /* end of include guard: OPER_GEN_H */
