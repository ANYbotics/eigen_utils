cmake_minimum_required(VERSION 3.16.3)
project(eigen_utils)

if("$ENV{ROS_VERSION}" STREQUAL "1")
    # gersemi: off

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

    # gersemi: on
else() # ROS version 2
    ###############
    ## Configure ##
    ###############

    set(CMAKE_CXX_STANDARD 17)

    add_compile_options(-Wall -Wextra -Wpedantic)

    set(PACKAGE_DEPENDENCIES Eigen3)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    find_package(ament_cmake REQUIRED)
    foreach(PKG ${PACKAGE_DEPENDENCIES})
        find_package(${PKG} REQUIRED)
    endforeach()

    ###########
    ## Build ##
    ###########

    add_library(${PROJECT_NAME} INTERFACE)
    target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)

    target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    )

    ament_target_dependencies(${PROJECT_NAME} ${PACKAGE_DEPENDENCIES})

    #############
    ## Install ##
    #############

    install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})

    ament_export_dependencies(${PACKAGE_DEPENDENCIES})

    ##########
    ## Test ##
    ##########

    if(BUILD_TESTING)
        find_package(ament_cmake_gtest REQUIRED)

        # Test testing.hpp
        ament_add_gtest(
            test_${PROJECT_NAME}_testing
            test/TestEigenUtilsTesting.cpp
        )
        target_link_libraries(test_${PROJECT_NAME}_testing ${PROJECT_NAME})

        find_package(cmake_code_coverage QUIET)
        if(cmake_code_coverage_FOUND)
            add_gtest_coverage(TEST_BUILD_TARGETS test_${PROJECT_NAME}_testing)
        endif(cmake_code_coverage_FOUND)
    endif()

    ament_package()
endif()
