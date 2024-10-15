CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -MMD

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

CLIENT_SOURCES = $(wildcard $(SRCDIR)/client*.c) $(wildcard $(SRCDIR)/common*.c)
CLIENT_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/client/%.o,$(CLIENT_SOURCES))
CLIENT_DEPS = $(CLIENT_OBJS:.o=.d)
CLIENT_TARGET = $(BINDIR)/client

SERVER_SOURCES = $(wildcard $(SRCDIR)/server*.c) $(wildcard $(SRCDIR)/common*.c)
SERVER_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/server/%.o,$(SERVER_SOURCES))
SERVER_DEPS = $(SERVER_OBJS:.o=.d)
SERVER_TARGET = $(BINDIR)/server

all: dir $(CLIENT_TARGET) $(SERVER_TARGET)

dir:
	@mkdir -p $(OBJDIR)/client $(OBJDIR)/server $(BINDIR)

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $@

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

$(OBJDIR)/client/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/server/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(CLIENT_DEPS) $(SERVER_DEPS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

rebuild: clean all

run-client: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)

run-server: $(SERVER_TARGET)
	./$(SERVER_TARGET)

.PHONY: all clean rebuild run-client run-server
