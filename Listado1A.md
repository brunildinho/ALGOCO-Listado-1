Listado 1: TDAs [CC]  Aug 20, 2026

# **Problem 1A. Game of Throwns**

**Time Limit** 1000 ms | **Mem Limit** 1048576 kB | **OS** Linux

Daenerys suele inventar juegos para enseñar a sus alumnos de segundo grado de Informática diversos aspectos de la disciplina. Para la lección de esta semana, pide a los niños que formen un círculo y se lancen (con cuidado) un huevo de dragón petrificado.

Los _n_ niños están numerados del 0 al _n_ −1 (al fin y al cabo, es una clase de Informática) en sentido horario alrededor del círculo. El niño 0 comienza siempre con el huevo. Daenerys puede indicar una de estas dos acciones:

1. Un número _t_, que indica que el huevo debe lanzarse al niño que se encuentra a _t_ posiciones en sentido horario respecto a quien tiene el huevo en ese momento (dando la vuelta al círculo si es necesario). Si _t_ es negativo, el lanzamiento se realiza en sentido antihorario.

2. La instrucción `undo` _m_, que indica que deben deshacerse los últimos _m_ lanzamientos. Cabe destacar que los comandos `undo` nunca deshacen otros comandos `undo`; solo revierten los lanzamientos descritos en el punto 1.

Por ejemplo, si hay varios niños y la profesora indica la secuencia de comandos `8 -2 3 undo 2`, los lanzamientos irán del niño 0 al 3, luego del 3 al 1 y, a continuación, del 1 al 4. Tras esto, la instrucción `undo 2` hará que el huevo regrese del niño 4 al 1 y, posteriormente, del 1 al 3. Si Daenerys indica 0 (o _n_, −_n_, 2_n_, −2_n_, etc.), el niño que tiene el huevo simplemente lo lanza hacia arriba y (con cuidado) vuelve a atraparlo.

Daenerys necesita un pequeño programa que determine dónde terminará el huevo si sus instrucciones se ejecutan correctamente. No preguntes qué les pasa a los niños si esto no es así.

## **Input**

La entrada consta de dos líneas. La primera línea contiene dos números enteros positivos, _n_ y _k_ (1 ≤ _n_ ≤ 30, 1 ≤ _k_ ≤ 100), que indican el número de niños y la cantidad de comandos de lanzamiento que Daenerys ordena, respectivamente. La siguiente línea contiene los comandos de lanzamiento. Cada comando consiste, o bien en un número entero _p_ (−10.000 ≤ _p_ ≤ 10.000) que indica cuántas posiciones debe desplazarse el huevo en sentido horario, o bien en la instrucción `undo` _m_ (_m_ ≥ 1), que indica que se deben deshacer los últimos _m_ lanzamientos. Daenerys nunca pide a los niños que deshagan movimientos más allá del inicio del juego.

## **Output**

Muestra el número del niño que tiene el huevo al finalizar el juego.

## **Sample 1**

|Input|Output|
|---|---|
|`5 4`<br>`8 -2 3 undo 2`|`3`|

## **Sample 2**

|Input|Output|
|---|---|
|`5 10`<br>`7 -3 undo 1 4 3 -9 5 undo 2 undo 1 6`|`2`|





