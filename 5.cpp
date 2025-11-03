#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

class Shape {
public:
    virtual float area() const = 0;
    virtual float perimeter() const = 0;
    virtual void show_info() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    float r;
public:
    Circle(float _r = 1) { r = _r; }
    float area() const override { return M_PI * r * r; }
    float perimeter() const override { return 2 * M_PI * r; }
    void show_info() const override {
        cout << "Circle(r=" << r << ") -> area=" << area() << ", peri=" << perimeter() << endl;
    }
};

class Square : public Shape {
    float s;
public:
    Square(float _s = 1) { s = _s; }
    float area() const override { return s * s; }
    float perimeter() const override { return 4 * s; }
    void show_info() const override {
        cout << "Square(s=" << s << ") -> area=" << area() << ", peri=" << perimeter() << endl;
    }
};

class Triangle : public Shape {
    float a;
public:
    Triangle(float _a = 1) { a = _a; }
    float area() const override { return (sqrt(3)/4)*a*a; }
    float perimeter() const override { return 3*a; }
    void show_info() const override {
        cout << "Triangle(a=" << a << ") -> area=" << area() << ", peri=" << perimeter() << endl;
    }
};

int main() {
    srand(time(0));

    Shape* arr[6];
    for (int i = 0; i < 6; i++) {
        int t = rand() % 3;
        if (t == 0) arr[i] = new Circle(rand() % 10 + 1);
        else if (t == 1) arr[i] = new Square(rand() % 10 + 1);
        else arr[i] = new Triangle(rand() % 10 + 1);
    }

    cout << "\nDursuud:\n";
    for (int i = 0; i < 6; i++) arr[i]->show_info();

    // Талбайгаар эрэмбэлэх 
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 5; j++)
            if (arr[j]->area() > arr[j+1]->area())
                swap(arr[j], arr[j+1]);

    cout << "\nTalbaigaar eremblev:\n";
    for (int i = 0; i < 6; i++) arr[i]->show_info();

    // Периметрээр эрэмбэлэх 
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 5; j++)
            if (arr[j]->perimeter() > arr[j+1]->perimeter())
                swap(arr[j], arr[j+1]);

    cout << "\nPerimetreer eremblev:\n";
    for (int i = 0; i < 6; i++) arr[i]->show_info();

    for (int i = 0; i < 6; i++) delete arr[i];

    return 0;
}
