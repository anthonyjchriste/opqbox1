#include "coresettings.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace pland;

Settings* Settings::instance_ = NULL;

Settings::Settings()
{
}

Settings* Settings::Instance()
{
    if(instance_ == NULL)
        instance_ = new Settings();
    return instance_;
}

bool Settings::setSetting(std::string key, OpqSetting value)
{
	boost::algorithm::trim(key);
    boost::unique_lock< boost::shared_mutex > lock(mutex_);
    settings_[key]= value;
	return true;
}

OpqSetting Settings::getSetting(std::string key)
{
	boost::algorithm::trim(key);
    boost::shared_lock< boost::shared_mutex > lock(mutex_);
    std::map<std::string, OpqSetting>::iterator pos = settings_.lower_bound(key);
    if(pos != settings_.end() && !(settings_.key_comp()(key, pos->first)))
	{
		return pos->second;
	}
	return "";
}

bool Settings::isSet(std::string key)
{
	boost::algorithm::trim(key);
    boost::shared_lock< boost::shared_mutex > lock(mutex_);
    std::map<std::string, OpqSetting>::iterator pos = settings_.lower_bound(key);
    if(pos != settings_.end() && !(settings_.key_comp()(key, pos->first)))
	{
		return true;
	}
	return false;
}

OpqSetting Settings::erase(std::string key)
{
	boost::algorithm::trim(key);
    boost::unique_lock< boost::shared_mutex > lock(mutex_);
    OpqSetting out;
    std::map<std::string, OpqSetting>::iterator pos = settings_.lower_bound(key);
    if(pos != settings_.end() && !(settings_.key_comp()(key, pos->first)))
	{
		out = pos->second;
        settings_.erase(pos);
	}
	return out;
}

void Settings::clear()
{
    boost::unique_lock< boost::shared_mutex > lock(mutex_);
    settings_.clear();
}
