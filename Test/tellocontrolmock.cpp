#include "tellocontrolmock.hpp"

char* TelloControlMock::genericCommand(const char* message)
{
	std::cout << "generic command..." << message << std::endl;
	char result[] = { 'o', 'k', '\0' };
	return result;
}

cv::Mat TelloControlMock::getVideoFrame()
{
	streamon();
	std::cout << "get Stream Data..." << std::endl;
}

bool TelloControlMock::isStreamOn()
{
	return false;
}

bool TelloControlMock::saveScreenshotJpeg(std::string filename)
{
	return false;
}

int TelloControlMock::batteryLevel()
{
	return 50;
}

int TelloControlMock::speed()
{
	return 50;
}

int TelloControlMock::time()
{
	std::cout << "time..." << std::endl;
	return 0;
}

int TelloControlMock::wifi()
{
	std::cout << "wi-fi..." << std::endl;
	return 0;
}

bool TelloControlMock::isLanded()
{
	return false;
}

bool TelloControlMock::takeoff()
{
	std::cout << "taking off..." << std::endl;
	return true;
}

bool TelloControlMock::land()
{
	std::cout << "land..." << std::endl;
	return false;
}

bool TelloControlMock::streamon()
{
	std::cout << "stream on..." << std::endl;
	return false;
}

bool TelloControlMock::streamoff()
{
	std::cout << "stream off..." << std::endl;
	return false;
}

bool TelloControlMock::emergency()
{
	std::cout << "emergency..." << std::endl;
	return false;
}

bool TelloControlMock::up(int x)
{
	std::cout << "up..." << std::endl;
	return false;
}

bool TelloControlMock::down(int x)
{
	std::cout << "down..." << std::endl;
	return false;
}

bool TelloControlMock::left(int x)
{
	std::cout << "left..." << std::endl;
	return false;
}

bool TelloControlMock::right(int x)
{
	std::cout << "right..." << std::endl;
	return false;
}

bool TelloControlMock::forward(int x)
{
	std::cout << "forward..." << std::endl;
	return false;
}

bool TelloControlMock::back(int x)
{
	std::cout << "back..." << std::endl;
	return false;
}

bool TelloControlMock::cw(int x)
{
	std::cout << "cw..." << std::endl;
	return false;
}

bool TelloControlMock::ccw(int x)
{
	std::cout << "ccw..." << std::endl;
	return false;
}

bool TelloControlMock::flip(std::string x)
{
	std::cout << "flip..." << std::endl;
	return false;
}

bool TelloControlMock::goXYZSpeed(int x, int y, int z, int speed)
{
	std::cout << "go xyz speed..." << std::endl;
	return false;
}

bool TelloControlMock::stop()
{
	std::cout << "stop..." << std::endl;
	return false;
}
