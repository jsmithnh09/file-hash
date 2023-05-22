CC = gcc
BUILD_DIR= ./build
SRC_DIR = ./src
CFLAGS = -Wall -O2 -I $(SRC_DIR)
OBJS = $(BUILD_DIR)/sha256.o $(BUILD_DIR)/sha1.o $(BUILD_DIR)/md5.o $(BUILD_DIR)/crc32.o
COMPILE = $(CC) $(CFLAGS)


all: hashfile

hashfile: $(SRC_DIR)/hashfile.c $(OBJS)
	$(COMPILE) -c $(SRC_DIR)/hashfile.c -o hashfile

$(BUILD_DIR)/sha256.o: $(SRC_DIR)/sha256.c $(SRC_DIR)/sha256.h
	$(COMPILE) -c $(SRC_DIR)/sha256.c -o $(BUILD_DIR)/sha256.o

$(BUILD_DIR)/sha1.o: $(SRC_DIR)/sha1.c $(SRC_DIR)/sha1.h
	$(COMPILE) -c $(SRC_DIR)/sha1.c -o $(BUILD_DIR)/sha1.o

$(BUILD_DIR)/md5.o: $(SRC_DIR)/md5.c $(SRC_DIR)/md5.h
	$(COMPILE) -c $(SRC_DIR)/md5.c -o $(BUILD_DIR)/md5.o

$(BUILD_DIR)/crc32.o: $(SRC_DIR)/crc32.c $(SRC_DIR)/crc32.h
	$(COMPILE) -c $(SRC_DIR)/crc32.c -o $(BUILD_DIR)/crc32.o