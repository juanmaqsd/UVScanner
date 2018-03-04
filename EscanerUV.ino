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

int vueltas = 0; // Contador de vueltas completas que da el motor
boolean ok;
int distancia; // Ancho de la placa.
int estado = 0; // Da el OK para pasar a la siguiente fase.
int contador = 0;
int sentido = 0;


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

}



void loop() {


  switch (estado) {

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
      if (!digitalRead(botonOk)) {
        if (contador = 0) {
          vueltas = 0;
          contador++;
        }
        else {
          if (vueltas < 0) {
            distancia = abs(vueltas);
            sentido = 1;
            estado = 1;
          } else {
            distancia = vueltas;
            sentido = 0;
          }
        }
      }

      delay(500);
      break;

    case 1: //Mover leds

      digitalWrite(Led, HIGH);
      delay(4000);

      digitalWrite(LedsUV, HIGH);
      delay(1000);

      if (sentido = 0) {

        for (int i = 0; i < 16; i++) {

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
        for (int i = 0; i < 16; i++) {

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
      estado = 0;

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
