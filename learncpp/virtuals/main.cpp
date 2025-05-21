#include <iostream>
#include <vector>

class Shape
{
public:
    virtual std::ostream& print(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        return s.print(out);
    }
    virtual ~Shape() = default;
};

struct Point
{
    int m_x{};
    int m_y{};

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "Point(" << p.m_x << ", " << p.m_y << ")";
        return out;
    }
};

class Triangle: public Shape
{
    Point m_1{};
    Point m_2{};
    Point m_3{};

public:
    Triangle(Point a, Point b, Point c)
        : m_1{a}, m_2{b}, m_3{c} {}

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle(" << m_1 << ", " << m_2 << ", " << m_3 << ")";
        return out;
    }
};

class Circle: public Shape
{
    int m_radius{};
    Point m_center{};

public:
    Circle(Point center, int radius)
        : m_radius{radius}, m_center{center} {}

    std::ostream& print(std::ostream& out) const override
    {
        out << "Circle(" << m_center << ", radius " << m_radius << ")";
        return out;
    }

    int getRadius() const {return m_radius;}
};

int getLargestRadius(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    int max_radius{};
    for (const auto& shape: shapes)
    {
        const Circle* c {dynamic_cast<const Circle*>(shape.get())};
        if (c)
        {
            if (c->getRadius() > max_radius)
            {
                max_radius = c->getRadius();
            }
        }
    }

    return max_radius;
}

int main()
{
	std::vector<std::unique_ptr<Shape>> v;
	v.reserve(3);
	v.push_back(std::make_unique<Circle>(Point{1, 2}, 7));
	v.push_back(std::make_unique<Triangle>(Point{1, 2}, Point{3, 4}, Point{5, 6}));
	v.push_back(std::make_unique<Circle>(Point{7, 8}, 3));


	// print each shape in vector v on its own line here
    for (const auto& element : v) std::cout << *element << '\n';

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	// delete each element in the vector here

	return 0;
}
