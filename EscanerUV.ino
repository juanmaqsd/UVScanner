//Constantes

//Led indicador
#define Led  4

//Barra de Leds UV
#define LedsUV 5

//Botones
#define botonMas 6
#define botonMenos 7
#define botonOk 8

//Pines del motor paso a paso
#define motorPin1 9
#define motorPin2 10
#define motorPin3 11
#define motorPin4 12

//Determina la velocidad (milisegundos) del motor paso a paso:
#define delayTime 5


//Variables

// Secuencia de pasos hacia adelante
int pasoAdelante [4][4] =
{
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};

// Secuencia de pasos hacia atras
int pasoAtras [4][4] =
{
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 1, 0, 0},
  {1, 0, 0, 0}
};

int vueltas = 0;                              // Contador de vueltas completas que da el motor.
int distancia;                                // Ancho de la placa.
int fase = 0;                                 // Indica en qué fase del programa nos encontramos (Búsqueda de límites fase = 0; Barrido automático fase = 1).
int ok = 0;                                   // Para detectar si es la primera o segunda vez que pulsamos el botón OK.
int sentido = 0;                              // Sentido en el que debe girar primero el motor.


void setup() {

  //Salidas
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(LedsUV, OUTPUT);
  pinMode(Led, OUTPUT);

  //Entradas
  pinMode(botonMas, INPUT);
  pinMode(botonMenos, INPUT);
  pinMode(botonOk, INPUT);

  digitalWrite(13, LOW);                     //El Led 13 se quedaba encendido. Lo apagamos.

}



void loop() {


  switch (fase) {

    case 0:                                     //Ajustar los limites de la placa.
      //Hacia delante
      while (!digitalRead(botonMas)) {
        Adelante();
        vueltas++;
      }


      //Hacia atras
      while (!digitalRead(botonMenos)) {
        Atras();
        vueltas--;
      }

      //Validar
      if (!digitalRead(botonOk)) {      //Primera pulsación del botón OK
        if (ok == 0) {

          vueltas = 0;                  //Inicializamos el contador vueltas
          ok++;
          delay(500);

        } else {                          //Segunda pulsación del botón OK

          if (vueltas < 0) {            //Limites Primero Arriba, luego Abajo
            vueltas = abs(vueltas);
            sentido = 1;
          } else {                      //Limites Primero Abajo, luego Arriba
            sentido = 0;
          }
          delay(500);
          
          ok = 0;
          distancia = vueltas;
          fase = 1;

        }
      }


      break;

      

    case 1:                             //Barrido con leds UV de la superficie

      digitalWrite(Led, HIGH);
      delay(4000);

      digitalWrite(LedsUV, HIGH);
      delay(1000);

      if (sentido == 0) {

        for (int i = 0; i < 15; i++) {

          while (vueltas > 0) {
            Atras();
            vueltas--;
          }

          delay(500);

          while (vueltas < distancia) {
            Adelante();
            vueltas++;
          }

          delay(500);
        }
      } else {
        for (int i = 0; i < 15; i++) {

          while (vueltas > 0) {
            Adelante();
            vueltas--;
          }

          delay(500);

          while (vueltas < distancia) {
            Atras();
            vueltas++;
          }

          delay(500);
        }
      }

      digitalWrite(Led, LOW);
      digitalWrite(LedsUV, LOW);
      fase = 0;

      break;

  }


}





//Función para girar el motor hacia delante una vuelta.
void Adelante() {

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(motorPin1, pasoAdelante[i][0]);
    digitalWrite(motorPin2, pasoAdelante[i][1]);
    digitalWrite(motorPin3, pasoAdelante[i][2]);
    digitalWrite(motorPin4, pasoAdelante[i][3]);
    delay(delayTime);
  }

}


//Función para girar el motor hacia atrás una vuelta.
void Atras() {

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(motorPin1, pasoAtras[i][0]);
    digitalWrite(motorPin2, pasoAtras[i][1]);
    digitalWrite(motorPin3, pasoAtras[i][2]);
    digitalWrite(motorPin4, pasoAtras[i][3]);
    delay(delayTime);
  }

}
