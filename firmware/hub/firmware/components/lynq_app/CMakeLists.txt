idf_component_register(SRCS "src/LynqApp.cpp" "src/BootStateMachine.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES board_port freertos)
