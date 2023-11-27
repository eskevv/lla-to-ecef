***Option A (Makefile-no tests):***    
    `make && make clean && ./$(basename "$PWD")`

***Option B (CMake-no tests):***  
    `cmake -Bbuild -G"Unix Makefiles" -DUSING_TESTS=OFF && cmake --build build && ./$(basename "$PWD")`  

***Option C (CMake-with tests | includes dependency installation):***  
    `cmake -Bbuild -G"Unix Makefiles" && cmake --build build && ./$(basename "$PWD") && ./tests_app`

***Option D (CMake-with tests | if Catch2 is already installed locally and the install path is on CMAKE_PREFIX_PATH (defaults to /usr/local/lib/)):***  
    `cmake -Bbuild -G"Unix Makefiles" -DCATCH_LOCAL=ON && cmake --build build && ./$(basename "$PWD") && ./tests_app`

***Option E (CMake-with tests | manual cloning):***  
    1. `mkdir vendor && git -C vendor/ clone https://github.com/catchorg/Catch2`  
    2. `cmake -Bbuild -G"Unix Makefiles" -DEXTERNAL_GIT=OFF && cmake --build build && ./$(basename "$PWD") && ./tests_app`  

---

![alt text]("preview.jpg")

### About Tests
* I wanted to include additional tests just to be sure things work corectly and to showcase what testing framework I use. I opted for the  
Catch2 framework here that works very well and is easy to setup. The few tests I created are placed in the tests directory next to the src dir.  
I tested some of the assignment problems and also a different way to calculate the velocity, although not many tests cases were actually implemented.

---
### Additional Notes
* Built and tested on a linux environment
* File was too large to include the Catch2 source so I addded it as an option
* CMakeLists was included for OS compatability just to be safe (it also includes tests)

---
### Interpolation Method
* Although not required I felt that what appeared to be a nonlinear velocity from the given object resulted in less  
accurate results if I went for velocity interpolation. For this random "object" I chose to interpolate the two closest coordinates  
for the given time and then compute the velocity between the generated point and the one that came before.

---
### Project Layout
* Most of my code was spread as utility functions inside of one namespace
* Interpolation was done on the ecef coordinates
* I decided to inline mostly everything to reduce project size and complexity

* The wgs namespace is spread throughout a couple of files: 
1. converter.hpp:
        the wgs84 parameter constants
        the lla to ecef conversion functions
2. parser.hpp:
        abstract template parser class
        lla constructor class
3. models.hpp:
        the vector class
        the coordinate system models
4. calculator.hpp:
        contains interpolation logic
        velocity computation given a set of data from the eces container
5. main.cpp    
        the main velocity at time given function for this assignment 
