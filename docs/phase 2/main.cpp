// Plateformio.ini
[env:lilygo-t-display-s3]
platform = espressif32
board = lilygo-t-display-s3
framework = arduino
lib_deps = 
	h2zero/NimBLE-Arduino@^2.3.6
	asukiaaa/XboxSeriesXControllerESP32_asukiaaa@^1.1.1

// main.cpp
#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

#define RPI_TX 17
#define RPI_RX 2

// Tache Xbox
void XboxTask(void *pvParameters) {
  xboxController.begin();
  Serial.println("En attente manette Xbox...");

  for (;;) {
    xboxController.onLoop();

    if (xboxController.isConnected() && !xboxController.isWaitingForFirstNotification()) {
      auto &notif = xboxController.xboxNotif;

      int16_t joyV = notif.joyLVert;
      int16_t joyH = notif.joyLHori;

      // Deadzone
      if (abs(joyV) < 200) joyV = 0;
      if (abs(joyH) < 200) joyH = 0;

      // Normalisation -100 a 100
      int linear  = constrain(map(joyV, -32767, 32767, -100, 100), -100, 100);
      int angular = constrain(map(joyH, -32767, 32767, -100, 100), -100, 100);

      // Calcul vitesses moteurs
      int left  = constrain(linear - angular, -100, 100);
      int right = constrain(linear + angular, -100, 100);

      // Envoi au RPi via UART
      String cmd = String(left) + "," + String(right) + "\n";
      Serial2.print(cmd);
      Serial.println(cmd);
    }

    vTaskDelay(pdMS_TO_TICKS(20)); // 50 Hz
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RPI_RX, RPI_TX);
  Serial.println("Demarrage ESP32...");
  xTaskCreatePinnedToCore(XboxTask, "XboxTask", 4096, NULL, 1, NULL, 0);
}

void loop() {
  vTaskDelay(1);
}
