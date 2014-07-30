#!/usr/bin/env python

from ConfigParser import SafeConfigParser
import datetime
import os.path
from subprocess import call, Popen, PIPE
import sys

date = str(datetime.datetime.now())
print "===== config.py " + date + " ====="
print

if len(sys.argv) != 2:
    print "USB root directory not supplied"
    print
    exit()

usb_root = sys.argv[1]
config = "config.ini"
custom_config = "wpa_supplicant.conf"
settings_path = "/usr/local/opqd/settings.set"
config_path = os.path.join(usb_root, wifi_config)
custom_path = os.path.join(usb_root, custom_config)

# Display all parameters for debugging/sanity checks
print "usb_root = " + usb_root
print "config = " + config
print "custom_config = " + custom_config
print "config_path = " + config_path
print "custom_path = " + custom_path
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
    f = open(settingsFile, "r")
    lines = f.readlines()
    f.close()
    
    # Resulting lines will be stored here
    results = []
    
    # Replace fields given in config
    for line in lines:
        if line.startswith("device.key"):
            results.append("device.key              :S  :" + deviceSettings["access_key"] + "\n")
        elif line.startswith("ws.url"):
            results.append("ws.url                  :S  :" + deviceSettings["opqhub_addr"] + "\n")
        else:
            results.append(line)
            
    # Write out the result
    f = open(settingsFile, "w")
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
        f = open("/home/pi/opq-hardware/rpi-firmware/rpid/wifi-config/wpa_supplicant.wep.conf.template", "r")
        t = f.read()
        f.close()
        return t
    else:
        print "Using wpa template..."
        f = open("/home/pi/opq-hardware/rpi-firmware/rpid/wifi-config/wpa_supplicant.wpa.conf.template", "r")
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
if os.path.exists(config_path):
    # Read in configuration
    print "Configuration file " + config_path + " found!"
    print "Generating wpa_supplicant..."
    wifi_config, device_config = parse_config(config_path)
    
    # Print out the configurations for sanity
    print "Parsed wifi_configuration = " + str(wifi_config)
    print "Parsed device_configuration = " + str(device_config)
    
    # Update settings.set
    print "Updating /usr/local/opqd/settings.set..."
    update_settings(device_configuration, settings_path)
    
    # Update wifi-configuration
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

if os.path.exists(custom_path):
    print "Custom configuration " + custom_path + " found!"
    print "Copying " + custom_path + " to device."
    print
    f = open(custom_path, "r")
    supplicant = f.read()
    f.close()
    
    write_supplicant(supplicant, "/etc/wpa_supplicant/wpa_supplicant.conf")

