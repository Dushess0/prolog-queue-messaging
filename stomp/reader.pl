% reader.pl
:- use_module(library(stomp)).
:- dynamic stop_listening/0.

% Predicate to start connecting and subscribing to the STOMP server
connect_to_stomp :-
    % Establish the connection with STOMP server using the service name
    stomp_connection('stomp-broker':61613, '/',
                     _{'heart-beat': '5000,5000', login: guest, passcode: guest},
                     on_frame, Connection),
    stomp_connect(Connection),
    
    % Subscribe to the topic/queue
    stomp_subscribe(Connection, '/queue/mytopic', 0, _{}),
    
    % Start listening loop
    listen_loop.

% Listen loop that continues until stop_listening is asserted
listen_loop :-
    % Check if the stop_listening flag has been set
    \+ stop_listening,
    
    % Wait for a short period before continuing the loop
    sleep(1),
    listen_loop.
listen_loop.

% Predicate to handle frames received from STOMP server
on_frame(connected, Connection, _Header, _Body) :-
    % Handle connection established event
    writeln('Connected to STOMP server'),
    stomp_subscribe(Connection, '/queue/mytopic', 0, _{}).

on_frame(message, _Connection, _Header, Body) :-
    % Handle incoming messages
    writeln('Received message:'),
    writeln(Body),
    
    % Stop listening if the message is 'stop'
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

% Run the connect_to_stomp predicate on startup
:- initialization(connect_to_stomp).
