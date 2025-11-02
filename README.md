![voverlay_web_logo](./static/voverlay_web_logo.png)



# **VOverlay interface C++ class**

**v1.1.4**



# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [Library files](#library-files)
- [VOverlay class description](#voverlay-class-description)
  - [Class declaration](#class-declaration)
  - [getVersion method](#getversion-method)
  - [overlay method](#overlay-method)
- [Build and connect to your project](#build-and-connect-to-your-project)



# Overview

The **VOverlay** C++ library provides a standard interface for overlaying information on video frames across different implementations. The library itself does nothing; it just provides an interface. This standard for overlaying information on video is used in video streamer interfaces. Video streamer interfaces work exclusively with standardized interfaces, allowing users to create custom video overlay class implementations depending on their specific requirements. The **VOverlay** interface provides only one method, **overlay(...)**, to overlay information on video frames. This method is called by the video streamer for each frame of the video. Any implementation may include additional methods depending on the situation. The library depends on the [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class, which defines the data structure of the video frame (source code included, Apache 2.0 license). It uses the C++17 standard. The library is licensed under the **Apache 2.0** license.



# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                              |
| ------- | ------------ | ------------------------------------------------------- |
| 1.0.0   | 31.08.2023   | First version.                                          |
| 1.1.0   | 13.12.2023   | - Virtual destructor added.<br />- Frame class updated. |
| 1.1.1   | 20.03.2024   | - Documentation updated.<br />- Frame class updated.    |
| 1.1.2   | 17.05.2024   | - Documentation updated.                                |
| 1.1.3   | 10.07.2024   | - CMake updated.<br />- Frame class updated.            |
| 1.1.4   | 02.11.2024   | - Fix code mistakes.<br />- Fix documentation mistakes.  |



# Library files

The library is supplied as source code only. The user is provided with a set of files in the form of a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ------------ Main CMake file of the library.
3rdparty ------------------ Folder with third-party libraries.
    CMakeLists.txt -------- CMake file to include third-party libraries.
    Frame ----------------- Folder with Frame library source code.
src ----------------------- Folder with library source code.
    CMakeLists.txt -------- CMake file of the library.
    VOverlay.h ------------ Main library header file.
    VOverlayVersion.h ----- Header file with library version.
    VOverlayVersion.h.in -- File for CMake to generate version header.
    VOverlay.cpp ---------- C++ implementation file.
```



# VOverlay class description



## Class declaration

The **VOverlay.h** file contains the **VOverlay** class declaration. Class declaration:

```cpp
namespace cr
{
namespace video
{
/// Video overlay interface class.
class VOverlay
{
public:

    /// Class destructor.
    virtual ~VOverlay();

    /// Get string of the current class version.
    static std::string getVersion();

    /// Overlay information on the video.
    virtual bool overlay(cr::video::Frame& frame, void* data = nullptr) = 0;
};
}
}
```



## getVersion method

The **getVersion()** method returns a string of the current version of the **VOverlay** class. Method declaration:

```cpp
static std::string getVersion();
```

This method can be used without a **VOverlay** class instance. Example:

```cpp
cout << "VOverlay class version: " << VOverlay::getVersion() << endl;
```

Console output:

```bash
VOverlay class version: 1.1.4
```



## overlay method

The **overlay(...)** method overlays custom information on video frames. Method declaration:

```cpp
virtual bool overlay(cr::video::Frame& frame, void* data = nullptr) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| frame     | Video [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class object on which to overlay information. Each video overlay implementation should support all RAW pixel formats declared in the [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class (RGB24, BGR24, YUYV, UYVY, GRAY, YUV24, NV12, NV21, YU12, YV12). |
| data      | Pointer to information structure to overlay. The user may define the data structure format depending on the implementation. |

**Returns:** TRUE if information is overlaid or FALSE if not (unsupported frame format, invalid frame data, etc.).



# Build and connect to your project

Typical commands to build **VOverlay** library:

```bash
git clone https://github.com/ConstantRobotics-Ltd/VOverlay.git
cd VOverlay
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

If you want connect **VOverlay** library to your CMake project as source code you can make as follows. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

You can add the **VOverlay** repository as a submodule with the following commands:

```bash
cd <your respository folder>
git submodule add https://github.com/ConstantRobotics-Ltd/VOverlay.git 3rdparty/VOverlay
git submodule update --init --recursive
```

In your repository folder, **3rdparty/VOverlay** will be created, which contains files of the **VOverlay** repository with the **Frame** subrepository. Alternatively, you can copy the **VOverlay** repository to the **3rdparty** folder of your repository. The new structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    VOverlay
```

Create a CMakeLists.txt file in the **3rdparty** folder. The CMakeLists.txt file should contain:

```cmake
cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
add_subdirectory(VOverlay)
```

The **3rdparty/CMakeLists.txt** file adds the **VOverlay** folder to your project. Your repository's new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    VOverlay
```

Next, you need to include the 3rdparty folder in the main **CMakeLists.txt** file of your repository. Add the following line at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next, you need to include the **VOverlay** library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} VOverlay)
```

Done!