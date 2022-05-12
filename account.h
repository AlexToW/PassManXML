#pragma once

#include <string>

class Account {
public:
    Account() = default;
    void SetUserName(const std::string& name) {
        user_name_ = name;
    }
    void SetMaterPass(const std::string& pass) {
        master_password_ = pass;
    }
    Account(const std::string& user_name, const std::string& master_pass)
            : user_name_(user_name), master_password_(master_pass) {}
    std::string GetUserName() const {
        return user_name_;
    }
    std::string GetMasterPass() const {
        return master_password_;
    }
private:
    std::string user_name_, master_password_;
};
