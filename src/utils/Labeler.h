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
  void addLabel();
  void addJump();

  // Function for poping jumps and labels from vectors (Useless functions for now)
  long long int getLabel();
  long long int getJump();

  // Constructor
  Labeler(vector<string>& assemblyCode, long long int& currLine);
};

Labeler::Labeler(vector<string>& assemblyCode, long long int& currLine){
  this->assemblyCode = &assemblyCode;
  this->currLine = &currLine;
}

void Labeler::fixIf() {

  for(int i=0; i<2; i++){
    long long int jumperLine = jumps.back();

    string jumper = assemblyCode->at(jumperLine-1);

    if(labels.empty()){
      return;
    }

    jumps.pop_back();

    long long int labelLine = labels.back();
    labels.pop_back();

    string s = jumper.substr(jumper.find_last_of(" "));
    jumper = jumper.substr(0, jumper.length() - s.length()).append(" ").append(to_string(labelLine)).append("\n");

    assemblyCode->at(jumperLine-1) = jumper;
  }
}

void Labeler::fixWhile(){

  int label1 = labels.back();
	labels.pop_back();
	int label2 = labels.back();
	labels.pop_back();
	labels.push_back(label1);
	labels.push_back(label2);

	for(int i=0; i<2; i++){
		long long int jumperLine = jumps.back();

		string jumper = assemblyCode->at(jumperLine-1);

		if(labels.empty()){
			return;
		}

		jumps.pop_back();

		long long int labelLine = labels.back();
		labels.pop_back();

    string s = jumper.substr(jumper.find_last_of(" "));
    jumper = jumper.substr(0, jumper.length() - s.length()).append(" ").append(to_string(labelLine)).append("\n");

		assemblyCode->at(jumperLine-1) = jumper;
  }
}

void Labeler::addLabel(){
  labels.push_back(*currLine);
}

void Labeler::addJump(){
  jumps.push_back(*currLine);
}

long long int Labeler::getLabel(){
  if(labels.empty()){
    return -1;
  }else{
    long long int tmp = labels.back();
    labels.pop_back();
    return tmp;
  }
}

long long int Labeler::getJump(){
  if(jumps.empty()){
    return -1;
  }else{
    long long int tmp = jumps.back();
    jumps.pop_back();
    return tmp;
  }
}

#endif /* end of include guard: LABELER_H */
