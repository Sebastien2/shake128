CC=gcc

all: shake128make collisionmake

shake128make: affichage.c conversion.c keccak.c keccakp.c round.c shake128.c sponge.c stepMappings.c
	$(CC) affichage.c conversion.c keccak.c keccakp.c round.c shake128.c sponge.c stepMappings.c -o shake128 -lm

collisionmake: affichage.c conversion.c keccak.c keccakp.c round.c sponge.c stepMappings.c collisionN.c collisions.c
	$(CC) affichage.c conversion.c keccak.c keccakp.c round.c sponge.c stepMappings.c collisionN.c collisions.c -o collisions -lm
