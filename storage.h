/*
 * Storage: (хранит все пароли, которые соотв. данному юзеру)
 *      1. Инициализация: проверка существования файлов (их создание)                       [done]
 *      2. Проверка наличия данного аккаунта по логину в authorisation.xml (ExistAccount)   [done]
 *      3. Проверка данного мастер-пароля в authorisation.xml
 *      4. Запись Account в authorisation.xml (проверка уникальности в PassMan)             [done]
 *      5. Парсинг всех паролей соотв. логину -- вызывается в PassMan сразу после того,     [done]
 *              если пользователь успешно авторизовался
 *      6. Поиск паролей по переданному Email (без парсинга)                                [done]
 *      7. Поиск паролей по переданному AppName (без парсинга)                              [done]
 *      8. Добавление нового пароля (принимает PasswordItem)                                [done]
 *          8.0 Проверяет поступивший PasswordItem на уникальность
 *          8.1 Добавляет PasswordItem в контейнер
 *          8.2 Добавляет PasswordItem в файл data.xml
 *      9. Редактирование пароля (EditPasswordItem)                                         [done]
 *          9.0 Проверка существования пароля для редактирования (выполняется в PassMan)
 *          9.1 Заменить необходимые поля в файле
 *          9.3 Заменить пароль в all_passwords_
 *      - шифрование                                                                        [done]
 *      - замена зарезервированных XML символов                                             [done]
 * */


#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <map>
#include <set>
#include <fstream>

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "account.h"
#include "password_item.h"
#include "hash.h"


enum class AUTHORISE_RES {
    SUCCESS,
    INCORRECT,      // неверный пароль
    NOACC           // не зарегистрован
};

enum class FIND_RES {
    SUCCESS,
    NOTFOUND,
    ERROR
};

class Storage {
public:
    Storage();
    bool XSDValidation();
    void Init();
    void ParseAllDataByLogin(const std::string& login);
    bool ExistDataFile();
    bool ExistAuthoFile();
    AUTHORISE_RES ConfirmAuthorisation(Account& account);
    bool RegisterAccount(Account& account);
    bool ExistAccount(const std::string& user_name);
    bool ExistPasswordItem(PasswordItem const& pass_item);
    std::pair<bool, PasswordItem> ExistPasswordItem(std::string& identifier);
    bool AddPasswordItem(PasswordItem& pass_item);
    static std::string PreprocessingToXML(std::string s);
    std::string PreprocessingFromXML(std::string s);
    void EditPasswordItem(std::string& identifier, PasswordItem& new_pass_item);
    boost::property_tree::ptree ChildByPasswordItem(PasswordItem& pass_item);
    std::pair<FIND_RES, std::vector<PasswordItem>> AllPasswords();
    std::pair<FIND_RES, std::vector<PasswordItem>> SelectAllByEmail(const std::string& email); // вызываются из PassMan для соотв. юзера
    std::pair<FIND_RES, std::vector<PasswordItem>> SelectAllByAppName(const std::string& app);
private:
    const std::string default_data_path_ = "data.xml";
    const std::string default_autho_path_ = "authorisation.xml";
    const std::string default_xml_data_ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<password_items></password_items>";
    const std::string default_autho_data_ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "<accounts></accounts>";
    const std::string path_xsd = "scheme.xsd";
    std::string active_login;
    std::vector<PasswordItem> all_passwords_; // all password items by active_login user
};