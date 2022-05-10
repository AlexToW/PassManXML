 
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

#include "account.h"
#include "storage.h"

using namespace std;

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
private:
    Storage storage;
    Account active_user;
};

void PassMan::EditPassword() {
    string identifier;
    cout << "Enter email or app name of password you want to edit: ";
    cin >> identifier;
    // проверка существования такого пароля
    auto res = storage.ExistPasswordItem(identifier);
    bool exist = res.first;
    PasswordItem old_pass_item = res.second;
    PasswordItem new_pass_item = old_pass_item;
    if(!exist) {
        cout << "There are no any passwords with '" << identifier << "'" << endl;
        return;
    }
    string answer = "0";
    do {
        cout << "Enter name of filed you want to edit [password[p]/email[e]/user_name[n]/url[u]/app_name[a]]" << endl;
        cout << "or [s] to stop editing and save changes: ";
        cin >> answer;
        if(answer == "p") {
            string new_password;
            cout << "Enter new password: ";
            cin >> new_password;
            new_pass_item.SetPassword(new_password);
        } else if(answer == "e") {
            string new_email;
            cout << "Enter new email: ";
            cin >> new_email;
            new_pass_item.SetEmail(new_email);
        } else if(answer == "n") {
            string new_user_name;
            cout << "Enter new user name: ";
            cin >> new_user_name;
            new_pass_item.SetUserName(new_user_name);
        } else if(answer == "u") {
            string new_url;
            cout << "Enter new URl: ";
            cin >> new_url;
            new_pass_item.SetUrl(new_url);
        } else if(answer == "a") {
            string new_app_name;
            cout << "Enter new app name: ";
            cin >> new_app_name;
            new_pass_item.SetAppName(new_app_name);
        } else {
            cout << "Choose one of the suggested options!" << endl;
        }
    } while (answer != "s");
 
    string confirm;
    cout << "You are about to change this password:" << endl;
    cout << old_pass_item << endl;
    cout << "to this one:" << endl;
    cout << new_pass_item << endl;
    cout << "Do you want to save your changes? It will be impossible to undo this operation. [y/n]: ";
    cin >> confirm;
    if(confirm == "y") {
        storage.EditPasswordItem(identifier, new_pass_item);
        cout << "All changes have been successfully saved!" << endl;
        return;
    }
    cout << "The changes were not saved." << endl;
}
 
 
void PassMan::AllPasswords() {
    auto res = storage.AllPasswords();
    if (res.first == FIND_RES::SUCCESS) {
        for(const auto& item : res.second) {
            cout << item << endl;
        }
    } else if(res.first == FIND_RES::NOTFOUND) {
        cout << "There are no any passwords!" << endl;
    } else if(res.first == FIND_RES::ERROR) {
        cout << "Error!" << endl;
    }
}
 
PassMan::PassMan() {
    storage.Init();
}

void PassMan::FindPassByName() {
    string app_name;
    cout << "Enter app name: ";
    cin >> app_name;
    auto res = storage.SelectAllByAppName(app_name);

    if(res.first == FIND_RES::SUCCESS) {
        for(const auto& item : res.second) {
            cout << item << endl;
        }
    } else if(res.first == FIND_RES::NOTFOUND) {
        cout << "There no any passwords with app name '" << app_name << "'" << endl;
    } else if(res.first == FIND_RES::ERROR) {
        cout << "Find by app name failed!" << endl;
    }
}

void PassMan::FindAccountsByEmail() {
    string email;
    cout << "Enter email: ";
    cin >> email;
    auto res = storage.SelectAllByEmail(email);
    if(res.first == FIND_RES::SUCCESS) {
        for(const auto& item : res.second) {
            cout << item << endl;
        }
    } else if(res.first == FIND_RES::NOTFOUND) {
        cout << "There are no any passwords with email '" << email << "'" << endl;
    } else if(res.first == FIND_RES::ERROR) {
        cout << "Find by email failed!" << endl;
    }
}

