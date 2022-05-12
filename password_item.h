#pragma once

#include <string>
#include <iostream>
#include <iomanip>

#define WIDTH 25

class PasswordItem {
public:
    PasswordItem() = default;
    PasswordItem(const std::string& password, const std::string& email, const std::string& user_name,
                 const std::string& url, const std::string& app_name)
            : password_(password), email_(email),
              user_name_(user_name), url_(url), app_name_(app_name) {}
    std::string GetPassword() const {return password_;}
    std::string GetEmail() const { return email_; }
    std::string GetUserName() const {return user_name_;}
    std::string GetUrl() const {return url_;}
    std::string GetAppName() const {return app_name_;}
    void SetPassword(std::string& password) {
        password_ = password;
    }
    void SetEmail(std::string& email) {
        email_ = email;
    }
    void SetUserName(std::string& user_name) {
        user_name_ = user_name;
    }
    void SetUrl(std::string& url) {
        url_ = url;
    }
    void SetAppName(std::string& app_name) {
        app_name_ = app_name;
    }
private:
    std::string password_, email_, user_name_, url_, app_name_;
};

bool operator==(const PasswordItem& lhs, const PasswordItem& rhs) {
    return lhs.GetUserName() == rhs.GetUserName() &&
            lhs.GetAppName() == rhs.GetAppName() &&
            lhs.GetEmail() == rhs.GetEmail() &&
            lhs.GetUrl() == rhs.GetUrl() &&
            lhs.GetPassword() == rhs.GetPassword();
}

std::ostream& operator<<(std::ostream& os, const PasswordItem& item) {
    return os << item.GetUserName() << std::setw(WIDTH) << item.GetPassword()
              << std::setw(WIDTH) << item.GetAppName() << std::setw(WIDTH) << item.GetUrl() << std::setw(WIDTH)
              << item.GetEmail();
}

