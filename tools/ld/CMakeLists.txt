configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cdt-ld.cpp.in ${CMAKE_BINARY_DIR}/gax-ld.cpp)

add_tool(gax-ld)

set_target_properties(gax-ld PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
