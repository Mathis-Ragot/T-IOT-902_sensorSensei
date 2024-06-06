//#include "SensorApi.h"
//#include "HttpClient.h"

#include "ReceptorApp.h"

ReceptorApp* app;

void setup() {
    app = new ReceptorApp();
}

void loop() {
    app->loop();
}

//constexpr int WAITING_WIFI = 100;

//void init_wifi() {
//    WiFiClass::mode(WIFI_STA); //Optional
//    WiFi.begin("OPPOa", "d6wf2yng");
//    Serial.println("\nConnecting");
//#pragma unroll
//    while(WiFiClass::status() != WL_CONNECTED){
//        Serial.print(".");
//        delay(WAITING_WIFI);
//    }
//
//    Serial.println("\nConnected to the WiFi network");
//    Serial.print("Local ESP32 IP: ");
//    Serial.println(WiFi.localIP());
//}

//void setup() {
//    Serial.begin(MONITOR_SPEED);
//    init_wifi();
//
//    SensorApi sensorApi(std::make_shared<HttpClient>(), "https://3c7e-163-5-23-29.ngrok-free.app");
//    tl::optional<Measure> dust = createMeasure(std::vector<String>{"10.2", "12.25"}, "dust");
//    if (dust.has_value()) {
//        sensorApi.addMeasure(dust.value());
//    }
//    auto temperature = createMeasure("18.56", Temperature);
//    sensorApi.addMeasure(temperature);
//    const auto [sendResult, sendError] = sensorApi.send();
//    if (sendResult == Success) {
//        printf("Measures sent successfully\n");
//    } else {
//        const auto [body, code] = sendError;
//        printf("Failed to send measures: %d - %s\n", code, body.c_str());
//    }
//    const auto [measureResult, getError, measures] = sensorApi.getMeasures();
//    if (measureResult == Success) {
//        printf("Measures received successfully\n");
//    } else {
//        auto [body, code] = getError;
//        printf("Failed to get measures: %s\n", body.c_str());
//    }
//    for (const Measure &measure: measures) {
//        printf("Measure type: %u\n", measure.kind);
//        printf("Measure value: %s\n", measure.value[0].c_str());
//    }
//}
//
//void loop() {
//
//}