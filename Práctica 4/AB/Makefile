# Nombre del ejecutable
TARGET = test

# Archivos fuente necesarios (solo los que usás realmente)
SRCS = test.c btree.c

# Archivos objeto generados automáticamente a partir de los .c
OBJS = $(SRCS:.c=.o)

# Compilador y flags
CC = gcc
CFLAGS = -Wall -g

# Regla principal: compila todo
all: $(TARGET)

# Cómo se construye el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regla genérica para compilar .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpieza de archivos intermedios
clean:
	rm -f *.o $(TARGET)
