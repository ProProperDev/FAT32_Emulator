# FAT32_Emulator
# Задание
Написать программу эмуляции fat32 диска и базовые msdos команды.

Программа принимает как параметр где находиться файл, если файл не существует то он создается с размером 20Мб.
Программа выдает console с path внутри файловой системы.

Следующие команды поддерживаются
1) если файл не формате fat32 то выдается ошибка : Unknown disk format , на любые команды
2) format - переформатировать диск ,вся информация стирается
3) ls - показывает файлу и директории в данной директории или корне диска
4) cd <path> -переходит на опрделенный path на диске ( дается только aбсолютный path) , если такого path не существует дается ошибка
5) mkdir <name> - создает каталог в данном каталоге
6) touch <name> - создает файл в данном каталоге  \
Пример:  \
./f32disk /local/test.disk  \
/> ls  \
Unknown disk format \
/>format  \
Ok  \
/>ls  \
. ..  \
/>mkdir ttt  \
Ok  \
/>ls  \
. .. ttt  \
/>cd /ttt  \
/ttt>ls  \
. ..  \
.ttt>cd /  \
/>
# Запуск и вывод программы
1. Клонируем репозиторий себе на компьютер  \
`$ git clone https://github.com/ProProperDev/FAT32_Emulator`
2. Переходим в директорию с проектом и собираем проект  \
`$ cd FAT32_Emulator`  \
`$ make`
3. Запускаем программу, но перед этим проверим смонтированные устройства  \
`$ lsblk`  \
`$ sudo ./fat32emulator test.disk`
![Screenshot](https://github.com/ProProperDev/FAT32_Emulator/blob/main/Screenshots/Run.png)
4. Тестируем программу  \
![Screenshot](https://github.com/ProProperDev/FAT32_Emulator/blob/main/Screenshots/Work1.png)
![Screenshot](https://github.com/ProProperDev/FAT32_Emulator/blob/main/Screenshots/work2.png)
5. При запущенной программе проверяем смонтированные устройства в отдельном терминале  \
`$ lsblk`
![Screenshot](https://github.com/ProProperDev/FAT32_Emulator/blob/main/Screenshots/mount_devices.png)
6. Завершаем работу эмулятора и проверим смонтированные устройства после завершения работы эмулятора  \
`fat32disk:/>exit`  \
`$ lsblk`
![Screenshot](https://github.com/ProProperDev/FAT32_Emulator/blob/main/Screenshots/mount_devices2.png)

