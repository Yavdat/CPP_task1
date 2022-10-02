
/* ========================================================================== */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
/* ========================================================================== */

/* ========================================================================== */
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

/* ========================================================================== */
namespace xml {

/* ========================================================================== */
static const std::string kPorts = "ControlSystem.Ports";
static const std::string kVlans = "ControlSystem.Vlans.defVlans";

/* ========================================================================== */
static const std::string kUp = "Up";
static const std::string kVlan = "vlan";
static const std::string kAutoNegotiationEnabled = "AutoNegotiationEnabled";
static const std::string kAllowedSpeed_10M = "AllowedSpeed_10M";
static const std::string kAllowedSpeed_100M = "AllowedSpeed_100M";
static const std::string kAllowedSpeed_1G = "AllowedSpeed_1G";

/* ========================================================================== */
}  // namespace xml
/* ========================================================================== */


/* ========================================================================== */
namespace xml {

/* ========================================================================== */
class XmlParser {
public:
    XmlParser() = default;
    ~XmlParser() = default;

public:
    bool read_xml_file(const std::string& path);

public:
    std::set<std::string> get_ports();
    std::map<int32_t, std::string> get_vlans(std::set<std::string>& ports);

private:
    boost::property_tree::ptree tree;
};
/* ========================================================================== */
}  // namespace xml
/* ========================================================================== */

using namespace xml;
using namespace boost::property_tree;

/* ========================================================================== */
bool XmlParser::read_xml_file(const std::string &path) {
    try {
        read_xml(path, tree);

    } catch (ptree_error &ex) {
        std::cerr << "Read xml failed! Error: " << ex.what() << std::endl;
        return false;
    }

    return true;
}

/* ========================================================================== */
std::set<std::string> XmlParser::get_ports() {
    std::set<std::string> ports;

    try {
    for (ptree::value_type &val : tree.get_child(kPorts)) {
        std::string ID = val.second.get<std::string>("<xmlattr>.ID");
        ports.insert(ID);

        std::cout << std::endl << "PORT[" << ID << "]:" << std::endl;

        std::cout << kUp << "                    : "
                << val.second.get<std::string>(kUp) << std::endl;

        std::cout << kAutoNegotiationEnabled << ": "
                << val.second.get<std::string>(kAutoNegotiationEnabled)
                << std::endl;

        std::cout << kAllowedSpeed_10M << "      : "
                << val.second.get<std::string>(kAllowedSpeed_10M) << std::endl;

        std::cout << kAllowedSpeed_100M << "     : "
                << val.second.get<std::string>(kAllowedSpeed_100M) << std::endl;

        std::cout << kAllowedSpeed_1G << "       : "
                << val.second.get<std::string>(kAllowedSpeed_1G) << std::endl;
        }
    } catch (boost::property_tree::ptree_error &ex) {
        std::cerr << "Get ports failed! Error: " << ex.what() << std::endl;
    }

  return ports;
}

/* ========================================================================== */
std::map<int32_t, std::string> XmlParser::get_vlans(std::set<std::string> &ports) {
    
    std::map<int32_t, std::string> vlans;

    try {
        for (ptree::value_type &val : tree.get_child(kVlans)) {
            std::string ID = val.second.get<std::string>("<xmlattr>.ID");

            if (ports.find(ID) not_eq ports.end()) {
                int32_t vlan = val.second.get<int32_t>(kVlan);

                std::cout << std::endl << "PORT[" << ID << "]:" << std::endl;
                std::cout << "VLAN: " << vlan << std::endl;

                vlans.insert(std::make_pair(vlan, ID));
            }
        }
    } catch (boost::property_tree::ptree_error &ex) {
    std::cerr << "Get vlans failed! Error: " << ex.what() << std::endl;
    }

    return vlans;
}

/* ========================================================================== */
/*
Задача 1:
	Дан файл конфигурации коммутатора "test_config.xml", нужно его считать и распарсить, 
	из корневого узла <Ports> вывести на в консоль конфигурацию портов, 
	из корневого узда <Vlans> вывести список значений Vlan по умолчания для данных портов (узел <defVlans>).
*/

int main() {
    xml::XmlParser parser;
    parser.read_xml_file("./test_config.xml");

    std::set<std::string> ports = parser.get_ports();
    if (ports.empty()) {
        std::cerr << "Ports is not found!" << std::endl;
        return EXIT_FAILURE;
    }

    std::map<int32_t, std::string> vlans = parser.get_vlans(ports);
    if (vlans.empty()) {
        std::cerr << "Vlans is not found!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
/* ========================================================================== */

/* для установки буста
sudo apt install libboost-all-dev
sudo apt install aptitude
aptitude search boost
*/

/* Ответ 
rb02@RB02MB:~/Develop/CPP/CPPvac1$ ./CPPvac_task1 

PORT[0]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[1]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[2]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[3]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[4]:
Up                    : On
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[5]:
Up                    : On
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[6]:
Up                    : On
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[7]:
Up                    : On
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[8]:
Up                    : On
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[9]:
Up                    : On
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[10]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[11]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[12]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[13]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[14]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[15]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[16]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[17]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[18]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[19]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[20]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[21]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[22]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[23]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[24]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[25]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[26]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[27]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[28]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[29]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[30]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[31]:
Up                    : Off
AutoNegotiationEnabled: Off
AllowedSpeed_10M      : Off
AllowedSpeed_100M     : Off
AllowedSpeed_1G       : Off

PORT[0]:
VLAN: 1

PORT[1]:
VLAN: 1

PORT[2]:
VLAN: 1

PORT[3]:
VLAN: 1

PORT[4]:
VLAN: 1

PORT[5]:
VLAN: 1

PORT[6]:
VLAN: 1

PORT[7]:
VLAN: 1

PORT[8]:
VLAN: 1

PORT[9]:
VLAN: 1

PORT[10]:
VLAN: 1

PORT[11]:
VLAN: 1

PORT[12]:
VLAN: 1

PORT[13]:
VLAN: 1

PORT[14]:
VLAN: 1

PORT[15]:
VLAN: 1

PORT[16]:
VLAN: 1

PORT[17]:
VLAN: 1

PORT[18]:
VLAN: 1

PORT[19]:
VLAN: 1

PORT[20]:
VLAN: 1

PORT[21]:
VLAN: 1

PORT[22]:
VLAN: 1

PORT[23]:
VLAN: 1

PORT[24]:
VLAN: 1

PORT[25]:
VLAN: 1

PORT[26]:
VLAN: 1

PORT[27]:
VLAN: 1

PORT[28]:
VLAN: 1

PORT[29]:
VLAN: 1

PORT[30]:
VLAN: 1

PORT[31]:
VLAN: 1

*/