cmake CMakeLists.txt
cmake --install .
cmake --build .
file(COPY "src/lists" DESTINATION "Debug\")
cd Debug\
Students_App.exe
pause