SRC = .
CFLAGS = -W -Wall -Ofast -march=native
LDFLAGS = 
CC = gcc

OBJ1 = o/sir.o o/read_nwk.o o/heap.o o/set_global.o o/linked_list.o o/pcg_rnd.o
# OBJ1 = o/sir.o o/read_nwk.o o/heap.o o/set_global.o o/create_dir_and_file.o o/linked_list.o o/pcg_rnd.o


all : sir

sir: $(OBJ1)
	$(CC) $(LDFLAGS) -o $@ $^ -lm

o/sir.o : $(SRC)/sir.c $(SRC)/sir.h $(SRC)/Makefile
	$(CC) $(CFLAGS) -c $(SRC)/sir.c -o $@

o/read_nwk.o : $(SRC)/read_nwk.c $(SRC)/sir.h $(SRC)/Makefile
	$(CC) $(CFLAGS) -c $(SRC)/read_nwk.c -o $@

o/heap.o : $(SRC)/heap.c $(SRC)/sir.h $(SRC)/Makefile
	$(CC) $(CFLAGS) -c $(SRC)/heap.c -o $@

o/set_global.o : $(SRC)/set_global.c $(SRC)/sir.h $(SRC)/Makefile
	$(CC) $(CFLAGS) -c $(SRC)/set_global.c -o $@

# o/create_dir_and_file.o : $(SRC)/create_dir_and_file.c $(SRC)/sir.h $(SRC)/Makefile
# 	$(CC) $(CFLAGS) -c $(SRC)/create_dir_and_file.c -o $@

o/linked_list.o : $(SRC)/linked_list.c $(SRC)/sir.h $(SRC)/Makefile
	$(CC) $(CFLAGS) -c $(SRC)/linked_list.c -o $@

o/pcg_rnd.o : $(SRC)/pcg_rnd.c $(SRC)/sir.h $(SRC)/Makefile
	$(CC) $(CFLAGS) -c $(SRC)/pcg_rnd.c -o $@