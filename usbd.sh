#!/bin/bash

# Start the usb monitoring daemon. 
wifi_root="/home/pi/opq-hardware/wifi-config"
wifi_config="python $wifi_root/wifi-config.py"
log="$wifi_root/wifi-config.log"

devmon --exec-on-drive "$wifi_config %d >> $log && cp -f $log %d/."
