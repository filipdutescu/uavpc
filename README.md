[![Actions Status](https://github.com/filipdutescu/uavpc/workflows/Ubuntu/badge.svg)](https://github.com/filipdutescu/uavpc/actions)
[![codecov](https://codecov.io/gh/filipdutescu/uavpc/branch/master/graph/badge.svg)](https://codecov.io/gh/filipdutescu/uavpc)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/filipdutescu/uavpc)](https://github.com/filipdutescu/uavpc/releases)

# UAVPC - Unmanned Aerial Vehicle Pose-based Control

A small utility intended to be used with a Raspberry Pi and MPU 6050 IMU. Its goal
is to control the flight of a drone using hand gestures (made with the MPU 6050)
and display its video feed. It can also detect poses in the video stream through
[OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose).

The names comes from the initial goal, of using the body poses to control the flight
of the drone, but due to the unreliable nature of the UDP protocol used in my drone
to send the video stream, it was unreliable. This lead to changing it to use gestures
made with the MPU 6050.

## Features

* Gesture recognition with the MPU 6050 using a Kalman filter. Supported gestures
include rotations around the X and Y axis of the IMU.
* Keyboard commands (as seen in the `uavpc::Joystick` class) for:
  * Sending commands to the drone, to compensate lack of more gestures
  * Toggling on/off pose recognition
  * Toggling on/off video stream saving
* Drone control using either commands or gestures.
  * Currently supported drones: DJI Tello (and any drone using the same API by using
the existing classes).

## Getting Started

These instructions will get you a copy of the project up and running on your local
machine for development and testing purposes.

### Prerequisites

The project is meant to run on a Raspberry Pi, connected to a MPU 6050 IMU and a
DJI Tello Drone. While not required, I found that using USB tethering on my
smartphone was a sufficient way to control the Raspberry Pi in a desktop mode
(using VNC).

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)
* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *GCC*,
*Clang*
* **OpenPose v1.7.0** - found at [https://github.com/CMU-Perceptual-Computing-Lab/openpose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
  * In order to make [OpenPose v1.7.0](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
work with [OpenCV 4.5.0](https://github.com/opencv/opencv), I used the patch found
at [vendor/openpose-opencv4.patch](vendor/openpose-opencv4.patch).
* **OpenCV 4.5.0** - found at [https://github.com/opencv/opencv](https://github.com/opencv/opencv)
* **Linux Kernel I2C module** - found in the official repos of ArchLinux, RaspbianOS
and Ubuntu. Also found at [https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/](https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/)
* **Catch2** (for tests) - found at [https://github.com/catchorg/Catch2/](https://github.com/catchorg/Catch2/)

> ***Note:*** *You also need to be able to provide ***CMake*** a supported
[generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).*

### Installing

It is fairly easy to install the project, all you need to do is clone or download
it from [GitHub](https://github.com/filipdutescu/uavpc).

If you wish to clone the repository, rather than download it, you simply need
to run:

```bash
git clone https://github.com/filipdutescu/uavpc.git
```

To install an [already built project](README.md#Building-the-project), you need
to run the `install` target with CMake. For example:

```bash
cmake --build build --target install --config Release

# a more general syntax for that command is:
cmake --build <build_directory> --target install --config <desired_config>
```

or

```bash
make install
```

which will also build the project.

## Building the project

To build the project, all you need to do, ***after correctly
[installing the project](README.md#Installing)***, is run a similar **CMake** routine
to the the one below:

```bash
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target install
```

or

```bash
make release
```

> ***Note:*** *The custom ``CMAKE_INSTALL_PREFIX`` can be omitted if you wish to
install in [the default install location](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html).*

## Generating the documentation

In order to generate documentation for the project, you need to configure the build
to use Doxygen. This is easily done, by modifying the workflow shown above as follows:

```bash
mkdir build/ && cd build/
cmake .. -Duavpc_ENABLE_DOXYGEN=1 -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target doxygen-docs
```

> ***Note:*** *This will generate a `docs/` directory in the **project's root directory**.*

## Running the tests

By default, the template uses [Catch2](https://github.com/catchorg/Catch2/) for
unit testing. Unit testing can be disabled in the options, by setting the
`ENABLE_UNIT_TESTING` (from
[cmake/StandardSettings.cmake](cmake/StandardSettings.cmake)) to be false. To run
the tests, simply use CTest, from the build directory, passing the desire
configuration for which to run tests for. An example of this procedure is:

```bash
cd build          # if not in the build directory already
ctest -C Release  # or `ctest -C Debug` or any other configuration you wish to test

# you can also run tests with the `-VV` flag for a more verbose output (i.e.
#Catch2 output as well)
```

To build and run tests you can also use:

```bash
make test
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our how you can
become a contributor and the process for submitting pull requests to us.

## Versioning

This project makes use of [SemVer](http://semver.org/) for versioning. A list of
existing versions can be found in the
[project's releases](https://github.com/filipdutescu/uavpc/releases).

## Authors

* **Filip-Ioan Dutescu** - [@filipdutescu](https://github.com/filipdutescu)

## License

This project is licensed under the [Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0)
\- see the [LICENSE](LICENSE) file for details.
