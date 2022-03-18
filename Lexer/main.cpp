/*
Jordana Betancourt Menchaca y Fermín Méndez García
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
using namespace std;

void lexerAritmetico(string archivo) {
  ifstream input;
  string resultados;
  vector<char>::iterator it;
  input.open(archivo);

   if (!input.is_open()) {
    cout << "No se puedo leer el archivo";
  }

  //Obtener las líneas del archivo de texto
  while(getline(input, resultados)){

    // Definimos conjuntos para cada tipo de token que podríamos tener

    /*Una variable empieza siempre por una letra, luego puede tener otra letra,
    underscore o dígito */
    string variable = "[a-zA-Z][a-zA-Z_0-9]*";  
    /*Para los reales*/
    string reales = "-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?"; // con los () y ? decimos que eso puede o no estar en la funcion establecid 
    /*Hay 6 operadores diferentes*/ 
    string operadores = "[\\*|\\/|\\^|\\=|\\+|\\-]";
    
    string especiales = "[\\(\\)]";
    string comentarios =  " //.*$"; //. cualquier elemento  y el $ indica que continua hasta llegar al final de la linea 

    //Generamos un regex de tokens que estabolecimos previamente
    regex regex_tokens(variable +"|"+ operadores +"|"+ reales +"|"+ especiales +"|"+ comentarios); // +"|"+ ees variable OR operador y el + es para agregar

    // definimos nuestro iterador para ir recorriendo y buscar en regex los tokens
   auto inicio_arch = 
        // iterador para ir recorriendo match por match y detectarlos en regex_tokens
        std::sregex_iterator(resultados.begin(), resultados.end(), regex_tokens); // leer de resultados incio a resultados final 
    auto fin_arch = std::sregex_iterator(); // cuando ya no tenga mas elementos se deja de leer 

    // vamos a ir leyendo caracter x caracter, al detectar su token, pasamos al siguiente carcater
    for (std::sregex_iterator i = inicio_arch; i != fin_arch; ++i) {
      std::smatch match = *i; // con el * lo desreferencia, desapuntador                                               
      std::string caracter = match.str(); // lo convertimos a string
      if(regex_match(caracter, regex(variable))){ //ya que tebemos el string, vemos si esta hace match con el regex, que basta solo con poner regex ya que se llama al constructor
        cout << caracter << " -> Token de Variable" << endl;
      }else if(regex_match(caracter, regex(reales))){
        cout << caracter << " -> Token de numero real" << endl;
      }else if(regex_match(caracter, regex(comentarios))){
        cout << caracter << " -> Token de comentario" << endl;
      }else if(regex_match(caracter, regex(especiales))){
        if(caracter == "("){
          cout << caracter << " -> Token especial, parentesis que abre" << endl;
        }else{
          cout << caracter << " -> Token especial, parentesis que cierra" << endl;
        }
      }else if(regex_match(caracter, regex(operadores))){
        if(caracter == "="){
          cout << caracter << " -> Token operador, asignacion" << endl;
        }
      }else if(caracter == "+"){
        cout << caracter << " -> Token operador, suma" << endl;
      }else if(caracter == "-"){
        cout << caracter << " -> Token operador, resta" << endl;
      }else if(caracter == "*"){
        cout << caracter << " -> Token operador, multiplicacion" << endl;
      }else if(caracter == "/"){
        cout << caracter << " -> Token operador, division" << endl;
      }else{
        cout << caracter << " -> Token operador, potencia" << endl;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  // if (argc != 2) {
  //   cout << "usage: " << argv[0] << " pathname\n";
  //   return -1;
  // }


  lexerAritmetico("input2.txt");

  return 0;
}
