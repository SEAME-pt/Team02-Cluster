// #include <CAN.h>

// void onReceive(int packetSize);
// #define LED_PIN 3

// void setup() {
//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, LOW); 
//   Serial.begin(9600);
//   while (!Serial);

//   Serial.println("CAN Receiver Callback");

//   // start the CAN bus at 500 kbps
//   if (!CAN.begin(500E3)) {
//     Serial.println("Starting CAN failed!");
//     while (1);
//   }

//   // register the receive callback
//   CAN.onReceive(onReceive);
// }

// void loop() {
//   // do nothing
// }

// void onReceive(int packetSize) {
//   // received a packet
//   Serial.print("Received ");

//   if (CAN.packetExtended()) {
//     Serial.print("extended ");
//   }

//   if (CAN.packetRtr()) {
//     // Remote transmission request, packet contains no data
//     Serial.print("RTR ");
//   }

//   Serial.print("packet with id 0x");
//   Serial.print(CAN.packetId(), HEX);

//   if (CAN.packetRtr()) {
//     Serial.print(" and requested length ");
//     Serial.println(CAN.packetDlc());
//   } else {
//     Serial.print(" and length ");
//     Serial.println(packetSize);

//     // only print packet data for non-RTR packets
//     while (CAN.available()) {
//       Serial.print((char)CAN.read());
//     }
//     Serial.println();
//   }

//   Serial.println();

//   digitalWrite(LED_PIN, HIGH); // Liga o LED
//   delay(1000); // Mantém o LED ligado por 100 ms
//   digitalWrite(LED_PIN, LOW); 
// }


#include <CAN.h>

void onReceive(int packetSize);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  CAN.onReceive(onReceive);
}

void loop() {
  // if (CAN.available()) {
  //   float speed = 0;
  //   int packetSize = CAN.packetDlc();

  //   if (packetSize == sizeof(speed)) {
  //     CAN.readBytes((byte*)&speed, sizeof(speed));
  //     Serial.print("Received Speed: ");
  //     Serial.print(speed);
  //     Serial.println(" RPM");
  //   }
  // }
}

void onReceive(int packetSize) 
{
  Serial.print("Received ");
  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }

  if (CAN.packetRtr()) {
    Serial.print("RTR ");
  }

  Serial.print("packet with id 0x");
  Serial.print(CAN.packetId(), HEX);

  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  } else {
    Serial.print(" and length ");
    Serial.println(packetSize);

    // while (CAN.available()) {
    //   Serial.print("valor:");
    //   Serial.print((char)CAN.read());
    // }
    char charValue = '\0'; // Inicializa com valor nulo
    if (CAN.available()) {
      charValue = (char)CAN.read(); // Lê um caractere do CAN
      Serial.print("Received char: ");
      Serial.println(charValue); // Imprime o caractere recebido
    }

    // Converte o caractere para número, se for um dígito
    //if (charValue >= '0' && charValue <= '9') {
    int numericValue = charValue - '0'; // Converte caractere para número
    Serial.print("Converted numeric value: ");
    Serial.println(numericValue);

    // Verifica se o número é 2 ou 4
    if (numericValue > 0) {
      pinMode(3, OUTPUT);
      digitalWrite(3, HIGH); // Liga o LED
      delay(1000); // Mantém o LED ligado por 1 segundo
      digitalWrite(3, LOW); // Desliga o LED
      Serial.println("LED blinked!");
    }
    //}
  }

  Serial.println();
}
