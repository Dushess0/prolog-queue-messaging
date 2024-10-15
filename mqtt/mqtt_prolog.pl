:- module(mqtt_prolog, [
    mqtt_connect/2, 
    mqtt_publish/2, 
    mqtt_subscribe/1, 
    mqtt_loop/0, 
    register_mqtt_callback/1
]).
:- use_foreign_library('/app/mqtt').  % Ensure the correct path and library name

% Prolog predicate to connect to the MQTT broker
% Takes Broker (string) and Port (integer) as arguments
mqtt_connect(Broker, Port) :-
    atom(Broker),
    integer(Port),
    pl_mqtt_connect(Broker, Port).

% Prolog predicate to publish a message to a specific topic
% Takes Topic (string) and Message (string) as arguments
mqtt_publish(Topic, Message) :-
    atom(Topic),
    atom(Message),
    pl_mqtt_publish(Topic, Message).

% Prolog predicate to subscribe to a specific topic
% Takes Topic (string) as an argument
mqtt_subscribe(Topic) :-
    atom(Topic),
    pl_mqtt_subscribe(Topic).

% Prolog predicate to start the MQTT loop to process incoming and outgoing messages
mqtt_loop :-
    writeln('Processing MQTT messages...'),
    pl_mqtt_loop.

% Prolog predicate to register a callback for incoming MQTT messages
% Takes PredicateName (string) as an argument
register_mqtt_callback(PredicateName) :-
    atom(PredicateName),
    pl_register_mqtt_callback(PredicateName).
