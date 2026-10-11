# Visual Node System Example

![build](https://github.com/Azzinoth/VisualNodeSystem-Example/actions/workflows/Build.yml/badge.svg?branch=master)

This repository provides an example of a simple application that integrates the [Visual Node System](https://github.com/Azzinoth/VisualNodeSystem).

This branch is a simple Windows-only example. To build the same example for Windows, MacOS, Linux and the web, use the [multi-backend branch](https://github.com/Azzinoth/VisualNodeSystem-Example/tree/multi-backend). It uses [FEBasicApplication](https://github.com/Azzinoth/FEBasicApplication) as an additional submodule.

**[Live demo](https://azzinoth.github.io/VisualNodeSystem-Example/)**: the web version from the multi-backend branch, running in the browser. It needs a browser with WebGPU support.

## Building the Project for Visual Studio (Windows)
```bash
# Initialize a new Git repository
git init

# Add the remote repository
git remote add origin https://github.com/Azzinoth/VisualNodeSystem-Example

# Pull the contents of the remote repository
git pull origin master

# Initialize and update submodules
git submodule update --init --recursive

# Generate the build files using CMake
# Will work in Windows PowerShell
cmake CMakeLists.txt
```