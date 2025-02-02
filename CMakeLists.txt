cmake_minimum_required(VERSION 3.0.0)
project(KTexComp)

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

if(LINUX)
  set(ISPC_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/ispc/linux/${CMAKE_HOST_SYSTEM_PROCESSOR}/ispc")
  set(OBJECT_EXT "o")
  
  if(CMAKE_LIBRARY_ARCHITECTURE STREQUAL "i386-linux-gnu")
	set(ISPC_ARCH "x86")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif(CMAKE_LIBRARY_ARCHITECTURE STREQUAL "x86_64-linux-gnu")
	set(ISPC_ARCH "x86_64")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif(CMAKE_LIBRARY_ARCHITECTURE STREQUAL "arm-linux-gnueabihf")
	set(ISPC_ARCH "arm")
	set(ISPC_TARGET "neon-i32x4")
	set(ISPC_PLATFORM_EXTS "neon")
  elseif(CMAKE_LIBRARY_ARCHITECTURE STREQUAL "aarch64-linux-gnu")
	set(ISPC_ARCH "aarch64")
	set(ISPC_TARGET "neon-i32x4")
	set(ISPC_PLATFORM_EXTS "neon")
  else()
	message(FATAL_ERROR "Unsupported target architecture: ${CMAKE_LIBRARY_ARCHITECTURE}")
  endif()

elseif(APPLE)
  set(ISPC_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/ispc/mac/${CMAKE_HOST_SYSTEM_PROCESSOR}/ispc")
  set(OBJECT_EXT "o")

  if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
	set(ISPC_ARCH "x86_64")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
	set(ISPC_ARCH "aarch64")
	set(ISPC_TARGET "neon-i32x4")
	set(ISPC_PLATFORM_EXTS "neon")
  else()
	message(FATAL_ERROR "Unsupported target architecture: ${CMAKE_LIBRARY_ARCHITECTURE}")
  endif()

elseif(WIN32 OR WIN64)
  set(ISPC_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/ispc/win/${CMAKE_HOST_SYSTEM_PROCESSOR}/ispc.exe")
  set(OBJECT_EXT "obj")

  if(CMAKE_GENERATOR_PLATFORM STREQUAL "")
    set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
  else()
    set(TARGET_ARCH ${CMAKE_GENERATOR_PLATFORM})
  endif()

  if(TARGET_ARCH STREQUAL "x86" OR TARGET_ARCH STREQUAL "Win32")
	set(ISPC_ARCH "x86")
	set(ISPC_TARGET "sse2,avx")
	set(ISPC_PLATFORM_EXTS "sse2;avx")
  elseif(TARGET_ARCH STREQUAL "x64" OR TARGET_ARCH STREQUAL "Win64" OR TARGET_ARCH STREQUAL "AMD64")
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
                      "Please grab the latest compiler for your platform at\n"
                      "https://github.com/ispc/ispc and try again\n"
					  "If you are an OldUnreal developer, you can also type\n"
					  "git clone git@github.com:OldUnreal/ispc-compiler ispc\n"
					  "in KTexComp's root folder")
endif()

if(UNIX)
	execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/ispc_texcomp)
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
  list(APPEND PUBLIC_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/${KERNEL}_ispc.h")

  string(FIND "${ISPC_PLATFORM_EXTS}" ";" TMP)
  if (${TMP} GREATER 1)
    foreach(PLATFORM_EXT ${ISPC_PLATFORM_EXTS})
      set(PLATFORM_OBJECT "${KERNEL}_${PLATFORM_EXT}.${OBJECT_EXT}")
      list(APPEND PLATFORM_OBJECTS ${PLATFORM_OBJECT})
      list(APPEND ALL_PLATFORM_OBJECTS ${PLATFORM_OBJECT})
    endforeach()
  endif()

  list(APPEND ALL_PLATFORM_OBJECTS ${OBJECT})

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
  ispc_texcomp/ASTC.cpp
  ispc_texcomp/BPTC.cpp
  ispc_texcomp/S3TC.cpp
  ispc_texcomp/ETC.cpp
  ispc_texcomp/BC.cpp    
)

add_library(KTexComp
  STATIC
  ${ALL_PLATFORM_OBJECTS}
  ${SOURCES}
)

set_target_properties(KTexComp
  PROPERTIES
  PUBLIC_HEADER "${PUBLIC_HEADERS};ispc_texcomp/BC.h"
)

install(TARGETS KTexComp
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
