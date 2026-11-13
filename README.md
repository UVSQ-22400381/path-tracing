Path Tracing Renderer
=====================

Authors
-------

* Isaac Ghorzi
* Sarah Khider
* Yusuf Dumlupinar
* Hamou Raik

Building
--------

### Dependencies

There are no dependencies as of today.

### How to build

You can do it manually with cmake and your backend of choice :

```sh
cmake -B <build_dir> [-DCMAKE_BUILD_TYPE=<build_type>]
# then call your build backend
```

Or you can use the `build_project.sh` script to do it as well with configurable build directory and type:

```sh
./build_project [build_type:-Debug] [build_dir:-build]
```

Testing
-------

Assuming you built the project, you just need to run one of these :

```sh
ctest --test-dir=<build_dir>
# or
./run_tests.sh [build_dir:-build]
```

_Note that the `run_tests.sh` script provides more details over which tests passed or failed._
