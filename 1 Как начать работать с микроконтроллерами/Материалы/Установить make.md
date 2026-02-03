---
тема: Как начать работать с микроконтроллерами
автор: Егор Анатольевич Денисов
дата: 2026-01-25
---

> [!ATTENTION] Внимание!
> Для наших задач подойдёт любая версии **make**. Установленная на вашем компьютере версия **может** отличаться.

# Linux

Выполнить в терминале:

``` bash
sudo apt update
sudo apt install make
make --version
```

# MacOS

Выполнить в терминале:

``` bash
brew install make
make --version
```

# Windows

- скачать установщик: https://gnuwin32.sourceforge.net/packages/make.htm;
- Нажать ссылку **Setup** напротив надписи **Complete package, except sources**, затем дождаться таймера на **SourceForge.net**

![[Pasted image 20260126171616.png|400]]

![[Pasted image 20260126171646.png|400]]

- запустить установщик make, следовать инструкциям установки

![[Pasted image 20260126171725.png|400]]

- найти расположение файла make.exe в файловой системе (при установке по умолчаию он должен быть тут):

```
C:\Program Files (x86)\GnuWin32\bin
```

- [[Добавить в PATH|добавить]] путь к файлу make.exe в переменную Path (вручную, т.к. установщик не умеет этого делать автоматически)
- после добавления пути к программе make в переменную Path перезапустить терминали и проверить

``` bash
make --version
```

# Результат

``` bash
PC C:\users\potylitcyn> make --version
GNU Make 3.81
Copyright (C) 2006  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

This program built for i386-pc-mingw32
PC C:\users\potylitcyn> 
```

Версия может отличаться, для наших задач это не принципиально