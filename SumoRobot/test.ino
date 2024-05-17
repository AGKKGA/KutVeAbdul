#include <QTRSensors.h>

// Создаем объект QTRSensors
QTRSensors qtr;

const uint8_t SensorCount = 1;
uint16_t sensorValues[SensorCount];
const uint8_t QTRSensorPin = 8;

void setup() {
  // Инициализируем датчик QTR
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ QTRSensorPin }, SensorCount);
}

void loop() {
  // Читаем значение с датчика
  qtr.read(sensorValues);
  
  // Определяем цвет: если значение сенсора меньше порогового, то это черный, иначе - белый
  if (sensorValues[0] < 500) {
    // Черный цвет
    Serial.println("Черный");
  } else {
    // Белый цвет
    Serial.println("Белый");
  }
  
  delay(250); // небольшая задержка перед следующим чтением
}