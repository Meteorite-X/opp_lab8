#include<iostream> 
#include<cstring> 
using namespace std;

class Shape{
    protected:
        char * name;
        static int count; //shape class-s үүсэн объектуудыг тоолно.
    public:
        Shape(){
            name = new char[20];
            strcpy(name, "No name");
            count++; //объект үүсэх бүрт нэмэгдэнэ.
        }

        Shape(const char * n){
            name = new char[strlen(n)+1];
            strcpy(name, n);
            count++; //объект үүсэх бүрт нэмэгдэнэ.
        }

        virtual ~Shape(){
            delete [] name;
            count--; //объект устах бүрт нэгээр багасна.
        }

        // count буюу хэдэн объект байгааг авах static гишүүн функц
        static int get_count() {
            return count;
        }

        // count-д утга оноох static г/ф
        static void set_count(int n){
            count = n;
        }
};

//анхны утга өгнө.
int Shape::count = 0; 




int main(){

    Shape::set_count(5);
    cout << "Shape-s uussen object: " << Shape::get_count() << endl;

    return 0;
}