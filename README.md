# Demi3D SDK 0.0.4 restoration

This is a modified source snapshot of the 2006 [Demi3D SDK](https://sourceforge.net/projects/demi3d/).
The CMake build produces a C++17 static library and the original Example and
Tutorial1 demos. SDL2 provides the window, events, and BMP loading. Rendering
still uses desktop OpenGL with the fixed-function pipeline and requires an
OpenGL 2.1 compatibility context and GLU.

## Windows x64

Install CMake 3.20 or later and Visual Studio with the Desktop development
with C++ workload. The commands below use Visual Studio 2026 and require
CMake 4.2 or later. Demi3D looks in `C:/vcpkg/installed/x64-windows` when
normal SDL2 package discovery fails on MSVC x64.

From the extracted source directory in PowerShell, install SDL2 once and build.

```powershell
C:/vcpkg/vcpkg.exe install sdl2:x64-windows
cmake -S . -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Release
Set-Location build/bin/Release
.\Example.exe
```

For Visual Studio 2022, use `Visual Studio 17 2022` as the generator.
Use a fresh build directory if a previous configuration used another generator
or an invalid toolchain path.

For MinGW-w64, use a matching SDL2 development package and point CMake at its
prefix with `CMAKE_PREFIX_PATH`. Use a separate build directory when switching
toolchains. A dynamic MinGW build also needs the compiler's runtime DLLs on PATH.

## Debian and Ubuntu

```sh
sudo apt install build-essential cmake libsdl2-dev libgl-dev libglu1-mesa-dev
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
cd build/bin/Release
./Example
```

Run either demo from its output directory so relative asset paths resolve.
Close the window to end the demo. In your own render loop, check
`DmDevice::isRunning()` after `beginScene()` and before rendering the next frame.

## Compatibility

- Rebuild client code against the new static library. The original 32-bit DLL ABI
  and Visual Studio 2005 project format are historical.
- Use one active rendering device per process. The legacy render registry and
  extension entry points are shared across devices.
- OBJ materials and full Quake III BSP rendering remain outside this restoration.
  The original MilkShape exporter and compiled help are included as archival files.
- The original Irrlicht-derived string header retains its attribution and license
  notice. SourceForge identifies the Demi3D project license as zlib/libpng.
