:- use_module(dbus_prolog).

% Main entry point for the reader
start :-
    format('\033[32mReader: Connecting to D-Bus via Unix socket...\033[0m~n'),
    dbus_connect,  % Connect to the D-Bus session bus
    register_dbus_callback(on_dbus_message),  % Register the callback to handle incoming messages
    format('\033[32mReader: Connected. Listening for messages...\033[0m~n'),
    dbus_receive.  % Start receiving messages in a loop

% Callback predicate to handle incoming D-Bus messages
on_dbus_message(Interface, Member, Path, Args) :-
    format('\033[32mReader: Callback triggered: Interface = ~w, Member = ~w, Path = ~w, Args = ~w\033[0m~n', [Interface, Member, Path, Args]),
    ( Interface == 'org.example.TestInterface', Member == 'TestSignal', Path == '/org/example/TestPath' ->
        format('\033[32mReader: Received the expected message from writer! Processing custom content...\033[0m~n'),
        format('\033[32mReader:   Arguments: ~w\033[0m~n', [Args]),
        format('\033[32mReader: Processing message...\033[0m~n')
    ).

% Start the reader
:- start.
