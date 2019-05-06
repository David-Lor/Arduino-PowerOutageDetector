#!/bin/sh

SERIAL_DEV=/dev/ttyUSB0
SERIAL_BAUDRATE=9600
MQTT_BROKER="127.0.0.1"
MQTT_TOPIC="power_outage"

last_rx=""
while :
do
    stty -F "$SERIAL_DEV" $SERIAL_BAUDRATE
    cat "$SERIAL_DEV" | while read -r line
    do
        if [ ! -z "$line" ] && [ "$last_rx" != "$line" ]
        then
            echo "Rx: $line"
            last_rx="$line"
            mosquitto_pub -h "$MQTT_BROKER" -t "$MQTT_TOPIC" -m "$line"
        fi
    done
    sleep 2
done
