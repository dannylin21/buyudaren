
#include <math.h>
#include "screenadaptrate.h"


// 我们的UI美术按这个尺寸来做
const int ScreenAdaptRate::WIN_UI_WIDTH = 960;
const int ScreenAdaptRate::WIN_UI_HIGHT = 640;

// 一般来说，我们直接伸缩UI尺寸，直到刚好满足屏幕

// 但我们希望经过伸缩之后，UI显示面积不超过一定范围[以UI宽度英寸数不超过该值来控制]
const double ScreenAdaptRate::MAX_WIN_UI_INCH = 7.2749996f;	// 以 ipad 2 里面960像素的宽度原始英寸大小作为参考

// 最大伸缩比例不超过该值，我们希望在高分辨率的时候能尽量利用高分辨率的优势，显示更大的场景
const double ScreenAdaptRate::MAX_RATE = 1.5f;

// 对于高分辨率但设备英寸实在太小的，我们还是希望UI宽度不要低于设备宽度的0.9
const double ScreenAdaptRate::MIN_WINUIW_DEVICEW_RATE = 0.9f;

double ScreenAdaptRate::RateCalc(double frame_inch, int frame_width, int frame_hight)
{
	double monitor_w_div_h = (double)frame_width / (double)frame_hight;
	double monitor_inch_h = frame_inch / sqrtf(1.0f + monitor_w_div_h * monitor_w_div_h);
	double monitor_inch_w = monitor_inch_h * monitor_w_div_h;

	double game_scale = (double)frame_width / (double)WIN_UI_WIDTH;
	if (WIN_UI_HIGHT * game_scale > frame_hight)
	{
		game_scale = (double)frame_hight / (double)WIN_UI_HIGHT;
	}

	int win_ui_width_after_scale = int(WIN_UI_WIDTH * game_scale);									//获取经过缩放后的屏幕宽度
	double win_ui_inch_w_after_scale = monitor_inch_w * win_ui_width_after_scale / frame_width;		//获取经过缩放后的屏幕英寸数

	// 处理大英寸屏幕
	if (win_ui_inch_w_after_scale > MAX_WIN_UI_INCH)
	{
		game_scale = frame_width * MAX_WIN_UI_INCH / (monitor_inch_w * WIN_UI_WIDTH);
	}

	// 处理超大像素屏幕
	if (game_scale > MAX_RATE)
	{
		game_scale = MAX_RATE;
	}

	// 处理超大像素屏幕, 但英寸实在很小的
	win_ui_width_after_scale = int(WIN_UI_WIDTH * game_scale);
	int win_ui_hight_after_scale = int(WIN_UI_HIGHT * game_scale);
	if (double(win_ui_width_after_scale) / double(frame_width) < MIN_WINUIW_DEVICEW_RATE && win_ui_hight_after_scale < frame_hight - 1/* 并且此时高度不满屏 */)
	{
		win_ui_width_after_scale = int(double(frame_width) * MIN_WINUIW_DEVICEW_RATE);

		game_scale = double(win_ui_width_after_scale) / double(WIN_UI_WIDTH);

		if (frame_hight/game_scale < WIN_UI_HIGHT)
		{
			game_scale = (double)frame_hight/(double)WIN_UI_HIGHT;	//如果缩放之后高度比640还要小 则使用640的缩放比
		}
	}

    if (fabs(game_scale-1.0f) < 0.0001f)
    {
        game_scale = 1.0;
    }

	return game_scale;
}


double ScreenAdaptRate::FrameInchCalc(double g_device_inch, int g_device_width, int g_device_hight, int frame_width, int frame_hight)
{
	double w_div_h = (double)g_device_width / (double)g_device_hight;
	double device_inch_h = g_device_inch / sqrtf(1.0f + w_div_h * w_div_h);
	double device_inch_w = device_inch_h * w_div_h;

	double frame_inch_h = (double)frame_hight * device_inch_h / (double)g_device_hight;
	double frame_inch_w = (double)frame_width * device_inch_w / (double)g_device_width;

	double frame_inch = sqrtf(frame_inch_w * frame_inch_w + frame_inch_h * frame_inch_h);

	return frame_inch;
}
