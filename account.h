#pragma once

#include <string>

using namespace std;

class Account {
public:
    Account() = default;
    void SetUserName(const string& name) {
        user_name_ = name;
    }
    void SetMaterPass(const string& pass) {
        master_password_ = pass;
    }
    Account(const string& user_name, const string& master_pass)
            : user_name_(user_name), master_password_(master_pass) {}
    string GetUserName() const {
        return user_name_;
    }
    string GetMasterPass() const {
        return master_password_;
    }
private:
    string user_name_, master_password_;
};
