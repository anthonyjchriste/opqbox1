#ifndef CORESETTINGS_HPP
#define CORESETTINGS_HPP

#include <string>
#include <map>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "datastructures.hpp"

namespace pland
{

class Settings
{
public:
    static Settings* Instance();
    bool setSetting(std::string key, OpqSetting value);
    OpqSetting getSetting(std::string key);
    bool isSet(std::string key);
    OpqSetting erase(std::string key);
    void clear();
private:
    Settings();
    Settings(Settings const&);
    Settings & operator=(Settings const&);
    static Settings* instance_;

    std::map <std::string, OpqSetting> settings_;
    boost::shared_mutex mutex_;
};

}
#endif // CORESETTINGS_HPP
