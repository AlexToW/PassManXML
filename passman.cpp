#include "passman.h"

void PassMan::PrintHeader() {
    std::cout << "User name"<< std::setw(WIDTH) << "Password" << std::setw(WIDTH) << "App name" 
            << std::setw(WIDTH) << "URL" << std::setw(WIDTH) << "Email" << std::endl;
}

void PassMan::CopyPassword() {
    std::string identifier;
    std::cout << indent_str <<  "Enter email or app name of password you want to copy: ";
    std::cin >> identifier;

    auto res = storage.ExistPasswordItem(identifier);
    bool exist = res.first;
    if(!exist) {
        std::cout << indent_str << "There are no any passwords with '" << identifier << "'" << std::endl;
        return;
    }
    PasswordItem pass_item = res.second;
    AesEncryption aes("cbc", 256);
    CryptoPP::SecByteBlock enc = aes.decrypt(pass_item.GetPassword(), active_user.GetMasterPass());
    std::string decrypted_password = std::string(enc.begin(), enc.end()); 
    pass_item.SetPassword(decrypted_password); 

    clipboardxx::clipboard clipboard;
    std::string password_ = pass_item.GetPassword();
    clipboard << password_;

    std::cout << indent_str << "The password has been copied to the clipboard." << std::endl;
    std::cout << indent_str << "It will be removed from the clipboard after " << SEC_CLIP << " seconds." << std::endl;
    for(int seconds = SEC_CLIP; seconds >= 0; seconds--) {
        std::cout << indent_str <<  seconds << " seconds left..." << std::endl;
        sleep(1);
    }
    std::cout << indent_str << "The password has been removed from the clipboard." << std::endl;
}

void PassMan::EditPassword() {
    std::string identifier;
    std::cout << indent_str <<  "Enter email or app name of password you want to edit: ";
    std::cin >> identifier;
    // проверка существования такого пароля
    auto res = storage.ExistPasswordItem(identifier);
    bool exist = res.first;
    PasswordItem old_pass_item = res.second;  
 
    AesEncryption aes("cbc", 256);
    CryptoPP::SecByteBlock enc = aes.decrypt(old_pass_item.GetPassword(), active_user.GetMasterPass());
    std::string decrypted_password = std::string(enc.begin(), enc.end()); 
    old_pass_item.SetPassword(decrypted_password); 
 
    PasswordItem new_pass_item = old_pass_item;
    if(!exist) {
        std::cout << indent_str << "There are no any passwords with '" << identifier << "'" << std::endl;
        return;
    }
    std::string answer = "0";
    do {
        std::cout << indent_str << "Enter name of filed you want to edit [password[p]/email[e]/user_name[n]/url[u]/app_name[a]]" << std::endl;
        std::cout << indent_str << "or [s] to stop editing and save changes: ";
        std::cin >> answer;
        if(answer == "p") {
            std::string new_password1, new_password2;
            std::cout << indent_str << "Enter new password: ";
            //std::cin >> new_password;
            new_password1 = GetPasswordSafety();
            std::cout << std::endl;
            std::cout << "Confirm new password: ";
            new_password2 = GetPasswordSafety();
            std::cout << std::endl;
            if(new_password1 == new_password2) {
                new_pass_item.SetPassword(new_password1);
            } else {
                std::cout << "Passwords must match! Try again." << std::endl;
            }
        } else if(answer == "e") {
            std::string new_email;
            std::cout << indent_str << "Enter new email: ";
            std::cin >> new_email;
            new_pass_item.SetEmail(new_email);
        } else if(answer == "n") {
            std::string new_user_name;
            std::cout << indent_str << "Enter new user name: ";
            std::cin >> new_user_name;
            new_pass_item.SetUserName(new_user_name);
        } else if(answer == "u") {
            std::string new_url;
            std::cout << indent_str << "Enter new URl: ";
            std::cin >> new_url;
            new_pass_item.SetUrl(new_url);
        } else if(answer == "a") {
            std::string new_app_name;
            std::cout << indent_str << "Enter new app name: ";
            std::cin >> new_app_name;
            new_pass_item.SetAppName(new_app_name);
        } else {
            std::cout << indent_str << "Choose one of the suggested options!" << std::endl;
        }
    } while (answer != "s");
 
    std::string confirm;
    std::cout << indent_str << "You are about to change this password:" << std::endl;
    std::cout << old_pass_item << std::endl;
    std::cout << indent_str << "to this one:" << std::endl;
    std::cout << new_pass_item << std::endl;
    std::cout << indent_str << "Do you want to save your changes? It will be impossible to undo this operation. [y/n]: ";
    std::cin >> confirm;
    if(confirm == "y") {
        CryptoPP::SecByteBlock enc2 = aes.encrypt(new_pass_item.GetPassword(), active_user.GetMasterPass());
        std::string encrypted_password = std::string(enc2.begin(), enc2.end());
        new_pass_item.SetPassword(encrypted_password);
        storage.EditPasswordItem(identifier, new_pass_item);
        std::cout << indent_str << "All changes have been successfully saved!" << std::endl;
        return;
    }
    std::cout << indent_str << "The changes were not saved." << std::endl;
}
 
 
void PassMan::AllPasswords() {
    auto res = storage.AllPasswords();
    if (res.first == FIND_RES::SUCCESS) {
        PrintHeader();
        AesEncryption aes("cbc", 256);
        for(auto& item : res.second) {
            CryptoPP::SecByteBlock enc = aes.decrypt(item.GetPassword(), active_user.GetMasterPass());
            std::string decrypted_password = std::string(enc.begin(), enc.end());
            item.SetPassword(decrypted_password);
            std::cout << item << std::endl;
        }
    } else if(res.first == FIND_RES::NOTFOUND) {
        std::cout << indent_str << "There are no any passwords!" << std::endl;
    } else if(res.first == FIND_RES::ERROR) {
        std::cout << indent_str << "Error!" << std::endl;
    }
}
 
