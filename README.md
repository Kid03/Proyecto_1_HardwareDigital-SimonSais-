# Proyecto_1_HardwareDigital-SimonSays-
Incorporar a un proyecto de base, hardware y software para ampliar su funcionalidad.

.-------------- Funciones --------------.

loseSequence(): Avisa al jugador que perdió, encendiendo los leds de colores y ejecutando un pequeño sonido. Posteriormente verifica que ningún botón esté presionado, de lo contrario se inicia un nuevo juego reestableciendo las variables. 

buttonCheck(): Entrega un entero, indicando que botón fue presionado(0;1;2;3). En el caso de que no presionará ningún botón, se entregará el entero (4).

allLeDoff(): Como indica el su nombre apaga las luces led con los que el jugador interactúa.

flashLED():Enciende el LED entregado, y ejecuta el sonido predeterminado para ese  LED.

winSequence():Indica al jugador que ganó, encendiendo todos los LEDs y ejecutando una canción de victoria, luego verifica que ningún botón esté presionado, para que al presionarlo se incie una partida.

startSequence():Asegurandoce que el numero random es realmente random. Guarda en la lista "buttonSequence" la secuencia que tendra que memorizas el usuario.
        Luego de crear la secuencia aleatoria, enciende 4 veces las luces indicando que comenzo el juego.

loop(): Se verifica si el juego aún no se ha comenzado. Se reinician el contador de Round, y comienza el juego. Cada ronda muestra la secuencia que el jugador debe imitar paulatinamente. Se verifica si el jugador sigue la secuencia; Si presionó un botón errado se ejecuta loseSequence() ; Si no se presionó ningún botón se verifica si el jugador pasó sobre el tiempo de respuesta, Si es así, se ejecuta loseSequence() ; En el caso de llegar a 16 Round ganadas, se dá por finalizado ejecutando winSequence().

setup():Declaración de pines y sus modos.
