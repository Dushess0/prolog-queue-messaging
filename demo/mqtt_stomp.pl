% mqtt_stomp.pl
:- use_module(mqtt_prolog).
:- use_module(library(stomp)).
:- initialization(main).

% Handler for incoming MQTT messages
mqtt_message_handler(Topic, Message) :-
    format("Received MQTT message on topic ~w: ~w~n", [Topic, Message]),
    send_to_stomp(Message).

% Predicate to send message via STOMP
send_to_stomp(Message) :-
    % Establish connection to STOMP server
    stomp_connection('stomp-broker':61613, '/',
                     _{'heart-beat': '5000,5000', login: guest, passcode: guest},
                     on_frame, Connection),
    stomp_connect(Connection),
    % Send the message to the STOMP queue
    stomp_send(Connection, '/queue/mqtt_to_stomp', _{}, Message),
    % Disconnect from STOMP server
    stomp_disconnect(Connection, []).

% Dummy on_frame predicate, required but not used
on_frame(_Type, _Connection, _Header, _Body).

% Main predicate to set up MQTT connection and start listening
main :-
    MQTT_BROKER = 'broker.hivemq.com',
    MQTT_PORT = 1883,
    MQTT_TOPIC = 'sensor_demo_prolog/readings',
    mqtt_connect(MQTT_BROKER, MQTT_PORT),
    mqtt_subscribe(MQTT_TOPIC),
    register_mqtt_callback(mqtt_message_handler),
    mqtt_loop.
