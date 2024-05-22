#include <cmath>
#include <fstream>
#include <iostream>
#include <save3d.hpp>
#include <vector>

#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
coneTriangles(const float radius, const float height, const size_t slices,
              const size_t stacks) {
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

  float sliceAngle = (float)(2 * M_PI) / slices;  // angulo interno de cada
                                                  // slice
  float stackSize = (float)height / stacks;  // diferença de y entre cada stack
  float rAux =
      (float)radius / stacks;  // diferença do valor do raio entre stacks
  printf("stackSize: %f\n", stackSize);
  printf("rAux: %f\n", rAux);
  printf("sliceAngle: %f\n", sliceAngle);

  // base
  for (float a = 0; a < (2 * M_PI);
       a += sliceAngle) {  // divide a base pelo numero de slices
    // centro da base(origem)
    float x1 = 0;
    float y1 = 0;
    float z1 = 0;

    // pontos contidos na circunferência da base
    float x3 = (float)radius * std::sin(a);
    float y3 = 0;
    float z3 = (float)radius * std::cos(a);

    float x2 = (float)radius * std::sin(a + sliceAngle);
    float y2 = 0;
    float z2 = (float)radius * std::cos(a + sliceAngle);

    points.push_back(Point(x3, y3, z3));
    points.push_back(Point(x1, y1, z1));
    points.push_back(Point(x2, y2, z2));

    normals.push_back(Point(0, -1, 0));
    normals.push_back(Point(0, -1, 0));
    normals.push_back(Point(0, -1, 0));

    textures.push_back(Point2D(0.5 + 0.5 * sin(a), 0.5 + 0.5 * cos(a)));
    textures.push_back(Point2D(0.5, 0.5));
    textures.push_back(Point2D(0.5 + 0.5 * sin(a + sliceAngle),
                               0.5 + 0.5 * cos(a + sliceAngle)));
  }

  // lados

  float sliceNormals[slices * 2][3];
  int filled = 0;
  int count = 0;
  for (int i = 0; i < stacks; i++) {  // divide a altura pelo numero de stacks
    for (float a = 0; a < (2 * M_PI);
         a += sliceAngle) {          // divide cada stack pelo numero de slices
      float yBaixo = i * stackSize;  // y da margem inferior da stack
      float yCima = (i + 1) * stackSize;  // y da margem inferior da stack

      float rBaixo =
          (float)radius - (i * rAux);  // raio da margem inferior da stack
      float rCima =
          (float)radius - ((i + 1) * rAux);  // raio da margem inferior da stack
      printf("a: %f rbaixo: %f\n", a, rBaixo);
      float x2 = rBaixo * sin(a);
      printf("x2: %f\n", x2);
      float y2 = yBaixo;
      float z2 = rBaixo * cos(a);
      Point normal2;
      if (filled == 0) {  // se for a primeira stack, calcula a normal para os
                          // pontos em comum com a base
        normal2.x = std::sin(a);
        normal2.y = (float)rBaixo / height;
        normal2.z = std::cos(a);
        normal2 = normal2.normalize();
        printf("normal2: %f %f %f\n", normal2.x, normal2.y, normal2.z);
        sliceNormals[count][0] = normal2.x;
        sliceNormals[count][1] = normal2.y;
        sliceNormals[count][2] = normal2.z;
      } else {
        normal2.x = sliceNormals[count][0];
        normal2.y = sliceNormals[count][1];
        normal2.z = sliceNormals[count][2];
      }
      count++;

      float x5 = rBaixo * sin(a + sliceAngle);
      float y5 = yBaixo;
      float z5 = rBaixo * cos(a + sliceAngle);

      Point normal5;
      if (filled == 0) {  // se for a primeira stack, calcula a normal para os
                          // pontos em comum com a base
        normal5.x = sin(a + sliceAngle);
        normal5.y = (float)rBaixo / height;
        normal5.z = cos(a + sliceAngle);
        normal5 = normal5.normalize();
        printf("normal5: %f %f %f\n", normal5.x, normal5.y, normal5.z);
        sliceNormals[count][0] = normal5.x;
        sliceNormals[count][1] = normal5.y;
        sliceNormals[count][2] = normal5.z;

      } else {
        normal5.x = sliceNormals[count][0];
        normal5.y = sliceNormals[count][1];
        normal5.z = sliceNormals[count][2];
      }
      count++;

      float x4 = rBaixo * sin(a + sliceAngle);
      float y4 = yBaixo;
      float z4 = rBaixo * cos(a + sliceAngle);
      Point normal4;
      normal4.x = sliceNormals[count - 1][0];
      normal4.y = sliceNormals[count - 1][1];
      normal4.z = sliceNormals[count - 1][2];

      float x1 = rCima * sin(a);
      float y1 = yCima;
      float z1 = rCima * cos(a);
      Point normal1;
      normal1.x = sliceNormals[count - 2][0];
      normal1.y = sliceNormals[count - 2][1];
      normal1.z = sliceNormals[count - 2][2];

      float x3 = rCima * sin(a);
      float y3 = yCima;
      float z3 = rCima * cos(a);
      Point normal3;
      normal3.x = sliceNormals[count - 2][0];
      normal3.y = sliceNormals[count - 2][1];
      normal3.z = sliceNormals[count - 2][2];

      float x6 = rCima * sin(a + sliceAngle);
      float y6 = yCima;
      float z6 = rCima * cos(a + sliceAngle);
      Point normal6;
      normal6.x = sliceNormals[count - 1][0];
      normal6.y = sliceNormals[count - 1][1];
      normal6.z = sliceNormals[count - 1][2];

      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x2, y2, z2));
      points.push_back(Point(x5, y5, z5));

      points.push_back(Point(x3, y3, z3));
      points.push_back(Point(x4, y4, z4));
      points.push_back(Point(x6, y6, z6));

      normals.push_back(normal1);
      normals.push_back(normal2);
      normals.push_back(normal5);

      normals.push_back(normal3);
      normals.push_back(normal4);
      normals.push_back(normal6);

      textures.push_back(Point2D(a / (2 * M_PI), yCima / height));
      textures.push_back(Point2D(a / (2 * M_PI), yBaixo / height));
      textures.push_back(
          Point2D((a + sliceAngle) / (2 * M_PI), yBaixo / height));

      textures.push_back(Point2D(a / (2 * M_PI), yCima / height));
      textures.push_back(
          Point2D((a + sliceAngle) / (2 * M_PI), yBaixo / height));
      textures.push_back(
          Point2D((a + sliceAngle) / (2 * M_PI), yCima / height));
    }
    filled = 1;
    count = 0;
  }

  return std::make_pair(std::make_pair(points, normals), textures);
}

bool generateCone(float radius, float height, int slices, int stacks,
                  const char* filepath, bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      cone = coneTriangles(radius, height, slices, stacks);

  if (advanced) {
    save3DAdvancedfile(cone.first.first, cone.first.second, cone.second,
                       filepath);
  } else {
    saveToFile(cone.first.first, filepath);
  }
  return true;
}
