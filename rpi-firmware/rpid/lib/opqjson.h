#ifndef libjson_opqjson_h
#define libjson_opqjson_h

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

int jsonify(char ** json, uint32_t magicWord, uint32_t packetType, uint64_t deviceId,
            std::string deviceKey,uint64_t timestamp, uint32_t duration, uint32_t checksum,
            double frequency, double voltage, uint32_t payloadSize, std::vector<double> payload) {

    std::stringstream ss;

    ss << "[";
    for(int i = 0; i < payload.size(); i++) {
        if(i != 0) {
            ss << ",";
        }
        ss << payload[i];
    }
    ss << "]";

    const char * text =
        "{"
        "\"magicWord\":%d, "
        "\"packetType\":%d, "
        "\"deviceId\":%llu, "
        "\"deviceKey\":\"%s\", "
        "\"timestamp\":%llu, "
        "\"duration\":%u, "
        "\"checksum\":%d, "
        "\"frequency\":%f, "
        "\"voltage\":%f, "
        "\"payloadSize\":%d, "
        "\"payload\":%s}";

    int ret = asprintf(json, text, magicWord,
                                    packetType,
                                    deviceId,
                                    deviceKey.c_str(),
                                    timestamp,
                                    duration,
                                    checksum,
                                    frequency,
                                    voltage,
                                    payloadSize,
                                    ss.str().c_str());

    return ret;
}

#endif
