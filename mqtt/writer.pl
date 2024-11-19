% writer.pl
:- use_module(mqtt_prolog).
:- initialization(main).

% Main predicate to set up MQTT connection and publish a message
main :-
    Broker = 'mqtt-broker',
    Port = 1883,
    Topic = 'test/topic',
    Message = 'Hello from Prolog with C++!',
    mqtt_connect(Broker, Port),         % Connect to the broker
    mqtt_publish(Topic, Message),       % Publish the message to the topic
    halt.                               % Exit after publishing
