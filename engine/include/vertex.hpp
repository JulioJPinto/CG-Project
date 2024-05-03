#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "utils.hpp"

struct Vertex {
  Point position;
  Point normal;
  Point2D texture;

  Vertex(Point position_val, Point normal_val, Point2D texture_val)
      : position(position_val), normal(normal_val), texture(texture_val) {}

  Vertex(float x, float y, float z, float nx, float ny, float nz, float u,
         float v)
      : position(x, y, z), normal(nx, ny, nz), texture(u, v) {}

  bool operator==(const Vertex& other) const {
    return position == other.position && normal == other.normal &&
           texture == other.texture;
  }

  Vertex(Point pos) : position(pos), normal(Point()), texture(Point2D()) {}
};

struct VertexHash {
  size_t operator()(const Vertex& p) const {
    return PointHash()(p.position) ^ PointHash()(p.normal) ^
           Point2DHash()(p.texture);
  }
};

#endif  // VERTEX_HPP