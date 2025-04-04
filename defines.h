#pragma once
#pragma clang system_header

// @brief Тип 8-битного беззнакового целого.
typedef unsigned char u8;

// @brief Тип 16-битного беззнакового целого.
typedef unsigned short u16;

// @brief Тип 32-битного беззнакового целого.
typedef unsigned int u32;

// @brief Тип 64-битного беззнакового целого.
typedef unsigned long long u64;

// @brief Тип 8-битного знакового целого.
typedef signed char i8;

// @brief Тип 16-битного знакового целого.
typedef signed short i16;

// @brief Тип 32-битного знакового целого.
typedef signed int i32;

// @brief Тип 64-битного знакового целого.
typedef signed long long i64;

// @brief Тип 32-битного числа c плавающей точкой.
typedef float f32;

// @brief Тип 64-битного числа c плавающей точкой.
typedef double f64;

#if defined __x86_64__ && !defined __ILP32__
    // @brief Тип беззнакового целого, для хранения адреса памяти.
    typedef u64 uptr;
#else
    // @brief Тип беззнакового целого, для хранения адреса памяти.
    typedef u32 uptr;
#endif

#ifndef __cplusplus
    // @brief Тип логического значения.
    typedef _Bool bool;
#endif

#if __cplusplus
    /*
        @brief Выполняет проверку утверждения во время компиляции, и выводит сообщение если оно ложно.
        @param assertion Проверяемое во время компиляции утверждение.
        @param message Сообщение которое будет выведено если утверждение ложно.
    */
    #define STATIC_ASSERT(assertion, message) static_assert(assertion, message)
#else
    /*
        @brief Выполняет проверку утверждения во время компиляции, и выводит сообщение если оно ложно.
        @param assertion Проверяемое во время компиляции утверждение.
        @param message Сообщение которое будет выведено если утверждение ложно.
    */
    #define STATIC_ASSERT(assertion, message) _Static_assert(assertion, message)
#endif

// Проверка типов.
STATIC_ASSERT(sizeof(u8)  == 1, "Assertion 'sizeof(u8) == 1' failed.");
STATIC_ASSERT(sizeof(u16) == 2, "Assertion 'sizeof(u16) == 2' failed.");
STATIC_ASSERT(sizeof(u32) == 4, "Assertion 'sizeof(u32) == 4' failed.");
STATIC_ASSERT(sizeof(u64) == 8, "Assertion 'sizeof(u64) == 8' failed.");
STATIC_ASSERT(sizeof(i8)  == 1, "Assertion 'sizeof(i8) == 1' failed.");
STATIC_ASSERT(sizeof(i16) == 2, "Assertion 'sizeof(i16) == 2' failed.");
STATIC_ASSERT(sizeof(i32) == 4, "Assertion 'sizeof(i32) == 4' failed.");
STATIC_ASSERT(sizeof(i64) == 8, "Assertion 'sizeof(i64) == 8' failed.");
STATIC_ASSERT(sizeof(f32) == 4, "Assertion 'sizeof(f32) == 4' failed.");
STATIC_ASSERT(sizeof(f64) == 8, "Assertion 'sizeof(f64) == 8' failed.");

// Определение логических констант.
#ifndef __cplusplus
    #define false 0
    #define true  1
#endif

// Определение нулевого указателя.
#ifndef __cplusplus
    #define nullptr ((void*)0)
#endif

#define U64_MAX 18446744073709551615UL
#define U32_MAX 4294967295U
#define U16_MAX 65535U
#define U8_MAX  255U
#define U64_MIN 0UL
#define U32_MIN 0U
#define U16_MIN 0U
#define U8_MIN  0U

#define I8_MAX  127
#define I16_MAX 32767
#define I32_MAX 2147483647
#define I64_MAX 9223372036854775807L
#define I8_MIN  (-I8_MAX  - 1)
#define I16_MIN (-I16_MAX - 1)
#define I32_MIN (-I32_MAX - 1)
#define I64_MIN (-I64_MAX - 1)

// Модификатор экспорта функий С для С++.
#if defined(__cplusplus)
    #define EXTERN_C extern "C"
#else
    #define EXTERN_C
#endif

// Модификаторы встроенной статической функции.
#define STATIC_INLINE static inline
#define STATIC_FORCEINLINE __attribute__((always_inline)) static inline

/*
    @brief Макрос установки атрибутов.
    @param attr Список атрибутов.
*/
#define ATTR(attr...) __attribute__((attr))

