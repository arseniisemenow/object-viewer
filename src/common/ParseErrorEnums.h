#ifndef CPP4_3D_VIEWER_V_2_0_1_COMMON_PARSE_ERROR_ENUMS_H_
#define CPP4_3D_VIEWER_V_2_0_1_COMMON_PARSE_ERROR_ENUMS_H_

namespace s21 {
enum class ModelLoadingError {
  kNoModelLoadingError,
  kNumberRangeError,
  kInvalidNumberConversion,
  kFileNotFound,
  kMemoryAllocationError,
  kIndexOutOfBounds,
};
}

#endif  // CPP4_3D_VIEWER_V_2_0_1_COMMON_PARSE_ERROR_ENUMS_H_