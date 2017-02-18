################################################

# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_DIR
# GLEW_LIBRARY
#

FIND_PATH(GLEW_INCLUDE_DIR glew.h
  HINTS
  $ENV{GLEWDIR}
  PATH_SUFFIXES include/GL include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/GL
  /usr/include/GL
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  ${PROJECT_ROOT_DIR}/ext/glew
)
#MESSAGE("GLEW_INCLUDE_DIR is ${GLEW_INCLUDE_DIR}")

FIND_LIBRARY(GLEW_LIBRARY
  NAMES GLEW GLEW32
  HINTS
  $ENV{GLEWDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  /sw
  /opt/local
  /opt/csw
  /opt
  ${PROJECT_ROOT_DIR}/ext/glew
)
#MESSAGE("GLEW_LIBRARY is ${GLEW_LIBRARY}")

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW REQUIRED_VARS GLEW_LIBRARY GLEW_INCLUDE_DIR)


