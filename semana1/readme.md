Primer programa
Configurar una salida digital
V1 - Hacer un blink (parpadeo cada 1s) - usando temporizador serie
Montar hardware (resistencia  y led)
V2 del programa. Realizar el parpadeo usando una interrupción de tiempo. Lo necesitáis para el ejercicio 3.
Segundo programa 
Configurar entrada digital (pullup, pulldown)
Realizar evaluación por polling
Escribir mensaje por consola, cuando se produzca (dos programas)
Flanco de subida
Flanco de bajada
Programa tres
V1 - Unir los dos anteriores para encender y apagar el led, con cada pulsación.
V2 - La versión v1 la podéis realizar realizando polling sobre el pulsador, pero en la V2 lo váis a realizar usando una interrupción, para atender al evento de pulsado
TIP: 
Para desarrollar este ejercicio necesitas usar una interrupción para atender la pulsación.
Otra interrupción asociada a un timer para evitar el rebote del pulsador
Programa cuatro.
Activar o desactivar el blink con cada pulsación.
TIP: Introducir el concepto de modo de funcionamiento 
Problemas:
No hace acciones en paralelo:
Detección de la pulsación
Temporización 
Introducimos el concepto de interrupción
Para evaluar una entrada
Para evaluar un tiempo
Añadir un modo más
apagado, encendido, blink. Los modos van cambiando en cada pulsación
TIP: Tenéis que usar:
interrupción para detectar uno de los flancos en la pulsación
Timer para evitar rebote (150ms - será un timer one-shot)
(opcional)Timer para realizar el blink (este sería de tipo periódico - arrancarlo al empezar al modo, y pararlo cuando vaya al siguiente modo)
