# Linux

- для линукс можно не устанавливать picotool, т.к. он будет собран автоматически для компиляции проекта прошивки. Если picotool все-таки нужен, то исходники и инструкции есть в официальном репозитории raspberry:
	- https://github.com/raspberrypi/picotool?tab=readme-ov-file;
	- https://github.com/raspberrypi/picotool/blob/master/BUILDING.md#building.

# MacOS

- Выполнить в терминале:

``` bash
brew install picotool
picotool version
```

# Windows

> [!ATTENTION] Обратите внимание!
>
>  picotool, в отличии от других программ, не имеет установщика, мы скачиваем сразу архив с исполняемым файлом и устанавливаем его самостоятельно.

- скачать архив с исполняемым файлом и вспомогательными данными:  https://github.com/raspberrypi/pico-sdk-tools/releases. На странице сначала нужно развернуть список полностью, нажав `Show all 18 assets`, затем найти и скачать архив `picotool-2.2.0-a4-x64-win.zip`;

![[Pasted image 20260126175639.png|400]]
![[Pasted image 20260126175745.png|400]]

- распаковать скаченный архив, запускать exe не нужно;
- переместить папку picotool в Program Files;
- добавить путь к picotool.exe в PATH;
- проверить корректность ручной установки:
	
``` bash
picotool version
```

# Результат

![[Pasted image 20260124152515.png]]

Версия может отличаться, для наших задач это не принципиально