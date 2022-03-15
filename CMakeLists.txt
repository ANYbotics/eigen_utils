cmake_minimum_required(VERSION 3.5.1)
project(eigen_utils)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CATKIN_PACKAGE_HEADER_DEPENDENCIES
)

## Create a list of catkin package dependencies, now for both header and source files.
set(CATKIN_PACKAGE_DEPENDENCIES
  ${CATKIN_PACKAGE_HEADER_DEPENDENCIES}
)

## Find catkin dependencies for building this package.
find_package(catkin REQUIRED
  COMPONENTS
    ${CATKIN_PACKAGE_DEPENDENCIES}
)

find_package(Eigen3 REQUIRED)

catkin_package(
  INCLUDE_DIRS
    include
    ${EIGEN3_INCLUDE_DIR}
  CATKIN_DEPENDS
    ${CATKIN_PACKAGE_HEADER_DEPENDENCIES}
)

#############
## Install ##
#############
install(
  DIRECTORY
    include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(
  FILES
    README.md
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

##########
## Test ##
##########

## GTest.
if(CATKIN_ENABLE_TESTING)
  find_package(catkin REQUIRED
    COMPONENTS
      ${CATKIN_PACKAGE_DEPENDENCIES}
  )

  # Test testing.hpp
  catkin_add_gtest(test_${PROJECT_NAME}_testing
    test/TestEigenUtilsTesting.cpp
  )
  target_include_directories(test_${PROJECT_NAME}_testing PRIVATE
    include
  )
  target_include_directories(test_${PROJECT_NAME}_testing SYSTEM PUBLIC
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
  )
  target_link_libraries(test_${PROJECT_NAME}_testing
    gtest_main
    ${catkin_LIBRARIES}
  )

  find_package(cmake_code_coverage QUIET)
  if(cmake_code_coverage_FOUND)
      add_gtest_coverage(
        TEST_BUILD_TARGETS
          test_${PROJECT_NAME}_testing
      )
  endif(cmake_code_coverage_FOUND)
endif()

###########
## Clang ##
###########

find_package(cmake_clang_tools QUIET)
if(cmake_clang_tools_FOUND)
  add_default_clang_tooling()
endif(cmake_clang_tools_FOUND)
