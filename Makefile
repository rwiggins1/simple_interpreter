# Configuration
BUILD_DIR := build
EXECUTABLE := interpreter
SRC_DIR := simple_interpreter

.PHONY: all build clean run

all: build

# Build project
build: 
	@echo "building..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && $(MAKE) -j4
	@echo "Build complete! Executable: $(BUILD_DIR)/$(EXECUTABLE)"


# Clean build
clean:
	@echo "Cleaning $(BUILD_DIR) directory..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Build and run
run: build
	@echo ""
	@echo "Running $(EXECUTABLE):"
	@echo "----------------------------"
	@./$(BUILD_DIR)/$(EXECUTABLE)

# Lint code with clang-tidy
lint:
	@echo "Running clang-tidy on source files..."
	@find $(SRC_DIR) -name "*.cpp" -o -name "*.hpp" | xargs clang-tidy -p $(BUILD_DIR)
	@echo "Lint complete!"
