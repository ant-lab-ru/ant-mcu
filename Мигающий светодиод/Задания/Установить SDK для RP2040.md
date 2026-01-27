---
тема: Мигающий светодиод
автор: Егор Анатольевич Денисов
дата: 2026-01-25
задание: false
---

# Результат

- [ ] На вашем компьютере установлены все инструменты для сборки прошивки под микроконтроллер **RP2040**
	- [ ] Система контроля версий **git**
	- [ ] Система автоматизации сборки программного обеспечения **cmake**
	- [ ] Система исполнения сценариев **make**
	- [ ] Компилятор **arm-none-eabi-gcc**
	- [ ] Утилита для преобразования прошивок RP2040 **picotool**
	- [ ] Редактор кода **VSCode**
- [ ] Все инструменты отвечают на запрос версий в терминале
	- [ ] `git --verison`
	- [ ] `camke --version`
	- [ ] `make --version`
	- [ ] `arm-none-eabi-gcc --version`
	- [ ] `picotool version`
	- [ ] `code --version`

> [!EXAMPLE] Пример
>  
> **Проверка версий инструментов в PowerShell**
> 
> ![[Pasted image 20260127124232.png]]

> [!ERROR] Проблемы и решения
> Если программа не отвечает на запрос версии:
> - Установите программу
> 
> Если вы установили программу, но она не отвечает на запрос версии:
> - Проверьте, добавлен ли путь к ней в системную переменную PATH

> [!ATTENTION] Внимание!
> Для наших задач подойдут любые версии инструментов. Установленная на вашем компьютере версия **может** отличаться.
> 
> **Решающим** является не совпадение версии, а наличие установленной программы.

# Система контроля версий git

1. В терминале выполните:

``` bash
git --version
```

2. Убедитесь в том, что программа **git** сообщила свою версию:

``` bash
git version 2.42.0.windows.2
```

3. Если версии нет, [[Установить git|установите git]]

# Система автоматизации сборки ПО cmake

1. В терминале выполните:

``` bash
cmake --version
```

2. Убедитесь в том, что программа **cmake** сообщила свою версию:

``` bash
cmake version 3.30.0

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

3. Если версии нет, [[Установить CMake|установите CMake]]

# Система исполнения сценариев make

1. В терминале выполните:

``` bash
make --version
```

2. Убедитесь в том, что программа **make** сообщила свою версию:

``` bash
GNU Make 3.81
Copyright (C) 2006  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

This program built for i386-pc-mingw32
```

3. Если версии нет, [[Установить make|установите make]]

# Компилятор arm-none-eabi-gcc

1. В терминале выполните:

``` bash
arm-none-eabi-gcc --version
```

2. Убедитесь в том, что программа **arm-none-eabi-gcc** сообщила свою версию:

``` bash
arm-none-eabi-gcc.exe (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

3. Если версии нет, [[Установить arm-none-eabi-gcc|установите arm-none-eabi-gcc]]

# Утилита picotool

1. В терминале выполните:

``` bash
picotool version
```

2. Убедитесь в том, что программа **picotool** сообщила свою версию:

``` bash
picotool v2.2.0-a4 (Windows, GNU-15.2.0, Release)
```

3. Если версии нет, [[Установить picotool|установите picotool]]

# Редактор кода VSCode

1. В терминале выполните:

``` bash
code --version
```

2. Убедитесь в том, что программа **code** сообщила свою версию:

``` bash
1.108.2
c9d77990917f3102ada88be140d28b038d1dd7c7
x64
```

3. Если версии нет, [[Установить VSCode|установите VSCode]]
