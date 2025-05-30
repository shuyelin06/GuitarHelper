#include "Window.h"

class RecorderWindow : public Window {
public:
    void pollInput();
    void update();
    void render();
};