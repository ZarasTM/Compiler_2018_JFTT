#ifndef UTILITY_H
#define UTILITY_H

extern long long int currLine;
extern vector<string> assemblyCode;
extern int yylineno;

using namespace std;

// Convert decimal string to binary string
string decToBin(string decStr){
  //cout << decStr << endl;
  string binStr = "";

  while(decStr.size()){
      int digit = decStr.at(decStr.size()-1);

      if(digit % 2){
          binStr = '1' + binStr;
      }else{
          binStr = '0' + binStr;
      }

      // Divide by 2
      long long int decInt = stoll(decStr);
      decInt = (long long int) decInt / 2;
      decStr = to_string(decInt);

      if(decStr.at(0) == '0'){
        decStr.erase(0,1);
      }
  }
  return binStr;
}

// Adds line to final assembly code
void addLine(string str){
  currLine++;
  assemblyCode.push_back(str.append("\n"));
}

void error(string msg){
  cerr << "Error: " << msg << " in line " << yylineno << endl;
  exit(1);
}

#endif /* end of include guard: UTILITY_H */
