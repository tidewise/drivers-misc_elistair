#include <iostream>
#include <misc_elistair/Driver.hpp>

using namespace std;
using namespace misc_elistair;

void usage(ostream& out) {
    out << "misc_elistair_ctl URI CMD\n";
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        usage(cerr);
        exit(1);
    }
    Driver driver;
    driver.openURI(argv[1]);

    return 0;
}
