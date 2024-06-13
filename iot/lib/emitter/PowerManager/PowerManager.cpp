//
// Created by clement.mathe on 12/04/2024.
//

#include "PowerManager.h"


void PowerManager::init() {
    esp_sleep_enable_timer_wakeup(WAKE_UP_BOARD_DELAY);
    pinMode(GPIO_PIN4_WAKEUP_ENABLE_S, INPUT);
}

void PowerManager::start() {
    esp_deep_sleep_start();
}
