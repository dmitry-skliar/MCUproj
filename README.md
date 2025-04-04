# Эксперементы с программированием микроконтроллеров на С++.

1. Использование clang вместо arm-none-eabi-gcc.

    clang -print-targets
    ...
    thumb

    clang --target=thumb -print-supported-cpus
    ...
    cortex-m3

    clang --target=thumb -mcpu=cortex-m3 -mfloat-abi=soft
    clang --target=thumb -mcpu=cortex-m3 -mfloat-abi=soft --print-effective-triple

  И в итоге получено вот это:

    clang --target=thumbv7m-none-eabi

2. Таблица прерываний, пример создания.

    IRQ_CREATE_TABLE - это макрос который создает структуру таблицы.
    (
        IRQ_TABLE_INSERT(&value) - этот макрос записывает значение в таблицу.
        IRQ_TABLE_INSERT(function_name) - или записывает адрес функции в таблицу.
    )

  Т.к. это макросы, то точки с запятой и запятые использовать нельзя!

  IRQ(...) и IRQ_DEFINE(...) использовать в одном файле нельзя, т.к. используемые атрибуты
  подразумевают слабое оъявление с указанием на функцию по умолчанию.

3. Поморгаем лампочкой из kmain функции.

    TODO!
