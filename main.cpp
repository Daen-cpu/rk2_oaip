#include <iostream>
#include <vector>
#include <memory>  

class MusicalInstrument {
protected:
    std::string name;   
    std::string material; 

public:
    // Конструктор для инициализации данных
    // Важно: Инициализация через конструктор базового класса
    MusicalInstrument(const std::string& name, const std::string& material)
        : name(name), material(material) {}

    // Виртуальная функция для вывода информации о музыкальном инструменте
    // Важно: Это метод полиморфизма, который может быть переопределен в производных классах
    virtual void display() const {
        std::cout << "Instrument: " << name << "\nMaterial: " << material << std::endl;
    }

    // Виртуальный деструктор для корректного уничтожения объектов производных классов
    // Важно: Для обеспечения полиморфного удаления объектов через указатели на базовый класс
    virtual ~MusicalInstrument() = default;
};

// Класс StringInstrument , наследуется от MusicalInstrument
// Важно: Расширяет базовую функциональность музыкального инструмента для струнных инструментов
class StringInstrument : public MusicalInstrument {
private:
    int stringCount;  

public:
    // Конструктор для инициализации струнного инструмента
    // Важно: Инициализация дополнительных данных
    StringInstrument(const std::string& name, const std::string& material, int stringCount)
        : MusicalInstrument(name, material), stringCount(stringCount) {}

    // Переопределение метода display для струнного инструмента
    // Важно: Переопределение метода для вывода специфичной информации о струнных инструментах
    void display() const override {
        std::cout << "String Instrument: " << name << "\nMaterial: " << material
                  << "\nNumber of strings: " << stringCount << std::endl;
    }
};

// Класс BrassInstrument (Духовой инструмент), наследуется от MusicalInstrument
// Важно: Представляет духовой инструмент с дополнительной информацией о типе латуни
class BrassInstrument : public MusicalInstrument {
private:
    std::string brassType; 

public:
    // Конструктор для инициализации духового инструмента
    // Важно: Инициализация специфической информации о типе латуни
    BrassInstrument(const std::string& name, const std::string& material, const std::string& brassType)
        : MusicalInstrument(name, material), brassType(brassType) {}

    // Переопределение метода display для духового инструмента
    // Важно: Переопределение метода для вывода специфической информации о духовых инструментах
    void display() const override {
        std::cout << "Brass Instrument: " << name << "\nMaterial: " << material
                  << "\nBrass type: " << brassType << std::endl;
    }
};

// Функция для изменения характеристик инструмента
// Важно: Эта функция демонстрирует полиморфизм, позволяя работать с объектами разных типов через указатель на базовый класс
void modifyInstrument(MusicalInstrument* instrument) {
    // Используем dynamic_cast для безопасного приведения типов
    // Важно: Проверяем и приводим указатель к конкретным типам (StringInstrument или BrassInstrument)
    if (auto stringInstrument = dynamic_cast<StringInstrument*>(instrument)) {
        stringInstrument->display(); 
    }
    else if (auto brassInstrument = dynamic_cast<BrassInstrument*>(instrument)) {
        brassInstrument->display(); 
    }
    else {
        std::cout << "Unknown instrument type.\n"; 
    }
}

int main() {
    // Контейнер для хранения указателей на музыкальные инструменты
    // Важно: Используем std::vector для хранения объектов различных типов через указатели на базовый класс
    std::vector<std::unique_ptr<MusicalInstrument>> instruments;

    // Добавляем объекты в контейнер
    // Важно: Используем умные указатели std::unique_ptr для автоматического управления памятью
    instruments.push_back(std::make_unique<StringInstrument>("Guitar", "Wood", 6));
    instruments.push_back(std::make_unique<StringInstrument>("Violin", "Wood", 4));
    instruments.push_back(std::make_unique<BrassInstrument>("Trumpet", "Brass", "Yellow Brass"));
    instruments.push_back(std::make_unique<BrassInstrument>("Trombone", "Brass", "Red Brass"));

    // Используем итераторы STL для вывода информации о каждом инструменте
    // Важно: С помощью полиморфизма вызываем метод display() для каждого инструмента в контейнере
    for (const auto& instrument : instruments) {
        instrument->display();  // Важно: Вызов метода display через базовый указатель на MusicalInstrument
        std::cout << std::endl;
    }

    // Применяем изменение характеристик для первого инструмента
    // Важно: Передаем указатель на базовый класс, и функция modifyInstrument работает с любыми производными классами
    modifyInstrument(instruments[0].get());  // Передаем указатель на первый элемент в контейнере

    return 0;
}
