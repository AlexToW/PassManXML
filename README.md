# PassManXML
An application designed to securely store all your passwords in one place. Powered by XML.

 ## Usage
```bash
$ git clone https://github.com/AlexToW/PassManXML
$ sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils
$ sudo apt-get install libboost-all-dev
$ cd PassManXML
$ make
$ ./passman
```

## Functionality
- Support for multiple users
- Creating a new password
- Selecting passwords by email or app name
- Option to display all passwords
- Editing an existing password
- Copy password to clipboard

## To-do
- [ ] Validation XML-files by schemes
- [x] Make characters invisible when entering a password
- [ ] Removing a password