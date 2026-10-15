![voverlay_web_logo](./static/voverlay_web_logo.png)



# **VOverlay interface C++ class**

**v1.1.5**



# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [Library files](#library-files)
- [VOverlay class description](#voverlay-class-description)
  - [Class declaration](#class-declaration)
  - [getVersion method](#getversion-method)
  - [overlay method](#overlay-method)
- [Build and connect to your project](#build-and-connect-to-your-project)
  - [Build stand alone](#build-stand-alone)
  - [CMake options](#cmake-options)
  - [Connect to your project](#connect-to-your-project)
- [Portability](#portability)



# Overview

The **VOverlay** C++ library provides a standard interface for overlaying information on video frames across different implementations. The library itself does nothing; it just provides an interface. This standard for overlaying information on video is used in video streamer interfaces. Video streamer interfaces work exclusively with standardized interfaces, allowing users to create custom video overlay class implementations depending on their specific requirements. The **VOverlay** interface provides only one method, **overlay(...)**, to overlay information on video frames. This method is called by the video streamer for each frame of the video. Any implementation may include additional methods depending on the situation. The library depends on the [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class, which defines the data structure of the video frame. The repository does not contain the source code of the **Frame** library (see [Build and connect to your project](#build-and-connect-to-your-project)). It uses the C++17 standard.



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
| 1.1.5   | 16.10.2026   | - Sub-repositories removed: the Frame library is expected next to the library folder or must be added by the top-level project.<br />- Compiler warning and exploit mitigation flags added to the library target, standard C++ only (no compiler extensions).<br />- Protected default, copy and move special member functions of the interface class declared.<br />- Documentation of the class methods updated (return values, null pointer and thread safety).<br />- Build instructions updated. |



# Library files

The library is supplied as source code only. The user is provided with a set of files in the form of a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ------------ Main CMake file of the library.
src ----------------------- Folder with library source code.
    CMakeLists.txt -------- CMake file of the library.
    VOverlay.h ------------ Main library header file.
    VOverlayVersion.h ----- Header file with library version.
    VOverlayVersion.h.in -- File for CMake to generate version header.
    VOverlay.cpp ---------- C++ implementation file.
static -------------------- Folder with images used in this document.
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

protected:

    /// Default constructor. The class can be used as a base only.
    VOverlay() = default;

    /// Copy constructor.
    VOverlay(const VOverlay& src) = default;

    /// Move constructor.
    VOverlay(VOverlay&& src) = default;

    /// Copy assignment operator.
    VOverlay& operator= (const VOverlay& src) = default;

    /// Move assignment operator.
    VOverlay& operator= (VOverlay&& src) = default;
};
}
}
```



## getVersion method

The **getVersion()** method returns a string of the current version of the **VOverlay** class. Method declaration:

```cpp
static std::string getVersion();
```

**Returns:** string of the current version in the format "Major.Minor.Patch".

This method can be used without a **VOverlay** class instance. The method is thread-safe. Example:

```cpp
std::cout << "VOverlay class version: " << cr::video::VOverlay::getVersion() << std::endl;
```

Console output:

```bash
VOverlay class version: 1.1.5
```



## overlay method

The **overlay(...)** method overlays custom information on video frames. Method declaration:

```cpp
virtual bool overlay(cr::video::Frame& frame, void* data = nullptr) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| frame     | Video [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class object on which to overlay information. The frame data is changed in place. Each video overlay implementation should support all RAW pixel formats declared in the [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class (RGB24, BGR24, YUYV, UYVY, GRAY, YUV24, NV12, NV21, YU12, YV12). |
| data      | Pointer to information structure to overlay. The user may define the data structure format depending on the implementation. The method does not take ownership of the data. The value can be nullptr if the implementation does not need custom data. |

**Returns:** TRUE if information is overlaid or FALSE if not (unsupported frame format, invalid frame data, invalid custom data, etc.). The content of the frame after FALSE depends on the implementation.

The interface does not check the frame and the custom data: they are passed to the implementation as is, and the implementation must validate them before use. The interface does not define thread safety of the method: the implementation documents whether the method can be called from several threads.



# Build and connect to your project



## Build stand alone

The repository does not contain sub-repositories. The **Frame** library the **VOverlay** library depends on must be cloned into the same folder as **VOverlay**. The folder structure must be:

```bash
<work folder>
    VOverlay
    Frame
```

Typical commands to build the **VOverlay** library (use the URLs of the repositories provided to you):

```bash
git clone <VOverlay repository URL>
git clone <Frame repository URL>
cd VOverlay
mkdir build
cd build
cmake ..
make
```

On Windows use `cmake --build . --config Release` instead of `make`. If **VOverlay** is the top-level CMake project, the main CMakeLists.txt file adds the folder ../Frame before the library itself. If the folder does not exist CMake stops with an error.



## CMake options

**Table 2** - CMake options of the repository. In the options below ${PARENT} is the prefix defined by the top-level project (empty if **VOverlay** is the top-level project).

| Option                              | Default                    | Description |
| ----------------------------------- | -------------------------- | ----------- |
| ${PARENT}_VOVERLAY                  | ON                         | Build the library. |
| ${PARENT}_SUBMODULE_CACHE_OVERWRITE | ON                         | Forced rewriting of the option above in the CMake cache. The top-level project sets it to OFF when it includes **VOverlay** as a sub-repository. |
| CMAKE_BUILD_TYPE                    | Release (if not specified) | Build type. |



## Connect to your project

The **VOverlay** library does not add its dependency when it is included in another project: the **Frame** library must be added by your project. If it is not added, the build stops with a compile error that the header **Frame.h** is not found.

If you want to connect the **VOverlay** library to your CMake project as source code you can do it as follows. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeLists.txt
    yourLib.h
    yourLib.cpp
```

You can add the **VOverlay** and **Frame** repositories as submodules with the following commands (use the URLs of the repositories provided to you):

```bash
cd <your repository folder>
git submodule add <Frame repository URL> 3rdparty/Frame
git submodule add <VOverlay repository URL> 3rdparty/VOverlay
git submodule update --init --recursive
```

In your repository folder, **3rdparty/Frame** and **3rdparty/VOverlay** will be created. Alternatively, you can copy the **Frame** and **VOverlay** repositories to the **3rdparty** folder of your repository. The structure of your repository:

```bash
CMakeLists.txt
src
    CMakeLists.txt
    yourLib.h
    yourLib.cpp
3rdparty
    Frame
    VOverlay
```

Create a CMakeLists.txt file in the **3rdparty** folder. The CMakeLists.txt file should contain (the **Frame** library is added before the **VOverlay** library):

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
## CONFIGURATION
## 3rd-party submodules configuration
################################################################################
SET(${PARENT}_SUBMODULE_FRAME                           ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_FRAME)
    SET(${PARENT}_FRAME                                 ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_FRAME_TEST                            OFF CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_VOVERLAY                        ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VOVERLAY)
    SET(${PARENT}_VOVERLAY                              ON  CACHE BOOL "" FORCE)
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_FRAME)
    add_subdirectory(Frame)
endif()

if (${PARENT}_SUBMODULE_VOVERLAY)
    add_subdirectory(VOverlay)
endif()
```

The **3rdparty/CMakeLists.txt** file adds the **Frame** and **VOverlay** folders to your project. Your repository structure:

```bash
CMakeLists.txt
src
    CMakeLists.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    Frame
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



# Portability

The library contains no platform specific code: it does not depend on the byte order or on CPU instruction sets and uses standard C++17 only (compiler extensions are switched off). The interface class has no data members. The library was built without compiler warnings with MSVC 2022 (x86-64), GCC 12 and 13 and Clang 15 and 18 (x86-64 Linux) and with GCC 13 and Clang 15 and 18 for aarch64 (cross build).