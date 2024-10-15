:- use_module(dbus_prolog).

% Main entry point for the writer
start :-
    writeln('Writer: Connecting to D-Bus via Unix socket...'),
    setenv('DBUS_SESSION_BUS_ADDRESS', 'unix:path=/tmp/session_bus_socket'),  % Set Unix socket connection
    dbus_connect,  % Connect to the D-Bus session bus
    writeln('Writer: Connected. Sending a custom message...'),
    % Send a custom signal with "Hello world from DBUS" to a specific service, path, and interface
    send_custom_signal('Hello world from DBUS'),
    writeln('Writer: Custom signal sent.').

% Predicate to send a custom signal to D-Bus
send_custom_signal(Message) :-
    % Adjust the service, path, and interface as needed for a signal
    dbus_send_signal('/org/example/TestPath', 'org.example.TestInterface', 'TestSignal', Message),
    writeln('Writer: Custom signal sent with content:'), writeln(Message).

% Start the writer
:- start.
