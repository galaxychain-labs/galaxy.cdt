configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cdt-init.cpp ${CMAKE_BINARY_DIR}/gax-init.cpp @ONLY)

add_tool(gax-init)

set_target_properties(gax-init PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
