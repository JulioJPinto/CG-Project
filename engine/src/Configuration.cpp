#include "Window.cpp"
#include "Camera.cpp"

class Configuration {
public:
    Window window;
    Camera camera;
    std::vector<char*> models;

    Configuration(Window window, Camera camera, std::vector<char*> models) {
        this->window = window;
        this->camera = camera;
        this->models = models;
    }
};
