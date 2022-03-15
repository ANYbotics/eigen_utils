#include <gtest/gtest.h>
#include <Eigen/Core>
#include "eigen_utils/testing.hpp"

TEST(TestEigenUtilsTesting, allReals) {  // NOLINT
  Eigen::Matrix<float, 10, 10> mat1;
  Eigen::Matrix<float, 10, 10> mat2;
  mat1.setConstant(42.0);
  mat2.setConstant(42.0);
  ASSERT_MATRICES_EQ_WITH_NAN(mat1, mat2);
}

TEST(TestEigenUtilsTesting, allNans) {  // NOLINT
  Eigen::Matrix<float, 10, 10> mat1;
  Eigen::Matrix<float, 10, 10> mat2;
  mat1.setConstant(NAN);
  mat2.setConstant(NAN);
  ASSERT_MATRICES_EQ_WITH_NAN(mat1, mat2);
}

TEST(TestEigenUtilsTesting, someValuesNan) {  // NOLINT
  Eigen::Matrix<float, 10, 10> mat1;
  Eigen::Matrix<float, 10, 10> mat2;

  mat1.setConstant(42.0);
  mat2.setConstant(42.0);

  mat1(2, 2) = NAN;
  mat2(2, 2) = NAN;

  mat1(3, 7) = NAN;
  mat2(3, 7) = NAN;

  ASSERT_MATRICES_EQ_WITH_NAN(mat1, mat2);
}

TEST(TestEigenUtilsTesting, differentMatrices) {  // NOLINT
  Eigen::Matrix<float, 10, 10> mat1;
  Eigen::Matrix<float, 10, 10> mat2;

  mat1.setConstant(42.0);
  mat2.setConstant(42.0);

  mat1(2, 2) = NAN;
  //  mat2(2,2) = NAN; this is where mat2 differs

  mat1(3, 7) = NAN;
  mat2(3, 7) = NAN;

  ASSERT_MATRICES_NE_WITH_NAN(mat1, mat2);
}