PassMan::PassMan() {
    storage.Init();
}

void PassMan::FindPassByName() {
    std::string app_name;
    std::cout << indent_str << "Enter app name: ";
    std::cin >> app_name;
    auto res = storage.SelectAllByAppName(app_name);

    if(res.first == FIND_RES::SUCCESS) {
        AesEncryption aes("cbc", 256);
        PrintHeader();
        for(auto& item : res.second) {
            CryptoPP::SecByteBlock enc = aes.decrypt(item.GetPassword(), active_user.GetMasterPass());
            std::string decrypted_password = std::string(enc.begin(), enc.end());
            item.SetPassword(decrypted_password);
            std::cout << item << std::endl;
        }
    } else if(res.first == FIND_RES::NOTFOUND) {
        std::cout << indent_str << "There no any passwords with app name '" << app_name << "'" << std::endl;
    } else if(res.first == FIND_RES::ERROR) {
        std::cout << indent_str << "Find by app name failed!" << std::endl;
    }
}

void PassMan::FindAccountsByEmail() {
    std::string email;
    std::cout << indent_str << "Enter email: ";
    std::cin >> email;
    auto res = storage.SelectAllByEmail(email);
    if(res.first == FIND_RES::SUCCESS) {
        PrintHeader();
        AesEncryption aes("cbc", 256);
        for(auto& item : res.second) {
            CryptoPP::SecByteBlock enc = aes.decrypt(item.GetPassword(), active_user.GetMasterPass());
            std::string decrypted_password = std::string(enc.begin(), enc.end());
            item.SetPassword(decrypted_password);
            std::cout << item << std::endl;
        }
    } else if(res.first == FIND_RES::NOTFOUND) {
        std::cout << indent_str << "There are no any passwords with email '" << email << "'" << std::endl;
    } else if(res.first == FIND_RES::ERROR) {
        std::cout << indent_str << "Find by email failed!" << std::endl;
    }
}

void PassMan::CreatePassword() {
    std::string password1, email, user_name, url, app_name;
    std::cout << indent_str << "Enter user name: ";
    std::cin >> user_name;
    std::cout << indent_str << "Enter email: ";
    std::cin >> email;
    std::cout << indent_str << "Enter app_name: ";
    std::cin >> app_name;
    std::cout << indent_str << "Enter URL: ";
    std::cin >> url;
    std::cout << indent_str << "Enter password: ";
    //std::cin >> password;
    password1 = GetPasswordSafety();
    std::cout << std::endl;
    std::cout << indent_str << "Confirm password: ";
    std::string password2 = GetPasswordSafety();
    std::cout << std::endl;
    if(password1 != password2) {
        std::cout << indent_str << "Passwords must match!" << std::endl;
        return;
    }
    AesEncryption aes("cbc", 256);
    CryptoPP::SecByteBlock enc = aes.encrypt(password1, active_user.GetMasterPass());
    std::string encrypted_password = std::string(enc.begin(), enc.end());
    PasswordItem pass_item(encrypted_password, email, user_name,
                           url, app_name);
    auto added = storage.AddPasswordItem(pass_item);
    if(!added) {
        std::cerr << indent_str << "Create new password failed!" << std::endl;
    } else {
        std::cout << indent_str << "Password successfully saved!" << std::endl;
    }
}

std::string PassMan::GetPasswordSafety() {
    std::string password;
    /* invisible password characters */
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &term);

    std::cin >> password;

    /* return visibility */
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &term);

    return password;
}

