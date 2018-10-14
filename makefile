#the compiler : gcc
CC=gcc
#Compiler flag
CFLAGS1 = -std=c99
CFLAGS2 = -ljpeg

#the build target executable

TARGET = exec


exec: drone.o encryption.o catch.o
	$(CC) $(CFLAGS1) drone.o encryption.o catch.o $(CFLAGS2) -o $(TARGET)
drone.o: drone.c
	$(CC) -c $(CFLAGS1) drone.c $(CFLAGS2) -o drone.o

catch.o: catch.c
	$(CC) -c $(CFLAGS1) catch.c $(CFLAGS2) -o catch.o
encryption.o: encryption.c
	$(CC) -c $(CFLAGS1) encryption.c $(CFLAGS2) -o encryption.o
decryption: decryption.c
	$(CC) $(CFLAGS1) decryption.c $(CFLAGS2) -o decrypt

clean:
	$(RM) $(TARGET) *.o
