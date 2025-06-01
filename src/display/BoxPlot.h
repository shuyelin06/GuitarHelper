#include "Figure.h"

class BoxPlot : public Figure {
private:
    std::vector<float> bars;
    float max_height;

public:
    BoxPlot(const Box& box);
    
    void addBar(float height);
    void clear();
    
protected:
    void drawFigure(sf::RenderWindow& window, const Box& screen_box) override;
};