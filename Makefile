
#
# Variables:
#
CC = clang
BIN =yolOCR
SRC = $(wildcard *.c) 
OBJ =$(SRC:.c=.o)

#
# Flags d'erreurs:
#
ERROR_FLAGS = -Wall -Wextra  -std=c99

#
# Flags pour le compilateur:
#
GTK_CFLAGS = $$( pkg-config --cflags  gtk+-2.0)

CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)


#
# Flags pour l'editeur de liens:
#
GTK_LDFLAGS = $$( pkg-config --libs gtk+-2.0)

LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)
LDLIBS=$$(pkg-config --libs gtk+-2.0)

#
# Construction du programme:
#
all:$(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -lSDLmain -lSDL -lSDL_image -o $(BIN) $(OBJ) -lm  findChar.c perfectImage.c interface.c tabPix.c
#
# Nettoyage:
#
clean:
	rm -f *.o *~ $(BIN) *.bmp
