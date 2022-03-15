#pragma once

#include <gtest/gtest.h>
#include <Eigen/Core>

#define ASSERT_MATRICES_EQ_WITH_NAN(first, second) assertMatricesEqualWithNanImpl((first), #first, (second), #second, __LINE__, true)
#define ASSERT_MATRICES_NE_WITH_NAN(first, second) assertMatricesEqualWithNanImpl((first), #first, (second), #second, __LINE__, false)

inline bool checkMatricesEqualWithNan(Eigen::Ref<const Eigen::MatrixXf> first, std::string firstName,
                                      Eigen::Ref<const Eigen::MatrixXf> second, std::string secondName, int line) {
  bool matricesHaveSameShape{first.rows() == second.rows() && first.cols() == second.cols()};
  EXPECT_TRUE(matricesHaveSameShape)                                                 // NO LINT
      << "L. " << std::to_string(line) << ": Matrices differ in shape!"              // NO LINT
      << "\n"                                                                        // NO LINT
      << firstName << ": rows = " << first.rows() << ", cols = " << first.cols()     // NO LINT
      << secondName << ": rows = " << second.rows() << ", cols = " << second.cols()  // NO LINT
      << "\n";                                                                       // NO LINT
  if (!matricesHaveSameShape) {
    return false;
  }

  bool matricesAreEqual = true;
  for (Eigen::Index row = 0; row < first.rows() && matricesAreEqual; ++row) {
    for (Eigen::Index col = 0; col < first.cols() && matricesAreEqual; ++col) {
      bool ifRealThenValid = first.block<1, 1>(row, col).isApprox(second.block<1, 1>(row, col));
      bool bothNaN = std::isnan(first(row, col)) && std::isnan(second(row, col));
      if (ifRealThenValid || bothNaN) {
        continue;
      } else {
        matricesAreEqual = false;
      }
    }
  }

  return matricesAreEqual;
}

inline void assertMatricesEqualWithNanImpl(Eigen::Ref<const Eigen::MatrixXf> first, std::string firstName,
                                           Eigen::Ref<const Eigen::MatrixXf> second, std::string secondName, int line,
                                           bool assertEquality) {
  bool matricesAreEqual{checkMatricesEqualWithNan(first, firstName, second, secondName, line)};
  Eigen::IOFormat compactFormat(2, 0, ",", "\n", "[", "]");
  ASSERT_EQ(assertEquality, matricesAreEqual)                         // NO LINT
      << "L. " << std::to_string(line) << ": Matrices are not equal"  // NO LINT
      << "\n"                                                         // NO LINT
      << firstName << "\n"                                            // NO LINT
      << first.format(compactFormat) << "\n"                          // NO LINT
      << secondName << "\n"                                           // NO LINT
      << second.format(compactFormat) << "\n";                        // NO LINT
}
