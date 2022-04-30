#lang racket
;---------------Materia----------------

;Implementación de métodos computacionales (Gpo 601)
;Actividad Integradora 3.4 Resaltador de sintaxis 


;---------------Profesor----------------
; Pedro Oscar Pérez Murueta

;---------------Autor----------------
;Jordana Betancourt Menchaca A01707434
;Fermín Méndez García        A01703366


;____________________________Requires______________________________
(require 2htdp/batch-io)
(require racket/string)

;____________________________Documentation______________________________
;;https://docs.racket-lang.org/teachpack/2htdpbatch-io.html#%28def._%28%28lib._2htdp%2Fbatch-io..rkt%29._write-file%29%29
;;https://docs.racket-lang.org/reference/characters.html
;;https://docs.racket-lang.org/reference/regexp.html
;____________________________Rutas ______________________________

;(define input-file "C:\\Users\\jordi\\Downloads\\test.cpp")

;(define output-file "C:\\Users\\jordi\\Downloads\\testhtml.html")

(define input-file "C:\\Users\\fmend\\OneDrive\\Escritorio\\Racket\\hola.cpp")

(define output-file "C:\\Users\\fmend\\OneDrive\\Escritorio\\Racket\\testhtml.html")

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
      ((empty? full-content) '())
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

;Este es un ejemplo del html que va en medio-> En este programa esta parte se genera dinamicamente
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

(define classes
(list
  (list "\\/\\/.*" "comentario")
  (list "\".*\"" "string")
  (list "\\s+" "espacio" )
  (list "[+-]?(?=\\d*[.eE])(?=\\.?\\d)\\d*\\.?\\d*(?:[eE][+-]?\\d+)?"  "flotantes" )
  (list "[\\-|\\+]?\\d+"  "enteros" )
  (list "[\\(|\\)|\\#|\\;|\\<|\\>|\\,\\[|\\]|\\{|\\}\\.|\\!]"  "simbolo_esp" )
  (list "auto|const|double|int|float|short|struct|unsigned|break|continue|else|for|long|
   signed|switch|void|case|default|enum|goto|register|sizeof|typedef|volatile|char|do|extern|if|return|static|
   union|while|asm|dynamic_cast|namespace|reinterpret_cast|try|bool|explicit|new|static_cast|typeid|catch|false|
   operator|template|typename|class|friend|private|this|using|const_cast|inline|public|throw|virtual|delete|
   mutable|protected|true|wchar_t" "reserved" )
  (list "[a-zA-Z][a-zA-Z0-9_]*"  "variable" )
  (list "[\\-|\\+|\\^|\\=|\\/|\\*]"  "operador" )
   )
  )

(define anyclass
  (lambda (classes)
    (cond
    ((empty? (cdr classes)) (car(car classes)))
    (else (string-append  (car(car classes)) "|" (anyclass (cdr classes))  ))
      )
    )
  )
;pregexp
;(separate-tokens2 code)
;--------------------------- Tokens ---------------------



(define separate-tokens ;La función separa el codigo por tokens identificados
  (lambda (code)
    (regexp-match* (pregexp (anyclass classes))  code)
    ))

(define clasify-element
  (lambda (element)
   ( clasify-element-aux element classes)
    )
  )

(define clasify-element-aux
  (lambda (element list-classes)
    (cond 
      ;Aqui todas las condiciones para identificar un elemento en regex usando regex-match?
      ((empty? list-classes) (list element "undefined") )
      ((regexp-match? (pregexp (car(car list-classes))) element) (list element (cadr(car list-classes)) ))
      (else (clasify-element-aux element (cdr list-classes)))
      )
    )
  )

(define pack-aux
  (lambda (content mem)
    (cond
    ((empty? content) mem)
    ( (and (eq? (cadr(car content)) (cadr(car mem))) (eq? (cadr(car content)) "enteros") (regexp-match? #px"[\\-|\\+]\\d+" (car (car mem)))  )
      (pack-aux (cdr content) (append (list   (list (car (car content))  "enteros") (list (car(regexp-match #px"[\\-|\\+]" (car (car mem)))) "operador") (list (car(regexp-match #px"\\d+" (car (car mem))))  "enteros") )  (cdr mem)) ))
    
    ((eq? (cadr(car content)) (cadr(car mem))) (pack-aux (cdr content) (append (list   (list (string-append (car (car content)) " " (car (car mem)))  (cadr(car mem)) ))  (cdr mem)) ) )
    (else (pack-aux (cdr content) (append (list (car content)) mem ) ))

      )
    )
  )
;(regexp-match? #px"\\+\\d+" (car (car mem))) 
;(map pack full-content)
;Para no crear una etiqueta de html por cada palabra, generamos una función que agrupe las palabras con mismo tipo y que sean consecutivas
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

(define code (apply string (file->list-of-chars input-file)))

(define full-content (map pack(clasify-code-by-line (code->lines code))))

;____________________________Prueba de funciones______________________________

(write-html full-content)


