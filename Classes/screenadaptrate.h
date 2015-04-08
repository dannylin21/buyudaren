
#ifndef SCREENADAPTRATE_H
#define SCREENADAPTRATE_H

class ScreenAdaptRate
{
public:
	static const int WIN_UI_WIDTH;
	static const int WIN_UI_HIGHT;

	static const double MAX_WIN_UI_INCH;
	static const double MAX_RATE;
	static const double MIN_WINUIW_DEVICEW_RATE;

	// 传入创建的游戏窗口的英寸和分辨率
	// 一般来说，游戏窗口都是创建全屏，所以只需要传入设备的英寸和分辨率即可
	static double RateCalc(double frame_inch, int frame_width, int frame_hight);

	// 如果不是整个设备全屏创建游戏窗口，则先调用下该函数，传入设备尺寸、分辨率，和游戏窗口分辨率，返回游戏窗口英寸用以传入RateCalc函数的第一个参数
	static double FrameInchCalc(double device_inch, int device_width, int device_hight, int frame_width, int frame_hight);
};




#endif



