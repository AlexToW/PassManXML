#pragma once

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#define WIDTH 25

class PasswordItem {
public:
    PasswordItem() = default;
    PasswordItem(const string& password, const string& email, const string& user_name,
                 const string& url, const string& app_name)
            : password_(password), email_(email),
              user_name_(user_name), url_(url), app_name_(app_name) {}
    string GetPassword() const {return password_;}
    string GetEmail() const { return email_; }
    string GetUserName() const {return user_name_;}
    string GetUrl() const {return url_;}
    string GetAppName() const {return app_name_;}
    void SetPassword(string& password) {
        password_ = password;
    }
    void SetEmail(string& email) {
        email_ = email;
    }
    void SetUserName(string& user_name) {
        user_name_ = user_name;
    }
    void SetUrl(string& url) {
        url_ = url;
    }
    void SetAppName(string& app_name) {
        app_name_ = app_name;
    }
private:
    string password_, email_, user_name_, url_, app_name_;
};

bool operator==(const PasswordItem& lhs, const PasswordItem& rhs) {
    return lhs.GetUserName() == rhs.GetUserName() &&
            lhs.GetAppName() == rhs.GetAppName() &&
            lhs.GetEmail() == rhs.GetEmail() &&
            lhs.GetUrl() == rhs.GetUrl() &&
            lhs.GetPassword() == rhs.GetPassword();
}

ostream& operator<<(ostream& os, const PasswordItem& item) {
    return os << item.GetUserName() << setw(WIDTH) << item.GetPassword()
              << setw(WIDTH) << item.GetAppName() << setw(WIDTH) << item.GetUrl() << setw(WIDTH)
              << item.GetEmail();
}


