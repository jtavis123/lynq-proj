#include "HubOsApp.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
namespace lynq::hub {
namespace { constexpr char kTag[]="LYNQ_HUB_OS"; }
bool HubOsApp::initialize(){
 boot_.addStep({BootStage::Hardware,"Hardware self-test",true,[]{ ESP_LOGI(kTag,"Hardware self-test"); return Result<void>::success(); }});
 boot_.addStep({BootStage::Storage,"Configuration storage",true,[]{ ESP_LOGI(kTag,"Initialize NVS/filesystem"); return Result<void>::success(); }});
 boot_.addStep({BootStage::Display,"Waveshare display",true,[]{ ESP_LOGI(kTag,"Display BSP integration gate"); return Result<void>::success(); }});
 boot_.addStep({BootStage::Touch,"Capacitive touch",true,[]{ ESP_LOGI(kTag,"Touch BSP integration gate"); return Result<void>::success(); }});
 boot_.addStep({BootStage::Network,"Wi-Fi and BLE",false,[]{ ESP_LOGI(kTag,"Network services"); return Result<void>::success(); }});
 boot_.addStep({BootStage::UserInterface,"LYNQ UI",true,[]{ ESP_LOGI(kTag,"Render splash and Home shell"); return Result<void>::success(); }});
 return boot_.run([](const BootProgress&p){ ESP_LOGI(kTag,"Boot %u/%u: %s",p.completed,p.total,p.label.c_str()); }).ok();
}
void HubOsApp::run(){ while(true){ vTaskDelay(pdMS_TO_TICKS(50)); } }
}
