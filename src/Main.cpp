#include <iostream>
#include <misc_elistair/Driver.hpp>

using namespace std;
using namespace misc_elistair;

void usage(ostream& out) {
    out << "misc_elistair_ctl URI CMD\n";
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        usage(cerr);
        exit(1);
    }
    Driver driver;
    driver.openURI(argv[1]);
    driver.setReadTimeout(base::Time::fromSeconds(1));

    string cmd = argv[2];

    if (cmd == "status") {
        driver.sendCommand(POWER_OFF, TORQUE_BUTTON, 0);
        auto status = driver.read();
        cout << status.power << " " << status.temperature << " " << status.cable_speed << " " << status.cable_length << std::endl;
    }

    return 0;
}
