/*
// File: main.cpp
// Authors: Jordana Betancourt Menchaca A01707434 y Fermín Méndez García A01703366
// Date: 19/03/2022
//
// Implementación de un DFA.
//
// Función que imprime los tokens encontrados en un archivo, caracter por caracter.
//
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void lexerAritmetico(string archivo) {
  ifstream input;
  string resultados;

  input.open(archivo);

   if (!input.is_open()) {
    cout << "No se puedo leer el archivo";
  }

  //Obtener las líneas del archivo de texto
  while(getline(input, resultados)){

    // Definimos conjuntos para cada tipo de token que podríamos tener

    /*Un entero puede tener un signo menos o no seguido de 1 o más dígitos*/
    string enteros = "\\-?[0-9]+"; 

     /*Un número real/flotante empieza igual que uno entero, con diversas opciones
     1) puede seguirle un punto con uno o más dígitos (63.1)
     2) puede seguirle un E/e para exponente seguido de uno o más dígitos (2e10)
     3) puede seguirle un E/e y un signo menos seguido de uno o más dígitos (2e-10)
     4) puede seguirle un punto decimal con uno o más dígitos seguido de un exponente
     con uno o varios dígitos 6.1e10
     5) puede seguirle un punto decimal con uno o más dígitos seguido de un exponente 
     y signo menos con uno o varios dígitos 6.1e-10
      */
    
    string reales = "(-?[0-9]+(\\.?|(E|e)?)\\-?[0-9]*(E|e)?\\-?[0-9]*)";


    /*Una variable empieza siempre por una letra, luego puede tener 0 o más veces
    otra letra,underscore o dígito */
    string variable = "[a-zA-Z][a-zA-Z_0-9]*";  

    /*Hay 6 operadores diferentes*/ 
    string operadores = "[\\-|\\+|\\^|\\=|\\/|\\*]";

   /*Hay 2 carácteres especiales*/ 
    string especiales = "[\\(\\)]";

   /*Un cometario empieza con dos slash seguido de cualquier símbolo hasta el fin de línea*/ 
    string comentarios = "\\/\\/.*";

    //Generamos un regex de tokens que estabolecimos previamente
    regex regex_tokens(comentarios +"|"+ reales+"|" +  operadores +"|"+ variable +"|"+  enteros +"|" + especiales ); // +"|"+ ees variable OR operador y el + es para agregar

    //Creamos un iterador para ir recorriendo el archivo
   auto inicio_arch = 
    // Ver si el elemento del iterador actual se encuentra en los toxens generados
      std::sregex_iterator(resultados.begin(), resultados.end(), regex_tokens);
    // Si ya es el fin del archivo termina
    auto fin_arch = std::sregex_iterator(); 

  
    //Leemos caracter por caracter, si detecta un token pasamos al siguiente caracter
    for (std::sregex_iterator i = inicio_arch; i != fin_arch; ++i) {
      std::smatch match = *i; // con el * lo desreferencia, desapuntador                                               
      std::string caracter = match.str(); // lo convertimos a string

      //¿Es un entero?
      if(regex_match(caracter, regex(enteros))){
        cout << caracter << " | TOKEN DE NÚMERO ENTERO" << endl;
        cout << "---------------------------------------------"<< endl;
      //¿Es un número real?
      }else if(regex_match(caracter, regex(reales))){
        cout << caracter << " | TOKEN DE NÚMERO REAL/FLOTANTE" << endl;
        cout << "---------------------------------------------"<< endl;
      //¿Es un comentario?
      }else if(regex_match(caracter, regex(comentarios))){
        cout << caracter << " | TOKEN DE COMENTARIO" << endl;
        cout << "---------------------------------------------"<< endl;
      //¿Es una variable?
      }else if(regex_match(caracter, regex(variable))){
        cout << caracter << " | TOKEN DE VARIABLE" << endl;
        cout << "---------------------------------------------"<< endl;
      // ¿Es un caracter especial?
      }else if(regex_match(caracter, regex(especiales))){
        if(caracter == "("){
          cout << caracter << " | TOKEN ESPECIAL -> Paréntesis izquierdo" << endl;
          cout << "---------------------------------------------"<< endl;
        }else{
          cout << caracter << " | TOKEN ESPECIAL -> Paréntesis derecho"  << endl;
          cout << "---------------------------------------------"<< endl;
        }
      //¿Es algún operador?
      }else if(regex_match(caracter, regex(operadores))){
        if(caracter == "="){
          cout << caracter << " | TOKEN OPERADOR -> Asignación" << endl;
          cout << "---------------------------------------------"<< endl;
      }else if(caracter == "+"){
        cout << caracter << " | TOKEN OPERADOR -> Suma" << endl;
        cout << "---------------------------------------------"<< endl;
      }else if(caracter == "-"){
        cout << caracter << " | TOKEN OPERADOR -> Resta" << endl;
        cout << "---------------------------------------------"<< endl;
      }else if(caracter == "*"){
        cout << caracter << " | TOKEN OPERADOR -> Multiplicación" << endl;
        cout << "---------------------------------------------"<< endl;
      }else if(caracter == "/"){
        cout << caracter << " | TOKEN OPERADOR -> División" << endl;
        cout << "---------------------------------------------"<< endl;
      }else{
        cout << caracter << " | TOKEN OPERADOR -> Potencia" << endl;
        cout << "---------------------------------------------"<< endl;
      }
    }
  }
  }
}

//Main 
int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
  }


  lexerAritmetico(argv[1]);
 

  return 0;
}
