#/*
Jordana Betancourt Menchaca y Fermín Méndez García
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <queue>
using namespace std;

class Token
{
private:
  string value;
  string type;
  bool finished;
  

public:
  Token();
  string print();
  void add(char c);
  //Para reiniciar el token
  bool is_complete();
  void reset();
  
  string get_type(){return type;};
};

Token::Token()
{
  value = "";
  type = "";
  finished= false;
}
void Token::reset(){
  value = "";
  type = "";
  finished= false;
}

bool Token::is_complete(){
  return finished;
}

string Token::print()
{
  return value + " es " + type + "\n";
}

void Token::add(char c)
{
  type="all";
  value+=c;
}

void lexerAritmetico(string archivo)
{
  ifstream input;
  string linea;
  input.open(archivo);

  queue<Token> tokens;//Donde se almacenan los tokens
  if (!input.is_open())
  {
    cout << "No se puedo leer el archivo";
  }

  int i=0;
  char c;
  Token current_token;
  // Obtener las líneas del archivo de texto
  while (getline(input, linea))
  {
    i=0;
    while (i<linea.size()){
      c=linea[i];
      current_token.add(c);
      if(current_token.is_complete()){
        tokens.push(current_token);
        current_token.reset();
      }
      i++;
    }
    if(current_token.get_type()!=""){
      tokens.push(current_token);
      current_token.reset();
    }
    cout<<endl;
  }

  while(!tokens.empty()){
    cout<<tokens.front().print()<<endl;
    tokens.pop();
  }

  
}

int main(int argc, char *argv[])
{
  // if (argc != 2) {
  //   cout << "usage: " << argv[0] << " pathname\n";
  //   return -1;
  // }

  lexerAritmetico("prueba.txt");

  return 0;
}