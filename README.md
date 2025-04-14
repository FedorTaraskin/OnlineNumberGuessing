# Descripción

Este repositorio consiste de dos proyectos (es decir, dos ejecutables): Cliente y Servidor. El programa consiste en varios jugadores (clientes) intentando adivinar un numero aleatorio que el servidor ha elegido. El jugador que adivine el número primero gana.

Se puede crear varias salas de juego, llamadas "lobby". El jugador que cree una sala de juego elige el rango de números y el nombre de la sala.

Sólo se permite ejecutar un cliente por red local, pero teoriticamente infinitos clientes. (Nota: el servidor no está optimizado para > 1000 clientes.)

Los comentarios están en inglés, y el código utiliza dos submódulos; ASIO y cereal. Este primero se utiliza para la comunicación por red a nivel bajo, mientras que cereal se encarga que los datos enviados de un ordenador se interpreten bien en el otro.

# Compilación

Una vez este trabajo esté más o menos en un estado jugable, habrán ejecutables disponibles pre-compilados. Sin embargo, si quieres compilarlo tú mismo vas a necesitar premake5.
