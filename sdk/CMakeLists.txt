add_library(lynq_sdk
    src/Logger.cpp
    src/UUID.cpp
    src/EventBus.cpp
    src/Configuration.cpp
    src/Timer.cpp
)

target_include_directories(lynq_sdk PUBLIC include)
target_compile_features(lynq_sdk PUBLIC cxx_std_20)

add_executable(lynq_sdk_tests tests/sdk_tests.cpp)
target_link_libraries(lynq_sdk_tests PRIVATE lynq_sdk)
add_test(NAME lynq_sdk_tests COMMAND lynq_sdk_tests)
