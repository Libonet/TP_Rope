# Integrantes del grupo

- Santiago Libonati
- Tomás Maiza

# Implementacion de 'Rope'

Una cuerda o 'rope' es una estructura de datos que permite representar secuencias de enteros
y calcular la suma de subsecuencias de manera eficiente.  
En concreto, un rope es un árbol binario donde:

- las hojas almacenan los enteros que definen la secuencia y
- los nodos internos almacenan la suma de enteros correspondiente al subintervalo definido por sus hojas descendientes.

### Implementamos distintos tipos de ropes

- Simple, de enteros. (ropeint.h)
- Simple, genérico. Definiendo conceptos para la operación. (rope.h)
- 'Lazy', de enteros. (lazyropeint.h)
- 'Lazy', genérico. Definiendo conceptos para la operación. (lazyrope.h)

Las respuestas a las consignas 1b y 2b se encuentran como comentarios en los archivos ropeint.cpp y lazyropeint.cpp, respectivamente.

# Build

Para compilar el proyecto, sólo hace falta correr `make`.  
Para correr los tests, ejecutas el programa 'tests' luego de compilar, o corres `make all`  
Para correr tests individuales (rope o lazyrope), ejecutas `./tests rope` o `./tests lazy`, o corres `make rope` o `make lazy`
