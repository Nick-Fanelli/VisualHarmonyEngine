# Visual Harmony Engine

Easy to learn and use 2D game engine written in C++ with OpenGL.

## Quick Links

1. [Cloning and Building Project](#cloning-and-building-the-project)
1. [Changelog](https://github.com/Nick-Fanelli/HarmonyEngine/blob/main/CHANGELOG.md)
1. [Instructions for Building Changelog](#creating-the-auto-changelog)
1. [How to Contribute](#how-to-contribute)

---

## Cloning and Building the Project

1. [Mac Instructions](#getting-started-with-mac)
1. [Windows Instructions](#getting-started-with-windows)
1. [Linux Instructions](#getting-started-with-linux)

---

### Getting Started with Mac

**1. Clone the Repository:** 
```shell
git clone https://github.com/Nick-Fanelli/HarmonyEngine --recursive
```
***Note use flag --recursive when cloning repository to get access to all submodules***

**2. Install the Dependencies:**

* Install [Homebrew](https://brew.sh/): 
    ```shell
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

* Install GLFW, CMake, GLEW, and GLM:
    ```shell
    brew install cmake glfw glew glm
    ```
**3. Building Project**:

* Navigate to the `HarmonyEngine/HarmonyEngine/cmake-build-debug` directory; or create it
* Run cmake in the current directory: 
    ```shell
    cmake ..
    ```
**4. Build and Run the C++ and Header Files**

* Run the make file
    ```shell
    make
    ```

* Navigate to the playspace directory.
    ```shell
    cd HarmonyEditor
    ```
    
* Run the Executable
    ```shell
    ./PlayspaceExecutable
    ```
---

### Getting Started with Windows

Getting statred instructions for Windows coming soon...

---

### Getting Started with Linux

Getting started instructions for Linux coming soon...

---

## Creating the Auto Changelog

**1. Make sure that NPM command line tools is installed**<br>
**2. Get the needed dependencies**
* Run the following command in the root directory of the project
```shell
npm install
```
**3. Create the version/change-log commit**
* Run the following command in the root directory of the project *(Replace {TARGET_VERSION_TAG} with the version tag. eg. v1.0.0 or SNAPSHOT-1.0.0)*
```shell
npm run release -- --release-as {TARGET_VERSION_TAG}
```
**4. Push the new tag/version**
* Run the following command in the root directory of the project
```shell
git push --follow-tags
```

---

## How to Contribute

Coming soon...