/*
    @brief Создает объявление/функцию обработчика прерывания заданными с атрибутами.
    @param handler Имя объявления/функции обработчика прерывания.
    @param attr Список стрибутов которые необходимо применить к обработчику (опционально).
*/
#define IRQ(handler, attr...) EXTERN_C ATTR(attr) void handler()

/*
    @brief Создает слабое объяевление функции обработчика прерывания с обработчиком по умолчанию.
    NOTE:  Не работает в одном файле, если есть реализация этой функции, нужно объявить в другом файле.
    @param handler Имя объявления функции обработчика прерывания.
    @param default Имя обработчика прерывания по умолчанию, если нет реализации функции.
*/
#define IRQ_DEFINE(handler, default) IRQ(handler, weak, alias(#default))

// TODO: Два нижних определения IRQ_ реализовать для разных микроконтроллеров, например для AVR (текущие для STM32).
// TODO: Задание секции вынеси в отдельное определение.
/*
    @brief Создает таблицу прерываний с предоставленными векторами прерывания в заданном порядке.
    NOTE:  Для вставки обработчиков прерывания необходимо использовать 'IRQ_TABLE_INSERT(...)'.
    @param handlers Список обработчиков прерываний которые необходимо вставить в таблицу.
*/
#define IRQ_CREATE_TABLE(handlers) EXTERN_C ATTR(section(".irq_table"), used) void (*__table[])() = { handlers };

/*
    @brief Создает запись вектора прерывания в таблицу прерываний в заданном месте.
    @param value Значение/адрес функции для добавления в таблицу, или nullptr для резервирования.
*/
#define IRQ_TABLE_INSERT(value) (void (*)())value,

/*
    @brief Макрос для копирования 8 байт(64 бита) из источника в память назначения.
    @param dest Источник байт которые нужно скопировать.
    @param src Место назначения куда нужно скопировать байты.
*/
#define KCOPY8BYTES(dest, src) *((u64*)dest) = *((u64*)src)

/*
    @brief Макрос для копирования 4 байта(32 бита) из источника в память назначения.
    @param dest Источник байт которые нужно скопировать.
    @param src Место назначения куда нужно скопировать байты.
*/
#define KCOPY4BYTES(dest, src) *((u32*)dest) = *((u32*)src)

/*
    @brief Макрос для копирования 2 байта(16 бит) из источника в память назначения.
    @param dest Источник байт которые нужно скопировать.
    @param src Место назначения куда нужно скопировать байты.
*/
#define KCOPY2BYTES(dest, src) *((u16*)dest) = *((u16*)src)

/*
    @brief Макрос для копирования 1 байт (8 бит) из источника в память назначения.
    @param dest Источник байт которые нужно скопировать.
    @param src Место назначения куда нужно скопировать байты.
*/
#define KCOPY1BYTE(dest, src) *((u8*)dest) = *((u8*)src)

/*
    @brief Макрос усечения значения в указанных пределах.
    @param value Значение, которое нужно усечь.
    @param min Значение минимального предела включительно.
    @param max Значение максимального предела включительно.
    @return Значение в заданных пределах.
*/
#define KCLAMP(value, min, max) ((value <= min) ? min : (value >= max) ? max : value)

/*
    @brief Макрос получения минимального значения из двух заданных.
    @param v0 Первое значение.
    @param v1 Второе значение.
    @return Минимальное значение.
*/
#define KMIN(v0,v1) (v0 < v1 ? v0 : v1)

/*
    @brief Макрос получения максимального значения из двух заданных.
    @param v0 Первое значение.
    @param v1 Второе значение.
    @return Максимальное значение.
*/
#define KMAX(v0,v1) (v0 > v1 ? v0 : v1)

/*
    @brief Вычисляет новый указатель относительно заданного указателя и смещения.
    @param ptr Указатель для вычисления нового.
    @param offset Смещение в байтах.
    @return Новое значение указателя.
*/
#define POINTER_GET_OFFSET(ptr, offset) (void*)((u8*)ptr + offset)

/*
    @brief Получает значение поля структуры заданного типом и указателем.
    @param type Тип структуры.
    @param ptr Указатель на структуру.
    @return Возращает значение поля структуры.
*/
#define MEMBER_GET_VALUE(type, ptr, member) (((type*)(ptr))->member)

/*
    @brief Получает смещение поля структуры заданного типом и указателем.
    @param type Тип структуры.
    @param ptr Указатель на структуру.
    @return Возращает смещение поля структуры.
*/
#define MEMBER_GET_OFFSET(type, ptr, member) (((type*)nullptr)->member)
