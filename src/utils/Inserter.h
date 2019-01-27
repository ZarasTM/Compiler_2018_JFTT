#ifndef INSERTER_H
#define INSERTER_H

using namespace std;

/*------------DECLARAIONS------------*/

class Inserter{
private:
  // Pointer to assemblyCode for improved accesibility
  vector<string>* assemblyCode;
  SymbolTable* symTab;

  // Insert functions for specific variable types
  void insertArr(Variable* var, string reg);
  void insertVar(Variable* var, string reg);
public:
  // Inserting to register non array variables
  void insertToReg(string name, string reg);
  void insertToReg(Variable* var, string reg);
  void insertNum(string dec, string reg);

  // Inserts index of var or tab(var) to reg A
  void insertIndex(Variable* var);

  // Constructor
  Inserter(vector<string>& assemblyCode, SymbolTable *symTab);
};

/*------------DEFINITIONS------------*/

void Inserter::insertToReg(string name, string reg){
  Variable* var = symTab->getVariable(name);
  insertToReg(var, reg);
}

// Clear numbers and arrays go directly here
void Inserter::insertToReg(Variable* var, string reg){
  if(var->isArr){
    insertArr(var, reg);
  }else if(var->isVar){
    Variable* temp = symTab->getVariable(var->name);
    insertVar(temp, reg);
  }else if(var->isNum){
    insertNum(var->name, reg);
  }else if(var->isBound){
    insertNum(to_string(var->index), "A");
    addLine("LOAD "+reg);
  }
}

void Inserter::insertArr(Variable* var, string reg){
  Variable* arr = symTab->getVariable(var->name);
  if(var->isNum){ // Insert array with index that is number to register
    long long int trueIndex = stoll(var->varIndex) - arr->start + arr->index;
    insertNum(to_string(trueIndex), "A");
    addLine("LOAD "+reg);
  }else if(var->isVar){ // Insert array with index that is number to register
    Variable* trueVar = symTab->getVariable(var->varIndex);
    insertVar(trueVar, "G");
    insertNum(to_string(arr->start), "H");
    addLine("SUB G H");
    insertNum(to_string(arr->index), "A");
    addLine("ADD A G");
    addLine("LOAD "+reg);
  }
}

void Inserter::insertIndex(Variable* var){
  if(var->isArr){
    Variable* arr = symTab->getVariable(var->name);
    if(var->isNum){
      long long int trueIndex = stoll(var->varIndex) - arr->start + arr->index;
      insertNum(to_string(trueIndex), "A");
    }else if(var->isVar){
      Variable* trueVar = symTab->getVariable(var->varIndex);
      insertVar(trueVar, "G");
      insertNum(to_string(arr->start), "H");
      addLine("SUB G H");
      insertNum(to_string(arr->index), "A");
      addLine("ADD A G");
    }
  }else if(var->isVar){
    Variable* trueVar = symTab->getVariable(var->name);
    insertNum(to_string(trueVar->index), "A");
  }else if(var->isNum){
    cout << "Cant get index of number " << var->name << endl;
  }
}

void Inserter::insertVar(Variable* var, string reg){
  insertNum(to_string(var->index), "A");
  addLine("LOAD "+reg);
}

void Inserter::insertNum(string dec, string reg){
  string bin = decToBin(dec);
  addLine("SUB "+reg+" "+reg+"\t\t# Inserting dec "+dec+" bin "+bin+" into register "+reg);

  // Insert using INC if number is less than 24
  if(stoll(dec) < 24){
    for(int i=stoll(dec); i>0; i--){
      addLine("INC "+reg);
    }
    return;
  }

  for(int i=0; i<bin.size(); i++){
    if(bin.at(i) == '1'){
      addLine("INC "+reg);
    }

    if(i<bin.size()-1){
      addLine("ADD "+reg+" "+reg);
    }
  }
}

Inserter::Inserter(vector<string>& assemblyCode, SymbolTable *symTab){
  this->assemblyCode = &assemblyCode;
  this->symTab = symTab;
}

#endif /* end of include guard: INSERTER_H */
