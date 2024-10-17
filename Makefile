CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -MMD

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

CLIENT_SOURCES = $(wildcard $(SRCDIR)/client*.c)
CLIENT_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/client/%.o,$(CLIENT_SOURCES))
CLIENT_DEPS = $(CLIENT_OBJS:.o=.d)
CLIENT_TARGET = $(BINDIR)/client

SERVER_SOURCES = $(wildcard $(SRCDIR)/server*.c)
SERVER_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/server/%.o,$(SERVER_SOURCES))
SERVER_DEPS = $(SERVER_OBJS:.o=.d)
SERVER_TARGET = $(BINDIR)/server

FILETEST_SOURCES = $(wildcard $(SRCDIR)/file_test*.c)
FILETEST_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/file_test/%.o,$(FILETEST_SOURCES))
FILETEST_DEPS = $(FILETEST_OBJS:.o=.d)
FILETEST_TARGET = $(BINDIR)/file_test

FILETEST2_SOURCES = $(wildcard $(SRCDIR)/file_test2*.c)
FILETEST2_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/file_test2/%.o,$(FILETEST_SOURCES))
FILETEST2_DEPS = $(FILETEST2_OBJS:.o=.d)
FILETEST2_TARGET = $(BINDIR)/file_test

all: dir $(CLIENT_TARGET) $(SERVER_TARGET) $(FILETEST_TARGET) $(FILETEST_TARGET2) 

dir:
	@mkdir -p $(OBJDIR)/file_test $(OBJDIR)/file_test2 $(OBJDIR)/client $(OBJDIR)/server $(BINDIR)

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $@

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

$(FILETEST_TARGET): $(FILETEST_OBJS)
	$(CC) $(CFLAGS) $(FILETEST_OBJS) -o $@

$(FILETEST2_TARGET): $(FILETEST2_OBJS)
	$(CC) $(CFLAGS) $(FILETEST2_OBJS) -o $@

$(OBJDIR)/client/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/server/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/file_test%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/file_test2%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(CLIENT_DEPS) $(SERVER_DEPS) $(FILETEST_DEPS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

rebuild: clean all

run-client: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)

run-server: $(SERVER_TARGET)
	./$(SERVER_TARGET)

.PHONY: all clean rebuild run-client run-server
