#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "SSID_WIFI_MU";
const char* pswd = "PASSWORD_WIFI_MU";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html>
        <head>
            <title>Muhammad Daffa</title>
        </head>
        <body>
            <p>
                Anda terkoneksi ke %ssid%
            </p>
        </body>
    </html>
)rawliteral";

String processor(const String& var) {
    if(var == "ssid") {
        return ssid;
    }
}

void setup(){
    // Memulai Serial
    Serial.begin(115200);

    Serial.println();
    Serial.print("Connecting to : ");
    Serial.println(ssid);

    WiFi.begin(ssid, pswd);

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }    

    Serial.println();
    Serial.println("Connected !");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest  *request){
        request->send_P(200, "text/html", index_html, processor);
    });

    server.begin();
}

void loop(){
    
}