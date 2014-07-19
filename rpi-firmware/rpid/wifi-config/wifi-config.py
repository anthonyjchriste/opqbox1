#!/usr/bin/env python

from ConfigParser import SafeConfigParser
import datetime
import os.path
from subprocess import call
import sys

date = str(datetime.datetime.now())
print "===== wifi-config.py " + date + " ====="
print

if len(sys.argv) != 2:
    print "USB root directory not supplied"
    print
    exit()

usb_root = sys.argv[1]
wifi_config = "wifi-config.txt"
custom_config = "wpa_supplicant.conf"
config_path = os.path.join(usb_root, wifi_config)
custom_path = os.path.join(usb_root, custom_config)

# Display all parameters for debugging/sanity checks
print "usb_root = " + usb_root
print "wifi_config = " + wifi_config
print "custom_config = " + custom_config
print "config_path = " + config_path
print "custom_path = " + custom_path
print

def parse_config(path):
    parser = SafeConfigParser()
    parser.read(path)
    section = "wifi_config"
    
    fields = ["ssid", "key", "security"]
    results = {}
    for field in fields:
        if not parser.has_option(section, field):
            print "ERROR: config field " + field + " missing!"
            exit()
        results[field] = parser.get(section, field)

    return results

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
    print "Configuration file " + config_path + " found!"
    print "Generating wpa_supplicant..."
    configuration = parse_config(config_path)
    print "Parsed configuration = " + str(configuration)
    template = get_wpa_template(configuration)
    wpa_supplicant = make_wpa_supplicant(configuration, template)
    
    print "Generated wpa_supplicant.conf..."
    print
    print wpa_supplicant
    print

    print "Copying wpa_supplicant.conf to device..."
    write_supplicant(wpa_supplicant, "/etc/wpa_supplicant/wpa_supplicant.conf")
    
    print "Attempting to restart networking..."
    restart_networking()

    print "Results of ifconfig"
    call("ifconfig")

else:
    print "ERROR: " + config_path + " not found!"
    print

# Check for provided wpa_supplicant.conf
# Note: If wpa_supplicant.conf is found on usb, it will always be used
#       even if wifi-config.txt is specified.

if os.path.exists(custom_path):
    print "Custom configuration " + custom_path + " found!"
    print "Copying " + custom_path + " to device."
    print
