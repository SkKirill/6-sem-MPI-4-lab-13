### Скоморохов Кирилл | 8 (900) 988-75-37 | Т-Банк | tg = @sk_kiriII  | vk = sk_kirill | VisualStudio2022 | C++

> **Стоимость - 800₽**

# Задача 13

> Создать описатель типа и использовать его при передаче данных в качестве шаблона для следующего преобразования

> обратная буква к.

# Установка

1. [Установить Microsoft MPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)  
2. Скачиваем оба файла(`msmpisetup.exe`, `msmpisdk.msi`) и устанавливаем ОБА ФАЙЛА!  
3. Находим кнопку `Проект`(`Project`) на верхней палитре и переходим в `Свойства`(`Properties`)  
4. Переходим во вкладку `C/C++` и в ней нажимаем на `Дополнительные каталоги включемых файлов`(`Aditional Include Directories`)
в данное поле указываем путь да скаченного MPI `C:\Program Files (x86)\Microsoft SDKs\MPI\Include` 
5. Переходим в `Компоновщик`(`Linker`) -> `Общие`(`General`) -> `Дополнительные каталоги библиотек`(`Aditional library Directories`)
и в указаное поле устанавливаем `C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64`  
6. Переходим в `Компоновщик`(`Linker`) -> `Ввод`(`Input`) -> `Дополнительные зависимости`(`Aditional Dependencies`) и вписываем в них `msmpi.lib`  
7. После выполненых действий нажимаем `Применить`(`Apply`)

> [!TIP]
> Если трудно понять что нужно сделать то можно перейти по этой ссылке и посмотреть видео на ютубе по установке  
Видео тут - [тыкаем](https://www.youtube.com/watch?v=PPEu5KyTx3c)  

# Запуск

Запустить MPI легко.

1. Нужно сбилдить проект `Сборка`(`Build`) -> `Собрать решение`(`Build Solution`)
2. Используем команду на клавиатуре `Win+R` -> пишем `cmd` или `PowerShell` и переходим в командную строку
3. После нужно перейти командой `cd` в нужную папку с исполняемым файлом проекта скорее всего он в папке `x64\Debug`
```PowerShell
cd "D:\VSU-Labs-git\6-sem\PP-RVS-MPI\4-lab\15\LabMPI\x64\Debug"
```
4. И с помощью команды   
```PowerShell
mpiexec -n 4 "LabMPI.exe"
```

# Пример работы программы 
```PowerShell

```

# Установка VisualStudio2022 и C++

- [Переходим по ссылке  и скачиваем себе Visual Studio 2022](https://visualstudio.microsoft.com/ru/vs/)
- Заходим в Visual Studio Installer и в модификацию IDE добавляем ***Desktop development with C++***
- Скачиваем около 9 гигов и все С++ установлен!
