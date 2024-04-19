#include <vector>
#include "App.h"
#include <GP2YDustSensor.h>
#include <hal/adc_types.h>
#include <driver/adc_common.h>

App *app;


//const uint8_t SHARP_LED_PIN = 14;   // Sharp Dust/particle sensor Led Pin
//const uint8_t SHARP_VO_PIN = 4;    // Sharp Dust/particle analog out pin used for reading
//
//GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);


void setup() {
    app = new App();

//    dustSensor.setBaseline(0.4); // set no dust voltage according to your own experiments
//    dustSensor.setCalibrationFactor(1.1); // calibrate against precision instrument
//    dustSensor.begin();


}

void loop() {
    app->loop();

//    Serial.print("Dust density: ");
//    Serial.print(dustSensor.getDustDensity());
//    Serial.print(" ug/m3; Running average: ");
//    Serial.print(dustSensor.getRunningAverage());
//    Serial.println(" ug/m3");
//    delay(200);
//



}







