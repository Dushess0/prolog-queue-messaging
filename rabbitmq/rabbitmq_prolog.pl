:- module(rabbitmq_prolog, [
    rabbitmq_connect/2, 
    rabbitmq_publish/2, 
    rabbitmq_subscribe/1, 
    rabbitmq_loop/0, 
    register_rabbitmq_callback/1
]).
:- use_foreign_library('/app/rabbitmq').  % Ensure the correct path and library name

% Prolog predicate to connect to the RabbitMQ server
% Takes Host (string) and Port (integer) as arguments
rabbitmq_connect(Host, Port) :-
    atom(Host),
    integer(Port),
    pl_rabbitmq_connect(Host, Port).

% Prolog predicate to publish a message to a specific queue
% Takes Queue (string) and Message (string) as arguments
rabbitmq_publish(Queue, Message) :-
    atom(Queue),
    atom(Message),
    pl_rabbitmq_publish(Queue, Message).

% Prolog predicate to subscribe to a specific queue
% Takes Queue (string) as an argument
rabbitmq_subscribe(Queue) :-
    atom(Queue),
    pl_rabbitmq_subscribe(Queue).

% Prolog predicate to start the RabbitMQ loop to process incoming and outgoing messages
rabbitmq_loop :-
    writeln('Processing RabbitMQ messages...'),
    pl_rabbitmq_loop.

% Prolog predicate to register a callback for incoming RabbitMQ messages
% Takes PredicateName (string) as an argument
register_rabbitmq_callback(PredicateName) :-
    atom(PredicateName),
    pl_register_rabbitmq_callback(PredicateName).
