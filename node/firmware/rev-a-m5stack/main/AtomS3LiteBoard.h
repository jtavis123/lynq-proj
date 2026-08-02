#pragma once

namespace lynq::rev_a {

class AtomS3LiteBoard {
public:
    bool initialize();
    void setStatusReady();
    void setStatusPairing();
    void setStatusError();
    bool pairingButtonPressed() const;
};

} // namespace lynq::rev_a
