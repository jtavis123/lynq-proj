#pragma once
#include "lynq/hub/BootManager.h"
namespace lynq::hub { class HubOsApp { public: bool initialize(); void run(); private: BootManager boot_; }; }
