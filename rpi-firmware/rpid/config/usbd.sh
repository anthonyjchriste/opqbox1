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
  echo "Starting usbd..." >> /home/pi/devmon.log
  root="/home/pi/opq-hardware/rpi-firmware/rpid/config"
  config="sudo python $root/config.py"
  log="$root/config.log"
  /usr/local/bin/devmon --exec-on-drive "$config %d >> $log && cp -f $log %d/." >> /home/pi/devmon.log
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


