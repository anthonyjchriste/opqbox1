#!/usr/bin/env python

from ConfigParser import SafeConfigParser
import datetime
import os.path
from subprocess import call, Popen, PIPE
import sys

date = str(datetime.datetime.now())
print "===== config.py " + date + " ====="
print

# File names
config_ini = "config.ini"
custom_wpa_supplicant = "wpa_supplicant.conf"
interfaces_template = "interfaces.template"
wpa_template = "wpa_supplicant.wpa.conf.template"
wep_template = "wpa_supplicant.wep.conf.template"

# Paths
usb_path = "/media/usb"
settings_path = "/usr/local/opqd/settings.set"
config_ini_path = os.path.join(usb_path, config_ini)
custom_wpa_supplicant_path = os.path.join(usb_path, custom_wpa_supplicant)
templates_path = "/home/pi/opq-hardware/rpi-firmware/rpid/config/templates"
wpa_template_path = os.path.join(templates_path, wpa_template)
wep_template_path = os.path.join(templates_path, wep_template)
wpa_supplicant_path = "/etc/wpa_supplicant/wpa_supplicant.conf"

# Display all parameters for debugging/sanity checks
print "-- Files --"
print "config_ini = " + config_ini
print "custom_wpa_supplicant = " + custom_wpa_supplicant
print "interfaces_template = " + interfaces_template
print "wpa_template = " + wpa_template
print "wep_template = " + wep_template
print
print "-- Paths --"
print "usb_path = " + usb_path + " -- (exists " + str(os.path.exists(usb_path)) + ")"
print "settings_path = " + settings_path + " -- (exists " + str(os.path.exists(settings_path)) + ")"
print "config_ini_path = " + config_ini_path + " -- (exists " + str(os.path.exists(config_ini_path)) + ")"
print "custom_wpa_supplicant_path = " + custom_wpa_supplicant_path + " -- (exists " + str(os.path.exists(custom_wpa_supplicant_path)) + ")"
print "templates_path = " + templates_path + " -- (exists " + str(os.path.exists(templates_path)) + ")"
print "wpa_template_path = " + wpa_template_path + " -- (exists " + str(os.path.exists(wpa_template_path)) + ")"
print "wep_template_path = " + wep_template_path + " -- (exists " + str(os.path.exists(wep_template_path)) + ")"
print

def parse_config(path):
    parser = SafeConfigParser()
    parser.read(path)
    
    config_fields = {"wifi_config": ["ssid", "key", "security"],
              "device_config": ["access_key", "opqhub_addr"]}
              
    wifi_results = {}
    device_results = {}
              
    for section in config_fields:
        for field in config_fields[section]:
            if not parser.has_option(section, field):
                print "ERROR: config field " + field + " missing!"
                exit()
            if section == "wifi_config":
                wifi_results[field] = parser.get(section, field)
            elif section == "device_config":
                device_results[field] = parser.get(section, field)
                
    return wifi_results, device_results

def update_settings(device_settings, settings_file):
    # Read in the current settings file
    f = open(settings_file, "r")
    lines = f.readlines()
    f.close()
    
    # Resulting lines will be stored here
    results = []
    
    # Replace fields given in config
    for line in lines:
        if line.startswith("device.key"):
            results.append("device.key              :S  :" + device_settings["access_key"] + "\n")
        elif line.startswith("ws.url"):
            results.append("ws.url                  :S  :" + device_settings["opqhub_addr"] + "\n")
        else:
            results.append(line)
            
    # Write out the result
    f = open(settings_file, "w")
    for line in results:
        f.write(line)
    f.close()

def get_wpa_template(configuration):
    security = configuration["security"]
    if (not security == "wep") and (not security == "wpa"):
        print "ERROR: Unknown security type " + security
        print "Should be one of either wep or wpa."
        exit()

    if security == "wep":
        print "Using wep template..."
        f = open(wep_template_path, "r")
        t = f.read()
        f.close()
        return t
    else:
        print "Using wpa template..."
        f = open(wpa_template_path, "r")
        t = f.read()
        f.close()
        return t

def make_wpa_supplicant(configuration, template):
    t = template.replace("_SSID_", configuration["ssid"])
    t = t.replace("_KEY_", configuration["key"])
    return t

def write_supplicant(supplicant, path):
    f = open(path, "w")
    f.write(supplicant)
    f.close()

def restart_networking():
    call(["sudo", "ifdown", "wlan0"])
    call(["sudo", "ifup", "wlan0"])
    call(["sudo", "dhclient", "wlan0"])

# Check for configuration file
if os.path.exists(config_ini_path):
    # Read in configuration
    print "Configuration file " + config_ini_path + " found!"
    wifi_config, device_config = parse_config(config_ini_path)
    print
    
    # Print out the configurations for sanity
    print "Parsed wifi_configuration = " + str(wifi_config)
    print "Parsed device_configuration = " + str(device_config)
    print    

    # Update settings.set
    print "Updating /usr/local/opqd/settings.set..."
    update_settings(device_config, settings_path)
    print    

    # Update wifi-configuration
    print "Generating wpa_supplicant..."
    template = get_wpa_template(wifi_config)
    wpa_supplicant = make_wpa_supplicant(wifi_config, template)    

    print "Generated wpa_supplicant.conf..."
    print
    print wpa_supplicant
    print

    print "Copying wpa_supplicant.conf to device..."
    write_supplicant(wpa_supplicant, "/etc/wpa_supplicant/wpa_supplicant.conf")
    
    print "Attempting to restart networking..."
    restart_networking()
    print

    print "Results of ifconfig"
    ifconfig = Popen("ifconfig", stdout=PIPE)
    output = ifconfig.communicate()[0]
    print output
else:
    print "ERROR: " + config_path + " not found!"
    print

# Check for provided wpa_supplicant.conf
# Note: If wpa_supplicant.conf is found on usb, it will always be used
# even if wifi-config.txt is specified.

if os.path.exists(custom_wpa_supplicant_path):
    print "Custom configuration " + custom_wpa_supplicant_path + " found!"
    print "Copying " + custom_wpa_supplicant_path + " to device."
    print
    f = open(custom_wpa_supplicant_path, "r")
    supplicant = f.read()
    f.close()
    
    write_supplicant(supplicant, wpa_supplicant_path)

