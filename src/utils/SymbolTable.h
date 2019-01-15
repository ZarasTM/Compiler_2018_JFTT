#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

using namespace std;

/*------------DECLARAIONS------------*/

struct Symbol{
  string name;
  Variable* var = nullptr;
};

class SymbolTable{
private:
  // Pointer to assemblyCode for improved accesibility
  vector<string>* assemblyCode;
  long long int* currMemIdx;

  vector<Symbol*> symbols;

public:
  // Returns Variable if exists
  Variable* getVariable(string name);

  // Insert variable to sym table (return 0 if ok 1 if already declared)
  int declare(string name);

  // Insert array to sym table
  int declareArray(string id, string start, string end);

  // used for initializing variables
  int initialize(Variable* var);

  // Lookup symbol in sym tab (return 0 if exists 1 if not)
  int lookup(string name);

  // Constructor
  SymbolTable(vector<string>& assemblyCode, long long int& currMemIdx);
};

/*------------DEFINITIONS------------*/

Variable* SymbolTable::getVariable(string name){
  for(int i=0; i<symbols.size(); i++){
    if(symbols.at(i)->name == name){
      if(symbols.at(i)->var != nullptr){
        return symbols.at(i)->var;
      }else{
        break;
      }
    }
  }
  return nullptr;
}

int SymbolTable::declare(string name){
  if(lookup(name) != 0){
    Symbol* tmp = new Symbol;
    tmp->name = name;
    symbols.push_back(tmp);
    return 0;
  }else{
    return 1;
  }
}

int SymbolTable::declareArray(string id, string start, string end){
  if(lookup(id) != 0){
    Variable* tmpV = new Variable(id, *currMemIdx);
    tmpV->setArray(stoll(start), stoll(end));
    Symbol* tmpS = new Symbol;
    tmpS->name = tmpV->name;
    tmpS->var = tmpV;
    symbols.push_back(tmpS);
    *currMemIdx += tmpS->var->size;
    return 0;
  }else{
    return 1;
  }
}

int SymbolTable::initialize(Variable* var){
  for(int i=0; i<symbols.size(); i++){
    if(symbols.at(i)->name == var->name){
      symbols.at(i)->var = var;
      return 0;
    }
  }
  return 1;
}

int SymbolTable::lookup(string name){
  for(int i=0; i<symbols.size(); i++){
    if(symbols.at(i)->name == name){
      return 0;
    }
  }
  return 1;
}

SymbolTable::SymbolTable(vector<string>& assemblyCode, long long int& currMemIdx){
  this->assemblyCode = &assemblyCode;
  this->currMemIdx = &currMemIdx;
}

#endif /* end of include guard: SYMBOL_TABLE_H */
