#include "Parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "Model/ModelConstants.h"

namespace s21 {
ParseResult Parser::ParseObjFile(const std::string &file_name) {
  std::ifstream file{file_name};
  if (!file) {
    std::cerr << "Parser::ParseObjFile - couldn't open obj file\n";
    return {{}, ModelLoadingError::kFileNotFound};
  }

  ClearMeshData();

  std::string line{};
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      GetVertexInfoFromLine(line);
      ++result_.mesh_data.number_of_vertices;
    } else if (line[0] == 'f' && line[1] == ' ') {
      GetSurfaceInfoFromLine(line);
    }
  }

  if (result_.error == ModelLoadingError::kNoModelLoadingError) {
    result_.mesh_data.number_of_edges = result_.mesh_data.indices.size() / 2;
  }

  if (result_.error == ModelLoadingError::kNoModelLoadingError) {
    result_.mesh_data.center = CalculateBoundingBoxCenter();
  }

  if (result_.error != ModelLoadingError::kNoModelLoadingError) {
    ClearMeshData();
  }

  return result_;
}

void Parser::GetVertexInfoFromLine(const std::string &line) {
  std::string trimmed_line{line.substr(2)};

  for (int i{0}; i < constants::kNumberOfVertexCoords &&
                 result_.error == ModelLoadingError::kNoModelLoadingError;
       ++i) {
    double coordinate{ReadVertexCoordinate(trimmed_line)};
    if (result_.error == ModelLoadingError::kNoModelLoadingError) {
      result_.mesh_data.vertices.push_back(coordinate);
    }
  }
}

void Parser::GetSurfaceInfoFromLine(const std::string &line) {
  bool first_index_was_set{false};
  int first_index{0};

  std::string trimmed_line{line.substr(2)};
  while (trimmed_line.length() > 0 &&
         result_.error == ModelLoadingError::kNoModelLoadingError) {
    int current_index{ReadVertexIndex(trimmed_line)};
    if (result_.error == ModelLoadingError::kNoModelLoadingError) {
      ProcessVertexIndex(current_index, first_index_was_set, first_index);
      SkipToNextIndex(trimmed_line);
    }
  }

  if (result_.mesh_data.indices.size() % 2 != 0 &&
      result_.error == ModelLoadingError::kNoModelLoadingError) {
    result_.mesh_data.indices.push_back(first_index);
  }
}

double Parser::ReadVertexCoordinate(std::string &line) {
  double number{};
  try {
    std::size_t number_length{};
    number = std::stod(line, &number_length);
    line = line.substr(number_length);
  } catch (const std::invalid_argument &exception) {
    result_.error = ModelLoadingError::kInvalidNumberConversion;
  } catch (const std::out_of_range &exception) {
    result_.error = ModelLoadingError::kNumberRangeError;
  }

  return number;
}

int Parser::ReadVertexIndex(std::string &line) {
  int number{};
  try {
    std::size_t number_length{};
    number = std::stoi(line, &number_length);
    line = line.substr(number_length);
  } catch (const std::invalid_argument &exception) {
    result_.error = ModelLoadingError::kInvalidNumberConversion;
  } catch (const std::out_of_range &exception) {
    result_.error = ModelLoadingError::kNumberRangeError;
  }

  return number;
}

void Parser::ProcessVertexIndex(int vertex_index, bool &first_index_was_set,
                                int &first_index) {
  if (vertex_index > 0) {
    --vertex_index;
  } else if (vertex_index < 0) {
    vertex_index = result_.mesh_data.number_of_vertices + vertex_index;
  }

  if (vertex_index >= result_.mesh_data.number_of_vertices ||
      vertex_index < 0) {
    result_.error = ModelLoadingError::kIndexOutOfBounds;
  } else {
    result_.mesh_data.indices.push_back(vertex_index);

    if (first_index_was_set) {
      result_.mesh_data.indices.push_back(vertex_index);
    }

    if (!first_index_was_set) {
      first_index = vertex_index;
      first_index_was_set = true;
    }
  }
}

void Parser::SkipToNextIndex(std::string &line) {
  while (line[0] != ' ' && line.length() > 0) {
    line = line.substr(1);
  }

  if (!std::any_of(line.begin(), line.end(), ::isdigit)) {
    line.clear();
  }
}

std::array<float, 3> Parser::CalculateBoundingBoxCenter() {
  std::array<float, 3> min_corner{};
  std::array<float, 3> max_corner{};
  for (int i{0}; i < 3; ++i) {
    min_corner[i] = result_.mesh_data.vertices[i];
    max_corner[i] = result_.mesh_data.vertices[i];
  }

  for (int i{0}; i < result_.mesh_data.number_of_vertices;
       i += constants::kNumberOfVertexCoords) {
    for (int j{0}; j < 3; ++j) {
      min_corner[j] =
          std::min(min_corner[j], result_.mesh_data.vertices[i + j]);
    }

    for (int j{0}; j < 3; ++j) {
      max_corner[j] =
          std::max(max_corner[j], result_.mesh_data.vertices[i + j]);
    }
  }

  std::array<float, 3> center{};
  for (int i{0}; i < 3; ++i) {
    center[i] = (min_corner[i] + max_corner[i]) / 2.0f;
  }

  return center;
}

void Parser::ClearMeshData() {
  result_.mesh_data.vertices.clear();
  result_.mesh_data.indices.clear();
  result_.mesh_data.number_of_vertices = 0;
  result_.mesh_data.number_of_edges = 0;
  for (int i{0}; i < 3; ++i) {
    result_.mesh_data.center[i] = 0.0f;
  }
}
}  // namespace s21
