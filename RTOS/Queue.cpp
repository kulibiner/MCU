/*
* Contoh penggunaan QUEUE pada RTOS ESP32
* 
*/

#include <Arduino.h>

// Buat Object Queue bernama queue
QueueHandle_t queue;

// Buat task pengirim
// Looping setiap 200ms
void TaskSend(void* param) {
    int counter = 0;
    while(true) {
        counter++;

        xQueueSend(queue, &counter, portMAX_DELAY);

        Serial.print("Kirim :");
        Serial.println(counter);

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

// Task Penerima
// Bekerja langsung ketika menerima queue
void TaskReceive(void* param) {
    int counter = 0;
    while(true) {
        if(xQueueReceive(queue, &counter, portMAX_DELAY)) {
            Serial.print("Terima :");
            Serial.println(counter);
        }
    }
}

void setup() {
    Serial.begin(115200);

    // Set objecy queue
    queue = xQueueCreate(10, sizeof(int));
    //                   |       |
    //                   |       └---------- Besarnya data yang dikirim
    //                   └------------------ Jumlah antrian

    xTaskCreate(TaskSend, "Task pengirim", 2048, NULL, 1, NULL);
    xTaskCreate(TaskReceive, "Task penerima", 2048, NULL, 1, NULL);
}

void loop ()  {

}
