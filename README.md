# Visual Node System Example (multi-backend)

This repository provides an example of a simple application that integrates the [Visual Node System](https://github.com/Azzinoth/VisualNodeSystem).

This branch (`multi-backend`) builds the same example for Windows, MacOS, Linux and the web. The window, Dear ImGui and the graphics backend come from [FEBasicApplication](https://github.com/Azzinoth/FEBasicApplication) (`multi-backend` branch), which is included as a second submodule.

If you only need a simple Windows example without the FEBasicApplication dependency, use the [master branch](https://github.com/Azzinoth/VisualNodeSystem-Example/tree/master).

**[Live demo](https://azzinoth.github.io/VisualNodeSystem-Example/)**: the web version, running in the browser. It needs a browser with WebGPU support.

## Supported targets

| Platform | Window system | Graphics API |
|---|---|---|
| Windows | GLFW | OpenGL (default) or WebGPU (Dawn) |
| MacOS | GLFW | OpenGL |
| Linux | GLFW (X11) | OpenGL |
| Web | Emscripten | WebGPU |

## Building the Project for Visual Studio (Windows)
```bash
# Initialize a new Git repository
git init

# Add the remote repository
git remote add origin https://github.com/Azzinoth/VisualNodeSystem-Example

# Pull the contents of the remote repository
git pull origin multi-backend

# Initialize and update submodules
git submodule update --init --recursive

# Generate the build files using CMake
# Will work in Windows PowerShell
cmake CMakeLists.txt
```

## Building the Project for the Web (Windows)
```bat
:: Release (default)
build-web.bat

:: Debug
build-web.bat debug
```
On the first run, the script downloads the Emscripten SDK and Ninja into the repository folder. It builds into `build-web\Release` or `build-web\Debug` and serves the result at http://localhost:8080/Visual_Node_System_Example.html.

The script needs Git and Python on `PATH`. The page needs a browser with WebGPU support.