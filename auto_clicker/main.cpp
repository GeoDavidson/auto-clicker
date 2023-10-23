#include "key_codes.hpp"
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

int leftKey = key_x;
int leftClickDelay = 100;
int leftRandomOffset = 50;
int leftHoldTime = 0;

int rightKey = mouse_middle;
int rightClickDelay = 100;
int rightRandomOffset = 50;
int rightHoldTime = 0;

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

int main()
{
    srand(time(0));

    while (!terminateThread)
    {
        std::thread leftThread(leftClicker, leftKey, leftClickDelay, leftRandomOffset, leftHoldTime);
        std::thread rightThread(rightClicker, rightKey, rightClickDelay, rightRandomOffset, rightHoldTime);

        std::cout << "press enter to exit...";
        std::cin.ignore();

        terminateThread = true;
        leftThread.join();
        rightThread.join();
    }
    return EXIT_SUCCESS;
}
