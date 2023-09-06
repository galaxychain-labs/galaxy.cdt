add_custom_command( TARGET CDTClang POST_BUILD COMMAND mkdir -p ${CMAKE_BINARY_DIR}/bin )
macro( cdt_clang_install file )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/cdt-llvm/bin)
   add_custom_command( TARGET CDTClang POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endmacro( cdt_clang_install )

macro( cdt_clang_install_and_symlink file symlink )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/cdt-llvm/bin)
   add_custom_command( TARGET CDTClang POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   add_custom_command( TARGET CDTClang POST_BUILD COMMAND cd ${CMAKE_BINARY_DIR}/bin && ln -sf ${file} ${symlink} )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/bin)")
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CDT_INSTALL_PREFIX}/bin/${file} ${CMAKE_INSTALL_PREFIX}/bin/${symlink})")
endmacro( cdt_clang_install_and_symlink )

macro( cdt_tool_install file )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/tools/bin)
   add_custom_command( TARGET CDTTools POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endmacro( cdt_tool_install )

macro( cdt_tool_install_and_symlink file symlink )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/tools/bin)
   add_custom_command( TARGET CDTTools POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/bin)")
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CDT_INSTALL_PREFIX}/bin/${file} ${CMAKE_INSTALL_PREFIX}/bin/${symlink})")
endmacro( cdt_tool_install_and_symlink )

macro( cdt_cmake_install_and_symlink file symlink )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/modules)
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/lib/cmake/cdt)")
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CDT_INSTALL_PREFIX}/lib/cmake/cdt/${file} ${CMAKE_INSTALL_PREFIX}/lib/cmake/cdt/${symlink})")
endmacro( cdt_cmake_install_and_symlink )

macro( cdt_libraries_install)
   execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
   execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include)
   install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/ DESTINATION ${CDT_INSTALL_PREFIX}/lib)
   install(DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION ${CDT_INSTALL_PREFIX}/include)
endmacro( cdt_libraries_install )

cdt_clang_install_and_symlink(llvm-ranlib cdt-ranlib)
cdt_clang_install_and_symlink(llvm-ar gax-ar)
cdt_clang_install_and_symlink(llvm-nm gax-nm)
cdt_clang_install_and_symlink(llvm-objcopy gax-objcopy)
cdt_clang_install_and_symlink(llvm-objdump gax-objdump)
cdt_clang_install_and_symlink(llvm-readobj gax-readobj)
cdt_clang_install_and_symlink(llvm-readelf gax-readelf)
cdt_clang_install_and_symlink(llvm-strip gax-strip)

cdt_clang_install(opt)
cdt_clang_install(llc)
cdt_clang_install(lld)
cdt_clang_install(ld.lld)
cdt_clang_install(ld64.lld)
cdt_clang_install(clang-9)
cdt_clang_install(wasm-ld)

cdt_tool_install_and_symlink(gax-pp cdt-pp)
cdt_tool_install_and_symlink(gax-wast2wasm cdt-wast2wasm)
cdt_tool_install_and_symlink(gax-wasm2wast cdt-wasm2wast)
cdt_tool_install_and_symlink(gax-cc gax-cc)
cdt_tool_install_and_symlink(gax-cpp gax-cpp)
cdt_tool_install_and_symlink(gax-ld gax-ld)
cdt_tool_install_and_symlink(gax-abidiff gax-abidiff)
cdt_tool_install_and_symlink(gax-init gax-init)
cdt_tool_install_and_symlink(antler-proj antler-proj)

cdt_clang_install(../lib/LLVMEosioApply${CMAKE_SHARED_LIBRARY_SUFFIX})
cdt_clang_install(../lib/LLVMEosioSoftfloat${CMAKE_SHARED_LIBRARY_SUFFIX})

cdt_cmake_install_and_symlink(cdt-config.cmake cdt-config.cmake)
cdt_cmake_install_and_symlink(CDTWasmToolchain.cmake CDTWasmToolchain.cmake)
cdt_cmake_install_and_symlink(CDTMacros.cmake CDTMacros.cmake)

cdt_libraries_install()
