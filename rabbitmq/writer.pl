% writer.pl
:- use_module(rabbitmq_prolog).
:- initialization(main).

% Main predicate to set up RabbitMQ connection and publish a message
main :-
    Host = 'rabbitmq',  % RabbitMQ service name in Docker Compose
    Port = 5672,        % Default RabbitMQ port
    Queue = 'test_queue',
    Message = 'Hello from Prolog with C++!',
    rabbitmq_connect(Host, Port),             % Connect to the RabbitMQ server
    rabbitmq_publish(Queue, Message).         % Publish the message to the queue

