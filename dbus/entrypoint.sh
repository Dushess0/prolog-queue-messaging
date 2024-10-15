#!/bin/sh

# Start the D-Bus daemon with the updated configuration
echo "Starting D-Bus daemon..."
dbus-daemon --config-file=/etc/dbus-1/session.conf --fork --print-address --address=unix:path=/tmp/session_bus_socket

# Export the session bus address for Unix socket
export DBUS_SESSION_BUS_ADDRESS=unix:path=/tmp/session_bus_socket

# Start the reader script
echo "Starting reader.pl..."
swipl -s reader.pl &

# Wait for 5 seconds to allow the reader to initialize
echo "Waiting for 5 seconds..."
sleep 5

# Start the writer script
echo "Starting writer.pl..."
swipl -s writer.pl

# Keep the container running if needed (optional)
tail -f /dev/null
