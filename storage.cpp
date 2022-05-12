#include "storage.h"


std::pair<bool, PasswordItem> Storage::ExistPasswordItem(std::string& identifier) {
    std::pair<bool, PasswordItem> res = {false, PasswordItem{}};
    auto it = find_if(begin(all_passwords_), end(all_passwords_), [identifier](PasswordItem& item) {
        return item.GetEmail() == identifier || item.GetAppName() == identifier;
    });
    if(it != end(all_passwords_)) {
        res.first = true;
        res.second = *it;
    }
    return res;
}

void Storage::EditPasswordItem(std::string& identifier, PasswordItem& new_pass_item) { // identifier == app_name or email
    // замена в файле
    ptree pt;
    read_xml(default_data_path_, pt);
    BOOST_FOREACH(ptree::value_type& password_item, pt.get_child("password_items")) {
        std::string tmp_email = PreprocessingFromXML(password_item.second.get_child("email").get_value("default"));
        std::string tmp_app_name = PreprocessingFromXML(password_item.second.get_child("app_name").get_value("default"));
        if(tmp_email == identifier || tmp_app_name == identifier) {
            password_item.second.get_child("password").put_value(PreprocessingToXML(new_pass_item.GetPassword()));
            password_item.second.get_child("email").put_value(PreprocessingToXML(new_pass_item.GetEmail()));
            password_item.second.get_child("user_name").put_value(PreprocessingToXML(new_pass_item.GetUserName()));
            password_item.second.get_child("url").put_value(PreprocessingToXML(new_pass_item.GetUrl()));
            password_item.second.get_child("app_name").put_value(PreprocessingToXML(new_pass_item.GetAppName()));
        }
        //password_item.second.get_child("password").put_value("XXX");
    }
    write_xml(default_data_path_, pt);
 
    // замена в all_passwords_
    auto it = find_if(begin(all_passwords_), end(all_passwords_), [identifier](PasswordItem& item) {
        return item.GetEmail() == identifier || item.GetAppName() == identifier;
    });
    if(it != end(all_passwords_)) {
        *it = new_pass_item;
    }
}

std::pair<FIND_RES, std::vector<PasswordItem>> Storage::AllPasswords() {
    if (all_passwords_.empty()){
        return std::make_pair(FIND_RES::NOTFOUND, std::vector<PasswordItem> {});
    } return make_pair(FIND_RES::SUCCESS, all_passwords_);
}

std::string Storage::PreprocessingToXML(std::string s) {
    std::string res = "";
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] == '<') res += "&lt;";
        else if (s[i] == '>') res += "&gt;";
        else if (s[i] == '&') res += "&amp;";
        else if (s[i] == '\"') res += "&quot;";
        else if (s[i] == '\'') res += "&apos;";
        else res += s[i];
    }
    return res;
}

std::string Storage::PreprocessingFromXML(std::string s) {
    std::string res = "";
    for (size_t i = 0; i < s.length(); i++){
        if (s[i] == '&'){
            if (s[i+1] == 'l') {
                res += '<';
                i += 3;
            } else if (s[i+1] == 'g') {
                res += '>';
                i += 3;
            } else if (s[i+1] == 'q') {
                res += '\"';
                i += 5;
            } else if (s[i+1] == 'a' && s[i+2] == 'm') {
                res += '&';
                i += 4;
            } else if (s[i+1] == 'a' && s[i+2] == 'p') {
                res += '\'';
                i += 5;
            }
        } else {
            res += s[i];
        }
    }
    return res;
}

void Storage::Init() {
    if (!ExistDataFile()) {
        std::ofstream data(default_data_path_);
        if (data.is_open()) {}
        data << default_xml_data_ << std::endl;
    }
    if (!ExistAuthoFile()) {
        std::ofstream author(default_autho_path_);
        if (author.is_open()) {
            author << default_autho_data_ << std::endl;
        }
    }
}

std::pair<FIND_RES, std::vector<PasswordItem>> Storage::SelectAllByAppName(const std::string& app) {
    std::vector<PasswordItem> res_v = {};
    for(const auto& item : all_passwords_) {
        if(item.GetAppName() == app) {
            res_v.push_back(item);
        }
    }
    std::pair<FIND_RES, std::vector<PasswordItem>> result;
    if(res_v.empty()) {
        result.first = FIND_RES::NOTFOUND;
    } else {
        result.first = FIND_RES::SUCCESS;
    }
    result.second = res_v;
    return result;
}

