class Window {
 public:
  float width;
  float height;

  Window() {
    this->width = 0;
    this->height = 0;
  }

  Window(float width, float height) {
    this->width = width;
    this->height = height;
  }
};
