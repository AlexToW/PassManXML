#pragma once

#include <string>
/*
* class required for working with accounts
*/
class Account {
public:
    Account() = default;
    Account(const std::string& user_name, const std::string& master_pass);
    void SetUserName(const std::string& name);
    void SetMaterPass(const std::string& pass);
    std::string GetUserName() const;
    std::string GetMasterPass() const;
private:
    std::string user_name_, master_password_;
};