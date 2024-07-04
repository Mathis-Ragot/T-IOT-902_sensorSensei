//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorDeviceManager.h"



ReceptorDeviceManager::ReceptorDeviceManager(LoRaClass &loraInstance) :
        dataManager(20),
        deviceInfo(DeviceInfos(RECEPTOR_ID, RECEPTOR_TYPE, RECEPTOR_LOCATION, RECEPTOR_LATITUDE, RECEPTOR_LONGITUDE)) {


    communicationManager = new LoraReceptorManager(loraInstance, dataManager);
    api = new SensorApi(std::make_shared<MyHttpClient>(), SENSOR_API_ENDPOINT);
    wifiManager = new WifiManager(new ArduinoWifiClient());

    dataManager.measures.addMeasure(std::make_shared<measure::DustMeasure>());
    dataManager.measures.addMeasure(std::make_shared<measure::TemperatureMeasure>());
    dataManager.measures.addMeasure(std::make_shared<measure::PressureMeasure>());
    dataManager.measures.addMeasure(std::make_shared<measure::SoundMeasure>());
    dataManager.measures.addMeasure(std::make_shared<measure::HumidityMeasure>());
//    dataManager.measures.addMeasure(std::make_shared<measure::TimeMeasure>());

}

void ReceptorDeviceManager::init() const {
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, false, LORA_FREQUENCY);
    Heltec.display->init();
    Heltec.display->clear();
    Heltec.display->display();

    communicationManager->init();
    communicationManager->connect();

    if (auto wifi_error = wifiManager->initialize()) {
        Serial.println(wifi_error.value().c_str());
    }
}


void ReceptorDeviceManager::loop() {
    std::vector<uint8_t> receivedPacket;
    if (dataManager.dequeuePacket(receivedPacket)) {
        Serial.print("Processing received packet at: ");
        Serial.println(millis());
        processReceivedPacket(receivedPacket);
    }
}

void ReceptorDeviceManager::processReceivedPacket(std::vector<uint8_t> &packet) {

    if(!dataManager.measures.checkAuthId(packet)){
        Serial.println("Authentification failed");
        return;
    }

    dataManager.measures.deserializeMeasureFromBytes(packet);

    // Affiche sur l'écran heltec lora les valeurs des mesures
    Heltec.display->clear();
    int y = 0;
    for (const std::shared_ptr<measure::AbstractMeasure> &measure: dataManager.measures.measures) {
        String value = measure->getDeSerializedMeasure();
        // Affichage des valeurs sur l'écran
        Heltec.display->drawString(2, y, String(measure->getInfos().sensorTypeToString(measure->getInfos().sensorType[0])));
        Heltec.display->drawString(90, y, String(value.c_str()));
        y += 10; // Ajuster l'espacement en fonction de vos besoins

        //Création des données à envoyer sur l'API
       Measure finalMeasure =  createMeasure(value.c_str(), measure->getInfos().getMeasureKind());
        api->addMeasure(finalMeasure);

    }

    Heltec.display->display();
    api->send();




    // Envoi des mesures sur l'API

}

void ReceptorDeviceManager::communicateMeasures() {

}

void ReceptorDeviceManager::communicateInfos() {

}

ReceptorDeviceManager::~ReceptorDeviceManager() {
    delete wifiManager;
    delete api;

}


