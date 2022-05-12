
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sys/stat.h>
#include <algorithm>

#include "passman.h"

int main() {
    PassMan passman;
    passman.PrintLogo();
    passman.Start();
    return 0;
}
