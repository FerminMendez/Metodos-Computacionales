#lang racket

;____________________________Requires______________________________
(require 2htdp/batch-io)
(require racket/string)

;____________________________Documentation______________________________
;;https://docs.racket-lang.org/teachpack/2htdpbatch-io.html#%28def._%28%28lib._2htdp%2Fbatch-io..rkt%29._write-file%29%29
;;https://docs.racket-lang.org/reference/characters.html
;;https://docs.racket-lang.org/reference/regexp.html


;____________________________File Reader______________________________

(define (slist->string slst)
  (cond ((empty? slst) "")
        ((empty? (rest slst)) (symbol->string (first slst)))
        (else (string-append (symbol->string (first slst))
                             " "
                             (slist->string (rest slst))))))

(define (flatten lists)
   (foldr append empty lists))
;;(string-downcase str)
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))

;
(define list-of-chars->file
  (lambda (lst filename)
    (write-file filename (list->string lst))))


;___________________________HTML  ______________________________

(define top-html
(string-append "<!DOCTYPE html>
<html>
 
   <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">
<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p\" crossorigin=\"anonymous\"></script>

<style>
body{

background-color:#262424;
font-weight: 100;
font: 150% monospace;

}

.container{
width: 70%;
margin-top: 100px;
text-indent: 1.5em
}


.string{
color: #CB1717;

}

.reserved{
color: #536DFE;

}

.enteros{
color: #30F01B;

}

.flotantes{
color: #C61BF0;

}

.operador{

color: #FFFF99;
font-weight: 900;


}

.variable{
color: #4AAB84;


}

.simbolo_esp{
color: #FFFF;
}

.comentario{
color: #486633;
}


.undefinded{
color:#9E9E9E;

}

</style>


<head>
        <title> Resaltador de sintaxis</title> <!--Título pestaña-->
        <meta charset = \"UTF-8\"> <!--Para utilizar caracteres especiales-->
   </head>
   <body>
      <nav class=\"navbar navbar-light bg-light\">
         <div class=\"container-fluid\">
         <a class=\"navbar-brand\" href=\"#\">
         <img src=\"http://elacontecer.com.mx/wp-content/uploads/2019/10/TecMonterrey_Horizontal_RGB.jpg\"\" alt=\"\" width=\"150\" height=\"40\" class=\"d-inline-block align-text-top\">
         </a>
         <span class=\"navbar-text\">
            <h3 style='font: 130% monospace'> Integradora 3.4 Resaltador de sintaxis</h3>
         </span>
         
         <span class=\"navbar-text\" style='font: 90% monospace'>
         <b>Jordana Betancourt Menchaca A01707434</b><br><b>Fermín Méndez García A01703366</b>
         <br>Implementación de métodos computacionales (Gpo 601)</span></div></nav>
         <div class=\"container \">
      

<ul type='square'>

<li style='color:  #CB1717'>String</li>

<li style='color:  #536DFE'>Palabra reservada</li>

<li style='color:  #30F01B'>Entero</li>

<li style='color:  #C61BF0'>Flotante</li>

<li style='color:  #FFFF99'>Operador</li>

<li style='color:  #4AAB84'>Variable</li>

<li style='color:  #FFFF'>Símbolo especial</li>

<li style='color:  #486633'>Comentario</li>

<li style='color:  #9E9E9E'>Indefinido</li>

</ul>
<div class=\"container\">

"
               )
)


(define mid-html
(string-append "
      
      <span class=\"reserved\">Palabra reservada --> int</span>
      <span class=\"enteros\">Entero --> 100</span>
      <span class=\"flotantes\">Flotante --> 1.12</span>
      <span class=\"operador\">Operador --> +</span>
      <span class=\"variable\">Variable --> vel_max</span>
      <span class=\"simbolo_esp\">Símbolo especial --> (</span>
      <span class=\"comentario\">Comentario --> //Esto es un comentario</span>
"
               )
)

(define bot-html
(string-append "
      </div>
    </body>
</html>"
               )
)
;___________________________Funciones______________________________

;--------------------------- Tokens ---------------------

