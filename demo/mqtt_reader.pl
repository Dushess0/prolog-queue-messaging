:- use_module(mqtt_prolog).
:- initialization(main).

mqtt_message_handler(Topic, Message) :-
    format("Received message on topic ~w: ~w~n", [Topic, Message]).

main :-
    MQTT_BROKER = 'broker.hivemq.com',
    MQTT_PORT = 1883,
    mqtt_connect(MQTT_BROKER, MQTT_PORT),

    MQTT_TOPIC = 'sensor_demo_prolog/readings',
    mqtt_subscribe(MQTT_TOPIC),
    register_mqtt_callback(mqtt_message_handler),
    mqtt_loop.
