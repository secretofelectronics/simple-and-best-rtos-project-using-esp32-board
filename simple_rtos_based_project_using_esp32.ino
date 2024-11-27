#include <Arduino.h>

// Pin Definitions
#define LED1_PIN 2  // LED1 pin
#define LED2_PIN 4  // LED2 pin
#define BUTTON_PIN 5 // Push button pin

// Task Handles
TaskHandle_t BlinkLEDTaskHandle;
TaskHandle_t ControlLEDTaskHandle;

// Task to blink LED1 with a 1-second delay
void BlinkLEDTask(void *pvParameters) {
  pinMode(LED1_PIN, OUTPUT);

  while (true) {
    digitalWrite(LED1_PIN, HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);  // Delay 1 second
    digitalWrite(LED1_PIN, LOW);
    vTaskDelay(200 / portTICK_PERIOD_MS);  // Delay 1 second
  }
}

// Task to control LED2 using a push button
void ControlLEDTask(void *pvParameters) {
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);

  while (true) {
    if (digitalRead(BUTTON_PIN) == HIGH) {  // If button is pressed
      digitalWrite(LED2_PIN, HIGH);         // Turn on LED2
    } else {
      digitalWrite(LED2_PIN, LOW);          // Turn off LED2
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);    // Small delay to debounce
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Create RTOS Tasks
  xTaskCreate(
    BlinkLEDTask,       // Task function
    "Blink LED Task",   // Name
    1000,               // Stack size
    NULL,               // Parameters
    1,                  // Priority
    &BlinkLEDTaskHandle // Task handle
  );

  xTaskCreate(
    ControlLEDTask,     // Task function
    "Control LED Task", // Name
    1000,               // Stack size
    NULL,               // Parameters
    1,                  // Priority
    &ControlLEDTaskHandle // Task handle
  );
}

void loop() {
  // Empty loop, tasks are managed by RTOS
}
