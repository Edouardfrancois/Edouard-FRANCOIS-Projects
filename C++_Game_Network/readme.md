# Epitech R-Type

The objective of this project and to reconstitute an [r-type](https://fr.wikipedia.org/wiki/R-Type) in multiplayer and several games at the same time. The server is multithreaded The graph uses SFML.

### author

---

Edouard Francois, Mayeul Kergall, Pierre Tran, Soheil Khalil, Yacine Abu-khalil

## Build

---

### On linux:

You need to install all of this package using your package manager

```
libgl1-mesa-dev udev libx11-dev xorg-dev freeglut3-dev libudev-dev libsfml-dev libflac-dev libvorbis-dev libopenal-dev
```

After Run:

```txt
mkdir -p ./build && cd build && cmake .. && make && cd ..
```

### Using Docker Compose

Run:

```txt
docker-compose --compatibility up --remove-orphans --build
```

If you don't have Docker Compose you can install it [hire](https://docs.docker.com/compose/install/).
