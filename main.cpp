#include <iostream>
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <vector>
#include <string>
#include <iomanip>
#include <sys/stat.h>

#include "password_item.h"
#include "storage.h"
#include "passman.h"
using namespace std;




int main() {
    PassMan passman;
    passman.Start();
    return 0;
}
