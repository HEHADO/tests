#include <iostream>
#include <fstream>
#include <deque>
#include <map>
//console colors
#define COLORENDS      "\x1b[0m"
#define GREEN          "\x1b[32m"
#define RED            "\x1b[31m"

using std::cin; 
using std::cout;
// контейнер с данными
class Container {
    public:
    std::string key;
    std::deque<std::string> body;
    Container* ptr = nullptr;
};
//новое имя для структуры с контейнерами
typedef std::map<std::string, Container> Map;
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
void normalize(Container& container) noexcept {
    quickSort<std::deque<std::string>, std::string>(container.body,0,container.body.size()-1);
    return;
}
//функция чтения пары ключ-данные
Container* readCouple(std::ifstream& file, Map& map,Container* Old_cnt) {
    Container container;
    std::string real_key;
    int i = 0;
    std::string body="";
    container.ptr = Old_cnt;
    file >> container.key >> body; 
    if (container.key == "") return nullptr;
    if (body == "") {
        std::cerr << RED << "bad file\n" << COLORENDS;
        return nullptr;
    }
    container.body.push_back(body);
    real_key = container.key;
    quickSort <std::string>(real_key, 0, real_key.size()-1);
    try {
        map.at(real_key);
        map[real_key].body.push_back(body);
        return nullptr;
    } catch(const std::out_of_range& e) {
        map.insert(std::make_pair(real_key,container));
        return &map[real_key];
    }
}

Container* Read_Wrap(std::ifstream& file, Map& map) {
    Container* ptr1,* ptr2;
    ptr1 = readCouple(file, map, nullptr);
    if (!ptr1) exit ;
    while (!file.eof()) {
        std::swap(ptr1,ptr2);
        if (!(ptr1 = readCouple(file, map, ptr2))){
            std::swap(ptr1,ptr2);
        }
    }
    return ptr1;
}

void print(Container* ptr){
    if (!ptr) return;
    print(ptr->ptr);
    cout << ptr->key << "   ";
    normalize(*ptr);
    for (int j = 0; j < ptr->body.size(); ++j) {
        cout << ptr->body[j];
    }
    cout<<std::endl;
}

int main(int argc, char const *argv[]) {
    Map map;
    Container* ptr;
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
    ptr = Read_Wrap(file, map);
    //сортируем все данные
    //normalize(map);
    //печатаем результат
    cout << GREEN << "Result\n" << COLORENDS;
    print(ptr);
    return 0;    
}