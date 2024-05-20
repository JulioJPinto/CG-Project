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

  float sliceAngle = (float) (2 * M_PI) / slices; //angulo interno de cada slice
    float stackSize = (float) height / stacks; //diferença de y entre cada stack
    float rAux = (float) radius / stacks; //diferença do valor do raio entre stacks

    //base
    for(float a = 0; a < (2 * M_PI); a += sliceAngle){ //divide a base pelo numero de slices
        //centro da base(origem)
        float x1 = 0;
        float y1 = 0;
        float z1 = 0;

        //pontos contidos na circunferência da base
        float x3 = (float) radius * sin(a);
        float y3 = 0;
        float z3 = (float)radius * cos(a);

        float x2 = (float) radius * sin(a + sliceAngle);
        float y2 = 0;
        float z2 =(float) radius * cos(a + sliceAngle);

        Point normal = {0, -1, 0};

        points.push_back({x3, y3, z3});
        points.push_back({x1, y1, z1});
        points.push_back({x2, y2, z2});

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);

        Point2D texture = {0, 0};
        textures.push_back(texture);
        textures.push_back(texture);
        textures.push_back(texture);

    }


    for(int i = 0; i<stacks; i++){ //divide a altura pelo numero de stacks
        for(float a = 0; a < (2 * M_PI); a += sliceAngle){ //divide cada stack pelo numero de slices
            float yBaixo = i * stackSize; //y da margem inferior da stack
            float yCima = (i + 1) * stackSize; //y da margem inferior da stack

            float rBaixo = (float) radius - (i * rAux); //raio da margem inferior da stack
            float rCima = (float) radius - ((i + 1) * rAux); //raio da margem inferior da stack

            
            float coneAngleBaixo = atan(rBaixo/(height-yBaixo));
            //float coneAngleCima = atan(rCima/(height-yCima));

            float x2 = rBaixo * sin(a);
            float y2 = yBaixo;
            float z2 = rBaixo * cos(a);
            Point normal2 = Point(sin(coneAngleBaixo) * sin(a), sin(coneAngleBaixo), sin(coneAngleBaixo) * cos(a));
            normal2.normalize();

            float x5 = rBaixo * sin(a + sliceAngle);
            float y5 = yBaixo;
            float z5 = rBaixo * cos(a + sliceAngle);
            Point normal5 = Point (sin(coneAngleBaixo) * sin(a + sliceAngle), sin(coneAngleBaixo), sin(coneAngleBaixo) * cos(a + sliceAngle));
            normal5.normalize();

            float x4 = rBaixo * sin(a + sliceAngle);
            float y4 = yBaixo;
            float z4 = rBaixo * cos(a + sliceAngle);
            Point normal4 = Point(normal5.x, normal5.y, normal5.z);
            normal4.normalize();

            float x1 = rCima * sin(a);
            float y1 = yCima;
            float z1 = rCima * cos(a);
            Point normal1 = Point(normal2.x, normal2.y, normal2.z);
            normal1.normalize();
          


            float x3 = rCima * sin(a);
            float y3 = yCima;
            float z3 = rCima * cos(a);
            Point normal3 = Point(normal2.x, normal2.y, normal2.z);
            normal3.normalize();

            float x6 = rCima * sin(a + sliceAngle);
            float y6 = yCima;
            float z6 = rCima * cos(a + sliceAngle);
            Point normal6 = Point(normal5.x, normal5.y, normal5.z);
            normal6.normalize();

            points.push_back({x1, y1, z1});
            points.push_back({x2, y2, z2});
            points.push_back({x5, y5, z5});
            
            points.push_back({x3, y3, z3});
            points.push_back({x4, y4, z4});
            points.push_back({x6, y6, z6});

            normals.push_back(normal1);
            normals.push_back(normal2);
            normals.push_back(normal5);
            normals.push_back(normal3);
            normals.push_back(normal4);
            normals.push_back(normal6);

            Point2D texture1 = {0, 0};

            textures.push_back(texture1);
            textures.push_back(texture1);
            textures.push_back(texture1);
            textures.push_back(texture1);
            textures.push_back(texture1);
            textures.push_back(texture1);

        }
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
