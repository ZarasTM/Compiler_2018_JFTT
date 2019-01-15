#ifndef LABELER_H
#define LABELER_H

using namespace std;

class Labeler{
private:
  // Pointers for improved accesibility
  vector<string>* assemblyCode;
  long long int* currLine;

  // Vectors holding labels and jump needed for fixing
  vector<long long int> labels;
  vector<long long int> jumps;

public:
  // Specific fixers for code blocks
  void fixWhile();
  void fixFor();
  void fixIf();
  void fixDo();

  // Functions adding jumps and labels to vectors
  void addLabel(long long int currLine);
  void addJump(long long int currLine);

  // Constructor
  Labeler(vector<string>& assemblyCode, long long int& currLine);
};

Labeler::Labeler(vector<string>& assemblyCode, long long int& currLine){
  this->assemblyCode = &assemblyCode;
  this->currLine = &currLine;
}

void Labeler::fixWhile(){}

void Labeler::fixFor(){}

void Labeler::fixIf(){}

void Labeler::fixDo(){}

void addLabel(){}

void addJump(){}

#endif /* end of include guard: LABELER_H */
