import paho.mqtt.client as mqtt
import random
import time
import json

# MQTT Broker details
MQTT_BROKER = "broker.hivemq.com"
MQTT_PORT = 1883  # TCP Port
MQTT_TOPIC = "sensor_demo_prolog/readings"

# Initialize previous temperature for delta calculation
previous_temperature = None

def generate_sensor_readings():
    global previous_temperature

    # Generate random sensor readings
    pressure = round(random.uniform(950, 1050), 2)  # Atmospheric pressure in hPa
    temperature = round(random.uniform(15, 30), 2)  # Temperature in Celsius
    humidity = round(random.uniform(30, 70), 2)     # Humidity in %

    # Calculate temperature delta
    if previous_temperature is not None:
        temperature_delta = round(temperature - previous_temperature, 2)
    else:
        temperature_delta = 0.0  # Initial delta is zero

    # Update previous temperature
    previous_temperature = temperature

    # Create a dictionary with the readings
    readings = {
        "pressure": pressure,
        "temperature": temperature,
        "temperature_delta": temperature_delta,
        "humidity": humidity
    }

    return readings

def on_connect(client, userdata, flags, rc):
    print(f"Connected to MQTT Broker with result code {rc}")

def main():
    # Create an MQTT client
    client = mqtt.Client()

    # Attach the on_connect function
    client.on_connect = on_connect

    # Connect to the MQTT Broker
    client.connect(MQTT_BROKER, MQTT_PORT, 60)

    # Start the loop
    client.loop_start()

    try:
        while True:
            # Generate sensor readings
            readings = generate_sensor_readings()

            # Convert readings to JSON format
            readings_json = json.dumps(readings)

            # Publish the readings to the MQTT topic
            client.publish(MQTT_TOPIC, readings_json)
            print(f"Published: {readings_json}")

            # Wait for 5 seconds before sending the next reading
            time.sleep(5)

    except KeyboardInterrupt:
        print("Exiting...")
        client.loop_stop()
        client.disconnect()

if __name__ == "__main__":
    main()
