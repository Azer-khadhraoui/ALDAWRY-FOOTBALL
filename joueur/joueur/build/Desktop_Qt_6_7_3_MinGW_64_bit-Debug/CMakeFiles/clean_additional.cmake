# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\joueur_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\joueur_autogen.dir\\ParseCache.txt"
  "joueur_autogen"
  )
endif()
