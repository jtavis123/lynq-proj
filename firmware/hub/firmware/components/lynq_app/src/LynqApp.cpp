#include "LynqApp.hpp"

#include "BoardPort.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lynq::hub {
namespace {
constexpr const char* kTag = "LYNQ_APP";
}

LynqApp::LynqApp(BoardPort& board) : board_(board) {}

void LynqApp::run() {
    boot_.transitionTo(BootState::BoardInit);
    boot_.transitionTo(BootState::ServicesInit);
    if (!initializeServices()) {
        boot_.transitionTo(BootState::Recovery);
        return;
    }

    boot_.transitionTo(BootState::UiInit);
    if (!initializeUi()) {
        boot_.transitionTo(BootState::Recovery);
        return;
    }

    showSplash();
    showHomeShell();
    boot_.transitionTo(BootState::Ready);

    while (true) {
        board_.service();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

bool LynqApp::initializeServices() {
    ESP_LOGI(kTag, "Core services initialized (scaffold)");
    return true;
}

bool LynqApp::initializeUi() {
    ESP_LOGI(kTag, "LYNQ UI initialized (LVGL adapter pending board BSP merge)");
    return board_.displayReady() && board_.touchReady();
}

void LynqApp::showSplash() {
    ESP_LOGI(kTag, "Splash: LYNQ | Smart Home. Simply Connected.");
}

void LynqApp::showHomeShell() {
    ESP_LOGI(kTag, "Home shell: Home / Devices / Scenes / Learn / Settings");
}

}  // namespace lynq::hub
