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
	- или тут: https://disk.360.yandex.ru/d/AukS_dPNij9O5w
	- запустить установщик, обязательно отметить добавление arm-none-eabi-gcc в Path (установить галочки, как на картинке):
	
![[Pasted image 20260126174512.png]]
	
	- если при установке произошел сбой "Current PATH length too long to modify in installer; set manually if needed", [[Добавить в PATH]] вручную;
	- после установки проверить
	
``` bash
arm-none-eabi-gcc --version
```

Результат:
![[Pasted image 20260124152216.png]]

Версия может отличаться, для наших задач это не принципиально


![[Pasted image 20260126174321.png]]