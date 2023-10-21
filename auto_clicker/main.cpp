#include <Windows.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "key_codes.hpp"

int leftKey = 88;
int leftClickDelay = 100;
int leftRandomOffset = 50;
int leftHoldTime = 0;

int rightKey = 4;
int rightClickDelay = 100;
int rightRandomOffset = 50;
int rightHoldTime = 0;

std::string keyCodes{table};
bool terminateThread = false;

void leftClicker(int leftKey, int leftClickDelay, int leftRandomOffset, int leftHoldTime)
{
	int leftAddedOffset = leftClickDelay + leftRandomOffset;
	int leftSubtractedOffset = leftClickDelay - leftRandomOffset;

	if (leftSubtractedOffset < 1)
	{
		leftSubtractedOffset = 1;
	}

	while (!terminateThread)
	{
		if (GetKeyState(leftKey))
		{
			int leftOffset = leftAddedOffset - leftSubtractedOffset;
			int randomNumber = rand() % leftOffset + leftSubtractedOffset;
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(leftHoldTime);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(randomNumber);
		}
	}
}

void rightClicker(int rightKey, int rightClickDelay, int rightRandomOffset, int rightHoldTime)
{
	int rightAddedOffset = rightClickDelay + rightRandomOffset;
	int rightSubtractedOffset = rightClickDelay - rightRandomOffset;

	if (rightSubtractedOffset < 1)
	{
		rightSubtractedOffset = 1;
	}

	while (!terminateThread)
	{
		if (GetKeyState(rightKey))
		{
			int rightOffset = rightAddedOffset - rightSubtractedOffset;
			int randomNumber = rand() % rightOffset + rightSubtractedOffset;
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			Sleep(rightHoldTime);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			Sleep(randomNumber);
		}
	}
}

void loadFile()
{
	std::ifstream file("settings.txt");
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			size_t equal = line.find('=');

			if (equal != std::string::npos)
			{
				std::string key = line.substr(0, equal);
				std::string value = line.substr(equal + 1);

				if (key == "leftKey")
				{
					leftKey = std::stoi(value);
				}
				else if (key == "leftClickDelay")
				{
					leftClickDelay = std::stoi(value);
				}
				else if (key == "leftRandomOffset")
				{
					leftRandomOffset = std::stoi(value);
				}
				else if (key == "leftHoldTime")
				{
					leftHoldTime = std::stoi(value);
				}
				else if (key == "rightKey")
				{
					rightKey = std::stoi(value);
				}
				else if (key == "rightClickDelay")
				{
					rightClickDelay = std::stoi(value);
				}
				else if (key == "rightRandomOffset")
				{
					rightRandomOffset = std::stoi(value);
				}
				else if (key == "rightHoldTime")
				{
					rightHoldTime = std::stoi(value);
				}
			}
		}
		file.close();
	}
	else
	{
		std::cout << "error: unable to open file\n";
	}
}

int main()
{
	loadFile();
	srand(time(0));
	std::string command;
	int value;

	while (true)
	{
		std::thread leftThread(leftClicker, leftKey, leftClickDelay, leftRandomOffset, leftHoldTime);
		std::thread rightThread(rightClicker, rightKey, rightClickDelay, rightRandomOffset, rightHoldTime);

		std::cout << "type 'help' for commands > ";
		std::cin >> command;
		if (command == "leftKey")
		{
			std::cout << "leftKey = ";
			std::cin >> value;
			std::cout << "you have set leftKey = " << value << "\n";
			leftKey = value;
		}
		else if (command == "leftClickDelay")
		{
			std::cout << "leftClickDelay = ";
			std::cin >> value;
			std::cout << "you have set leftClickDelay = " << value << " milliseconds\n";
			leftClickDelay = value;
		}
		else if (command == "leftRandomOffset")
		{
			std::cout << "leftRandomOffset = ";
			std::cin >> value;
			std::cout << "you have set leftRandomOffset = " << value << " milliseconds\n";
			leftRandomOffset = value;
		}
		else if (command == "leftHoldTime")
		{
			std::cout << "leftHoldTime = ";
			std::cin >> value;
			std::cout << "you have set leftHoldTime = " << value << " milliseconds\n";
			leftHoldTime = value;
		}
		else if (command == "rightKey")
		{
			std::cout << "rightKey = ";
			std::cin >> value;
			std::cout << "you have set rightKey = " << value << "\n";
			rightKey = value;
		}
		else if (command == "rightClickDelay")
		{
			std::cout << "rightClickDelay = ";
			std::cin >> value;
			std::cout << "you have set rightClickDelay = " << value << " milliseconds\n";
			rightClickDelay = value;
		}
		else if (command == "rightRandomOffset")
		{
			std::cout << "rightRandomOffset = ";
			std::cin >> value;
			std::cout << "you have set rightRandomOffset = " << value << " milliseconds\n";
			rightRandomOffset = value;
		}
		else if (command == "rightHoldTime")
		{
			std::cout << "rightHoldTime = ";
			std::cin >> value;
			std::cout << "you have set rightHoldTime = " << value << " milliseconds\n";
			rightHoldTime = value;
		}
		else if (command == "list")
		{
			std::cout << keyCodes;
		}
		else if (command == "help")
		{
			std::cout << "'leftKey'           - change keybind for left click\n";
			std::cout << "'leftClickDelay'    - change left click delay in milliseconds\n";
			std::cout << "'leftRandomOffset'  - change the amount of random offset applied to the left click\n";
			std::cout << "'leftHoldTime'      - change how long the left mouse button is pressed and released\n";
			std::cout << "'rightKey'          - change keybind for right click\n";
			std::cout << "'rightClickDelay'   - change right click delay in milliseconds\n";
			std::cout << "'rightRandomOffset' - change the amount of random offset applied to the right click\n";
			std::cout << "'rightHoldTime'     - change how long the right mouse button is pressed and released\n";
			std::cout << "'list'              - list all the key codes and descriptions\n";
			std::cout << "'quit'              - quit the program\n";
		}
		else if (command == "quit")
		{
			terminateThread = true;
			leftThread.join();
			rightThread.join();
			break;
		}
		else
		{
			std::cout << "'" << command << "' is not recognized\n";
		}

		terminateThread = true;
		leftThread.join();
		rightThread.join();
		terminateThread = false;
	}
	return EXIT_SUCCESS;
}
