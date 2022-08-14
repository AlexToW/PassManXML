#include "password_item.h"

PasswordItem::PasswordItem(const std::string& password, const std::string& email, const std::string& user_name,
                 const std::string& url, const std::string& app_name)
            : password_(password), email_(email),
              user_name_(user_name), url_(url), app_name_(app_name) {}

std::string PasswordItem::GetPassword() const   {return password_;}
std::string PasswordItem::GetEmail() const      {return email_; }
std::string PasswordItem::GetUserName() const   {return user_name_;}
std::string PasswordItem::GetUrl() const        {return url_;}
std::string PasswordItem::GetAppName() const    {return app_name_;}

void PasswordItem::SetPassword(std::string& password) { password_ = password; }

void PasswordItem::SetEmail(std::string& email) { PasswordItem::email_ = email; }

void PasswordItem::SetUserName(std::string& user_name) { user_name_ = user_name; }

void PasswordItem::SetUrl(std::string& url) { url_ = url; }

void PasswordItem::SetAppName(std::string& app_name) { app_name_ = app_name; }  

bool operator==(PasswordItem const& lhs, PasswordItem const& rhs) {
    return lhs.GetUserName() == rhs.GetUserName() &&
            lhs.GetAppName() == rhs.GetAppName() &&
            lhs.GetEmail() == rhs.GetEmail() &&
            lhs.GetUrl() == rhs.GetUrl() &&
            lhs.GetPassword() == rhs.GetPassword();
}


std::ostream& operator<<(std::ostream& os, const PasswordItem& item) {
    std::string u_n = item.GetUserName();
    os << u_n << std::string(abs(width - u_n.length()), ' ');
    size_t pass_len = item.GetPassword().length();
    os << std::string(pass_len, '*') << std::string(abs(width - pass_len), ' ');
    std::string app = item.GetAppName();
    os << app << std::string(abs(width - app.length()), ' ');
    std::string url = item.GetUrl();
    os << url << std::string(abs(width - url.length()), ' ');
    std::string email = item.GetEmail();
    os << email;
    return os;
}
