#include <windows.h>
#include<stdio.h>
#include<iostream>
int  CalculateFrameRate(int fps)
{
	static int framesPerSecond = 0.0f;       // This will store our fps
	static float lastTime = 0.0f;       // This will hold the time from the last frame
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		;
		std::cout << framesPerSecond << std::endl;
		fps = framesPerSecond;
		//sprintf(strFrameRate, "Current Frames Per Second: %d", int(framesPerSecond));
		//SetWindowText(g_hWnd, strFrameRate);
		framesPerSecond = 0;
		return fps;
	}
	return -1;

}