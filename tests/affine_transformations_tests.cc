#include <gtest/gtest.h>

#include "../src/Controller/Controller.h"
#include "../src/Matrix/Matrix.h"
#include "../src/Model/Model.h"
#include "../src/Model/Transformation/Transformation.h"

namespace s21 {
TEST(AffineTransformationsTest, translation_test_1) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Translate({2.0, 3.0, 4.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 3.0f,
                             0.0f, 0.0f, 1.0f, 4.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, translation_test_2) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Translate({3.0, 5.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {1.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, 5.0f,
                             0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, translation_test_3) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Translate({3.0, 5.0, -50.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {1.0f, 0.0f, 0.0f, 3.0f,   0.0f, 1.0f, 0.0f, 5.0f,
                             0.0f, 0.0f, 1.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, scaling_test_1) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Scale({2.0, 3.0, 4.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, scaling_test_2) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Scale({0.0, 5.0, 6.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, scaling_test_3) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Scale({0.0, 5.0, -6.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 5.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, -6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_x_axis_90_degrees) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(90.0, {1.0, 0.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_y_axis_90_degrees) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(90.0, {0.0, 1.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                             1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_z_axis_90_degrees) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(90.0, {0.0, 0.0, 1.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_x_axis_45_degrees) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(45.0, {1.0, 0.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {
      1.0f, 0.0f,       0.0f,      0.0f, 0.0f, 0.707107f, 0.707107f, 0.0f,
      0.0f, -0.707107f, 0.707107f, 0.0f, 0.0f, 0.0f,      0.0f,      1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_y_axis_60_degrees) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(60.0, {0.0, 1.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.5f, 0.0f, -0.866025f, 0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 0.866025f,  0.0f, 0.5f, 0.0f,
                             0.0f, 0.0f, 0.0f,       1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_z_axis_random_angle) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(37.5, {0.0, 0.0, 1.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {
      0.793353f, 0.608761f, 0.0f, 0.0f, -0.608761f, 0.793353f, 0.0f, 0.0f,
      0.0f,      0.0f,      1.0f, 0.0f, 0.0f,       0.0f,      0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_negative_x_axis_random_angle) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(20.0, {-1.0, 0.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {
      1.0f, 0.0f,      0.0f,      0.0f, 0.0f, 0.939693f, -0.342020f, 0.0f,
      0.0f, 0.342020f, 0.939693f, 0.0f, 0.0f, 0.0f,      0.0f,       1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_negative_y_axis_random_angle) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(45.0, {0.0, -1.0, 0.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.707107f, 0.0f, 0.707107f,  0.0f, 0.0f,      1.0f,
                             0.0f,      0.0f, -0.707107f, 0.0f, 0.707107f, 0.0f,
                             0.0f,      0.0f, 0.0f,       1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}

TEST(AffineTransformationsTest, rotate_test_negative_z_axis_random_angle) {
  Matrix matrix{4, 4};
  matrix.SetToIdentity();

  Model model{};
  Controller controller{&model};
  controller.SetModelMatrix(matrix);
  controller.Rotate(60.0, {0.0, 0.0, -1.0});
  matrix = controller.GetModelMatrix();

  float desiredMatrix[16] = {0.5f, -0.866025f, 0.0f, 0.0f, 0.866025f, 0.5f,
                             0.0f, 0.0f,       0.0f, 0.0f, 1.0f,      0.0f,
                             0.0f, 0.0f,       0.0f, 1.0f};

  for (int row{0}; row < 4; ++row) {
    for (int col{0}; col < 4; ++col) {
      ASSERT_NEAR(matrix(row, col), desiredMatrix[row * 4 + col], 1e-6);
    }
  }
}
}  // namespace s21
