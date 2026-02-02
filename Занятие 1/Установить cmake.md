---
тема: Как начать работать с микроконтроллерами
автор: Егор Анатольевич Денисов
дата: 2026-01-25
---

> [!INFO] Факт
> В операционных системах Linux и MacOS при установке программ через терминал они скачиваются из интернета из специальных репозиториев при помощи [[Менеджер пакетов|пакетных менеджеров]].

> [!ATTENTION] Внимание!
> Для наших задач подойдёт любая версии **CMake**. Установленная на вашем компьютере версия **может** отличаться.

# Linux

1. Выполнить в терминале [[обновление списка доступных пакетов]]:

``` bash
sudo apt update
sudo apt install cmake
cmake --version
```

# MacOS

1. В терминале при помощи программы **brew** установите программу **CMake**:

``` bash
brew install cmake
cmake --version
```

2. Запросите версию программы **CMake**

``` bash
cmake --version
```

3.  Убедитесь в том, что программа **CMake** сообщает свою версию:

``` bash
ivanpotylitcyn@Ivans-MacBook-Pro ~ % cmake --version
cmake version 4.2.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
ivanpotylitcyn@Ivans-MacBook-Pro ~ %
```

# Windows

1. Cкачать установщик:

https://cmake.org/download/

2. Запустить установщик
	- При установке обязательно поставьте галочку **Добавить git в Path**

3. В терминале убедитесь в том, что программа **CMake** сообщает свою версию:

``` bash
PC C:\users\potylitcyn> cmake --version
cmake version 3.30.0

CMake suite maintained and supported by Kitware (kitware.com/cmake).
PC C:\users\potylitcyn> 
```
