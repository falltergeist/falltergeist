#
# Find GLM
#
# Try to find GLM : OpenGL Mathematics.
# This module defines 
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
#
# The following variables can be set as arguments for the module.
# - GLM_ROOT_DIR : Root library directory of GLM 
#
# References:
# - https://github.com/Groovounet/glm/blob/master/util/FindGLM.cmake
# - https://bitbucket.org/alfonse/gltut/src/28636298c1c0/glm-0.9.0.7/FindGLM.cmake
#

FIND_PATH(GLM_INCLUDE_DIR glm.hpp
  HINTS
  $ENV{GLMWDIR}
  PATH_SUFFIXES include/glm include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/glm
  /usr/include/glm
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  ${PROJECT_ROOT_DIR}/ext/glm
)
#MESSAGE("GLM_INCLUDE_DIR is ${GLM_INCLUDE_DIR}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLM REQUIRED_VARS GLM_INCLUDE_DIR)
