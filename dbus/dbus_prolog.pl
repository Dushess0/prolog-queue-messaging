:- module(dbus_prolog, [dbus_connect/0, dbus_send_message/4, dbus_receive/0, register_dbus_callback/1, dbus_send_signal/4]).
:- use_foreign_library('/app/dbus').  % Ensure the correct path and library name

% Prolog predicate to connect to the D-Bus session bus
dbus_connect :-
    pl_dbus_connect.

% Prolog predicate to send a message to a specific service, path, interface, and method
dbus_send_message(Service, Path, Interface, Method) :-
    atom(Service),
    atom(Path),
    atom(Interface),
    atom(Method),
    pl_dbus_send_message(Service, Path, Interface, Method).

% Prolog predicate to receive messages from D-Bus
dbus_receive :-
    writeln('Listening for messages on D-Bus...'),
    pl_dbus_receive.

% Prolog predicate to send a signal to a specific path, interface, and member with a message
dbus_send_signal(Path, Interface, Member, Message) :-
    atom(Path),
    atom(Interface),
    atom(Member),
    atom(Message),
    pl_dbus_send_signal(Path, Interface, Member, Message).

% Prolog predicate to register a callback for incoming D-Bus messages
register_dbus_callback(PredicateName) :-
    atom(PredicateName),
    pl_register_callback(PredicateName).
