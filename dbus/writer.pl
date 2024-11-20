:- use_module(dbus_prolog).

% Main entry point for the writer
start :-
    format('\033[31mWriter: Connecting to D-Bus via Unix socket...\033[0m~n'),
    setenv('DBUS_SESSION_BUS_ADDRESS', 'unix:path=/tmp/session_bus_socket'),  % Set Unix socket connection
    dbus_connect,  % Connect to the D-Bus session bus
    format('\033[31mWriter: Connected. Sending a custom message...\033[0m~n'),
    % Send a custom signal with "Hello world from DBUS" to a specific service, path, and interface
    send_custom_signal('Hello world from DBUS'),
    format('\033[31mWriter: Custom signal sent.\033[0m~n').

% Predicate to send a custom signal to D-Bus
send_custom_signal(Message) :-
    % Adjust the service, path, and interface as needed for a signal
    dbus_send_signal('/org/example/TestPath', 'org.example.TestInterface', 'TestSignal', Message),
    format('\033[31mWriter: Custom signal sent with content: ~w\033[0m~n', [Message]).

% Start the writer
:- start.
