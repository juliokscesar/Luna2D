:: Build GLFW
cd Luna\ext\glfw
if not exist build mkdir build
cd build
cmake ..
cmake --build . --config Release --target ALL_BUILD -j 4
cd ..\..\..\..


:: Build project
if not exist build mkdir build

cd build
cmake .. -DCMAKE_INSTALL_PREFIX=.
cmake --build . --target LunaSandbox -j 4
