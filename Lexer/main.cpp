#include <iostream>
#include <vector>
using namespace std;

void lexerAritmetico(string archivo) {
  int current=0;
  string token;
  while(current<archivo.size()){
    cout<<archivo[current];
    if(archivo[current]== ' ' || archivo[current]=='\n'){

    }
    else{
      token=getToken(current, archivo);
    }
    current++;
  }
  // to do
}

string getToken(int current, string archivo){
 string type=" ";
 string thisChar;
 if(type=" "){
 thisChar=identifyElement(archivo[current]);

 }
 

}

string identifyElement(char c){
  if(isanum(c)){
    return "num";
  }
  //...
  else{
    return "nf";
  }
}

bool isanum(char c){
  vector<char> numbers={'0','1','2','3','4','5','6','7','8','9'};
  return find(numbers.begin(),numbers.end(),c) != numbers.end();
}

int main(int argc, char* argv[]) {
  // if (argc != 2) {
  //   cout << "usage: " << argv[0] << " pathname\n";
  //   return -1;
  // }
  string cadena= "b=7 \na = 32.4 *(-8.6 - b)/       6.1E-8\nd = a ^ b // Esto es un comentario";
  //lexerAritmetico(argv[1]);
  lexerAritmetico(cadena);
  return 0;
}
