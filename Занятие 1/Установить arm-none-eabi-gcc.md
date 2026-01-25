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
	- запустить установщи, обязательно отметить добавление cmake в Path;
	- после установки проверить ```arm-none-eabi-gcc --version```.

Результат:
![[Pasted image 20260124152216.png]]

Версия может отличаться, для наших задач это не принципиально