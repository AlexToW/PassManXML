 
/*
 * class PassMan:
 *      1. запускает инициализацию Storage                              [done]
 *      2. регистрация:                                                 [done]
 *          2.1 запрос логина
 *          2.2 проверка, что аккаунта с таким логином нет (Storage)
 *          2.3 запрос мастер-пароля, подтверждение пароля
 *          2.4 Создание объекта Account
 *          2.5 Запрос к Storage на добавление аккаунта
 *      3. авторизация:                                                 [done]
 *          3.1 запрос логина
 *          3.2 проверка, что аккаунтом с таким логином есть (Storage)
 *          3.3 запрос пароля
 *          3.4 проверка пароля (Storage)
 *          3.5 запуск парсинга всех паролей в Storage
 *      4. Добавление пароля:                                           [done]
 *          4.1 получение данных
 *          4.2 запрос к Storage
 *      5. Поиск паролей по Email:                                      [done]
 *          5.1 получение email
 *          5.2 запрос к Storage
 *      6. Поиск паролей по AppName:                                    [done]
 *          6.1 получение AppName
 *          6.2 запрос к Storage
 *      7. Вывести все пароли                                           [done]
 *          7.1 запрос к Storage
 *      8. Редактирование существующего пароля                          [done]
 *          8.1 запрос email/app_name пароля на редактирование
 *          8.2 проверка существования такого пароля (Storage)
 *          8.3 какое поле хотим отредактировать?
 *          8.4 получение значения для нового поля + подтверждение
 *          8.5 запрос на изменение к Storage
 *      9. Удаление пароля                                              [to do]
 * */
#pragma once

#include <string>


//#include "account.h"
#include "storage.h" 
#include "encryption.h"

class PassMan {
public:
    PassMan();
    void Start();
    void Menu();
    bool Registration();
    AUTHORISE_RES Authorisation();
    void CreatePassword();
    void FindAccountsByEmail();
    void FindPassByName();
    void AllPasswords();
    void EditPassword();
    void PrintLogo();
private:
    Storage storage;
    Account active_user;
};

