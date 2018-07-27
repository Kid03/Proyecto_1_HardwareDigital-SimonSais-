int button[] = {2,4,6,8}; //rojo es button[0], verde es button[1], azul es button[2], amarillo es button[3]
int led[] = {3,5,7,9}; //rojo es led[0], verde es led[1], azul es led[2], amarillo es led[3]
int tones[] = {262, 330, 392, 494}; //tonos para tocar segun el boton apretado(c, e, g, b)
int roundsToWin = 10; //numero de rondas para ganar(soporta un maximo de 16 rondas)
int buttonSequence[16]; // listado de colores que el usuario debera memorizar para ganar 
int buzzerPin = 10; //pin donde el buzzer esta conectado
int pressedButton = 4; //variable que recuerda el boton pulsado, si es 4 significa que ningun boton.
int roundCounter = 1; //contador de rondas.
long startTime = 0; // variable de tiempo limite para precionar un botton
long timeLimit = 2000; //tiempo limite para precionar un boton
boolean gameStarted = false; //variable que guarda el estado del juego.

void setup(){
  //se declaran los pines para los botones como input_pullup. 
  pinMode(button[0], INPUT_PULLUP);
  pinMode(button[1], INPUT_PULLUP);
  pinMode(button[2], INPUT_PULLUP);
  pinMode(button[3], INPUT_PULLUP);
  //se declaran los pines de los leds y buzzer como OUTPUT
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(buzzerPin, OUTPUT); //Establecer el buzzer para salida
}
void loop(){
  if (gameStarted == false){ //Si el juego aún no ha comenzado .
    startSequence(); //flash de comienzo de juego.
    roundCounter = 0;//reinicia el contador a 0.
    delay(1500);
    gameStarted = true; //Cambiamos el estado del juego a true.
  }
  //Cada ronda, comienza mostrando la secuencia que se repetirá.
  for(int i=0; i <= roundCounter; i++){ // Va atraves del arreglo, hasta el número de rondas actual.
    flashLED(buttonSequence[i]); //Se enciende el LED en la posición pedida, reproduciendo el sonido.
    delay(200); /Espera
    allLEDoff(); //Apaga todo los LEDs
    delay(200);
  }
  //Comiensa a recorrer la secuencia de a uno por vez y ve si el usuario presiona el botón correcto.
  for(int i=0; i <= roundCounter; i++){ //Para cada botón a presionar en la secuencia.
    startTime = millis(); //Registra la hora de inicio.
    while(true){ //Se crea un bucle hasta que el jugador presiona un botón o el límite de tiempo se acaba. (la verificación de límite de tiempo está en una declaración if)
      pressedButton = buttonCheck(); //Se guarda cada ves que se presiona un botón botón.
      if (pressedButton < 4){ //Se verifica si se presionó el botón indicado con un número entero.("4" si no se presionó ningún botón).
        flashLED(pressedButton); //parpadea el LED del botón que se presionó
        if(pressedButton == buttonSequence[i]){ //Pregunta si el botón coincide con la secuencia.
          delay(250); //Deja la luz LED encendida por un momento.
          allLEDoff(); //Deja la luz LED encendida por un momento.
          break; //Finaliza el ciclo while (esto irá al siguiente número en el ciclo for).
        }
        else{ //Si no coincide con el botón de la secuencia
          loseSequence(); //Es hora de que la función loseSequence funcione (descrita en el informe). 
          break; //Cuando el programa regrese de la secuencia de pérdida, rompa el ciclo while para que el juego pueda comenzar de nuevo.
        }
      }
      else { //Si no se presiona ningún botón
        allLEDoff(); //Apaga todos los LEDs
      }
      //Verifique si el límite de tiempo está activo.
      if(millis() - startTime > timeLimit){ //Si el está sobre el tiempo limite.
        loseSequence(); //Funciona loseSequence();
        break; //Cuando el programa regrese de la secuencia de pérdida, rompa el ciclo while para que el juego pueda comenzar de nuevo.
      }
    }
  }
  roundCounter = roundCounter + 1; //Aumentar el número de ronda en 1.
  if (roundCounter >= roundsToWin){ //Si el jugador llega a la ronda 16.
    winSequence(); //Toca la canción ganadora.
  }
  delay(500); //Espera medio segundo entre ronda.
}
//----------FUNCTIONS------------
//FLASH LED
void flashLED (int ledNumber){
  digitalWrite(led[ledNumber], HIGH);
  tone(buzzerPin, tones[ledNumber]);
}

