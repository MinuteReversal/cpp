# C++ Program for wasm
WebAssembly  
[https://emscripten.org/docs/getting_started/downloads.html](https://emscripten.org/docs/getting_started/downloads.html)  
[https://emscripten.org/docs/building_from_source/toolchain_what_is_needed.html](https://emscripten.org/docs/building_from_source/toolchain_what_is_needed.html)

```
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk


# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes ~/.emscripten file)
emsdk activate latest

# Activate PATH and other environment variables in the current terminal
emsdk_env.bat
```
clear cache
```
emcc --clear-cache
```

output html
```
em++ Program.cpp -s WASM=1 -o index.html
```