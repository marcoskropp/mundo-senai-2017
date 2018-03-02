// Programa : Controlando o servo com 3 chaves
// Autor: Arduino e Cia

#include <Servo.h>

Servo myservo;
Servo m;


int val;
int ChaveEsquerda = 3; //Pino a ser ligado na chave esquerda
int ChaveCentral = 2; //Pino a ser ligado na chave central

void setup()
{
  // Pino de dados do servo conectado ao pino 9 do Arduino
  myservo.attach(9);
  m.attach(8);
  //Define o pino como entrada
  pinMode(ChaveEsquerda, INPUT);
  //Aciona o resistor pull-up interno
  digitalWrite(ChaveEsquerda, HIGH);
  pinMode(ChaveCentral, INPUT);
  digitalWrite(ChaveCentral, HIGH);
}

void loop()
{
  //Le o valor da Chave Esquerda (On/Off)
  val = digitalRead(ChaveEsquerda);
  //Caso a chave seja pressionada, movimenta o servo
  if (val != 1)
  {

    myservo.write(0);  //Move o servo para o angulo de 60 graus
    m.write(0);  //Move o servo para o angulo de 60 graus
    delay(150);
    myservo.write(90);  //Move o servo para o angulo de 60 graus
    m.write(90);  //Move o servo para o angulo de 60 graus


  }

  val = digitalRead(ChaveCentral);
  if (val != 1)
  {
    myservo.write(120);  //Move o servo para o angulo de 90 graus
    m.write(120);  //Move o servo para o angulo de 60 graus

    delay(15);

    myservo.write(90);
    m.write(90);  //Move o servo para o angulo de 60 graus



  }

}
