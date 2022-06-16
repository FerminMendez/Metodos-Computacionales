/*************************************************************
* Implementación de métodos computacionales (Gpo 601)
*
* Actividad Integradora 5.3 Resaltador de sintaxis paralelo
* 
* Jordana Betancourt Menchaca A01707434
* Fermín Méndez García A01703366
* 
* Para compilar g++ mainLexer.cpp -pthread
*
*
*************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "utils.h"
#include "html_generator.h"


using namespace std;

// const int THREADS = 8;

/*************************************************************
 * Implementación secuencial
 *************************************************************/

void lexerAritmetico(string archivo, string nom_arch) {

  ifstream input;
  string resultados;

  string respuesta;

  input.open(archivo);

   if (!input.is_open()) {
    cout << "No se puedo leer el archivo";
  }

  //Obtener las líneas del archivo de texto
  while(getline(input, resultados)){

    // Definimos conjuntos para cada tipo de token que podríamos tener
    string enteros = "\\-?[0-9]+"; 
    
    string reales = "(-?[0-9]+(\\.?|(E|e)?)\\-?[0-9]*(E|e)?\\-?[0-9]*)";

    string reservadas = "auto|const|double|int|float|short|struct|unsigned|break|continue|else|for|long";

  reservadas += "signed|switch|void|case|default|enum|goto|register|sizeof|typedef|volatile|char|do|extern|if|return|static|";
  reservadas += "union|while|asm|dynamic_cast|namespace|reinterpret_cast|try|bool|explicit|new|static_cast|typeid|catch|false|";
  reservadas += "operator|template|typename|class|friend|private|this|using|const_cast|inline|public|throw|virtual|delete|" ;
  reservadas += "mutable|protected|true|wchar_t";

    string variable = "[a-zA-Z][a-zA-Z_0-9]*";  

    string texto = "\".*\""; 

    string operadores = "[\\-|\\+|\\^|\\=|\\/|\\*]";

    string especiales = "[\\(|\\)|\\#|\\;|\\<|\\>|\\,\\[|\\]|\\{|\\}\\.|\\!]";

    string comentarios = "\\/\\/.*";

   string espacio = "\\s+";

    //Generamos un regex de tokens que estabolecimos previamente
    // regex regex_tokens(reservadas +"|" + comentarios +"|"+ reales+"|" +  operadores +"|"+ variable +"|"+  enteros +"|" + especiales + "|"+ texto +"|" + espacio ); 
    regex regex_tokens(reservadas +"|" + variable +"|"+ comentarios+"|" +  reales +"|"+ operadores +"|"+  enteros +"|" + especiales + "|"+ texto +"|" + espacio ); 

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

        // string respuesta;

      //¿Es un entero?
      if(regex_match(caracter, regex(enteros))){
            respuesta += "<span class= enteros>" + caracter +"</span>";
        
      //¿Es un número real?
      }else if(regex_match(caracter, regex(reales))){
       respuesta += "<span class= flotantes>" + caracter +"</span>";

      //¿Es un comentario?
      }else if(regex_match(caracter, regex(comentarios))){
        respuesta += "<span class= comentario>" + caracter +"</span>";

    //¿Es una palabra reservada?
     }else if(regex_match(caracter, regex(reservadas))){
       respuesta += "<span class= reserved>" + caracter +"</span>";

      //¿Es una variable?
    }else if(regex_match(caracter, regex(variable))){
       respuesta += "<span class= variable>" + caracter +"</span>";

      // ¿Es un caracter especial?
      }else if(regex_match(caracter, regex(especiales))){
        if(caracter == "("){
          respuesta += "<span class= simbolo_esp>" + caracter +"</span>";
        }else{
          respuesta += "<span class= simbolo_esp>" + caracter +"</span>";
        }

      //¿Es algún operador?
      }else if(regex_match(caracter, regex(operadores))){
        if(caracter == "="){
          respuesta += "<span class= operador>" + caracter +"</span>";
      }else{
          respuesta += "<span class= operador>" + caracter +"</span>";
      }

    //¿Es una cadena de texto?
    }else if(regex_match(caracter, regex(texto))){
        respuesta += "<span class= string>" + caracter +"</span>";
            //¿Es un espacio?
     }else if(regex_match(caracter, regex(espacio))){
       respuesta += "<span>_</span>";
     }

  }
  respuesta += "<br>";
 }

 create_html(respuesta,nom_arch); 
}


/*************************************************************
 * Implementación concurrente
 *************************************************************/

 typedef struct {
   string filepath, nom_arch;
} Block;


void* taskLexer(void* param) {
    Block *block;
    block = (Block*) param;


    lexerAritmetico(block->filepath, block->nom_arch);    
    pthread_exit(0);
}


/*************************************************************
 * Main
 *************************************************************/

int main(int argc, char* argv[]) {

  int THREADS = argc;

  cout << "Archivos recibidos: " << THREADS -1 <<endl;
  cout << "\n---- Serial ----\n";

 
  double ms, result;
  pthread_t tids[THREADS];
   Block blocks[THREADS];


  /*--------------------- MONO THREAD ---------------------*/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();

    for (int j = 1; j < THREADS; j++) {
    lexerAritmetico(argv[j],nombreSecuencial(j));
    }

    ms += stop_timer();
  }
  
  cout << "Tiempo = " << (ms / N) << "ms\n";

  float T1 = (ms / N);

  

  /*--------------------- MULTI THREAD ---------------------*/

  cout << "\n\n---- Multithread ----\n";
  
  for (int i = 1; i < THREADS; i++) {

    blocks[i-1].filepath = argv[i];
    blocks[i-1].nom_arch = nombreConcurrente(i);

  }

  ms = 0;

  for (int i = 0; i < N; i++) {
    start_timer();

    for (int j = 1; j < THREADS; j++) {
      pthread_create(&tids[j-1], NULL, taskLexer, (void*) &blocks[j-1]);
    }

   
    for (int j = 1; j < argc; j++) {
      pthread_join(tids[j-1], NULL);
    }

    ms += stop_timer();
  }
  
  cout << "Tiempo = " << (ms / N) << "ms\n";

  float TP = (ms / N);

 /*--------------------- SPEED UP---------------------*/
    cout << "\n---- Speedup  ----\n";
    float speedup = T1/ TP;
    cout << "El speedup es de: " << speedup << "\n\n";
    
 
  return 0;
}