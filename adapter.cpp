#include <iostream>

class Rectangle // final component
{
public:
	virtual void draw() = 0;
	virtual ~Rectangle() = default;
};

class Figure // adapted element
{
public:
	Figure(const int x1, const int y1, const int x2, const int y2)
		: x1(x1), y1(y1), x2(x2), y2(y2)
	{
		std::cout << "Figure(x1, y1, x2, y2)" << std::endl;
	}
	void drawFigure()
	{
		std::cout << "Figure: drawFigure()." << std::endl;
	}
private:
	int x1{};
	int y1{};
	int x2{};
	int y2{};
};

class AdapterRectangle : public Rectangle, Figure
{
public:
	AdapterRectangle(const int x, const int y, const int w, const int h)
		: Figure(x, y, x + w, y + h)
	{
		std::cout << "AdapterRectangle:(x, y, x + w, y + h)" << std::endl;
	}
	void draw() override
	{
		std::cout << "AdapterRectangle: draw()." << std::endl;
		drawFigure();
	}
};

int main()
{
	int x{ 10 };
	int y{ 45 };
	int w{ 320 };
	int h{ 1200 };

	// The customer uses the target element and the adapted element is called
	Rectangle* rectangle = new AdapterRectangle(x, y, w, h);
	rectangle->draw();
}