void PassMan::CreatePassword() {
    std::string password, email, user_name, url, app_name;
    cout << "Enter user name: ";
    cin >> user_name;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter app_name: ";
    std::cin >> app_name;
    std::cout << "Enter URL: ";
    std::cin >> url;
    std::cout << "Enter password: ";
    std::cin >> password;
    PasswordItem pass_item(password, email, user_name,
                           url, app_name);
    auto added = storage.AddPasswordItem(pass_item);
    if(!added) {
        std::cerr << "Create new password failed!" << std::endl;
    } else {
        std::cout << "Password successfully saved!" << std::endl;
    }
}

AUTHORISE_RES PassMan::Authorisation() {
    std::string login, master_pass_entered;
    std::cout << "Enter login: ";
    std::cin >> login;
    std::cout << "Enter Master Password: ";
    std::cin >> master_pass_entered;
    Account tmp_acc(login, master_pass_entered);
    auto res = storage.ConfirmAuthorisation(tmp_acc);
    if(res == AUTHORISE_RES::SUCCESS) {
        active_user = tmp_acc;
        storage.ParseAllDataByLogin(login);
    }
    return res;
}

bool PassMan::Registration() {
    string login;
    cout << "Enter user name: ";
    cin >> login;
    if(storage.ExistAccount(login)) {
        cerr << "Account with login '" << login << "' already exists!" << endl;
        return false;
    }
    string master_password, master_password2;
    cout << "Enter master password: ";
    cin >> master_password;
    cout << "Confirm master password: ";
    cin >> master_password2;
    if(master_password != master_password2) {
        cerr << "Passwords must match!" << endl;
        return false;
    }
    Account new_account;
    new_account.SetUserName(login);
    new_account.SetMaterPass(master_password);
    if(storage.RegisterAccount(new_account)) {
        active_user = new_account;
        return true;
    }
    return false;
}

void PassMan::Start() {
    cout << "                                                     \n"
            ",------.                   ,--.   ,--.               \n"
            "|  .--. ',--,--.,---. ,---.|   `.'   |,--,--,--,--,  \n"
            "|  '--' ' ,-.  (  .-'(  .-'|  |'.'|  ' ,-.  |      \\ \n"
            "|  | --'\\ '-'  .-'  `.-'  `|  |   |  \\ '-'  |  ||  | \n"
            "`--'     `--`--`----'`----'`--'   `--'`--`--`--''--' \n"
            "                                                     " << "\n";
    std::cout << "_________Password Manager_________" << std::endl;
    std::cout << "Registration / Authorisation / Exit? [r/a/e]: ";
    std::string command;
    std::cin >> command;
    if(command == "e") {
        exit(0);
    }
    if(command == "r") {
        if(Registration()) {
            std::cout << "Registration completed successfully." << std::endl;
            std::cout << "Please login using the created account." << std::endl;
            Start();
        } else {
            std::cout << "Registration failed!" << std::endl;
            Start();
        }
    } else if(command == "a") {
        auto aut_res = Authorisation();
        if(aut_res == AUTHORISE_RES::SUCCESS) {
            std::cout << "You are in!" << std::endl;
            Menu();
        } else if(aut_res == AUTHORISE_RES::INCORRECT) {
            std::cout << "Authorisation failed! Incorrect login or master password!" << std::endl;
            Start();
        } else {
            std::cout << "There are no any accounts with this login!" << std::endl;
            Start();
        }
    } else {
        std::cout << "Choose one of the proposed options!" << std::endl;
        Start();
    }
}

void PassMan::Menu() {
    std::cout << std::string(20, '_') << std::endl;
    std::cout << std::string(8, '_') << "Menu" << std::string(8, '_') << std::endl;
    std::cout << "1. Create new password" << std::endl;
    std::cout << "2. Find all sites and apps connected to an email" << std::endl;
    std::cout << "3. Find a password for a site or app" << std::endl;
    std::cout << "4. Print all passwords" << std::endl;
    std::cout << "5. Edit existing password" << endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << std::string(20, '_') << std::endl;
    std::cout << ": ";
    std::string answer;
    std::cin >> answer;
    if(answer == "1") {
        CreatePassword();
    } else if(answer == "2") {
        FindAccountsByEmail();
    } else if(answer == "3") {
        FindPassByName();
    } else if(answer == "4") {
        AllPasswords();
    } else if(answer == "5") {
        EditPassword();
    }
    else if(answer == "6") {
        exit(0);
    } else {
        std::cout << "Choose one of the suggested options!" << std::endl;
    }
    Menu();
}