AUTHORISE_RES PassMan::Authorisation() {
    std::string login, master_pass_entered;
    std::cout << indent_str << "Enter login: ";
    std::cin >> login;
    std::cout << indent_str << "Enter Master Password: ";

    //std::cin >> master_pass_entered;
    master_pass_entered = GetPasswordSafety();
    std::cout << std::endl;
    Account tmp_acc(login, master_pass_entered);
    auto res = storage.ConfirmAuthorisation(tmp_acc);
    if(res == AUTHORISE_RES::SUCCESS) {
        active_user = tmp_acc;
        storage.ParseAllDataByLogin(login);
    }
    return res;
}

bool PassMan::Registration() {
    std::string login;
    std::cout << indent_str << "Enter user name: ";
    std::cin >> login;
    if(storage.ExistAccount(login)) {
        std::cerr << indent_str << "Account with login '" << login << "' already exists!" << std::endl;
        return false;
    }
    std::string master_password, master_password2;

    std::cout << indent_str << "Enter master password: ";
    //std::cin >> master_password;
    master_password = GetPasswordSafety();
    std::cout << std::endl;
    std::cout << indent_str << "Confirm master password: ";
    //std::cin >> master_password2;
    master_password2 = GetPasswordSafety();
    std::cout << std::endl;

    if(master_password != master_password2) {
        std::cerr << indent_str << "Passwords must match!" << std::endl;
        return false;
    }
    Account new_account;
    new_account.SetUserName(login);
    new_account.SetMaterPass(master_password);
    if(storage.RegisterAccount(new_account)) {
        active_user = new_account;
        return true;
    }
    return false;
}

void PassMan::Start() {
    std::cout << std::string(UNDERLINE_LEN, '_') << "Password Manager" << std::string(UNDERLINE_LEN, '_') << std::endl;
    std::cout << indent_str << "Registration / Authorisation / Exit? [r/a/e]: ";
    std::string command;
    std::cin >> command;
    if(command == "e") {
        exit(0);
    }
    if(command == "r") {
        if(Registration()) {
            std::cout << indent_str << "Registration completed successfully." << std::endl;
            std::cout << indent_str << "Please login using the created account." << std::endl;
            Start();
        } else {
            std::cout << indent_str << "Registration failed!" << std::endl;
            Start();
        }
    } else if(command == "a") {
        auto aut_res = Authorisation();
        if(aut_res == AUTHORISE_RES::SUCCESS) {
            std::cout << indent_str << "You are in!" << std::endl;
            Menu();
        } else if(aut_res == AUTHORISE_RES::INCORRECT) {
            std::cout << indent_str << "Authorisation failed! Incorrect login or master password!" << std::endl;
            Start();
        } else {
            std::cout << indent_str << "There are no any accounts with this login!" << std::endl;
            Start();
        }
    } else {
        std::cout << indent_str << "Choose one of the proposed options!" << std::endl;
        Start();
    }
}

void PassMan::Menu() {
    std::cout << std::string(UNDERLINE_LEN_TOTAL, '_') << std::endl;
    std::cout << std::string(UNDERLINE_LEN, '_') << "Menu" << std::string(UNDERLINE_LEN, '_') << std::endl;
    std::cout << indent_str << "1. Create new password" << std::endl;
    std::cout << indent_str << "2. Find all sites and apps connected to an email" << std::endl;
    std::cout << indent_str << "3. Find a password for a site or app" << std::endl;
    std::cout << indent_str << "4. Print all passwords" << std::endl;
    std::cout << indent_str << "5. Edit existing password" << std::endl;
    std::cout << indent_str << "6. Copy password" << std::endl;
    std::cout << indent_str << "7. Exit" << std::endl;
    std::cout << std::string(20, '_') << std::endl;
    std::cout << ": ";
    std::string answer;
    std::cin >> answer;
    if(answer == "1") {
        CreatePassword();
    } else if(answer == "2") {
        FindAccountsByEmail();
    } else if(answer == "3") {
        FindPassByName();
    } else if(answer == "4") {
        AllPasswords();
    } else if(answer == "5") {
        EditPassword();
    } else if(answer == "6") {
        CopyPassword();
    }
    else if(answer == "7") {
        exit(0);
    } else {
        std::cout << indent_str << "Choose one of the suggested options!" << std::endl;
    }
    Menu();
}

void PassMan::PrintLogo() {
    std::cout << "                                                     \n"
            ",------.                   ,--.   ,--.               \n"
            "|  .--. ',--,--.,---. ,---.|   `.'   |,--,--,--,--,  \n"
            "|  '--' ' ,-.  (  .-'(  .-'|  |'.'|  ' ,-.  |      \\ \n"
            "|  | --'\\ '-'  .-'  `.-'  `|  |   |  \\ '-'  |  ||  | \n"
            "`--'     `--`--`----'`----'`--'   `--'`--`--`--''--' \n"
            "                                                     " << std::endl;
}
