## Introduction

> The protocol we use is a `binary protocol`. The client sends a `structure` to the server and the server sends back a response in the same format.

### Connection request

> Client:

Type: CONNECTION

> Res:

**Sucess**

Type: CONNECTION

The server returns n \* LOBBY_CREATE type requests to new users

**Failure**

Type: ERROR

- message: Error Message

```cpp
std::byte message[200];
```

## Lobby

### Lobby Create by client

> Client:

Type: LOBBY_CREATE

- Lobby_name: Lobby name

When a user creates a lobby, all users who are in the lobby menu will see the server's response unless there is an error.

The client how create lobby go inside

```cpp
packet_t p;

p.lobby.Lobby_name # std::byte[40]
```

> Respond of server send to all usr in menu:

**Sucess**

Type: LOBBY_CREATE

- Lobby_name: Lobby name
- id: uuid of the Lobby

```cpp
packet_t p;

p.lobby.Lobby_name # std::byte[40]
p.lobby.id # uui_t
```

**Failure**

Type: ERROR

- message: Error Message

```cpp
std::byte message[200];
```

### Client Join Lobby

> Client:

Type: LOBBY_JOIN

- id: Lobby uuid

```cpp
packet_t p;

p.lobby.id # uuid_t
```

> Respond of server:

**Sucess**

Type: LOBBY_JOIN

- id: uuid of the Lobby

```cpp
packet_t p;

p.lobby.id # uuid_t
```

The customer will receive the package below n \* the number of people in the lobby

> For all the peoples in the lobby

Type: LOBBY_NEW_USR

- usr_name: name of joining user
- id: id of the new user

```cpp
packet_t p;

p.lobby.usr_name # std::byte[40]
p.lobby.id # uuid_t
```

**Failure**

Type: ERROR

- message: Error Message

```cpp
std::byte message[200];
```

### Client cick Lobby

The client who created the lobby exclude a member.

Only the lobby owner can exclude.

Other users receive the message that someone is disconnected from the lobby: cf LOBBY_LEAVE

The excluded client must send the CONNECTION request

> Client:

Type: LOBBY_CICK

- id: id of the user to exclude

```cpp
packet_t p;

p.lobby.id # uuid_t
```

> Respond of server:

**Sucess**

Type: LOBBY_CICK

- id: id of the user who was excluded

```cpp
packet_t p;

p.lobby.id # uuid_t
```

**Failure**

Type: ERROR

- message: Error Message

```cpp
std::byte message[200];
```

### Client Leave Lobby

If the client who created the group leaves then everyone leaves as a cick

The deconected client must send the CONNECTION request

> Client:

Type: LOBBY_LEAVE

> Respond of server:

**Sucess**

Type: LOBBY_LEAVE

**Failure**

Type: ERROR

- message: Error Message

```cpp
std::byte message[200];
```

> For all the peoples in the lobby

Type: LOBBY_USR_LEAVE

- id: id of the usr how leave

```cpp
packet_t p;

p.lobby.id # uuid_t
```
