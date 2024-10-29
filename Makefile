CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -MMD

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# CLIENT_SOURCES = $(wildcard $(SRCDIR)/client.c)
# CLIENT_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/client/%.o,$(CLIENT_SOURCES))
# CLIENT_DEPS = $(CLIENT_OBJS:.o=.d)
# CLIENT_TARGET = $(BINDIR)/client

# SERVER_SOURCES = $(wildcard $(SRCDIR)/server.c)
# SERVER_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/server/%.o,$(SERVER_SOURCES))
# SERVER_DEPS = $(SERVER_OBJS:.o=.d)
# SERVER_TARGET = $(BINDIR)/server

# FILETEST_SOURCES = $(wildcard $(SRCDIR)/file_test.c) $(wildcard $(SRCDIR)/file_common.c) 
# FILETEST_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/file_test/%.o,$(FILETEST_SOURCES))
# FILETEST_DEPS = $(FILETEST_OBJS:.o=.d)
# FILETEST_TARGET = $(BINDIR)/file_test

# FILETEST2_SOURCES = $(wildcard $(SRCDIR)/file_test2.c) $(wildcard $(SRCDIR)/file_common.c)
# FILETEST2_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/file_test/%.o,$(FILETEST2_SOURCES))
# FILETEST2_DEPS = $(FILETEST2_OBJS:.o=.d)
# FILETEST2_TARGET = $(BINDIR)/file_test2

# CLIENT_SOURCES = $(wildcard $(SRCDIR)/client.c)
# CLIENT_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/client/%.o,$(CLIENT_SOURCES))
# CLIENT_DEPS = $(CLIENT_OBJS:.o=.d)
# CLIENT_TARGET = $(BINDIR)/client

TCP_SERVER_SRCS = $(wildcard $(SRCDIR)/tcp_server.c)
TCP_SERVER_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/tcp/%.o,$(TCP_SERVER_SRCS))
TCP_SERVER_DEPS = $(TCP_SERVER_OBJS:.o=.d)
TCP_SERVER_TARGET = $(BINDIR)/tcp_server

TCP_CLIENT_SRCS = $(wildcard $(SRCDIR)/tcp_client.c)
TCP_CLIENT_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/tcp/%.o,$(TCP_CLIENT_SRCS))
TCP_CLIENT_DEPS = $(TCP_CLIENT_OBJS:.o=.d)
TCP_CLIENT_TARGET = $(BINDIR)/tcp_client

TCP_SERVER2_SRCS = $(wildcard $(SRCDIR)/tcp_server2.c)
TCP_SERVER2_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/tcp2/%.o,$(TCP_SERVER2_SRCS))
TCP_SERVER2_DEPS = $(TCP_SERVER2_OBJS:.o=.d)
TCP_SERVER2_TARGET = $(BINDIR)/tcp_server2

TCP_CLIENT2_SRCS = $(wildcard $(SRCDIR)/tcp_client2.c)
TCP_CLIENT2_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/tcp/%.o,$(TCP_CLIENT2_SRCS))
TCP_CLIENT2_DEPS = $(TCP_CLIENT2_OBJS:.o=.d)
TCP_CLIENT2_TARGET = $(BINDIR)/tcp_client2

all: dir $(TCP_SERVER_TARGET) $(TCP_CLIENT_TARGET) \
	$(TCP_SERVER2_TARGET) $(TCP_CLIENT2_TARGET) \
	# $(CLIENT_TARGET) $(SERVER_TARGET) \
	# $(FILETEST_TARGET) $(FILETEST2_TARGET) \
	

dir:
	@mkdir -p $(OBJDIR)/tcp $(OBJDIR)/tcp2 $(OBJDIR)/file_test $(OBJDIR)/client $(OBJDIR)/server $(BINDIR)

# $(CLIENT_TARGET): $(CLIENT_OBJS)
# 	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $@

# $(SERVER_TARGET): $(SERVER_OBJS)
# 	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

# $(FILETEST_TARGET): $(FILETEST_OBJS)
# 	$(CC) $(CFLAGS) $(FILETEST_OBJS) -o $@

# $(FILETEST2_TARGET): $(FILETEST2_OBJS)
# 	$(CC) $(CFLAGS) $(FILETEST2_OBJS) -o $@

$(TCP_CLIENT_TARGET): $(TCP_CLIENT_OBJS)
	$(CC) $(CFLAGS) $(TCP_CLIENT_OBJS) -o $@

$(TCP_SERVER_TARGET): $(TCP_SERVER_OBJS)
	$(CC) $(CFLAGS) $(TCP_SERVER_OBJS) -o $@

$(TCP_CLIENT2_TARGET): $(TCP_CLIENT2_OBJS)
	$(CC) $(CFLAGS) $(TCP_CLIENT2_OBJS) -o $@

$(TCP_SERVER2_TARGET): $(TCP_SERVER2_OBJS)
	$(CC) $(CFLAGS) $(TCP_SERVER2_OBJS) -o $@

# $(OBJDIR)/client/%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJDIR)/server/%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJDIR)/file_test%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJDIR)/file_test2%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/tcp/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/tcp2/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(TCP_CLIENT_DEPS) $(TCP_SERVER_DEPS) $(TCP_CLIENT2_DEPS) $(TCP_SERVER2_DEPS)
# $(CLIENT_DEPS) $(SERVER_DEPS) $(FILETEST_DEPS) $(FILETEST2_DEPS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

rebuild: clean all

run-client: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)

run-server: $(SERVER_TARGET)
	./$(SERVER_TARGET)

.PHONY: all clean rebuild run-client run-server
