% rabbitmq_dbus.pl
:- use_module(rabbitmq_prolog).
:- use_module(dbus_prolog).
:- initialization(main).

% Handler for incoming RabbitMQ messages
rabbitmq_message_handler(Queue, Message) :-
    format("Received RabbitMQ message on queue ~w: ~w~n", [Queue, Message]),
    send_to_dbus(Message).

% Predicate to send message via D-Bus
send_to_dbus(Message) :-
    dbus_connect,  % Connect to the D-Bus session bus
    % Send a custom signal with the message
    dbus_send_signal('/org/example/SensorData', 'org.example.Sensor', 'NewReading', Message),
    writeln('Sent message to D-Bus.').

% Main predicate to set up RabbitMQ connection and start listening
main :-
    Host = 'rabbitmq',  % RabbitMQ service name in Docker Compose
    Port = 5672,        % Default RabbitMQ port
    Queue = 'stomp_to_rabbitmq',
    rabbitmq_connect(Host, Port),
    rabbitmq_subscribe(Queue),
    register_rabbitmq_callback(rabbitmq_message_handler),
    rabbitmq_loop.
