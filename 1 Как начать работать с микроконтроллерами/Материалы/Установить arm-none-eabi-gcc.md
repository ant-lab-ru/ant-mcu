---
тема: Как начать работать с микроконтроллерами
автор: Егор Анатольевич Денисов
дата: 2026-01-22
---

# Linux
- Выполнить в терминале:

``` bash
sudo apt update
sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
arm-none-eabi-gcc --version
```

# MacOS
- Выполнить в терминале:

``` bash
brew install gcc-arm-embedded
arm-none-eabi-gcc --version
```

# Windows
- скачать установщик: https://developer.arm.com/downloads/-/gnu-rm;
- или тут: https://disk.360.yandex.ru/d/AukS_dPNij9O5w
- запустить установщик, обязательно отметить добавление arm-none-eabi-gcc в Path (установить галочки, как на картинке):

![[Pasted image 20260126174512.png|300]]

> [!ERROR] Проблемы и решения
> При запуске может появиться такое сообщение, нажимаем запустить
> 
> ![[Pasted image 20260126174321.png|300]]

- если при установке произошел сбой "Current PATH length too long to modify in installer; set manually if needed", [[Добавить в PATH]] вручную;
- после установки проверить
	
``` bash
arm-none-eabi-gcc --version
```

# Результат

``` bash
PC C:\users\potylitcyn> arm-none-eabi-gcc --version
arm-none-eabi-gcc.exe (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
PC C:\users\potylitcyn> 
```

Версия может отличаться, для наших задач это не принципиально