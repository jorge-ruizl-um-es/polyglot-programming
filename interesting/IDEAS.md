## IDEAS PARA MEJORAR PROGRAMAS ##

Mejora de sort_char: 
Hacerlo por campos. Incluir opciones para:
	- ordenamiento de números
	- revertir (de mayor a menor, alfabético descendente)
	- no distinguir mayúsculas de minúsculas
	- orden de directorio (contar solo letras, dígitos y blancos)
	
Permitir introducir línea a línea por campos separados por un carácter separador, como si fuera una hoja de Excel (por ejemplo: Nombre		Edad		Salario).

Habría que especificar de alguna manera el número máximo de campos, y las opciones a aplicar para cada uno al ejecutar el programa. Puede tener más utilidad si le pasamos como entrada el contenido de un fichero haciendo cat fichero | ./programa; o redirigiendo la entrada estandar con ./programa "<" fichero. 

La salida del programa sería devolver cada campo ordenado según las opciones especificadas (por ejemplo: 
	todos los nombres ordenados
	todas las edades ordenadas
	...)


Mejora de tree_counting_words: 
Hacer un programa para procesar código en C y que detecta las variables definidas, las agrupa (hace grupos de variables que comiencen por el mismo patrón de n caracteres), e imprime por orden alfabético cada grupo que tenga más de una variable. Si una misma variable aparece varias veces en el programa, solo la tiene en cuenta una vez.

Esto podría implementarse con una struct que represente los distintos grupos en una especie de lista de grupos enlazada (cada grupo tiene una referencia al siguiente). Además, cada uno tendrá el patrón inicial de las variables que pertenecen a él, y una referencia (puntero) a la raíz de un árbol binario de búsqueda donde se almacenan las palabras. 

La función getword detectará si nos encontramos dentro de un comentario o cadena (detecta //, /**/, y "") para descartar las palabras que lea; y se detectarán las variables comprobando si una palabra leída corresponde a un tipo de dato nativo de C (int, float, char...) y almacenando la palabra siguiente. 
