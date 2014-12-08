#
# Variables:
#
CC = clang
BIN = YolOCR
SRC = $(wildcard *.c) 
OBJ = $(SRC:.c=.o)

#
# Flags d'erreurs:
#
ERROR_FLAGS = -Wall -Wextra -Werror -std=c99

#
# Flags pour le compilateur:
#
GTK_CFLAGS = $$(pkg-config --cflags gtk+-2.0)

CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)


#
# Flags pour l'editeur de liens:
#
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0)

LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)


#
# Construction du programme:
#
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -lSDLmain -lSDL -lSDL_image -lSDL_ttf -o $(BIN) $(OBJ) -lm


#
# Nettoyage:
#
clean:
	rm -f *.o *~ $(BIN) *.bmp
