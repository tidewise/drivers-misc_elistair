#include <boost/test/unit_test.hpp>
#include <misc_elistair/Dummy.hpp>

using namespace misc_elistair;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    misc_elistair::DummyClass dummy;
    dummy.welcome();
}
