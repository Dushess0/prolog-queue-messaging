% stomp_rabbitmq.pl
:- use_module(library(stomp)).
:- use_module(rabbitmq_prolog).
:- dynamic stop_listening/0.
:- initialization(connect_to_stomp).

% Predicate to start connecting and subscribing to the STOMP server
connect_to_stomp :-
    % Establish the connection with STOMP server
    stomp_connection('stomp-broker':61613, '/',
                     _{'heart-beat': '5000,5000', login: guest, passcode: guest},
                     on_frame, Connection),
    stomp_connect(Connection),
    % Start listening loop
    listen_loop.

% Listen loop that continues until stop_listening is asserted
listen_loop :-
    \+ stop_listening,
    sleep(1),
    listen_loop.
listen_loop.

% Predicate to handle frames received from STOMP server
on_frame(connected, Connection, _Header, _Body) :-
    % Handle connection established event
    writeln('Connected to STOMP server'),
    stomp_subscribe(Connection, '/queue/mqtt_to_stomp', 0, _{}).

on_frame(message, _Connection, _Header, Body) :-
    % Handle incoming messages
    writeln('Received STOMP message:'),
    writeln(Body),
    send_to_rabbitmq(Body),
    % Stop listening if needed
    (Body = stop -> assert(stop_listening) ; true).

on_frame(disconnected, _Connection, _Header, _Body) :-
    % Handle disconnection event
    writeln('Disconnected from STOMP server.').

on_frame(error, _Connection, Header, Body) :-
    % Handle error messages
    writeln('Error frame received:'),
    writeln(Header),
    writeln(Body).

on_frame(heartbeat_timeout, _Connection, _Header, _Body) :-
    % Handle heartbeat timeout
    writeln('Heartbeat timeout occurred.').

% Predicate to send message via RabbitMQ
send_to_rabbitmq(Message) :-
    Host = 'rabbitmq',  % RabbitMQ service name in Docker Compose
    Port = 5672,        % Default RabbitMQ port
    Queue = 'stomp_to_rabbitmq',
    rabbitmq_connect(Host, Port),
    rabbitmq_publish(Queue, Message),
    rabbitmq_disconnect.

% Ensure rabbitmq_prolog module is properly initialized
:- initialization(rabbitmq_initialize).
