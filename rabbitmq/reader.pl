% reader.pl
:- use_module(rabbitmq_prolog).
:- initialization(main).

% Handler for incoming RabbitMQ messages
rabbitmq_message_handler(Queue, Message) :-
    format("Received message on queue ~w: ~w~n", [Queue, Message]).

% Main predicate to set up RabbitMQ connection and start listening
main :-
    Host = 'rabbitmq',  % RabbitMQ service name in Docker Compose
    Port = 5672,        % Default RabbitMQ port
    Queue = 'test_queue',
    rabbitmq_connect(Host, Port),             % Connect to the RabbitMQ server
    rabbitmq_subscribe(Queue),                % Subscribe to the queue
    register_rabbitmq_callback(rabbitmq_message_handler),  % Register callback for incoming messages
    rabbitmq_loop.                            % Start listening indefinitely
