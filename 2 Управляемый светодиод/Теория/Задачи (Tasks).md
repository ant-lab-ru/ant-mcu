## 1. Что такое задачи?

**Task (задача)** — это независимая программная единица, которая выполняет определенную функцию в системе. В контексте микроконтроллеров задачи обычно реализуются как бесконечные циклы или функции, которые выполняются параллельно или псевдопараллельно.

### Ключевые характеристики задач:

- **Самостоятельность** — каждая задача имеет свою логику работы
    
- **Параллельность** — задачи выполняются "одновременно" (на самом деле последовательно в RTOS или поочередно в суперцикле)
    
- **Изолированность** — задачи минимально зависят друг от друга
    
- **Ответственность** — каждая задача отвечает за конкретную функцию системы
    

## 2. Архитектуры управления задачами

### 2.1 Суперцикл (Super Loop)

Наиболее простой подход для начинающих:

c

void main(void) {
    init_system();  // Инициализация
    
    while(1) {      // Бесконечный цикл - суперцикл
        task_button_check();      // Задача 1: опрос кнопок
        task_led_control();       // Задача 2: управление светодиодами
        task_sensor_read();       // Задача 3: чтение датчиков
        task_uart_process();      // Задача 4: обработка UART
        delay_ms(10);             // Задержка для контроля частоты
    }
}

**Преимущества:**

- Простота реализации
    
- Нет накладных расходов на переключение контекста
    
- Предсказуемое время выполнения
    

**Недостатки:**

- Плохая масштабируемость
    
- Сложность реализации приоритетов
    
- Проблемы с длительными операциями
    

### 2.2 Кооперативная многозадачность (Cooperative Multitasking)

Задачи добровольно отдают управление:

c

typedef struct {
    void (*task_func)(void);  // Функция задачи
    uint32_t period;          // Период выполнения (мс)
    uint32_t last_run;        // Время последнего запуска
} Task;

Task task_list[] = {
    {task_button_check, 10, 0},
    {task_led_control, 20, 0},
    {task_sensor_read, 100, 0},
    {task_uart_process, 5, 0}
};

void scheduler(void) {
    uint32_t current_time = get_system_tick();
    
    for(int i = 0; i < NUM_TASKS; i++) {
        if(current_time - task_list[i].last_run >= task_list[i].period) {
            task_list[i].task_func();              // Выполняем задачу
            task_list[i].last_run = current_time;  // Обновляем время
        }
    }
}

void main(void) {
    init_system();
    
    while(1) {
        scheduler();  // Планировщик задач
        idle_task();  // Фоновая задача (режим пониженного энергопотребления)
    }
}

### 2.3 RTOS (Real-Time Operating System)

Профессиональный подход с вытесняющей многозадачностью:

c

// Пример для FreeRTOS
void task_button(void *pvParameters) {
    while(1) {
        button_check();
        vTaskDelay(pdMS_TO_TICKS(10));  // Задержка 10 мс
    }
}

void task_led(void *pvParameters) {
    while(1) {
        led_control();
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void main(void) {
    // Создание задач
    xTaskCreate(task_button, "Button", 128, NULL, 1, NULL);
    xTaskCreate(task_led, "LED", 128, NULL, 2, NULL);
    
    // Запуск планировщика
    vTaskStartScheduler();
    
    while(1);  // Сюда не должны попасть
}

## 3. Проектирование задач

### 3.1 Принципы декомпозиции системы на задачи

**Критерии выделения задач:**

1. **Функциональная независимость** — задача должна выполнять одну логическую функцию
    
2. **Временные характеристики** — задачи с разной периодичностью лучше разделять
    
3. **Критичность** — критические и некритические функции в разных задачах
    
4. **Ресурсная изоляция** — задачи, использующие разные периферийные модули
    

**Пример декомпозиции системы "Умный термостат":**

- `task_temperature_read` — чтение температуры (период: 1 сек)
    
- `task_display_update` — обновление дисплея (период: 100 мс)
    
- `task_button_handler` — обработка кнопок (период: 10 мс)
    
- `task_network` — сетевое взаимодействие (период: 50 мс)
    
- `task_heater_control` — управление нагревателем (период: 500 мс)
    

### 3.2 Временные параметры задач

c

typedef struct {
    char name[16];           // Имя задачи для отладки
    void (*function)(void);  // Функция задачи
    uint16_t period_ms;      // Период выполнения
    uint16_t deadline_ms;    // Максимальное время выполнения
    uint16_t wcet_ms;        // Worst-Case Execution Time
    uint8_t priority;        // Приоритет (0 - самый низкий)
    uint32_t run_count;      // Счетчик запусков (для статистики)
} TaskDescriptor;

## 4. Синхронизация и взаимодействие задач

### 4.1 Общие проблемы многозадачности

1. **Состояние гонки (Race Condition)** — результат зависит от порядка выполнения
    
2. **Взаимная блокировка (Deadlock)** — задачи ждут ресурсы друг у друга
    
3. **Инверсия приоритетов** — низкоприоритетная задача блокирует высокоприоритетную
    

### 4.2 Механизмы синхронизации

**Флаги и семафоры:**

c

// Простой флаг для суперцикла
volatile uint8_t button_pressed_flag = 0;

void task_button_check(void) {
    if(button_is_pressed()) {
        button_pressed_flag = 1;
    }
}

void task_led_control(void) {
    if(button_pressed_flag) {
        toggle_led();
        button_pressed_flag = 0;
    }
}

**Очереди сообщений (для RTOS):**

c

// Создание очереди
QueueHandle_t sensor_queue = xQueueCreate(10, sizeof(SensorData));

// Отправка в задаче-производителе
void task_sensor_read(void *pvParameters) {
    SensorData data;
    while(1) {
        read_sensor(&data);
        xQueueSend(sensor_queue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Получение в задаче-потребителе
void task_data_process(void *pvParameters) {
    SensorData data;
    while(1) {
        if(xQueueReceive(sensor_queue, &data, portMAX_DELAY) == pdTRUE) {
            process_data(&data);
        }
    }
}