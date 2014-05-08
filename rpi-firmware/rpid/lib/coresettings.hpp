#ifndef CORESETTINGS_HPP
#define CORESETTINGS_HPP

#include <string>
#include <map>
#include <boost/thread/shared_mutex.hpp>
#include "datastructures.hpp"

class OpqSettings
{
public:
    static OpqSettings* Instance();
    bool setSetting(std::string key, OpqSetting value);
    OpqSetting getSetting(std::string key);
    bool isSet(std::string key);
    OpqSetting erase(std::string key);
    bool loadFromFile(std::string filename);
    bool saveToFile(std::string filename);
    void clear();
private:
    OpqSettings();
    OpqSettings(OpqSettings const&);
    OpqSettings & operator=(OpqSettings const&);
    static OpqSettings* instance_;

    std::map <std::string, OpqSetting> settings_;
    boost::shared_mutex mutex_;
};

#endif // CORESETTINGS_HPP
