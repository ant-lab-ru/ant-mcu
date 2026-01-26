- Linux:
	для линукс можно не устанавливать picotool, т.к. он будет собран автоматически для компиляции проекта прошивки. Если picotool все-таки нужен, то исходники и инструкции есть в официальном репозитории raspberry: 
	- https://github.com/raspberrypi/picotool?tab=readme-ov-file;
	- https://github.com/raspberrypi/picotool/blob/master/BUILDING.md#building.

- MacOS. Выполнить в терминале:
``` bash
brew install picotool
picotool version
```

- Windows:
	==picotool, в отличии от других программ, не имеет установщика, мы скачиваем сразу архив с исполняемым файлом и устанавливаем его самостоятельно==
	- скачать архив с исполняемым файлом и вспомогательными данными:  https://github.com/raspberrypi/pico-sdk-tools/releases архив с названием picotool-2.2.0-a4-x64-win.zip;
	- распаковать скаченный архив, запускать exe не нужно;
	- переместить папку в Program Files;
	- добавить путь к picotool.exe в PATH;
	- проверить корректность ручной установки: ```picotool version```.

Результат:
![[Pasted image 20260124152515.png]]

Версия может отличаться, для наших задач это не принципиально