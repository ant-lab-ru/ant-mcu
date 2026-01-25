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
	- Скачать установщик: https://developer.arm.com/downloads/-/gnu-rm
	- Запустить установщи, обязательно отметить добавление cmake в Path
	- В процессе установки возможно появление следующего сообщения:
	
	![[Path.png]]
		
	- В этом случае нужно добавить Path вручную аналогично [[Установить make]]
	- После установки проверить ```arm-none-eabi-gcc --version```

Результат:
![[Pasted image 20260124152216.png]]

Версия может отличаться, для наших задач это не принципиально