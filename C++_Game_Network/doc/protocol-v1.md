# Protocol R-type

---

Le protocol est de type binaire.

## Definition:

un **uuid** est coder sur **16 octets**.
On appelera **packetuuid** l'id du packet coder sur **16 octets (uuid)**.
un **packet_type** est un nombre coder sur **4 octets non signer**. Selon sa valeur **l'objectif su packet sera differante**.
Tout les messages d'erreur sont negatif.

Il peut avoir ces valeurs pour les valeurs positives:

- T_CONNECTION = 0
- T_BEGIN_GAME = 1
- T_CREATE_ENTITY = 2
- T_BEGIN_MOUVE = 3
- T_PING_ENTITY = 4
- T_END_MOUVE = 5
- T_UUID_GET_INFO = 6
- T_UUID_MABY_MISS = 7

On appelera **float** tout nombre flotant sous la norme **IEER 754**.

Il est composer d'un header sur **52 octets**. Et d'un **body** variable de **x octets**.

### Header

Le header est definie de la façons suivante dans l'ordre:

- un uuid representant l'id de l'envoyeur
- un uuid representant le lobby de l'envoyeur
- un uuid representant l'id du packet (pour faire le lien entre l'envoie -> retour)
- un packet_type representant le type du packet.

Si l'**uuid** representant l'id de l'envoyeur est que des **0 sur 16 octets** alor le message **viens du server** et non d'un des joueurs.

Le client doit generer lui meme sont packetuuid.

## Le body

Le body du packet change en fonction du packet_type definie dans le header.

## Protocol

Le protocol utiliser est **UDP**

### Connection

> #### Client

Le packet_type doit etre egal a **T_CONNECTION**

> Header

```txt
remplie de 0 (16 octets)
remplie de 0 (16 octets)
packetuuid (16 octets)
packet_type (T_CONNECTION) (4 octets)
```

##### Sucess

Le server remplira les 16 premiers octets pour **l'uuid du client** puis 16 octets pour **l'uuid du lobby** puis 16 octets pour l'uuid du packet (_packetuuid_).

Il met dans **le body la taille de réference de l'ecrant** (x et y chaqun sur 2 octets signed)

> Header

```txt
your new Uuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_CONNECTION) (8 octets)
```

```txt
x (2 octets)
y (2 octets)
```

##### Falure

> Header

```txt
remplie de 0 (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERR0R_LOBBY_FULL or T_ERROR) (4 octets)
```

Le **packet_type** peut avoir les valeurs suivante:

> T_ERR0R_LOBBY_FULL = -2: il y a deja 4 jouers connecter et vous ne pouvez pas rejoindre la partie.

> T_ERROR = - 1: une Erreur coter server est survenue et le client ne peut pas se connecter.

### Lancement du jeux

Pour **lancer le jeux un des joeurs doit envoyeur ce packet: T_BEGIN_GAME**

> #### Client

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_BEGIN_GAME) (4 octets)
```

> #### Server

##### Sucess

Le server renvoie a tous le joueurs le packet de type T_BEGIN_GAME avec leur possition sur le screen de reference (x et y coder chaqun sur 2 octets signed)

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 bits)
packet_type (T_CONNECTION) (4 bits)
```

> Body

```txt
x (2 octets)
y (2 octets)
```

##### Falure

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR) (4 octets)
```

### Creation d'une entiter

> #### Client

Le client envoie le type d'entiter (**id**) créer sur 2 octets signed avec **sa position** (x et y sur 2 octets signed).
Sur **1 octets (true of false)** l'entiter peut directement **bouger** en envoyant **sa direction** en degrer (float 4 octets), **2 vecteur** (Vx et Vy) pour **la direction** sur 2 octets signed.

Si il ne **bouge pas** les element apres sa direction **ne sont pas nesesaire**.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_CREATE_ENTITY) (4 octets)
```

> Body

```txt
identity id (2 octets)
x (2 octets)
y (2 octets)
Degree (4 octets)
Vx (2 octets)
Vy (2 octets)
```

> #### Server

##### Sucess

Le server cree l'entity et renvoye a touts le monde qu'une entity de type id a ete creer avec sa propre uuid avec sa possition x et y sur 2 octets signed et si elle bouge, il transmet les meme information si dessus.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_CREATE_ENTITY) (4 octets)
```

> Body

```txt
identity id (2 octets)
x (2 octets)
y (2 octets)
Degree (4 octets)
Vx (2 octets)
Vy (2 octets)
uuid of the entity (16 octets)
```

##### Falure

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_IMPOSIBLE_TO_CREATE_ENTITY) (4 octets)
```

Si l'id de l'entity est inconue le server renvoie:

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_UNKNOWN_ENTITY_ID) (4 octets)
```

### Mouvement d'une entity

#### Debut de movement

> #### Client

Le packet_type doit etre egal a **T_BEGIN_MOUVE**

Le client envoie **la vitesse** coder chaqun sur 2 octet signed avec **l'angle en degree** (float sur 4 octets)

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_BEGIN_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
Degree (float 4octets)
Velocity (2 octets)
```

