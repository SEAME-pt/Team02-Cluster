#include <CAN.h>
#include <Stepper.h>

const int stepsPerRevolution = 1000;
Stepper myStepper(stepsPerRevolution, 7, 6, 5, 4);

// Configuração do sensor de velocidade
const int sensorPin = 3; // Pino onde o sensor está conectado
volatile unsigned int pulseCount = 0;
unsigned long previousMillis = 0;
const int pulsesPerRotation = 20; // Número de pulsos por rotação
float wheelCircumference = 0.067; // Circunferência da roda em metros
float speed = 0.0; // Velocidade em m/s

void countPulse() {
  pulseCount++; // Incrementa os pulsos
}

void setup() {

  //motor
  myStepper.setSpeed(16);
  Serial.begin(9600);
  Serial.println("Iniciando o Motor de Passo...");
  // -----------------------------------------

  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, RISING);


  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  float speedKmH = 0.0;
  if (currentMillis - previousMillis >= 1000) { // Atualiza a cada 1 segundo
    noInterrupts();
    unsigned int pulses = pulseCount;
    pulseCount = 0; // Reseta o contador
    interrupts();

    // Calcula a velocidade em m/s
    speed = (pulses / (float)pulsesPerRotation) * wheelCircumference;

    // Converte para km/h
    speedKmH = speed * 3.6;

    // Exibe no Serial Monitor
    Serial.print("Velocidade: ");
    Serial.print(static_cast<int>(speedKmH * 100));
    Serial.println(" km/h");

    previousMillis = currentMillis;
  }

  // Envia a velocidade pelo barramento CAN
  Serial.print("Enviando velocidade CAN ... ");
  CAN.beginPacket(0x12);
  CAN.print(static_cast<int>(speedKmH * 100));
  CAN.endPacket();

  // Motor de passo roda no sentido horário
  myStepper.step(stepsPerRevolution / 10); // Pequeno movimento para cada ciclo
}