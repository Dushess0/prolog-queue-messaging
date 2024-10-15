% reader.pl
:- use_module(mqtt_prolog).
:- initialization(main).

% Handler for incoming MQTT messages
mqtt_message_handler(Topic, Message) :-
    format("Received message on topic ~w: ~w~n", [Topic, Message]).

% Main predicate to set up MQTT connection and start listening
main :-
    Broker = 'mqtt-server',
    Port = 1883,
    Topic = 'test/topic',
    mqtt_connect(Broker, Port),          % Connect to the broker
    mqtt_subscribe(Topic),               % Subscribe to the topic
    register_mqtt_callback(mqtt_message_handler),  % Register callback for incoming messages
    mqtt_loop.                           % Start listening indefinitely
