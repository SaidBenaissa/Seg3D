[![Build Status](https://jenkins.sci.utah.edu/job/check-manifest/badge/icon)](https://jenkins.sci.utah.edu/job)

Table of Contents
=================

  * [Seg3D](#seg3d)
    * [Installing Seg3D from source](#installing-seg3d-from-source)
      * [Compiler Requirements](#compiler-requirements)
        * [Windows Vista, 7, 8](#windows-vista-7-8)
        * [Mac OS X](#mac-os-x)
        * [Linux](#linux)
      * [Dependencies](#dependencies)
        * [Qt](#qt)
          * [Windows](#windows)
          * [Mac OS X](#mac-os-x-1)
          * [Linux](#linux-1)
      * [Compiling Seg3D](#compiling-seg3d)
    * [Seg3D Data](#seg3d-data)
    * [Seg3D Support](#seg3d-support)

<!-- Created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc) -->

# Seg3D
Seg3D (www.seg3d.org) is a free volume segmentation and processing tool developed by the NIH Center for Integrative Biomedical Computing at the University of Utah Scientific Computing and Imaging (SCI) Institute.

See the Seg3D site (www.seg3d.org) for detailed information about the software, platform support and documentation.

## Installing Seg3D from source

### Compiler Requirements

**C++11 64-bit compiler support is required.**

#### Windows Vista, 7, 8

The current source code was optimized for use with Visual Studio (VS2013).
The code should compile on Windows Vista, 7 and 8 using the Visual Studio Express versions as well. The code
has not been tested under Cygwin or MinGW compilers.

#### Mac OS X

The source code base was built with Xcode 4-6 as well as GNU Make and works for both 
environments on OS X 10.7+.

**Xcode 7 is not currently supported.**

#### Linux

The code base has been tested for use with GCC, and this is the recommended compiler for
linux. Compiler must support C++11.


### Dependencies

#### Qt

Before building Seg3D, please make sure that Qt 4.7 or higher has been installed on your system.

##### Windows

A Visual Studio binary build is available.
To our knowledge the Windows Visual Studio development libraries are only available in a 32-bit version.
A 64-bit version can be built from the source code download, configuring it as described on the Qt webpage.

##### Mac OS X

Qt binaries are available on the Qt website or can be built from source code.
Clang with C++11 support is required.

##### Linux

Qt is available from most package managers. Look for Qt 4.7-4.8.


### Compiling Seg3D

Once you have obtained a compatible compiler and installed Qt 4.7 on your system, you need to 
download and install CMake 2.8 (http://www.cmake.org/files/v2.8) to actually build the software.
CMake is a platform independent configuring system that is used for generating Makefiles,
Visual Studio project files, or Xcode project files.
Once CMake has been installed, run CMake from your build (bin) directory and give a path to the CMake Superbuild directory containing the master CMakeLists.txt file.
For example, on the command line:

```
cd bin
cmake ../Superbuild
```

The console version ccmake, or GUI version can also be used.
You may be prompted to specify your location of the Qt installation.
If you installed Qt in the default location, it should find Qt automatically.
After configuration is done, generate the make files or project files for your favorite
development environment and build.

Following the previous example, the Seg3D application will be built in bin/Seg3D.

A bash build script (build.sh) is also available for Linux and Mac OS X to simplify the process.
Usage information is available using the --help flag:

```
./build.sh --help
```

## Seg3D Data

Seg3D sample data (also used in the tutorial) is available [here](https://github.com/CIBC-Internal/Seg3DData/releases).

## Seg3D Support

For questions and issues regarding building the software from source, 
please email our support list: seg3d@sci.utah.edu
