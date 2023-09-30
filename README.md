# Tarea-2

Guía compilación y ejecución:

Configuración botón run: make -s ./main

Al darle a "Run", el programa mostrará un menú en el que hay que escribir un número del 1 al 7 para indicar lo que el usuario desee realizar. Luego de seleccionar la opción, si es que el número ingresado es 1, se pedirá al usuario los tipos de datos correspondientes al punto, mientras que si se ingresa el 4, se hará lo mismo pero con los datos correspondientes al punto. Las otras opciones pedirán tipos de datos dependiendo de lo que se quiera mostrar, pero de todos, el programa imprime la solicitud de ingreso del dato que necesita para buscar e imprimir información.

Cuando se termine el proceso de la función del número que se ingresa, muestra nuevamente el menú para seguir seleccionando opciones, o para terminar la ejecución del programa ingresando un 0.


(*) quiere decir pequeño error que no imposibilita la compilación del programa de ninguna forma.

Funcionando correctamente:

- Registrar punto de interés (*)
- Mostrar datos de punto de interés (*)
- Eliminar punto de interés
- Registrar turista
- Agregar lugar favorito a turista
- Mostrar turistas por país
- Mostrar puntos de interés por tipo

Problemas conocidos:

- Al hacer ingreso de cualquier tipo de dato, existe un error de formato que impide mostrar cualquier palabra luego del espacio, es decir, de una oración solo se mostrará la primera palabra. Esto se puede trabajar ingresando las oraciones con, por ejemplo, un guión bajo simulando el espacio, pero es entendible que esto no es lo ideal para quien esté usando el programa.
- Al seleccionar la opción 2 (Mostrar datos punto de interés), solo mostrará los tres primeros datos del punto que seleccionamos: nombre, tipo y dirección. No importará en que formato se ingrese el horario, este siempre mostrará un espacio en blanco después de ":". Esto genera un problema también al mostrar la descripción del punto, ya que va después del horario.


Contribuciones:

Francisco Quiroga (3/3):
- Diseño de los struct requeridos para emplear los puntos de la tarea.
- Esqueleto de las funciones de TDA.
- Diseño de las funciones crear lista, crear mapa, insertar, buscar, además de las funciones necesarias para trabajar con una lista.
- Diseño preliminar de las funciones necesarias para la tarea (sin aplicar TDA), para proceder a realizar sutiles cambios pero manteniendo una estructura base en cada de ellas.

Felipe Núñez (3/3):
- Comentarios de funciones.
- Construcción de archivo README.
- Corrección de errores de punteros en función mostrarTuristasPorPaís.
- Identificación de errores de formato de entrada en funciones específicas.
