/*
* Contoh penggunaan Mutex pada RTOS ESP32
* 
*/

#include <Arduino.h>

// Buat object Mutex bernama mtx
SemaphoreHandle_t mtx;

// Buat fungsi yang di proteksi oleh mutex
void printData(String caller, int val) {
    // Ambil Mutex
    if(xSemaphoreTake(mtx, portMAX_DELAY)) {
        unsigned long nowMillis = millis();

        Serial.print("[");
        Serial.print(caller);
        Serial.print("] Value :");
        Serial.print(val);
        Serial.print(", ");
        Serial.println(nowMillis);

        // Lepas Mutex
        xSemaphoreGive(mtx);
    }
}

// Buat sebuah Task untuk memanggil fungsi printData
// TaskA : Looping setiap 500ms
void TaskA(void* param) {
    int a = 0;
    while(true) {
        printData("Task 1", a);
        a++;
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

// Buat sebuah Task untuk memanggil fungsi printData
// TaskB : Looping setiap 700ms
void TaskB(void* param) {
    int a = 0;
    while(true) {
        printData("Task 2", a);
        a += 2;
        vTaskDelay(700 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);

    // Simpan handle mutex kedalam object
    mtx = xSemaphoreCreateMutex();

    // Buat task 
    xTaskCreate(TaskA, "TaskA", 2048, NULL, 1, NULL);
    xTaskCreate(TaskB, "TaskB", 2048, NULL, 1, NULL);

    // Buat Task dalam core yang sama
    // xTaskCreate(Fungsi_Task, "Nama_Task", Stack_Size, NULL, Priority, NULL);
    //                |             |            |        |        |       |
    //                |             |            |        |        |       └- Task Handle
    //                |             |            |        |        └--------- Prioritas Task                                                            └
    //                |             |            |        └------------------ Parameter        
    //                |             |            └--------------------------- Stack Size (Memory)        
    //                |             └---------------------------------------- Nama Task        
    //                └------------------------------------------------------ Fungsi yang dijadikan task        

    // Buat Task dalam core yang berbeda
    // xTaskCreatePinnedToCore(Fungsi_Task, "Nama_Task", Stack_Size, NULL, Priority, NULL, 0);
    //                             |             |            |        |        |      |   |
    //                             |             |            |        |        |      |   └- Core 
    //                             |             |            |        |        |      └----- Task Handle
    //                             |             |            |        |        └------------ Prioritas Task                                                            └
    //                             |             |            |        └--------------------- Parameter        
    //                             |             |            └------------------------------ Stack Size (Memory)        
    //                             |             └------------------------------------------- Nama Task        
    //                             └--------------------------------------------------------- Fungsi yang dijadikan task  
}

void loop ()  {

}
