#include <iostream>
#include <fstream>
#include <list>
//console colors
#define COLORENDS      "\x1b[0m"
#define RED            "\x1b[31m"

using std::cin; 
using std::cout;
// крнтейнер с данными
class Container {
    public:
    std::string body, key, real_key;
};
// функция сортировки, аналог qsort для строк
void quickSort(std::string &str, const int left,const int right) noexcept {
          int i = left, j = right;
          int mid = str[(left + right) / 2];

          /* partition */
          while (i <= j) {
                while (str[i] < mid)
                      i++;
                while (str[j] > mid)
                      j--;
                if (i <= j) {
                      std::swap(str[i], str[j]);
                      i++; j--;
                }
          };

          /* recursion */
          if (left < j)
                quickSort(str, left, j);
          if (i < right)
                quickSort(str, i, right);
    }


void normalize(std::string& s1){
    //qsort();
    s1.c_str();
}


int main(int argc, char const *argv[]) {
    std::list<Container, std::allocator<Container> > list;
    std::ifstream file;
    // открываем файл
    if (argc > 1) {
        file.open(argv[1]);
    } else {
        std::string s1;
        cout << "write imput filename" << std::endl;
        cin >> s1;
        file.open(s1); 
    }
    if (!file.is_open()){
        std::cerr << RED << "can't open input file\n" << COLORENDS;
        return 1;
    }
    // читаем файл  и создаем список контейнеров, в которых хранятся ключи с данными
    while (!file.eof()){
        Container container;
        file >> container.key >> container.body;
        if ((container.key == "")||(container.body == "")) {
            std::cerr << RED << "bad file\n" << COLORENDS;
            break;
        }
        container.real_key = container.key;
        quickSort (container.real_key, 0, container.real_key.size() );
        list.push_front(container);
    }

    return 0;
}


