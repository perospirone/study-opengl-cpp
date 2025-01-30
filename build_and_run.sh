# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake if needed
if [ ! -f Makefile ]; then
  cmake ..
fi

# Build the project
make

# Run the executable (optional)
./main
