#include <iostream>
#include <vector>
#include <list>
#include <chrono>

/*
std::vector

Преимущества:

- Оптимизирована для произвольного доступа: Будучи массивом, вектор имеет постоянное время доступа к элементам по индексу.
- Эффективное вставка и удаление в конце: Операции вставки и удаления в конце вектора работают с амортизированной сложностью O(1), поскольку он может увеличивать свой размер для размещения новых элементов.
- Поддержка итераторов: Вектор предоставляет итераторы для обхода его элементов.

Недостатки:

- Неэффективное вставка и удаление в середине: Вставка или удаление элементов в середине вектора требует перераспределения всех последующих элементов. Это может привести к значительным задержкам для больших векторов.
- Пространство фиксированного размера: Вектор имеет фиксированный размер, и его необходимо перераспределять при добавлении элементов за пределы его текущей емкости. Это может привести к фрагментации памяти.

std::list

Преимущества:

- Эффективная вставка и удаление в середине: Список имеет сложность вставки и удаления в середине O(1), так как он подключен с использованием отдельных узлов.
- Гибкий размер: Список может динамически увеличиваться и уменьшаться по мере добавления и удаления элементов без каких-либо перераспределений.
- Поддержка двунаправленных итераторов: Список предоставляет двунаправленные итераторы, что позволяет обходить элементы как вперед, так и назад.

Недостатки:

- Медленный произвольный доступ: Доступ к элементам по индексу в списке имеет сложность O(n), так как каждый элемент нужно найти, переходя по списку.
- Дополнительные расходы: Хранение данных в отдельных узлах приводит к дополнительным расходам памяти.
*/

int listSizeInBytes(const std::list<int>& list) {
    // Get the size of the list in bytes.
    size_t sizeInBytes = sizeof(list);

    // Iterate over the list and add the size of each element in bytes.
    for (auto it = list.begin(); it != list.end(); ++it) {
        sizeInBytes += sizeof(*it);
    }

    // Return the size of the list in bytes.
    return sizeInBytes;
}
int main()
{
    setlocale(LC_ALL, "rus");
    // Создать вектор и список с 1 миллионом элементов
    std::vector<int> v(1000000);
    std::list<int> l(1000000);
    {
        // Вычислить объем памяти, используемой каждым контейнером

        // Для std::vector: размер массива * размер элемента
        std::cout << "Объем памяти std::vector: " << v.size() * sizeof(v[0]) << " байт" << std::endl;

        // Для std::list: размер списка * (размер элемента + размер узла)
        std::cout << "Объем памяти std::list: " << listSizeInBytes(l) << " байт" << std::endl;
    }
    {
        // заполняем
        for (int i = 0; i < 100000; ++i) {
            v.insert(v.begin(), i);
            l.push_front(i);
        }

        // таймер
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100000; ++i) {
            v[i] = i;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time_taken_vector_write = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на запись std::vector " << time_taken_vector_write << " наносекунд" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100000; ++i) {
            v[i];
        }
        end = std::chrono::high_resolution_clock::now();
        auto time_taken_vector_read = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на чтение std::vector " << time_taken_vector_read << " наносекунд" << std::endl;

        int j = 0;
        start = std::chrono::high_resolution_clock::now();
        for (int x: l) {
            x = j;
            j++;
        }
        end = std::chrono::high_resolution_clock::now();
        auto time_taken_list_write = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на запись std::list " << time_taken_list_write << " наносекунд" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (int x : l) {
            x;
        }
        end = std::chrono::high_resolution_clock::now();
        auto time_taken_list_read = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на чтение std::list " << time_taken_list_read << " наносекунд" << std::endl;
    }
    return 0;
}