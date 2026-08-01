# Exposes the portable LYNQ SDK to ESP-IDF components.
idf_component_register(
    SRCS
        "../../../../sdk/src/Logger.cpp"
        "../../../../sdk/src/UUID.cpp"
        "../../../../sdk/src/EventBus.cpp"
        "../../../../sdk/src/Configuration.cpp"
        "../../../../sdk/src/Timer.cpp"
        "../../../../sdk/src/WifiProvisioningController.cpp"
    INCLUDE_DIRS "../../../../sdk/include"
)
target_compile_features(${COMPONENT_LIB} PUBLIC cxx_std_20)
