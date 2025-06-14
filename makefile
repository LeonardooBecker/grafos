COMMON_FLAGS = -pipe \
	       -ggdb3 -Wstrict-overflow=5 -fstack-protector-all \
	       -W -Wall -Wextra \
	       -Wcast-align \
	       -Wcast-qual \
	       -Wconversion \
	       -Wfloat-equal \
	       -Wformat-y2k \
	       -Winit-self \
	       -Winline \
	       -Winvalid-pch \
	       -Wmissing-declarations \
	       -Wmissing-field-initializers \
	       -Wmissing-format-attribute \
	       -Wmissing-include-dirs \
	       -Wmissing-noreturn \
	       -Wnormalized=nfc \
	       -Woverlength-strings \
	       -Wpacked \
	       -Wpointer-arith \
	       -Wredundant-decls \
	       -Wshadow \
	       -Wsign-compare \
	       -Wstack-protector \
	       -Wstrict-aliasing=2 \
	       -Wundef \
	       -Wunsafe-loop-optimizations \
	       -Wvolatile-register-var \

CFLAGS  = $(COMMON_FLAGS) \
          -std=c99 \
	  -Wbad-function-cast \
	  -Wmissing-prototypes \
	  -Wnested-externs \
	  -Wold-style-definition \
	  -Wstrict-prototypes \
	  -Wwrite-strings

CPPFLAGS = $(COMMON_FLAGS)

#------------------------------------------------------------------------------
.PHONY : all clean

#------------------------------------------------------------------------------
all : teste

grafo.o teste.o : %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

processa_grafo.o : processa_grafo.c
	$(CC) -c $(CFLAGS) -o $@ $^

fila.o : fila.c
	$(CC) -c $(CFLAGS) -o $@ $^

dfs.o : dfs.c
	$(CC) -c $(CFLAGS) -o $@ $^

dijkstra.o : dijkstra.c
	$(CC) -c $(CFLAGS) -o $@ $^

# grafo.o : grafo.cpp
# 	$(CC) -c $(CPPFLAGS) -o $@ $^

teste : teste.o grafo.o processa_grafo.o fila.o dfs.o dijkstra.o
	$(CC) $(CFLAGS) -o $@ $^

#------------------------------------------------------------------------------
clean :
	$(RM) teste *.o
