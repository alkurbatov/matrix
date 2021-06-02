# matrix
Simple implementation of a matrix.

## Requirements
* A compiler with C++17 support.
* cmake (>= 3.18).
* gtest (>= 1.10.0).

## Test instructions
(!) Tested on OS X, could cause build issues on other platforms.

### OS X (cmdline)
```bash
# Create build directory.
$ mkdir build && cd build

# Generate a Makefile.
# Use 'cmake -DCMAKE_BUILD_TYPE=Debug ../' if debuginfo is needed
$ cmake ../

# Build the project.
$ make

# Launch the tests.
$ ./bin/test_matrix
```

### Windows (Visual Studio)
```bat
:: Create build directory.
$ mkdir build
$ cd build

:: Create Visual Studio project files.
$ cmake ../ -G "Visual Studio 16 2019"

:: Build and run the project using Visual Studio.
$ start test_matrix.sln
```

## License
Copyright (c) 2021 Alexander Kurbatov

Licensed under the [MIT license](LICENSE).
