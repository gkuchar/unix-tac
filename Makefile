CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Werror -pedantic
LDFLAGS  :=

SRC_DIR   := src
BUILD_DIR := build

TARGETS := hftac hftac-naive

BLOCK_SIZE ?= 4096



all: $(TARGETS)

hftac: $(SRC_DIR)/hftac.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $(BUILD_DIR)/$@ $(LDFLAGS)

hftac-naive: $(SRC_DIR)/hftac-naive.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $(BUILD_DIR)/$@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)



.PHONY: all clean run-sample run-sample-custom-block

clean:
	rm -rf $(BUILD_DIR) generated_*.txt grader_*.out expected_*.out student_*.out

run-sample-naive: all
	./$(BUILD_DIR)/hftac-naive tests/sample.txt

run-sample-block: all
	./$(BUILD_DIR)/hftac tests/sample.txt

run-sample-custom-block: all
	./$(BUILD_DIR)/hftac --block-size $(BLOCK_SIZE) tests/sample.txt