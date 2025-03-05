# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\competition_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\competition_autogen.dir\\ParseCache.txt"
  "competition_autogen"
  )
endif()
