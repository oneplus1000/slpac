rm -f *.o

g++   -c order.cpp
g++   -c  dir.cpp
g++   -c find_srv.cpp
g++   -c syntax.cpp
g++    -c control_value.cpp
g++   -c mainx.cpp
g++   -c read_info.cpp
g++   -c loop.cpp
g++   -c C_link_list.cpp
g++   -c c_file.cpp
g++ -lslp  -o slpac_tool  *.o
rm -f *.o

