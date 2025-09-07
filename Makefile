# Makefile for Simplified AES Implementation
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
TARGET = aes
SOURCES = enc.c

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o *.exe

# Install (copy to /usr/local/bin)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Test the implementation
test: $(TARGET)
	@echo "Running comprehensive test suite..."
	@./test.sh

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the AES program (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  test     - Run basic tests"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  help     - Show this help message"

.PHONY: all clean test install uninstall help