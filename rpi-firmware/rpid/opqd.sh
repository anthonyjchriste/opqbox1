#!/bin/sh
### BEGIN INIT INFO
# Provides:          opqd
# Required-Start:    $local_fs $network $named $time $syslog
# Required-Stop:     $local_fs $network $named $time $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Description:       opq power quality daemon
### END INIT INFO

SCRIPT=/usr/local/bin/opqd
RUNAS=pi
PIDFILE=/var/run/opqd.pid
LOGFILE=/var/log/opqd.log

export OPQD_SETTINGS_FILE=/usr/local/opqd/settings.set
MSP_PORT=/dev/ttyAMA0
MSP_SPEED=115200

start() {
  if [ -f /var/run/$PIDNAME ] && kill -0 $(cat /var/run/$PIDNAME); then
    echo 'Service already running' >&2
    return 1
  fi
  echo 'Configuring serial port' >&2
  stty -F $MSP_PORT ispeed $MSP_SPEED ospeed $MSP_SPEED raw
  echo 'Reseting flow control' >&2
  pinctl  export 18
  pinctl out 18
  pinctl high 18
  echo "Starting opqd with the data folder $OPQD_SETTINGS_FILE" >&2
  local CMD="$SCRIPT &> \"$LOGFILE\" & echo \$!"
  su -c "$CMD" $RUNAS > "$PIDFILE"
  echo 'Service started' >&2
}

stop() {
  if [ ! -f "$PIDFILE" ] || ! kill -0 $(cat "$PIDFILE"); then
    echo 'Service not running' >&2
    return 1
  fi
  echo 'Stopping service…' >&2
  kill -15 $(cat "$PIDFILE") && rm -f "$PIDFILE"
  echo 'Service stopped' >&2
}


case "$1" in
  start)
    start
    ;;
  stop)
    stop
    ;;
  restart)
    stop
    start
    ;;
  *)
    echo "Usage: $0 {start|stop|restart|uninstall}"
esac
