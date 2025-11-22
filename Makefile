# Configuration
BUILD_DIR := build
EXECUTABLE := interpreter

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
