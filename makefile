CC = gcc
BUILD_DIR= ./build
SRC_DIR = ./src
CFLAGS = -std=c99 -Wall -O2 -I $(SRC_DIR) -D_FILE_OFFSET_BITS=64
OBJS = $(BUILD_DIR)/common.o $(BUILD_DIR)/sha256.o $(BUILD_DIR)/sha1.o $(BUILD_DIR)/md5.o $(BUILD_DIR)/crc32.o
COMPILE = $(CC) $(CFLAGS)
COMMONS = $(SRC_DIR)/common.c $(SRC_DIR)/common.h

all: hashfile

hashfile: $(SRC_DIR)/hashfile.c $(OBJS)
	$(COMPILE) $(OBJS) $(SRC_DIR)/hashfile.c -o hashfile

$(BUILD_DIR)/sha256.o: $(SRC_DIR)/sha256.c $(SRC_DIR)/sha256.h $(BUILD_DIR)/common.o
	$(COMPILE) -c $(SRC_DIR)/sha256.c -o $(BUILD_DIR)/sha256.o

$(BUILD_DIR)/sha1.o: $(SRC_DIR)/sha1.c $(SRC_DIR)/sha1.h $(BUILD_DIR)/common.o
	$(COMPILE) -c $(SRC_DIR)/sha1.c -o $(BUILD_DIR)/sha1.o

$(BUILD_DIR)/md5.o: $(SRC_DIR)/md5.c $(SRC_DIR)/md5.h $(BUILD_DIR)/common.o
	$(COMPILE) -c $(SRC_DIR)/md5.c -o $(BUILD_DIR)/md5.o

$(BUILD_DIR)/crc32.o: $(SRC_DIR)/crc32.c $(SRC_DIR)/crc32.h $(BUILD_DIR)/common.o
	$(COMPILE) -c $(SRC_DIR)/crc32.c -o $(BUILD_DIR)/crc32.o

$(BUILD_DIR)/common.o: $(COMONS)
	$(COMPILE) -c $(SRC_DIR)/common.c -o $(BUILD_DIR)/common.o
