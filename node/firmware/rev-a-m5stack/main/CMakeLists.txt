idf_component_register(
    SRCS
        "app_main.cpp"
        "RevANodeApp.cpp"
        "AtomS3LiteBoard.cpp"
        "Rf433Adapter.cpp"
        "IrUnitAdapter.cpp"
    INCLUDE_DIRS "."
    REQUIRES nvs_flash esp_wifi bt esp_timer driver
)
