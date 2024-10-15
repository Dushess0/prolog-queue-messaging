:- use_module(dbus_prolog).

% Main entry point for the reader
start :-
    writeln('Reader: Connecting to D-Bus via Unix socket...'),
    dbus_connect,  % Connect to the D-Bus session bus
    register_dbus_callback(on_dbus_message),  % Register the callback to handle incoming messages
    writeln('Reader: Connected. Listening for messages...'),
    dbus_receive.  % Start receiving messages in a loop

% Callback predicate to handle incoming D-Bus messages
on_dbus_message(Interface, Member, Path) :-
    format('Callback triggered: Interface = ~w, Member = ~w, Path = ~w~n', [Interface, Member, Path]),
    ( Interface == 'org.example.TestInterface', Member == 'TestSignal', Path == '/org/example/TestPath' ->
        format('\033[32mReceived the expected message from writer! Processing custom content...\033[0m~n'),
        writeln('  Arguments:'),
        writeln('\033[34m    String: Hello world from DBUS\033[0m')
    ; 
        writeln('Processing message...')
    ).

% Start the reader
:- start.
