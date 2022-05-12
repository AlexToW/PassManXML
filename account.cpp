#include "account.h" 
 
Account::Account(const std::string& user_name, const std::string& master_pass)
            : user_name_(user_name), master_password_(master_pass) {}

void Account::SetUserName(const std::string& name) {
        user_name_ = name;
}  

void Account::SetMaterPass(const std::string& pass) {
        master_password_ = pass;
}  

std::string Account::GetUserName() const {
        return user_name_;
} 

std::string Account::GetMasterPass() const {
    return master_password_;
}