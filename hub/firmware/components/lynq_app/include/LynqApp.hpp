#pragma once

#include "BootStateMachine.hpp"

namespace lynq::hub {

class BoardPort;

class LynqApp {
public:
    explicit LynqApp(BoardPort& board);
    void run();

private:
    bool initializeServices();
    bool initializeUi();
    void showSplash();
    void showHomeShell();

    BoardPort& board_;
    BootStateMachine boot_;
};

}  // namespace lynq::hub
