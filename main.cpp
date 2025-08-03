/*
Soma atual: 390521.00
Número de medições feitas: 20
Resultado final: 20551.60
Peso de referência: 47g

fator_calibracao = 20551.60/47
fator_calibracao = 437.2680851064
*/

#include <Arduino.h>
#include "HX711.h"

#define CALIBRATION_FACTOR 437.2680851064

// Ligação do HX711 no Arduino
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

float last_reading = 0.0;
float reading;

// Botão para tara da balança
const int TARE_BUTTON_PIN = 7;
HX711 scale;
int button_state;

void setup() {
  Serial.begin(57600);

  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.println("Inicializando a balança.");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Fator de calibração: " + String(CALIBRATION_FACTOR));
  scale.set_scale(CALIBRATION_FACTOR);
  scale.set_calibration(0.982022, 0.378200);
  scale.tare();
  Serial.println("Pronto.");
  delay(1000);
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  }

void loop() {
  if (scale.wait_ready_timeout(200)) {
    button_state = digitalRead(TARE_BUTTON_PIN);
    if (button_state == 1) {
      reading = scale.get_units(10);
      Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\nMedição: ");
      Serial.print(reading);
      Serial.println(" g\t Leitura HX711: " + String(scale.read()));
    } else {
      Serial.println("Zerando a referência da balança.");
      scale.tare();
      Serial.println("Pronto! Agora é só apertar o botão de novo para medir.");
      while (digitalRead(TARE_BUTTON_PIN) == 0) {}
    }
  } else {
      Serial.println("\nHX711 não encontrado.");
    }
/*
  button_state = digitalRead(TARE_BUTTON_PIN);
  if (scale.is_ready()) {
    if (button_state == 1) {
      float it = 0.0;
      while (digitalRead(TARE_BUTTON_PIN) == 1) {
        it = it + 1.0;
        Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.println("Press the button at any time to finish the calibration.");
        Serial.print("Current sum: ");
        Serial.print(avg);
        Serial.print("\tNumber of measurements made: ");
        Serial.println(it);
        avg += tare_fn();
        delay(1000);
        if (digitalRead(TARE_BUTTON_PIN) == 0) {
          Serial.print("\n\nFinal result: ");
          Serial.println(avg/it);
          delay(5000);
        }
      }
    } else {
      Serial.println("Press the button to start the calibration.");
      avg = 0;
      while(digitalRead(TARE_BUTTON_PIN) == 0) {

      }
    }
  } else {
    Serial.println("\nHX711 not found.");
  }
  delay(1000);

  float one = scale.get_units();
  float ten = scale.get_units(10);
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.print("one reading:\t");
  Serial.print(one, 1);
  Serial.print("\t average:\t");
  Serial.println(ten, 5);
  */
}
