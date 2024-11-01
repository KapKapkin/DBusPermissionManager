# DBusPermissionManager

## Описание проекта

Проект включает два D-Bus сервиса, реализованных на языке C++, и одно клиентское приложение. Эти компоненты взаимодействуют между собой через D-Bus, обеспечивая управление разрешениями и получение системного времени.

### Сервисы

1. ```com.system.permissions```
   - Методы:
     - ```void RequestPermission(int permissionEnumCode)```: Запрашивает разрешение для исполняемого файла и сохраняет информацию в базе данных SQLite.
     - ```bool CheckApplicationHasPermission(String applicationExecPath, int permissionEnumCode)```: Проверяет, имеет ли исполняемый файл заданное разрешение.

2. ```com.system.time```
   - Методы:
     - ```uint64 GetSystemTime()```: Возвращает текущую метку времени, проверяя наличие у клиента разрешения SystemTime.

### Клиентское приложение

Клиентское приложение выполняет следующие действия:
1. Запрашивает текущее время у сервиса com.system.time.
2. При получении ошибки ```UnauthorizedAccess``` запрашивает разрешение ```SystemTime``` у сервиса ```com.system.permissions```.
3. Повторяет запрос времени после получения разрешения.
4. Выводит метку времени в человекочитаемом формате.

## Установка

1. Клонируйте репозиторий:
   ```
   git clone https://github.com/KapKapkin/DBusPermissionManager.git
   cd DBusPermissionManager
   ```
   

2. Соберите проект:
   ```
   mkdir build && cd build
   cmake ..
   make
   ```

3. Запустите сервисы:
   ```
   # В одном терминале запустите сервис com.system.permissions
   ./PermissionsService/DBusPermissionService 

   # В другом терминале запустите сервис com.system.time
   ./TimeService/DBusTimeService 
   ```

4. Запустите клиентское приложение:
   ```
   ./TimeRequester/DBusTimeRequester
   ```

## Примеры использования

### Запрос разрешения

Используйте ```gdbus``` для отправки сообщений на сервис:
```
gdbus call -e -d com.system.permissions -o /com/system/permissions -m com.system.permissions.RequestPermission 0
```

### Проверка разрешения
```
gdbus call -e -d com.system.permissions -o /com/system/permissions -m com.system.permissions.CheckApplicationHasPermission /usr/bin/com.example.example 0
```

### Получение системного времени
```
gdbus call -e -d com.system.time -o /com/system/time -m com.system.time.GetSystemTime
```

## Ошибки

(Почти) все  ошибки обрабатываются и возвращаются в читаемом формате. Убедитесь, что D-Bus сервисы запущены, прежде чем выполнять запросы.
