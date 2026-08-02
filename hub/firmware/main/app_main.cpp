#include "HubOsApp.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
extern "C" void app_main(){
 esp_err_t r=nvs_flash_init();
 if(r==ESP_ERR_NVS_NO_FREE_PAGES||r==ESP_ERR_NVS_NEW_VERSION_FOUND){ESP_ERROR_CHECK(nvs_flash_erase());r=nvs_flash_init();}
 ESP_ERROR_CHECK(r);
 static lynq::hub::HubOsApp app;
 if(!app.initialize()){ESP_LOGE("LYNQ","Hub OS initialization failed");return;}
 app.run();
}
