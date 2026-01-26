- Linux. Выполнить в терминале:
``` bash
sudo apt update
sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
arm-none-eabi-gcc --version
```

- MacOS. Выполнить в терминале:
``` bash
brew install gcc-arm-embedded
arm-none-eabi-gcc --version
```

- Windows:
	- скачать установщик: https://developer.arm.com/downloads/-/gnu-rm;
	- запустить установщик, обязательно отметить добавление arm-none-eabi-gcc в Path;
	- если при установке произошел сбой "Current PATH length too long to modify in installer; set manually if needed", [[Добавить в Path]] вручную;
	- после установки проверить ```arm-none-eabi-gcc --version```.

Результат:
![[Pasted image 20260124152216.png]]

Версия может отличаться, для наших задач это не принципиально