---
тема: Как работать с дисплеем
автор: Иван Юрьевич Потылицын
дата: 2026-03-12
задание: false
---

# Результат

- [ ] В `main.c` включен заголовочные файлы драйвера дисплея
- [ ] В `main.c` создана статическая переменная контекста дисплея с интерфейсом к платформе
- [ ] В `main.c` объявлены макросы номеров подключённых GPIO
- [ ] В `main.c` реализованы функции интерфейса к платформе
- [ ] В `main.c` реализована функция инициализации интерфейса к платформе
- [ ] В  функции `main()` инициализированы интерфейс к платформе и контекст дисплея, задана ориентация экрана

# Инструкция

1. Подключить в `main.c` заголовочный файл драйвера дисплея

``` C
#include "ili9341-driver.h"
```

> [!NOTE] Примечание
> 
> В библиотеке четыре заголовочных файла. Мы будем подключать их по одному, чтобы понимать какие функции собраны в разных файлах, почему они разделены именно так и почему это удобно.

2. Создать статические переменные для хранения интерфейса к платформе и контекста дисплея

``` C
static ili9341_display_t ili9341_display = {0};
static ili9341_hal_t ili9341_hal = {0};
```

> [!INFO] Определение
> **HAL (Hardware Abstraction Layer)** - это шаблон проектирования при котором логика библиотеки пишется исключая любую прямую связь с конкретным микроконтроллером или платой. Эта связь сводится к ограниченному набору функций, которые реализует пользователь.

> [!NOTE] Примечание
> 
> В нашем случае связь логики драйвера дисплея с «железом» сводится к двум функциям интерфейса SPI, трём функциям GPIO и одной функции запроса времени у микроконтроллера.
> 
> ``` C
> typedef struct {
>     ili9341_spi_write spi_write;
>     ili9341_spi_read spi_read;
>     ili9341_gpio_cs_write gpio_cs_write;
>     ili9341_gpio_dc_write gpio_dc_write;
>     ili9341_gpio_reset_write gpio_reset_write;
>     ili9341_delay_ms delay_ms;
> } ili9341_hal_t;
> ```
> Прототипы функций, составляющих HAL нашего драйвера, представлены ниже.
> 
> ``` C
> typedef void (*ili9341_spi_write)(const uint8_t* data, uint32_t size);
> typedef void (*ili9341_spi_read)(uint8_t* buffer, uint32_t length);
> typedef void (*ili9341_gpio_cs_write)(bool level);
> typedef void (*ili9341_gpio_dc_write)(bool level);
> typedef void (*ili9341_gpio_reset_write)(bool level);
> typedef void (*ili9341_delay_ms)(uint32_t ms);
> ```

3. Объявить макросы номеров GPIO, к которым подключены провода от дисплея

``` C
#define ILI9341_PIN_MISO  4
#define ILI9341_PIN_CS    10
#define ILI9341_PIN_SCK   6
#define ILI9341_PIN_MOSI  7
#define ILI9341_PIN_DC    8
#define ILI9341_PIN_RESET 9
// #define PIN_LED -> 3.3V
```

4. Реализовать функции интерфейса к платформе

``` C
void rp2040_spi_write(const uint8_t *data, uint32_t size) {
    spi_write_blocking(spi0, data, size);
}

void rp2040_spi_read(uint8_t *buffer, uint32_t length) {
    spi_read_blocking(spi0, 0, buffer, length);
}

void rp2040_gpio_cs_write(bool level) {
    gpio_put(ILI9341_PIN_CS, level);
}

void rp2040_gpio_dc_write(bool level) {
    gpio_put(ILI9341_PIN_DC, level);
}

void rp2040_gpio_reset_write(bool level) {
    gpio_put(ILI9341_PIN_RESET, level);
}

void rp2040_delay_ms(uint32_t ms) {
    sleep_ms(ms);
}
```

