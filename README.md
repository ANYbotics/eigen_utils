\page page_eigen_utils Eigen Utils

# Eigen Utils

## Overview
This package provides common utilities around the eigen library. 

### Unit Tests

Run the unit tests with

    catkin run_tests eigen_utils

## Usage

### Testing

```
#include <eigen_utils/testing.hpp>

cv::Mat myFirstMat;
cv::Mat mySecondMat;

...

ASSERT_MATRICES_EQ_WITH_NAN(myFirstMat, mySecondMat);

```
