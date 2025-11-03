#include <iostream>
#include <cmath>      // sqrt(), M_PI гэх мэт тоон функцууд
#include <cstring>    // string хуулбарлахад
#include <cstdlib>    // rand() функц ашиглахад
#include <ctime>      // time() функц ашиглахад (санамсаргүй тоо үүсгэх)
using namespace std;

// 1. Shape класс
// Энэ класс нь бүх дүрсний хамгийн ерөнхий (суурь) класс юм.
// Дүрс болгон нэртэй байна, мөн энэ классын статик хувьсагч нь
// үүссэн бүх Shape төрлийн объектын тоог тоолж хадгална.
class Shape {
protected:
    char *name;           // дүрсний нэрийг хадгалах хувьсагч
    static int count;     // (1) нийт үүссэн объектуудын тоог хадгалах static хувьсагч

public:
    Shape() {
        name = new char[20];
        strcpy(name, "No name");
        count++;          // шинэ объект үүсэх бүрт тоог нэмэгдүүлнэ
    }

    Shape(const char *n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        count++;          // объект үүсэх бүрт нэмэгдэнэ
    }

    virtual ~Shape() {
        delete [] name;
        count--;          // устахад тоо буурна
    }

    // (2) Static гишүүн функцууд — утга оноох, авах
    static void set_count(int c) { count = c; }
    static int get_count() { return count; }

    // (3) this ашигласан гишүүн функц
    char* get_name() { return this->name; }

    // (4) Жинхэнэ хийсвэр функцууд (pure virtual)
    virtual float area() const = 0;        // талбай олох
    virtual float perimeter() const = 0;   // периметр олох
};

// static хувьсагчийн анхны утгыг 0 болгоно
int Shape::count = 0;

// 2. TwoDShape класс
// Энэ класс нь 2 хэмжээст дүрсүүдийн суурь класс юм.
// Shape классыг удамшуулсан бөгөөд бүх дүрсүүд координаттай байна.
class TwoDShape : public Shape {
protected:
    float *x;           // x координатын массив
    float *y;           // y координатын массив
    int point_count;    // оройн тоо (жишээ нь: гурвалжин = 3, квадрат = 4)
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

// 3. Circle класс
// Энэ класс нь TwoDShape-ээс удамшсан бөгөөд тойргийн радиус хадгална.
class Circle : public TwoDShape {
    float radius;   // радиус
public:
    Circle(float _r = 1) : TwoDShape(1, "Circle") {
        this->radius = _r;
        this->x[0] = rand() % 10;
        this->y[0] = rand() % 10;
    }

    // (4) Жинхэнэ хийсвэр функцуудыг дахин тодорхойлж байна
    float area() const override { return M_PI * this->radius * this->radius; }
    float perimeter() const override { return 2 * M_PI * this->radius; }

    void show_info() override {
        cout << "Circle - radius: " << this->radius
             << "  area: " << this->area()
             << "  perimeter: " << this->perimeter() << endl;
    }
};

// 4. Square класс
class Square : public TwoDShape {
    float side;  // квадратын талын урт
public:
    Square(float _s = 1) : TwoDShape(4, "Square") {
        this->side = _s;
    }

    float area() const override { return this->side * this->side; }
    float perimeter() const override { return 4 * this->side; }

    void show_info() override {
        cout << "Square - side: " << this->side
             << "  area: " << this->area()
             << "  perimeter: " << this->perimeter() << endl;
    }
};

// 5. Triangle класс
class Triangle : public TwoDShape {
    float side;  // зөв гурвалжны талын урт
public:
    Triangle(float _s = 1) : TwoDShape(3, "Triangle") {
        this->side = _s;
    }

    float area() const override { return (sqrt(3)/4) * this->side * this->side; }
    float perimeter() const override { return 3 * this->side; }

    void show_info() override {
        cout << "Triangle - side: " << this->side
             << "  area: " << this->area()
             << "  perimeter: " << this->perimeter() << endl;
    }
};

// 6. Main функц
int main() {
    srand(time(0));  // rand() функцийг randomize хийнэ

    TwoDShape *p[10];  // олон төрлийн дүрсний заагчийн массив

    // 10 ширхэг дүрс үүсгэх
    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0) p[i] = new Circle(rand() % 10 + 1);
        if (i % 3 == 1) p[i] = new Square(rand() % 10 + 1);
        if (i % 3 == 2) p[i] = new Triangle(rand() % 10 + 1);
    }

    cout << "Shape-s uusen object: " << Shape::get_count() << endl;
    
    // (5) Талбайгаар эрэмбэлэх
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

    // (5) Периметрээр эрэмбэлэх
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

    // Объектуудыг устгах
    for (int i = 0; i < 10; i++) delete p[i];

    cout << "\nUstgagdsnii daraa object: " << Shape::get_count() << endl;

    return 0;
}
