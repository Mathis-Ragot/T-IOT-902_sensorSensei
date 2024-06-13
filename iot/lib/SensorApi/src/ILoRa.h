//
// Created by clement.mathe on 13/06/2024.
//

#ifndef IOT_ILORA_H
#define IOT_ILORA_H

#include <cstdint>
#include <cstddef>

class ILoRa {
public:
    virtual bool begin(long frequency) = 0;
    virtual void end() = 0;
    virtual int parsePacket() = 0;
    virtual int available() = 0;
    virtual int read() = 0;
    virtual void beginPacket() = 0;
    virtual void write(const uint8_t* buffer, size_t size) = 0;
    virtual void endPacket() = 0;
    virtual ~ILoRa() = default;
};

#endif //IOT_ILORA_H