Si le client **change de Direction** ou de **vitesse** ce packet doit etre aussi envoyer sans envoyer le packet **(T_END_MOUVE)**.

> #### Server

##### Sucess

Le server renvoie a tous les joeurs que t'elle **uuild** a commencer a bouger avec les informations qui lui permete de bouger.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_BEGIN_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
Degree (float 4octets)
Velocity (2 octets)
```

##### Falure

L'erreur est renvoyer qu'au joeurs qui a demander de bouger.
Le server renvoie la possition actuel sur x et y sur 2 octets signed avec l'uuid de l'element qui a voulu etre bouger.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_IMPOSIBLE_TO_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

Si l'uuid de l'entity est inconue le server renvoie:

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_UNKNOWN_ENTITY_ID) (4 octets)
```

#### Tout au long du jeux (packet de check/syscronisation de possition)

Pour que le server puise **etre toujours syncroniser avec le client** et **resoudre un packet lost**, Le client doit **regulierement** (chaque _X_ frame) envoyer ces informations de **ces uuid** en interne au server.

Si **le server** detecte qu'**un client n'envoie pas réguliairement les informations d'un uuid**, le server previendra que le **client** a peut etre **un entity_uuid** manquant dans sa base donner (**T_UUID_MABY_MISS**).
Si le client ne l'a pas il peut demander au server les informations d'un uuid au server (**T_UUID_GET_INFO**).

> #### Client

x et y sont les possitions chaqun sur 2 octets signed.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_PING_ENTITY) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

> #### Server

x et y sont les possitions chaqun sur 2 octets signed.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_PING_ENTITY) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

##### Falure

Si l'uuid est **inconue** le server renvera se packet (si cela arrive nous vous conseillons de **recréer l'entity**)

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_UNKNOWN_ENTITY_ID) (4 octets)
```

#### Fin de movement

> #### Client

Le packet_type doit etre egal a **T_END_MOUVE**
Le client renvoie ces positions actuel pour **gerer la syncronisation entre le server et les clients** (2 octets signed)

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_END_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

> #### Server

##### Sucess

Le server renvoie a tous les joeurs qu' une entiter a finie de bouger avec sa possition (x et y 2 octets signed).

```txt
UUid of the player how begin to move (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_END_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

**Si il y a une colision, ce packet est aussi envoyer.**

##### Falure

L'erreur est renvoyer qu'au joeurs qui a demander la fin d'un mouvement.
Le server renvoie la possition actuel sur x et y sur 2 octets signed avec l'uuid de l'element qui a voulu etre bouger.

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_IMPOSIBLE_TO_STOP_MOVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

Si l'uuid de l'entity est inconue le server renvoie:

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_UNKNOWN_ENTITY_ID) (4 octets)
```

#### Recuperer des informations d'un uuid au server

> #### Client

Si le **client** veut des informations sur une **entity** le client peut
envoyer se packet (T_UUID_GET_INFO).

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_UUID_GET_INFO) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
```

> #### Server

##### Sucess

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_BEGIN_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
Degree (4 octets)
identity id (2 octets)
x (2 octets)
y (2 octets)
Vx (2 octets)
Vy (2 octets)
```

##### Falure

Si l'uuid de l'entity est inconue le server renvoie:

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_UNKNOWN_ENTITY_ID) (4 octets)
```

#### Possibiliter de manque d'une information du client sur un uuid

> #### Server

Si le server **detecte** que **le client ne revoie pas assez les informations d'un uuid** le server peut **signaler** au client qu'il lui manque peut etre une entity dans **sa base de donner** (T_UUID_MABY_MISS).

```txt
full 0 (16 octets)
lobbyUuid (16 octets)
full 0 (16 octets)
packet_type (T_BEGIN_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
```

Le client peut alor envoyer (T_UUID_GET_INFO) si cette uuid n'est pas dans sa base de donner interne.

#### Destruction d'un entiter

> #### Server

##### Sucess

Le server renvoie a tous les joeurs qu' une entiter a eter detruite avec sa possition (x et y 2 octets signed).

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_END_MOUVE) (4 octets)
```

> Body

```txt
entity uuid (16 octets)
x (2 octets)
y (2 octets)
```

##### Falure

Si l'uuid de l'entity est inconue le server renvoie ou si l'entity n'est pas detruite

> Header

```txt
senderUuid (16 octets)
lobbyUuid (16 octets)
packetuuid (16 octets)
packet_type (T_ERROR_UNKNOWN_ENTITY_ID | T_ERROR_ENTITY_NOT_DESTROY) (4 octets)
```

#### Reconnection

Si durant la partie le server resoie un packet de connection (T_CONNECTION)
le server revera toutes les informations sur toutes les entity de la games:

- T_UUID_GET_INFO
- T_INVENTORY
- T_USE_BOOST
