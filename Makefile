CXX = g++
PYTHON_VERSION = 3.12
VENV = .venv
PYTHON = $(VENV)/bin/python
PIP = $(VENV)/bin/pip
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

CXXFLAGS = -Wall -std=c++17 -I./include -fvisibility=hidden $(shell $(PYTHON) -m pybind11 --includes 2>/dev/null)
LDFLAGS = -lpython$(PYTHON_VERSION)

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all system-deps setup venv install data sampledata rmdata pytest run clean

all: $(TARGET)

system-deps:
	sudo apt install g++ python$(PYTHON_VERSION)-dev python$(PYTHON_VERSION)-venv sqlite3

setup: venv install

venv:
	python$(PYTHON_VERSION) -m venv $(VENV)

install: venv
	$(PIP) install -r requirements.txt

data: setup
	$(PYTHON) scripts/create_database.py

sampledata: data
	sqlite3 library.db < sample_data.sql

rmdata:
	rm -f library.db library.db-journal library.db-shm library.db-wal

pytest: setup
	PYTHONPATH=pythonFunctions:. $(PYTHON) -m pytest tests/python_db

tests: pytest

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
