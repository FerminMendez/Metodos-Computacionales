#include <iostream>
#include <vector>
#include "token.h"
using namespace std;



char getType(char c){
  if(c==1|| c==2 || c==3){
    return 'n';
  }
  else{
    return 'f';
  }
}


void lexerAritmetico(string archivo) {
  Token t;
  int* current=0;
  string token;
  bool finishedToken=true;
  while(*current<archivo.size()){
    cout<<archivo[*current];
    if(archivo[*current]== ' ' || archivo[*current]=='\n'){
      finishedToken=true;
    }
    else{
      Token t;
      while(t.valid(archivo[*current],getType(archivo[*current]))){
        current++;
      }
      cout<<t.printToken();
      finishedToken=false;
    }
    current++;
  }
  // to do
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