> [!NOTE] Примечание
> 
> Для работы с SPI необходимо подключить в `CMakeLists.txt` библиотеку `hardware_spi`, а в `main.c` подключить заголовочный файл.
> 
> ``` C
> #include "hardware/spi.h"
> ```
> 

5. Реализовать в `main.c` функцию инициализации интерфейса к платформе

``` C
void ili9341_rp2040_init()
{
	spi_init(spi0, 62500000);
	
	gpio_set_function(ILI9341_PIN_MISO, GPIO_FUNC_SPI);
	gpio_set_function(ILI9341_PIN_SCK, GPIO_FUNC_SPI);
	gpio_set_function(ILI9341_PIN_MOSI, GPIO_FUNC_SPI);
	
	gpio_init(ILI9341_PIN_CS);
	gpio_init(ILI9341_PIN_DC);
	gpio_init(ILI9341_PIN_RESET);
	
	gpio_set_dir(ILI9341_PIN_CS, GPIO_OUT);
	gpio_set_dir(ILI9341_PIN_DC, GPIO_OUT);
	gpio_set_dir(ILI9341_PIN_RESET, GPIO_OUT);
	
	gpio_put(ILI9341_PIN_CS, 1);
	gpio_put(ILI9341_PIN_DC, 0);
	gpio_put(ILI9341_PIN_RESET, 0);
	
	ili9341_hal.spi_write = rp2040_spi_write;
	ili9341_hal.spi_read = rp2040_spi_read;
	ili9341_hal.gpio_cs_write = rp2040_gpio_cs_write;
	ili9341_hal.gpio_dc_write = rp2040_gpio_dc_write;
	ili9341_hal.gpio_reset_write = rp2040_gpio_reset_write;
	ili9341_hal.delay_ms = rp2040_delay_ms;
}
```

> [!NOTE] Примечание
> 
> Функция инициализации интерфейса делает то, что мы обычно делали в начале функции `main()` перед запуском суперцикла. В этом случае можно было сделать также, но, чтобы не загромождать `main()` предлагаем вынести в отдельную функцию инициализацию GPIO, SPI и сбор указателей на функции интерфейса.
> 

> [!HINT] Совет
> 
> Подход с выделением программного кода в отдельные смысловые части очень сильно помогает держать проект понятным, надёжным и готовым к новым функциям.

6. В функции `main()` инициализировать интерфейс к платформе, драйвер дисплея и задать ориентацию экрана

``` C
ili9341_rp2040_init();
ili9341_init(&ili9341_display, &ili9341_hal);
ili9341_set_rotation(&ili9341_display, ILI9341_ROTATION_90);
```

> [!NOTE] Примечание
> 
> В файлах `ili9341-driver.h` и `ili9341-driver.c` собраны только сущности, необходимые именно взаимодействия с дисплеем: макросы регистров, структуры контекстов, прототипы функций HAL и функции общения с микросхемой.
> 
> Причём функций общения с микросхемой всего четрые:
> 
> ``` C
> void ili9341_write_cmd();
void ili9341_write_data();
void ili9341_write_data_byte();
void ili9341_set_address_window();
> ```
> 
> Этих функций (собранных в `ili9341-driver`) достаточно, чтобы взаимодействовать с дисплеем «на низком уровне». Для такого взаимодействия нужно уметь пользоваться [[ILI9341 Datasheet.pdf#page=83|командами, которые поддерживает микросхема ILI9341]].
> 
> Однако, пользователь дисплея вероятнее всего захочет использовать и добавлять свои «высокоуровневые» или «прикладные» команды, например:
> - нарисовать прямоугольник
> - нарисовать пиксель
> - нарисовать символ
> 
> Такие команды, использующие подключённый в этом задании драйвер, реализованы в библиотеке в файле `ili9341-display.c`.

7. Скомпилировать прошивку, загрузить в RP2040, проверить, что прошивка отвечает на запросы по API
