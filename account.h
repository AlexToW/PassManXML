#pragma once

#include <string>

class Account {
public:
    Account() = default;
    void SetUserName(const std::string& name); 
    void SetMaterPass(const std::string& pass); 
    Account(const std::string& user_name, const std::string& master_pass);
    std::string GetUserName() const;
    std::string GetMasterPass() const;
private:
    std::string user_name_, master_password_;
};