idf_component_register(
    SRCS "EspIdfTextStorage.cpp"
    INCLUDE_DIRS "include"
    REQUIRES lynq_sdk nvs_flash spiffs
)
