#include <iostream>
#include <vector>
#include<bits/stdc++.h>

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
 if(type==" "){
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

//Para identificar si es un número
bool isanum(char c){
  vector<char> numbers={'0','1','2','3','4','5','6','7','8','9'};

    //El iterador nos sirve para avanzar en el vector.
    std::vector<char>::iterator it;
        
    //Para averiguar si el char actual está en el vector de números.
    it = find (numbers.begin(), numbers.end(), c);
    if (it != numbers.end())
    {
      //Si el itarador no está en el final (es porque ya encontró que es un número)
        return true;
    }
    else
    //De otra forma, no es un número.
       return false;
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
