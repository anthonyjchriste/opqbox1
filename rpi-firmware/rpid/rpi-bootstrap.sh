#!/bin/bash

# Install needed libs
echo "Installing dependicies from apt..."
apt-get install time libgsl0-dev libboost-dev libboost-filesystem-dev vim-nox libboost-thread-dev eject zenity

# Install usb monitor
echo "Installing usb monitoring and auto-mounting..."
install contrib/devmon /usr/local/bin/devmon

