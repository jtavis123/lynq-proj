idf_component_register(
    SRCS "src/HubWifiService.cpp"
    INCLUDE_DIRS "include"
    REQUIRES esp_wifi esp_event nvs_flash lynq_sdk
)
