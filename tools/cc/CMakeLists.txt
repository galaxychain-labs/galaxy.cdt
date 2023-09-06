configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cdt-cc.cpp.in ${CMAKE_BINARY_DIR}/gax-cc.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cdt-cpp.cpp.in ${CMAKE_BINARY_DIR}/gax-cpp.cpp)

add_tool(gax-cc)
add_tool(gax-cpp)

set_target_properties(gax-cc PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
set_target_properties(gax-cpp PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
