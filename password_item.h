#pragma once

#include <string>
#include <iostream>
#include <iomanip>

#define WIDTH 25

class PasswordItem {
public:
    PasswordItem() = default;
    PasswordItem(std::string const& password, std::string const& email, std::string const& user_name,
                std::string const& url, std::string const& app_name);
    std::string GetPassword() const;
    std::string GetEmail() const;
    std::string GetUserName() const;
    std::string GetUrl() const;
    std::string GetAppName() const;
    void SetPassword(std::string& password);
    void SetEmail(std::string& email);
    void SetUserName(std::string& user_name);
    void SetUrl(std::string& url);
    void SetAppName(std::string& app_name);
private:
    std::string password_, email_, user_name_, url_, app_name_;
};
