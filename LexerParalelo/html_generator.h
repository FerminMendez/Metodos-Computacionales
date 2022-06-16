#include <string>
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#ifndef HTML_H
#define HTML_H

string html_top = "<!DOCTYPE html>"
                  "<html>"
                  "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">"
                  "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p\" crossorigin=\"anonymous\"></script>"

                  "<style>"
                  "body{"

                  "background-color:#262424;"
                  "font-weight: 100;"
                  "font: 150% monospace;"

                  "}"

                  ".container{"
                  "width: 70%;"
                  "margin-top: 100px;"
                  "ext-indent: 1.5em"
                  "}"

                  ".string{"
                  "color: #CB1717;"

                  "}"

                  ".reserved{"
                  "color: #536DFE;"

                  "}"

                  ".enteros{"
                  "color: #30F01B;"
                  "}"

                  ".flotantes{"
                  "color: #C61BF0;"

                  "}"

                  ".operador{"

                  "color: #FFFF99;"
                  "font-weight: 900;"

                  "}"

                  ".variable{"
                  "color: #4AAB84;"

                  "}"

                  ".simbolo_esp{"
                  "color: #FFFF;"
                  "}"

                  ".comentario{"
                  "color: #486633;"
                  "}"

                  ".undefinded{"
                  "color:#9E9E9E;"

                  "}"

                  "</style>"

                  "<head>"
                  "   <title> Resaltador de sintaxis</title> <!--Título pestaña-->"
                  "  <meta charset = \"UTF-8\"> <!--Para utilizar caracteres especiales-->"
                  "  </head>"
                  "<body>"
                  "  <nav class=\"navbar navbar-light bg-light\">"
                  "<div class=\"container-fluid\">"
                  "<a class=\"navbar-brand\" href=\"#\">"
                  "<img src=\"http://elacontecer.com.mx/wp-content/uploads/2019/10/TecMonterrey_Horizontal_RGB.jpg\"\" alt=\"\" width=\"150\" height=\"40\" class=\"d-inline-block align-text-top\">"
                  "</a>"
                  " <span class=\"navbar-text\">"
                  "<h3 style='font: 100% monospace'>Actividad Integradora 5.3 Resaltador de sintaxis paralelo</h3>"
                  "</span>"

                  "<span class=\"navbar-text\" style='font: 80% monospace'>"
                  "<b>Jordana Betancourt Menchaca A01707434</b><br><b>Fermín Méndez García A01703366</b>"
                  "<br>Implementación de métodos computacionales (Gpo 601)</span></div></nav>"
                  "<div class=\"container \">"

                  "<ul type='square'>"

                  "<li style='color:  #CB1717'>String</li>"

                  "<li style='color:  #536DFE'>Palabra reservada</li>"

                  "<li style='color:  #30F01B'>Entero</li>"

                  "<li style='color:  #C61BF0'>Flotante</li>"

                  "<li style='color:  #FFFF99'>Operador</li>"

                  "<li style='color:  #4AAB84'>Variable</li>"

                  "<li style='color:  #FFFF'>Símbolo especial</li>"

                  "<li style='color:  #486633'>Comentario</li>"

                  "<li style='color:  #9E9E9E'>Indefinido</li>"

                  "</ul>"
                  "<div class=\"container\">";



    string html_bot =
        "</div>"
        "</body>"
        "</html>"
        ;

    string html_mid =
        " <span class=\"reserved\">Palabra reservada --> int</span>"
        "  <span class=\"enteros\">Entero --> 100</span>"
        "<span class=\"flotantes\">Flotante --> 1.12</span>"
        "  <span class=\"operador\">Operador --> +</span>"
        "<span class=\"variable\">Variable --> vel_max</span>"
        " <span class=\"simbolo_esp\">Símbolo especial --> (</span>"
        "      <span class=\"comentario\">Comentario --> //Esto es un comentario</span>"
        ;


string nombreSecuencial(int num_arch){

    string nom_arch = "secuencial";
    
    string s = to_string(num_arch);
    nom_arch += s;
    nom_arch += ".html";

    return nom_arch;
    
}

string nombreConcurrente(int num_arch){

    string nom_arch = "concurrente";
    
    string s = to_string(num_arch);
    nom_arch += s;
    nom_arch += ".html";

    return nom_arch;
}

    void create_html(string html_lexer, string nom_arch)
{
    // ofstream outfile("test.html");
    // outfile << "hola" << std::endl;
    // outfile.close();

    

    string filename(nom_arch);
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open())
    {
        cout << "failed to open " << filename << '\n';
    }
    else
    {
        file_out << html_top << html_lexer << html_bot << endl;
        //cout << "Lexer creado!" << endl;
    }
}

#endif
// int main()
// {
//     cout << "hola";
//     cout << html_top;
//     create_html(html_mid);

// };