std::pair<FIND_RES, std::vector<PasswordItem>> Storage::SelectAllByEmail(const std::string& email) {
    std::vector<PasswordItem> res_v = {};
    for(const auto& item : all_passwords_) {
        if(item.GetEmail() == email) {
            res_v.push_back(item);
        }
    }
    std::pair<FIND_RES, std::vector<PasswordItem>> result;
    if(res_v.empty()) {
        result.first = FIND_RES::NOTFOUND;
    } else {
        result.first = FIND_RES::SUCCESS;
    }
    result.second = res_v;
    return result;
}

void Storage::ParseAllDataByLogin(const std::string& login) {
    ptree pt;
    read_xml(default_data_path_, pt);
    BOOST_FOREACH(ptree::value_type& password_item, pt.get_child("password_items")) {
        std::string tmp_login = PreprocessingFromXML(password_item.second.get_child("login").get_value("default"));
        if(tmp_login == login) {
            std::string user_name = PreprocessingFromXML(password_item.second.get_child("user_name").get_value("default"));
            std::string password = PreprocessingFromXML(password_item.second.get_child("password").get_value("default"));
            std::string email = PreprocessingFromXML(password_item.second.get_child("email").get_value("default"));
            std::string url = PreprocessingFromXML(password_item.second.get_child("url").get_value("default"));
            std::string app_name = PreprocessingFromXML(password_item.second.get_child("app_name").get_value("default"));
            PasswordItem item(password, email, user_name, url, app_name);
            all_passwords_.push_back(item);
        }
    }
    active_login = login;
}

Storage::Storage() = default;

bool Storage::ExistDataFile() {
    struct stat buffer{};
    return stat(default_data_path_.c_str(), &buffer) != -1;
}

bool Storage::ExistAuthoFile() {
    struct stat buffer{};
    return stat(default_autho_path_.c_str(), &buffer) != -1;
}

AUTHORISE_RES Storage::ConfirmAuthorisation(Account &account) {
    // парсим xml с аакаунтами
    ptree pt;
    bool exist = false;
    read_xml(default_autho_path_, pt);
    BOOST_FOREACH(ptree::value_type & acc, pt.get_child("accounts")) {
        std::string tmp_user_name = PreprocessingFromXML(acc.second.get_child("user_name").get_value("default"));
        std::string tmp_master_pass = PreprocessingFromXML(acc.second.get_child("master_password").get_value("default"));
        if(account.GetUserName() == tmp_user_name) {
            exist = true;
            if(account.GetMasterPass() == tmp_master_pass) {
                return AUTHORISE_RES::SUCCESS;
            }
        }
    }
    return exist ? AUTHORISE_RES::INCORRECT : AUTHORISE_RES::NOACC;
}

bool Storage::ExistAccount(const std::string& user_name) {
    ptree pt;
    read_xml(default_autho_path_, pt);
    BOOST_FOREACH(ptree::value_type & acc, pt.get_child("accounts")) {
        std::string tmp_user_name = PreprocessingFromXML(acc.second.get_child("user_name").get_value("default"));
        if(user_name == tmp_user_name) {
            return true;
        }
    }
    return false;
}

bool Storage::RegisterAccount(Account& acc) {
    if(ExistAccount(acc.GetUserName())) {
        return false;
    }
    ptree pt;
    read_xml(default_autho_path_, pt);

    ptree child;
    child.add("user_name", PreprocessingToXML(acc.GetUserName()));
    child.add("master_password", PreprocessingToXML(acc.GetMasterPass()));
    pt.add_child("accounts.account", child);

    write_xml(default_autho_path_, pt);
    return true;
}

bool Storage::ExistPasswordItem(PasswordItem& pass_item) {
    //const PasswordItem const_pass_item = pass_item;
    return find(all_passwords_.begin(), all_passwords_.end(), pass_item) != all_passwords_.end();
}

boost::property_tree::ptree Storage::ChildByPasswordItem(PasswordItem& pass_item) {
    ptree child;
    child.add("login", PreprocessingToXML(active_login));
    child.add("password", PreprocessingToXML(pass_item.GetPassword()));
    child.add("email", PreprocessingToXML(pass_item.GetEmail()));
    child.add("user_name", PreprocessingToXML(pass_item.GetEmail()));
    child.add("url", PreprocessingToXML(pass_item.GetUrl()));
    child.add("app_name", PreprocessingToXML(pass_item.GetAppName()));
    return child;
}

bool Storage::AddPasswordItem(PasswordItem& pass_item) {
    if(ExistPasswordItem(pass_item)) {
        return false;
    }
    ptree pt;
    read_xml(default_data_path_, pt);

    ptree child = ChildByPasswordItem(pass_item);
    pt.add_child("password_items.password_item", child);
    write_xml(default_data_path_, pt);
    all_passwords_.push_back(pass_item);
    return true;
}
