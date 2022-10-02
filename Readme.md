Задача 1:
	Дан файл конфигурации коммутатора "test_config.xml", нужно его считать и распарсить, 
	из корневого узла <Ports> вывести на в консоль конфигурацию портов, 
	из корневого узда <Vlans> вывести список значений Vlan по умолчания для данных портов (узел <defVlans>).
	

#установка boost для парсинга
sudo apt install libboost-all-dev
sudo apt install aptitude
aptitude search boost
