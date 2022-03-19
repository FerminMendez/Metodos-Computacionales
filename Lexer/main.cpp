#/*
Jordana Betancourt Menchaca y Fermín Méndez García
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <queue>
using namespace std;

class Token
{
private:
  string value;
  char type;
  //e = empty
  //n= number
  // l= letter
  bool finished;
  

public:
  Token();
  string print();
  void add(char c);
  //Para reiniciar el token
  bool is_complete();
  void reset();
  
  char get_type(){return type;};
};

Token::Token()
{
  value = "";
  type = 'e';
  finished= false;
}
void Token::reset(){
  value = "";
  type = 'e';
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
  switch (type){
   case 'e':
        if(isblank(c)){
          return;
        }
        if(isdigit(c)){
          type='n';
          value+=c;
        }
    case 'n':
       if(isdigit(c)){
          value+=c;
        }
    default:
      finished=true;
  }
  
  // if(type=='e' ){//Se come los espacios en blanco
  //  if(isblank(c)){
  //    return;
  //  }
  //  if(isdigit(c)){
  //    type="number";
  //  }
  // }
  // if(c==isblank(c)){
  // finished=true;
  // return;
  // }
  // if(type=="number"){
  //   if(isdigit(c)){
  //     value+=c;
  //   }
  //   else{
  //     finished=true;

  //   }
  // }
  
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
    if(current_token.get_type()!='e'){
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