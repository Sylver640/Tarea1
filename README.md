# Tarea1
Nombre de grupo : Showtimers.
Integrantes : Rodrigo Araos.
              Javier Marín.
              Camila Díaz.
              Vicente Mercado.

*Cómo compilar y ejecutar la tarea:

1. Abrir una terminal de perfil "Microsoft Powershell".

2. Una vez cargada la terminal escribir el siguiente código:
gcc -g main.c list.c -o Tarea1 , y luego enter. Esto ayudará a compilar el programa.

3. Una vez terminada la compilación, escribir "./Tarea1" sin las comillas y luego enter, lo
cual efectuará la ejecución del programa
(También puedes abrir directamente el archivo .exe en el directorio donde se guardó).

*Funciones que funcionan correctamente:

-> buscarCancionNombre.
-> buscarCancionArtista.
-> buscarCancionGenero.
-> exportarCanciones.
-> agregarCancion.
-> contarGeneros.
-> mostrarListasRep.
-> eliminar_deListaGlobal.
-> eliminar_cancion.
-> mostrarCancionesListaRep.
-> mostrarTodasLasCanciones.



*Funciones que no funcionan correctamente:

-> importarCanciones: Al agregar los géneros a la canción añadida, no se copian ni se muestran correctamente en los casos donde las canciones importadas del CSV contienen más de un género.
Potencialmente sea un problema proveniente de la función separarGeneros que aún no desciframos.

-> separarGeneros: El problema podría residir al momento de separar los tokens, lo cual no se efectúa correctamente.

*Co-evaluación de grupo:

Rodrigo Araos: Atento en los procedimientos de programación como grupo y asistió a todas las ayudantías y reuniones grupales, también ayudó a pulir las funciones de otros compañeros. Faltó mejor comunicación interna. 

Javier Marín: Encargado de proponer ideas para implementar múltiples funciones, también asiste a todas las reuniones grupales y ayudantías. Faltó mejor comunicación interna.

Camila Díaz: Encargada de dar el primer pié como grupo y programar la función agregarCancion, asiste a todas la reuniones grupales y la mayoría de ayudantías. Faltó mejor comunicación interna.

Vicente Mercado: Responde preguntas internas del grupo y asiste a ayudantías y reuniones grupales. Faltó mejor comunicación interna.

Consenso de grupo: Faltó mejor comunicación y organización de los deberes.

*Puntos de premio/castigo:

Rodrigo Araos : 0
Javier Marín : 0
Camila Díaz : 0
Vicente Mercado : 0

Puntuación total de grupo : 0. 