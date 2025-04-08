#ifndef ASSERT_H
#define ASSERT_H

#include <cassert>
#include <iostream>

/**
 * @brief Кастомный макрос для отладки с выводом подробной информации
 *
 * @param condition Условие, которое должно быть истинным
 * @param message Сообщение об ошибке
 *
 * Пример использования:
 * @code
 * ASSERT(value > 0, "Значение должно быть положительным");
 * ASSERT(ptr != nullptr, "Указатель не может быть null");
 * @endcode
 */
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << "\n" \
                      << "Message: " << message << "\n" \
                      << "File: " << __FILE__ << "\n" \
                      << "Line: " << __LINE__ << std::endl; \
            assert(false); \
        } \
    } while(0)

#endif // ASSERT_H
