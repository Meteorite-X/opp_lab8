#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class Shape {
protected:
    char *name;
    static int count;
public:
    Shape(const char *n = "No name") {
        this->name = new char[strlen(n) + 1];
        strcpy(this->name, n);
        count++;
    }

    virtual ~Shape() {
        delete [] this->name;
        count--;
    }

    static void set_count(int c) { Shape::count = c; }
    static int get_count() { return Shape::count; }

    char* get_name() { return this->name; }

    virtual float area() const = 0;
    virtual float perimeter() const = 0;
};

int Shape::count = 0;

class TwoDShape : public Shape {
protected:
    float *x, *y;
    int point_count;
public:
    TwoDShape(int n = 1, const char *nname = "2DShape") : Shape(nname) {
        this->point_count = n;
        this->x = new float[this->point_count];
        this->y = new float[this->point_count];
        for (int i = 0; i < this->point_count; i++) {
            this->x[i] = 0;
            this->y[i] = 0;
        }
    }

    virtual ~TwoDShape() {
        delete [] this->x;
        delete [] this->y;
    }

    // Жинхэнэ хийсвэр функцууд
    virtual float area() const = 0;
    virtual float perimeter() const = 0;

    void show_info() {
        cout << "2DShape: " << this->get_name() << endl;
    }
};

class Circle : public TwoDShape {
    float radius;
public:
    Circle(float r = 1) : TwoDShape(1, "Circle") {
        this->radius = r;
    }

    float area() const override { return M_PI * this->radius * this->radius; }
    float perimeter() const override { return 2 * M_PI * this->radius; }

    void show_info() {
        cout << "Circle name: " << this->get_name()
             << " | radius: " << this->radius
             << " | area: " << this->area()
             << " | perimeter: " << this->perimeter() << endl;
    }
};

int main() {
    Circle c1(3.5);
    Circle c2(5);

    cout << "Object count: " << Shape::get_count() << endl;

    c1.show_info();
    c2.show_info();

    cout << "After objects destroyed, count will decrease automatically.\n";

    return 0;
}
