# HarmonyEngine

## Getting Started | Cloning and Building the Project

1. [Mac Instructions](#getting-started-with-mac)
1. [Windows Instructions](#getting-started-with-windows)
1. [Linux Instructions](#getting-started-with-linux)

---

### Getting Started with Mac

**1. Clone the Repository:** 
```shell
git clone https://github.com/Nick-Fanelli/HarmonyEngine
```

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
    make HarmonyEngine
    ```

* Run the Executable
    ```shell
    ./HarmonyEngine
    ```
---

### Getting Started with Windows

Getting statred instructions for Windows coming soon...

---

### Getting Started with Linux

Getting started instructions for Linux coming soon...

---

## Creating the Auto Changelog

**1. Make sure that NPM command line tools is installed**
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
