#include <iostream>
#include <fstream>
#include <deque>
//console colors
#define COLORENDS      "\x1b[0m"
#define GREEN          "\x1b[32m"
#define RED            "\x1b[31m"

using std::cin; 
using std::cout;
// контейнер с данными
class Container {
    public:
    std::string key, real_key;
    std::deque<std::string> body;
    int count = 0;
};
//новое имя для структуры с контейнерами
typedef std::deque<Container, std::allocator<Container> > List;
// функция сортировки, аналог qsort для любых типов данных поддерживающих сравнение
template <typename T, typename L = int>
void quickSort(T &str, const int left,const int right) noexcept {
    int i = left, j = right;
    L mid = str[(left + right) / 2];
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
    if (left < j)
        quickSort<T, L>(str, left, j);
    if (i < right)
        quickSort<T, L>(str, i, right);
}
//функция сортировки для данных
void normalize(List& list) noexcept {
    int i=-1;
    while (++i < list.size()) {
        if (list[i].count==1) continue;
        quickSort<std::deque<std::string>, std::string>(list[i].body,0,list[i].body.size()-1);
    }
    return;
}
//функция чтения пары ключ-данные
void readCouple(std::ifstream& file, List& list) noexcept {
    Container container;
    int i = 0;
    std::string body="";
    file >> container.key >> body;
    if (container.key == "") return;
    if (body == "") {
        std::cerr << RED << "bad file\n" << COLORENDS;
        return;
    }
    container.body.push_back(body);
    container.real_key = container.key;
    quickSort <std::string>(container.real_key, 0, container.real_key.size()-1);
    while (i < list.size()) {
        if(list[i].real_key == container.real_key){
            list[i].body.push_back(body);
            ++list[i].count;
            return;
        }
        ++i;
        }
    ++list[i].count;
    list.push_back(container);
}

int main(int argc, char const *argv[]) {
    List list;
    std::ifstream file;
    // открываем файл
    if (argc > 1) {
        file.open(argv[1]);
    } else {
        std::string s1;
        cout << RED << "Write the name of the input file" << COLORENDS << std::endl;
        cin >> s1;
        file.open(s1); 
    }
    if (!file.is_open()){
        std::cerr << RED << "Can't open input file\n" << COLORENDS;
        return 1;
    }
    // читаем файл  и создаем список контейнеров, в которых хранятся ключи с данными
    while (!file.eof()){
        readCouple(file,list);
    }
    //сортируем все данные
    normalize(list);
    //печатаем результат
    cout << GREEN << "Result\n" << COLORENDS;
    for (int i = 0; i < list.size(); ++i){
        Container container = list[i];
        cout << container.key << "   ";
        for (int j = 0; j < container.body.size(); ++j) {
            cout << container.body[j];
        }
        cout << std::endl;
    }
    return 0;    
}