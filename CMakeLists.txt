cmake_minimum_required(VERSION 3.0.0)
project(KTexComp)

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

if(LINUX)
  set(ISPC_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/ispc/linux/${CMAKE_HOST_SYSTEM_PROCESSOR}/ispc")
  set(OBJECT_EXT "o")
  
  if("${CMAKE_LIBRARY_ARCHITECTURE}" STREQUAL "i386-linux-gnu")
	set(ISPC_ARCH "x86")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif("${CMAKE_LIBRARY_ARCHITECTURE}" STREQUAL "x86_64-linux-gnu")
	set(ISPC_ARCH "x86_64")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif("${CMAKE_LIBRARY_ARCHITECTURE}" STREQUAL "arm-linux-gnueabihf")
	set(ISPC_ARCH "arm")
	set(ISPC_TARGET "neon-i32x4")
	set(ISPC_PLATFORM_EXTS "neon")
  elseif("${CMAKE_LIBRARY_ARCHITECTURE}" STREQUAL "aarch64-linux-gnu")
	set(ISPC_ARCH "aarch64")
	set(ISPC_TARGET "neon-i32x4")
	set(ISPC_PLATFORM_EXTS "neon")
  else()
	message(FATAL_ERROR "Unsupported target architecture: ${CMAKE_LIBRARY_ARCHITECTURE}")
  endif()

elseif(APPLE)
  set(ISPC_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/ispc/mac/${CMAKE_HOST_SYSTEM_PROCESSOR}/ispc")
  set(OBJECT_EXT "o")

  if("${CMAKE_HOST_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
	set(ISPC_ARCH "x86_64")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif("${CMAKE_HOST_SYSTEM_PROCESSOR}" STREQUAL "arm64")
	set(ISPC_ARCH "aarch64")
	set(ISPC_TARGET "neon-i32x4")
	set(ISPC_PLATFORM_EXTS "neon")
  else()
	message(FATAL_ERROR "Unsupported target architecture: ${CMAKE_LIBRARY_ARCHITECTURE}")
  endif()

elseif(WIN32 OR WIN64)
  set(ISPC_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/ispc/win/${CMAKE_HOST_SYSTEM_PROCESSOR}/ispc.exe")
  set(OBJECT_EXT "obj")

  if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "")
    set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
  else()
    set(TARGET_ARCH ${CMAKE_GENERATOR_PLATFORM})
  endif()

  if("${TARGET_ARCH}" STREQUAL "x86" OR "${TARGET_ARCH}" STREQUAL "Win32")
	set(ISPC_ARCH "x86")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif("${TARGET_ARCH}" STREQUAL "x64" OR "${TARGET_ARCH}" STREQUAL "Win64")
	set(ISPC_ARCH "x86_64")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  else()
	message(FATAL_ERROR "Unsupported target architecture: ${TARGET_ARCH}")
  endif()

else()
  message(FATAL_ERROR "Unrecognized platform")
endif()

if (NOT EXISTS ${ISPC_COMPILER})
  message(FATAL_ERROR "Could not find ispc compiler: ${ISPC_COMPILER}\n"
                      "Please grab the latest compiler for your platform at https://github.com/ispc/ispc and try again")
endif()

foreach(KERNEL 
  "ispc_texcomp/kernel"
  "ispc_texcomp/kernel_astc"
  "ispc_texcomp/kernel_bptc"
  "ispc_texcomp/kernel_etc"
)
  set(OBJECT "${KERNEL}.${OBJECT_EXT}")
  list(APPEND OBJECTS ${OBJECT})
  set(PLATFORM_OBJECTS "")

  foreach(PLATFORM_EXT ${ISPC_PLATFORM_EXTS})
    set(PLATFORM_OBJECT "${KERNEL}_${PLATFORM_EXT}.${OBJECT_EXT}")
    list(APPEND PLATFORM_OBJECTS ${PLATFORM_OBJECT})
    list(APPEND ALL_PLATFORM_OBJECTS ${PLATFORM_OBJECT})
  endforeach()
  
  add_custom_command(
    OUTPUT ${OBJECT} ${PLATFORM_OBJECTS}
	COMMAND ${ISPC_COMPILER} -O2 "${KERNEL}.ispc" -o "${CMAKE_CURRENT_BINARY_DIR}/${KERNEL}.${OBJECT_EXT}" -h "${CMAKE_CURRENT_BINARY_DIR}/${KERNEL}_ispc.h" --arch=${ISPC_ARCH} --target=${ISPC_TARGET} --opt=fast-math
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endforeach()	

include_directories(
  "${CMAKE_CURRENT_BINARY_DIR}/ispc_texcomp"
)

set(SOURCES
  ispc_texcomp/ispc_texcomp.cpp
  ispc_texcomp/ispc_texcomp_astc.cpp
  ispc_texcomp/KTexCompBPTC.cpp
)

add_library(ispc_texcomp
  STATIC
  ${ALL_PLATFORM_OBJECTS}
  ${SOURCES}
)

install(TARGETS ispc_texcomp
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
)
