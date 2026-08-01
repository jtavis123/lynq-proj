add_library(lynq_sdk
    src/Logger.cpp
    src/UUID.cpp
    src/WifiProvisioningController.cpp
    src/NodeRegistry.cpp
    src/NodeManager.cpp
    src/LearningController.cpp
    src/CommandRouter.cpp
    src/DeviceRegistry.cpp
    src/RoomRegistry.cpp
    src/SceneEngine.cpp
    src/AutomationScheduler.cpp
    src/JsonConfigurationStore.cpp
    src/UiApplicationModel.cpp
    src/EventBus.cpp
    src/Configuration.cpp
    src/Timer.cpp
)

target_include_directories(lynq_sdk PUBLIC include)
target_compile_features(lynq_sdk PUBLIC cxx_std_20)

add_executable(lynq_sdk_tests tests/sdk_tests.cpp)
target_link_libraries(lynq_sdk_tests PRIVATE lynq_sdk)
add_test(NAME lynq_sdk_tests COMMAND lynq_sdk_tests)

add_executable(lynq_learning_tests tests/learning_tests.cpp)
target_link_libraries(lynq_learning_tests PRIVATE lynq_sdk)
add_test(NAME lynq_learning_tests COMMAND lynq_learning_tests)

add_executable(lynq_command_router_tests tests/command_router_tests.cpp)
target_link_libraries(lynq_command_router_tests PRIVATE lynq_sdk)
add_test(NAME lynq_command_router_tests COMMAND lynq_command_router_tests)

add_executable(lynq_device_scene_tests tests/device_scene_tests.cpp)
target_link_libraries(lynq_device_scene_tests PRIVATE lynq_sdk)
add_test(NAME lynq_device_scene_tests COMMAND lynq_device_scene_tests)

add_executable(lynq_automation_storage_tests tests/automation_storage_tests.cpp)
target_link_libraries(lynq_automation_storage_tests PRIVATE lynq_sdk)
add_test(NAME lynq_automation_storage_tests COMMAND lynq_automation_storage_tests)

add_executable(lynq_ui_application_tests tests/ui_application_tests.cpp)
target_link_libraries(lynq_ui_application_tests PRIVATE lynq_sdk)
add_test(NAME lynq_ui_application_tests COMMAND lynq_ui_application_tests)