//TURN ALL LEDS OFF
void allLEDoff (){
  //apaga todos los LED
  digitalWrite(led[0],LOW);
  digitalWrite(led[1],LOW);
  digitalWrite(led[2],LOW);
  digitalWrite(led[3],LOW);
  //Apaga el buzzer.
  noTone(buzzerPin);
}
//COMPRUEBA CUANDO SE PRESIONA EL BOTÓN
int buttonCheck(){
  //Comprueba si se presionan algunos botones.
  if(digitalRead(button[0]) == LOW){
    return 0;
  }
  else if(digitalRead(button[1]) == LOW){
    return 1;
  }else if(digitalRead(button[2]) == LOW){
    return 2;
  }else if(digitalRead(button[3]) == LOW){
    return 3;
  }else{
    return 4; //Este será el valor que significará que no se a presionado ningún botón.
  }
}
//START SEQUENCE
void startSequence(){
  randomSeed(analogRead(A0)); //Se asegura que todos los números sean aleatorios.
  //Llena el arreglo de numeros aleatorios entre 0 y 3.
  for (int i=0;i<=roundsToWin;i++){
    buttonSequence[i] = round(random(0,4));
  }
  //Parpadea todos los LED cuando comience el juego.
  for(int i=0; i<=3; i++){
    tone(buzzerPin, tones[i], 200); //Toca 1 de los 4 tonos.
    //turn all of the leds on
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
    digitalWrite(led[2],HIGH);
    digitalWrite(led[3],HIGH);
    delay(100); //Espera un momento.
    //Apaga todos los LEDs
    digitalWrite(led[0],LOW);
    digitalWrite(led[1],LOW);
    digitalWrite(led[2],LOW);
    digitalWrite(led[3],LOW);
    delay(100); //Espera un momento.
  } //Esto se repetira 4 veces
}
//WIN SEQUENCE
void winSequence(){
  //Enciende todos los LEDs.
  for(int j=0; j<=3; j++){
    digitalWrite(led[j], HIGH);
  }
  //Toca la primera melodia.
  tone(buzzerPin, 1318, 150); //E6
  delay(175);
  tone(buzzerPin, 1567, 150); //G6
  delay(175);
  tone(buzzerPin, 2637, 150); //E7
  delay(175);
  tone(buzzerPin, 2093, 150); //C7
  delay(175);
  tone(buzzerPin, 2349, 150); //D7
  delay(175);
  tone(buzzerPin, 3135, 500); //G7
  delay(500);
  //Espera hasta que se presione el botón.
  do {
    pressedButton = buttonCheck();
  } while(pressedButton > 3);
  delay(100);
  gameStarted = false; //Reinicia el juego para que la secuencia de inicio se reproduzca nuevamente.
}
//LOSE SEQUENCE
void loseSequence(){
  //Enciende todos los LEDs.
  for(int j=0; j<=3; j++){
    digitalWrite(led[j], HIGH);
  }
  //Toca la melodia.
 
  tone(buzzerPin, 130, 250); //E6
  delay(275);
  tone(buzzerPin, 73, 250); //G6
  delay(275);
  tone(buzzerPin, 65, 150); //E7
  delay(175);
  tone(buzzerPin, 98, 500); //C7
  delay(500);
  aux();
   noTone(buzzerPin);
  //Espera hasta que se presione el botón.
  do {
    pressedButton = buttonCheck();
  } while(pressedButton > 3 );
  delay(200);
  gameStarted = false; //Reinicia el juego para que la secuencia de inicio se reproduzca nuevamente.
}

void aux(){
  for(int i=0; i<roundCounter; i++){
    digitalWrite(11, HIGH);
    tone(buzzerPin, 65, 150);
    delay(400);
    digitalWrite(11, LOW);
    delay(200);
    }
  }
