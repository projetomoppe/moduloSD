#include <NewPing.h>
#include <SdFat.h>

SdFat sdCard;
SdFile meuArquivo;

// Pino ligado ao CS do modulo
const int echoPin = 4;
const int trigPin = 5;
const int chipSelect = 6;
const int potPin = A5;
const int botaoPin = 7;

int valorPot = 0;
int valorBot = 0;
float distancia = 0.0;
long microsec = 0;

NewPing sonar(trigPin, echoPin, 100);

void setup()
{
  Serial.begin(9600);
  // Define o pino do potenciometro como entrada
  pinMode(A5, INPUT);
  pinMode(7, INPUT);  

  // Inicializa o modulo SD
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
  // Abre o arquivo
  if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
  {
    sdCard.errorHalt("Erro na abertura do arquivo!");
  }
}

void loop()
{
  microsec = sonar.ping_median();
  distancia = sonar.convert_cm(microsec);

  // Leitura da porta A5/Potenciometro
  valorPot = analogRead(potPin);
  Serial.print("Leitura ultra: ");
  Serial.println(distancia);
  Serial.print("Leitura pot: ");
  Serial.println(valorPot);

  // Grava dados
  meuArquivo.print("Leitura ultra: ");
  meuArquivo.println(distancia);
  meuArquivo.print("Leitura pot: ");
  meuArquivo.println(valorPot);

  valorBot = digitalRead(botaoPin);
  if (valorBot == 1)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("Processo de gravacao interrompido. Retire o SD!");
    meuArquivo.close();
    while (1) {
    }
  }
}
