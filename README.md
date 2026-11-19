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

Using the program
-------------------

In order to generate a render, you must provide a scene file as argument to the program. You should also make a `config.ini` file to change many parameters of the renderer such as the camera's position, the fov or the output image's dimensions. The config file must be in your current working directory, or else the program will default to set parameters which might not fit for the scene you're trying to render.

### Common formats

Here are some common data type formats in order to understand the next sections:

```
int    :: [0-9]+
float  :: [-+][0-9]+.[0-9]+
vector :: <float>;<float>;<float>
color  :: [0-9A-F]{6}
```

### Scene file specifications

Scene files can be used to describe the composition of the scene you want to render. To put it simply, it's a list of 3D shapes preceded by the total amount of shapes. Entries beginning with a S are spheres, and those that begins with a B are boxes. Each of those shape type have their own definition detailled below, but they both end with an RGB color as a hexadecimal value. The color defaults to black if not provided.

Here is a more detailled description of the file format:

```
<N:int>

S <center:vector> <radius:float> [<color>]
B <A:vector> <B:vector> [<color>]
```

### Configuration specifications

The configuration can be written as a list of `key=value` pairs. Some values might require to be formatted in a certain way to be parsed correctly.

You may configure 5 distinct parameters:
- `cam_pos` and `target` as 3D vectors.
- `fov` as a float.
- `width` and `height` as integers (`size_t`).

Any key that is not listed here is ignored. Here are the default values if no configuration is defined:

```
cam_pos=0.0;0.0;0.0
target=1.0;0.0;0.0
fov=60.0
height=512
width=512
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
