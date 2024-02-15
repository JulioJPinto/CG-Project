#pragma once
#include <vector>
#include <string>
#include <tuple>

typedef std::vector<std::tuple<std::string, std::string>> Point;

class Figure{
    public:
        Figure();
        void exportFile(std::string filename);
    private:
        std::vector<Point> points;
};