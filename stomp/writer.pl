% writer.pl
:- use_module(library(stomp)).

% Predicate to start the message sending process
send_message :-
    % Establish the connection with STOMP server using the service name
    stomp_connection('stomp-broker':61613, '/', 
                     _{'heart-beat': '5000,5000', login: guest, passcode: guest}, 
                     on_frame, Connection),
    stomp_connect(Connection),

    % Send a message to the topic/queue
    stomp_send_json(Connection, '/queue/mytopic', _{}, _{text: "Hello from sender"}),

    % Optional: Close the connection
    stomp_disconnect(Connection, []).

% Dummy on_frame predicate, as it's required but not used in this case
on_frame(_Type, _Connection, _Header, _Body).

% Run the send_message predicate on startup
:- initialization(send_message).
