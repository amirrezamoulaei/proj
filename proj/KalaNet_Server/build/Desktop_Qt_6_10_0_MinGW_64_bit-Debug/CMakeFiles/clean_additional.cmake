# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\KalaNet_Server_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\KalaNet_Server_autogen.dir\\ParseCache.txt"
  "KalaNet_Server_autogen"
  )
endif()
