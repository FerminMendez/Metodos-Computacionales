# Metodos-Computacionales
Implementación de un lexer de operaciones aritmeticas

## Descripción

Este programa recibe como entrada un archivo de texto con expresiones aritmeticas respetando ciertas reglas.
Entonces el programa devuelve una lista de tokens reconocido y su tipo. Si no se cumplen las reglas se manda un error.

Lenguaje de programación: c++

## Tipos de tokens reconocidos

### Enteros
Ejemplo: 1  -15  8012    -501

### Flotantes (Reales)
Ejemplo: 0.10203  5.123e-15  29.3192   33

### Operadores
'=' Asignación
'+' Suma
'-' Resta
'*' Multiplicación
'/' División
'^' Potencia

### Identificadores
Ejemplo: x1     num_registros   Variable

### Símbolos especiales
( Parentesis que abre
)   Parentesis que cierra

### Comentarios
// seguido de caracteres hasta que se acabe el renglón

## Reglas de formación de algunos tokens

### Variables:
Deben empezar con una letra (mayúscula o minúscula).
Sólo están formadas por letras, números y underscore (‘_’).

### Números reales (de punto flotante):
Pueden ser positivos o negativos
Pueden o no tener parte decimal pero deben contener un punto (e.g. 10. o 10.0)
Pueden usar notación exponencial con la letra E, mayúscula o minúscula, pero después de la letra E sólo puede ir un entero positivo o negativo (e.g. 2.3E3, 6.345e-5, -0.001E-3, .467E9).

### Comentarios:
Inician con // y todo lo que sigue hasta que termina el renglón es un comentario

# Manual de uso

1. g++ main.cpp
2. ./a.exe nombreArchivo
