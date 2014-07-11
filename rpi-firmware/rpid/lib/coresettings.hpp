#ifndef CORESETTINGS_HPP
#define CORESETTINGS_HPP

#include <string>
#include <map>
#include <boost/thread/shared_mutex.hpp>
#include "datastructures.hpp"

/**
 * @brief The OpqSettings class synchronized singleton key value pair database.
 */
class OpqSettings
{
public:
    /**
     * @brief Instance get an instance of the settings manager.
     * @return
     */
    static OpqSettings* Instance();

    /**
     * @brief setSetting set a key value pair.
     * @param key key.
     * @param value value.
     * @return false if the key is not present otherwise true.
     */
    bool setSetting(std::string key, OpqSetting value);

    /**
     * @brief getSetting get the value for a key.
     * @param key key.
     * @return value corresponding to the key.
     */
    OpqSetting getSetting(std::string key);

    /**
     * @brief isSet checks if the key is present.
     * @param key key.
     * @return true is the key is set.
     */
    bool isSet(std::string key);

    /**
     * @brief erase erases a key from the database.
     * @param key key.
     * @return setting that was erased.
     */
    OpqSetting erase(std::string key);

    /**
     * @brief loadFromFile load the database from file.
     * @param filename filename.
     * @return true on success, false otherwise.
     */
    bool loadFromFile(std::string filename);
    /**
     * @brief saveToFile save the database to a file. Will overwrite the file.
     * @param filename filename.
     * @return true on success, false otherwise.
     */
    bool saveToFile(std::string filename);

    /**
     * @brief clear clear everything.
     */
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
