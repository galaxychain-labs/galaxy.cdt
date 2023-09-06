configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cdt-abidiff.cpp.in ${CMAKE_BINARY_DIR}/gax-abidiff.cpp)

add_tool(gax-abidiff)

set_target_properties(gax-abidiff PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
