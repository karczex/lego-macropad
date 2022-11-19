#include <iostream>
#include <string>
#include <cstring>

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>

struct device {

	device(std::string path="/dev/uinput") {
		fd = open(path.c_str(), O_WRONLY | O_NONBLOCK);
		if (fd < 0){
			throw std::runtime_error("Canot open file" + path);
		}

		ioctl(fd, UI_SET_EVBIT, EV_KEY);
		ioctl(fd, UI_SET_KEYBIT, KEY_VOLUMEDOWN);
		ioctl(fd, UI_SET_KEYBIT, KEY_VOLUMEUP);

		usetup.id.bustype = BUS_USB;
		usetup.id.vendor = 0xDEAD; /* sample vendor */
		usetup.id.product = 0xBEEF; /* sample product */
		std::strcpy(usetup.name, "Virtual Macropad");

		if(ioctl(fd, UI_DEV_SETUP, &usetup) != 0){
			throw std::runtime_error("Cannot setup device");
		}
		if( ioctl(fd, UI_DEV_CREATE) != 0){
			throw std::runtime_error("Cannot create device");
		}

	}

	void volume_up(){
		type(KEY_VOLUMEUP);
	}

	void volume_down(){
		type(KEY_VOLUMEDOWN);
	}

	~device(){
		ioctl(fd, UI_DEV_DESTROY);
		close(fd);
	}
private:

	void type(int key) {
		emit(fd, EV_KEY, key, 1);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_KEY, key, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
	}

	void emit(int fd, int type, int code, int val) {
	   struct input_event ie;

	   ie.type = type;
	   ie.code = code;
	   ie.value = val;
	   /* timestamp values below are ignored */
	   ie.time.tv_sec = 0;
	   ie.time.tv_usec = 0;

	   write(fd, &ie, sizeof(ie));
	}

	int fd;
	uinput_setup usetup = {};
};

int main(int argc, char *argv[]) {

	try{
		auto dev = device();
		sleep(1);
		std::string input;
		while(std::cin >> input) {
			if(input == "VOLUME_UP") {
				dev.volume_up();
			} else if (input == "VOLUME_DOWN") {
				dev.volume_down();
			}
		}
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
