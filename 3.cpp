#include <iostream>
#include <cmath>     
#include <cstring> 
#include <cstdlib>    
#include <ctime>      
using namespace std;

class Shape {
protected:
    char *name;          
    static int count;     

public:
    Shape() {
        name = new char[20];
        strcpy(name, "No name");
        count++;          \
    }

    Shape(const char *n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        count++;          
    }

    virtual ~Shape() {
        delete [] name;
        count--;          
    }

    static void set_count(int c) { count = c; }
    static int get_count() { return count; }

    // (3) this ашигласан гишүүн функц
    char* get_name() { return this->name; }

    virtual float area() const = 0;        
    virtual float perimeter() const = 0;   
};

int Shape::count = 0;

class TwoDShape : public Shape {
protected:
    float *x;         
    float *y;         
    int point_count;    
public:
    TwoDShape(int n = 1, const char *nname = "2DShape") : Shape(nname) {
        this->point_count = n;             // this ашиглав
        this->x = new float[this->point_count];
        this->y = new float[this->point_count];
        for (int i = 0; i < this->point_count; i++) {
            this->x[i] = 0;
            this->y[i] = 0;
        }
    }

    ~TwoDShape() {
        delete [] this->x;
        delete [] this->y;
    }

    virtual void show_info() {
        cout << "2DShape: " << this->name << endl;
    }
};

class Circle : public TwoDShape {
    float radius;   
public:
    Circle(float _r = 1) : TwoDShape(1, "Circle") {
        this->radius = _r;          //this ашиглав
        this->x[0] = rand() % 10;
        this->y[0] = rand() % 10;
    }

    float area() const override { return M_PI * this->radius * this->radius; }
    float perimeter() const override { return 2 * M_PI * this->radius; }

    void show_info() override {
        cout << "Circle - radius: " << this->radius
             << "  area: " << this->area()
             << "  perimeter: " << this->perimeter() << endl;
    }
};

class Square : public TwoDShape {
    float side;  
public:
    Square(float _s = 1) : TwoDShape(4, "Square") {
        this->side = _s;          //this ашиглав
    }

    float area() const override { return this->side * this->side; }
    float perimeter() const override { return 4 * this->side; }

    void show_info() override {
        cout << "Square - side: " << this->side
             << "  area: " << this->area()
             << "  perimeter: " << this->perimeter() << endl;
    }
};

class Triangle : public TwoDShape {
    float side;  
public:
    Triangle(float _s = 1) : TwoDShape(3, "Triangle") {
        this->side = _s;            //this ашиглав
    }

    float area() const override { return (sqrt(3)/4) * this->side * this->side; }
    float perimeter() const override { return 3 * this->side; }

    void show_info() override {
        cout << "Triangle - side: " << this->side
             << "  area: " << this->area()
             << "  perimeter: " << this->perimeter() << endl;
    }
};

int main() {
    srand(time(0));  

    TwoDShape *p[10];  

    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0) p[i] = new Circle(rand() % 10 + 1);
        if (i % 3 == 1) p[i] = new Square(rand() % 10 + 1);
        if (i % 3 == 2) p[i] = new Triangle(rand() % 10 + 1);
    }

    cout << "Shape-s uusen object: " << Shape::get_count() << endl;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            if (p[j]->area() > p[j + 1]->area()) {
                TwoDShape *tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }

    cout << "\nTalbaigaar erembelsen dursuud \n";
    for (int i = 0; i < 10; i++) {
        p[i]->show_info();
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            if (p[j]->perimeter() > p[j + 1]->perimeter()) {
                TwoDShape *tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }

    cout << "\nPerimetreer erembelsen dursuud \n";
    for (int i = 0; i < 10; i++) {
        p[i]->show_info();
    }

    for (int i = 0; i < 10; i++) delete p[i];

    cout << "\nUstgagdsnii daraa object: " << Shape::get_count() << endl;

    return 0;
}