(define separate-tokens ;La función separa el codigo por tokens identificados
  (lambda (code)
    ; El #px debe ser el OR de todas las definiciones de tokens que tenemos
   
    (regexp-match* #px"\\/\\/.*|\".*\"|\\s+|[\\-|\\+]?\\d+\\.\\d*[eE]?[\\-|\\+]?\\d*|[\\-|\\+]?\\d+[eE]?[\\-|\\+]?\\d*|[\\(|\\)|\\#|\\;|\\<|\\>|\\,\\[|\\]|\\{|\\}|\\.|\\!]|[\\-|\\+|\\^|\\=|\\/|\\*]|[a-zA-Z][a-zA-Z0-9_]*"  code)
    ))

;[\\-|\\+]?\\d+(.\\d+)?([e|E]([\\-|\\+])?\\d+)?

(define clasify-element
  (lambda (element)
    (cond
      ;Aqui todas las condiciones para identificar un elemento en regex usando regex-match?

      ;Comentario
      ((regexp-match? #px"\\/\\/.*"element)(list element "comentario" ) )
      ;String
      ((regexp-match? #px"\".*\"" element) (list element "string" ) )
      ;Espacio
      ((regexp-match? #px"\\s+"element)(list element "espacio" ) )
      
      ;Flotantes
      ((regexp-match? #px"[\\-|\\+]?\\d+\\.\\d*[eE]?[\\-|\\+]?\\d*" element) (list element "flotantes" ) )
       
       ;Enteros
      ((regexp-match? #px"[\\-|\\+]?\\d+[eE]?[\\-|\\+]?\\d*" element) (list element "enteros" ) )
      
      ;Simbolo especial
       ((regexp-match? #px"[\\(|\\)|\\#|\\;|\\<|\\>|\\,\\[|\\]|\\{|\\}\\.|\\!]" element) (list element "simbolo_esp" ) )
      
       ;Palabras reservadas
      ((regexp-match? #px"auto|const|double|int|float|short|struct|unsigned|break|continue|else|for|long|
signed|switch|void|case|default|enum|goto|register|sizeof|typedef|volatile|char|do|extern|if|return|static|
union|while|asm|dynamic_cast|namespace|reinterpret_cast|try|bool|explicit|new|static_cast|typeid|catch|false|
operator|template|typename|class|friend|private|this|using|const_cast|inline|public|throw|virtual|delete|
mutable|protected|true|wchar_t" element) (list element "reserved" ) )
     
       ;Variable
      ((regexp-match? #px"[a-zA-Z][a-zA-Z0-9_]*" element) (list element "variable" ) )

      ;Operador
      ((regexp-match? #px"[\\-|\\+|\\^|\\=|\\/|\\*]" element) (list element "operador" ) ) 

      ;Indefinido
      (else  (list element "undefined" ) )
      )
    )
  )

(define pack-aux
  (lambda (content mem)
    (cond
    ((empty? content) mem)
    ((eq? (cadr(car content)) (cadr(car mem))) (pack-aux (cdr content) (append (list   (list (string-append (car (car content)) " " (car (car mem)))  (cadr(car mem)) ))  (cdr mem)) ) )
    (else (pack-aux (cdr content) (append (list (car content)) mem ) ))

      )
    )
  )


(define pack
  (lambda (content)
    (cond
    ((empty? content) '())
    (else (pack-aux (cdr (reverse content)) (list(car (reverse content))) ))

      )
    )
  )

;--------------------------- write in html ---------------------
(define write-html
  (lambda (full-content)
    (write-file output-file (paste-parts-html full-content))
    )
  )

(define paste-parts-html
  (lambda (full-content)
    (string-append top-html (generate-body full-content) bot-html)
    )
  )

(define generate-mid-html
  (lambda (content)
    
    (cond
      ((empty? content) '())
      (else (string-join  (map generate-current-element-html content) " " )  )
      )
    )
  )

(define generate-current-element-html
  (lambda (element)
    
    (cond
      ((empty? element) '())
      ;¿Es entero?
      ((equal? (cadr element) "enteros")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es palabra reservada?
      ((equal? (cadr element) "reserved")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es string?
      ((equal? (cadr element) "string")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es variable?
      ((equal? (cadr element) "variable")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es operador?
      ((equal? (cadr element) "operador")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es símbolo especial?
      ((equal? (cadr element) "simbolo_esp")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es comentario?
      ((equal? (cadr element) "comentario")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es float?
      ((equal? (cadr element) "flotantes")(string-append "<span class=\"" (cadr element) "\">" (car element) "</span>"  ))
      ;¿Es espacio?
      ((equal? (cadr element) "espacio")(string-append "<span>_</span>"))
      ;Deber ser indefinido
      (else (string-append "<span class=\"undefinded\">" (car element) "</span>"  ) )
      )
    )
  )
;____________________________ Constantes ______________________________

(define input-file "C:\\Users\\jordi\\Downloads\\test.cpp")

(define output-file "C:\\Users\\jordi\\Downloads\\testhtml.html")

;(define input-file "C:\\Users\\fmend\\OneDrive\\Escritorio\\Racket\\test.cpp")

;(define output-file "C:\\Users\\fmend\\OneDrive\\Escritorio\\Racket\\testhtml.html")

(define code (apply string (file->list-of-chars input-file)))

(define content (map clasify-element (separate-tokens code)))
;____________________________Lectura por lineas______________________________

(define code->lines
  (lambda (code)
    (regexp-split #rx"\n" code)))

(define clasify-code-by-line
  (lambda (code-by-line)
    (map clasify-line code-by-line)))

(define clasify-line
  (lambda (line-code)
    (map clasify-element (separate-tokens line-code))))


(define generate-body
  (lambda (full-content)
    
    (cond
      ((empty? content) '())
      (else  (string-join (map generate-current-line-html full-content) "<br> " ) )
      )
    )
  )

(define generate-current-line-html
  (lambda (content)
    
    (cond
      ((empty? content) "")
      (else (string-join  (map generate-current-element-html content) "" )   )
      )
    )
  )


;____________________________Prueba de funciones______________________________
;Recibe el codigo por lineas y devuelve una content separado por lineas
; input:("#include <iostream>"
 ; "#include <string>"
 ; "using namespace std;"
 ;""
 ; "    int r,c;")

(define full-content (clasify-code-by-line (code->lines code)))

;____________________________Prueba de funciones______________________________
;( code->lines code)

;content
(write-html full-content)

;(separate-tokens "    int r,c;")
;(clasify-line "    int r,c;")
;full-content
;(generate-current-line-html '(("                    " "espacio") ("x" "variable") ("x" "variable") (" " "espacio") ("to_string" "variable") ("i" "variable") ("j" "variable")) )
;(generate-body full-content)