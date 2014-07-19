#!/bin/sh
### BEGIN INIT INFO
# Provides:          usbd
# Required-Start:    $local_fs $network $named $time $syslog
# Required-Stop:     $local_fs $network $named $time $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Description:       opq power quality usb monitoring daemon
### END INIT INFO

start(){
  echo "Starting usbd..."
  wifi_root="/home/pi/opq-hardware/rpi-firmware/rpid/wifi-config"
  wifi_config="sudo python $wifi_root/wifi-config.py"
  log="$wifi_root/wifi-config.log"
  devmon --exec-on-drive "$wifi_config %d >> $log && cp -f $log %d/." &
  echo "usbd started."
}

stop() {
  echo "Stopping usbd..."
  killall devmon
  echo "Stopped usbd."
}

restart() {
  start
  stop
}

case "$1" in
  start)
    start
    ;;
  stop)
    stop
    ;;
  restart)
    restart
    ;;
  *)
    echo "Usage: /etc/init.d/usbd {start|restart|stop}"
    exit 1
    ;;
esac

exit 0


