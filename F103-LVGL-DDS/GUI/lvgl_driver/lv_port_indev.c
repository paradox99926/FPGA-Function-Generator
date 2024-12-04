#if 0

#include "lv_port_indev.h"
#include "touch.h"

// 函数申明
static bool touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);

// lvgl的输入设备初始化
void lv_port_indev_init(void)
{
	lv_indev_drv_t indev_drv;

	// lvgl支持很多种输入设备,但是我们一般常用的就是触摸屏,也就是Touchpad
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = touchpad_read;
	lv_indev_drv_register(&indev_drv);
}

// 将会被lvgl周期性调用,周期值是通过lv_conf.h中的LV_INDEV_DEF_READ_PERIOD宏来定义的
// 此值不要设置的太大,否则会感觉触摸不灵敏,默认值为30ms
static bool touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
	static uint16_t last_x = 0;
	static uint16_t last_y = 0;

	if (tp_dev.sta & TP_PRES_DOWN) // 触摸按下了
	{
		last_x = tp_dev.x[0];
		last_y = tp_dev.y[0];
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_PR;
	}
	else
	{ // 触摸松开了
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_REL;
	}

	// 返回false代表没有缓冲的数据
	return false;
}
#endif

#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "touch.h"
#include "lcd.h"
#include "key.h"
#include "led.h"
/*********************
 *      DEFINES
 *********************/
/************************************************
 * 一、我们在文件"lv_port_indev.c"顶部定义宏定义
 ************************************************/
#define LV_USE_INDEV_TOUCHPAD 0x1u
#define LV_USE_INDEV_MOUSE 0x2u
#define LV_USE_INDEV_KEYPAD 0x4u
#define LV_USE_INDEV_ENCODER 0x8u
#define LV_USE_INDEV_BUTTON 0x10u
#define LV_USE_INDEV LV_USE_INDEV_TOUCHPAD // 使用Touchpad
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
#if (LV_USE_INDEV & LV_USE_INDEV_TOUCHPAD) == LV_USE_INDEV_TOUCHPAD
static void touchpad_init(void);
static bool touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t *x, lv_coord_t *y);
#endif

#if (LV_USE_INDEV & LV_USE_INDEV_MOUSE) == LV_USE_INDEV_MOUSE
static void mouse_init(void);
static bool mouse_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static bool mouse_is_pressed(void);
static void mouse_get_xy(lv_coord_t *x, lv_coord_t *y);
#endif

#if (LV_USE_INDEV & LV_USE_INDEV_KEYPAD) == LV_USE_INDEV_KEYPAD
static void keypad_init(void);
static bool keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static uint32_t keypad_get_key(void);
#endif

#if (LV_USE_INDEV & LV_USE_INDEV_ENCODER) == LV_USE_INDEV_ENCODER
static void encoder_init(void);
static bool encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static void encoder_handler(void);
#endif

#if (LV_USE_INDEV & LV_USE_INDEV_BUTTON) == LV_USE_INDEV_BUTTON
static void button_init(void);
static bool button_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);
#endif
/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t *indev_touchpad;
lv_indev_t *indev_mouse;
lv_indev_t *indev_keypad;
lv_indev_t *indev_encoder;
lv_indev_t *indev_button;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
	/* Here you will find example implementation of input devices supported by LittelvGL:
	 *  - Touchpad
	 *  - Mouse (with cursor support)
	 *  - Keypad (supports GUI usage only with key)
	 *  - Encoder (supports GUI usage only with: left, right, push)
	 *  - Button (external buttons to press points on the screen)
	 *
	 *  The `..._read()` function are only examples.
	 *  You should shape them according to your hardware
	 */

	lv_indev_drv_t indev_drv;

	/*------------------
	 * Touchpad
	 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_TOUCHPAD) == LV_USE_INDEV_TOUCHPAD
	/*Initialize your touchpad if you have*/
	touchpad_init();

	/*Register a touchpad input device*/
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = touchpad_read;
	indev_touchpad = lv_indev_drv_register(&indev_drv);
#endif
	/*------------------
	 * Mouse
	 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_MOUSE) == LV_USE_INDEV_MOUSE
	/*Initialize your touchpad if you have*/
	mouse_init();

	/*Register a mouse input device*/
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = mouse_read;
	indev_mouse = lv_indev_drv_register(&indev_drv);

	/*Set cursor. For simplicity set a HOME symbol now.*/
	lv_obj_t *mouse_cursor = lv_img_create(lv_disp_get_scr_act(NULL), NULL);
	lv_img_set_src(mouse_cursor, LV_SYMBOL_HOME);
	lv_indev_set_cursor(indev_mouse, mouse_cursor);
#endif
	/*------------------
	 * Keypad
	 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_KEYPAD) == LV_USE_INDEV_KEYPAD
	/*Initialize your keypad or keyboard if you have*/
	keypad_init();

	/*Register a keypad input device*/
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_KEYPAD;
	indev_drv.read_cb = keypad_read;
	indev_keypad = lv_indev_drv_register(&indev_drv);

	/* Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
	 * add objects to the group with `lv_group_add_obj(group, obj)`
	 * and assign this input device to group to navigate in it:
	 * `lv_indev_set_group(indev_keypad, group);` */
#endif
	/*------------------
	 * Encoder
	 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_ENCODER) == LV_USE_INDEV_ENCODER
	/*Initialize your encoder if you have*/
	encoder_init();

	/*Register a encoder input device*/
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_ENCODER;
	indev_drv.read_cb = encoder_read;
	indev_encoder = lv_indev_drv_register(&indev_drv);

	/* Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
	 * add objects to the group with `lv_group_add_obj(group, obj)`
	 * and assign this input device to group to navigate in it:
	 * `lv_indev_set_group(indev_encoder, group);` */
#endif
	/*------------------
	 * Button
	 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_BUTTON) == LV_USE_INDEV_BUTTON
	/*Initialize your button if you have*/
	button_init();

	/*Register a button input device*/
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_BUTTON;
	indev_drv.read_cb = button_read;
	indev_button = lv_indev_drv_register(&indev_drv);

	/*Assign buttons to points on the screen*/
	static const lv_point_t btn_points[2] = {
		{10, 10},  /*Button 0 -> x:10; y:10*/
		{40, 100}, /*Button 1 -> x:40; y:100*/
	};
	lv_indev_set_button_points(indev_button, btn_points);
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_TOUCHPAD) == LV_USE_INDEV_TOUCHPAD

/*Initialize your touchpad*/
static void touchpad_init(void)
{
	/*Your code comes here*/
	tp_dev.init(); // 触摸屏初始化
}

/**
 * @brief       图形库的触摸屏读取回调函数
 * @param       indev_drv   : 触摸屏设备
 *   @arg       data        : 输入设备数据结构体
 * @retval      无
 */
static bool touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
	static lv_coord_t last_x = 0;
	static lv_coord_t last_y = 0;

	/*Save the pressed coordinates and the state*/
	if (touchpad_is_pressed())
	{
		touchpad_get_xy(&last_x, &last_y);
		data->state = LV_INDEV_STATE_PR;
	}
	else
	{
		data->state = LV_INDEV_STATE_REL;
	}

	/*Set the last pressed coordinates*/
	data->point.x = last_x;
	data->point.y = last_y;

	/*Return `false` because we are not buffering and no more data to read*/
	return false;
}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
	/*Your code comes here*/
	/* 在这里我们对触摸屏是否被触摸进行判断 */
	/* 例如触摸屏一般有INT引脚，就是中断引脚 */
	/* 我们根据中断引脚是否有信号判断是否被触摸（不过STM32貌似没有电平触发中断，只有边沿触发） */
	/* 边沿触发只能触发一次，容易判断错误，所以我们一般采用轮询读点 */
	/* 我们分别以电容和电阻触摸屏为例 */

	bool res = false;

	/* 电阻屏 */
	res = tp_dev.sta & TP_PRES_DOWN; // 触摸屏被按下
	return res;

	/* 电容屏 */
	/* 电容屏一般可以读status寄存器是否有值来判断是否有点 */
	// uint8_t status = cap_is_touched();
	// if (status)
	// 	return true;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(lv_coord_t *x, lv_coord_t *y)
{
	/*Your code comes here*/
	(*x) = tp_dev.x[0];
	(*y) = tp_dev.y[0];
	// (*x) = 0;
	// (*y) = 0;
}
#endif
/*------------------
 * Mouse
 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_MOUSE) == LV_USE_INDEV_MOUSE
/* Initialize your mouse */
static void mouse_init(void)
{
	/*Your code comes here*/
}

/* Will be called by the library to read the mouse */
static bool mouse_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
	/*Get the current x and y coordinates*/
	mouse_get_xy(&data->point.x, &data->point.y);

	/*Get whether the mouse button is pressed or released*/
	if (mouse_is_pressed())
	{
		data->state = LV_INDEV_STATE_PR;
	}
	else
	{
		data->state = LV_INDEV_STATE_REL;
	}

	/*Return `false` because we are not buffering and no more data to read*/
	return false;
}

/*Return true is the mouse button is pressed*/
static bool mouse_is_pressed(void)
{
	/*Your code comes here*/

	return false;
}

/*Get the x and y coordinates if the mouse is pressed*/
static void mouse_get_xy(lv_coord_t *x, lv_coord_t *y)
{
	/*Your code comes here*/

	(*x) = 0;
	(*y) = 0;
}
#endif
/*------------------
 * Keypad
 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_KEYPAD) == LV_USE_INDEV_KEYPAD
/* Initialize your keypad */
static void keypad_init(void)
{
	/*Your code comes here*/
}

/* Will be called by the library to read the mouse */
static bool keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
	static uint32_t last_key = 0;

	/*Get the current x and y coordinates*/
	mouse_get_xy(&data->point.x, &data->point.y);

	/*Get whether the a key is pressed and save the pressed key*/
	uint32_t act_key = keypad_get_key();
	if (act_key != 0)
	{
		data->state = LV_INDEV_STATE_PR;

		/*Translate the keys to LVGL control characters according to your key definitions*/
		switch (act_key)
		{
		case 1:
			act_key = LV_KEY_NEXT;
			break;
		case 2:
			act_key = LV_KEY_PREV;
			break;
		case 3:
			act_key = LV_KEY_LEFT;
			break;
		case 4:
			act_key = LV_KEY_RIGHT;
			break;
		case 5:
			act_key = LV_KEY_ENTER;
			break;
		}

		last_key = act_key;
	}
	else
	{
		data->state = LV_INDEV_STATE_REL;
	}

	data->key = last_key;

	/*Return `false` because we are not buffering and no more data to read*/
	return false;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
	/*Your code comes here*/

	return 0;
}
#endif
/*------------------
 * Encoder
 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_ENCODER) == LV_USE_INDEV_ENCODER
/* Initialize your keypad */
static void encoder_init(void)
{
	/*Your code comes here*/
}

/* Will be called by the library to read the encoder */
static bool encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{

	data->enc_diff = encoder_diff;
	data->state = encoder_state;

	/*Return `false` because we are not buffering and no more data to read*/
	return false;
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
	/*Your code comes here*/

	encoder_diff += 0;
	encoder_state = LV_INDEV_STATE_REL;
}
#endif
/*------------------
 * Button
 * -----------------*/
#if (LV_USE_INDEV & LV_USE_INDEV_BUTTON) == LV_USE_INDEV_BUTTON
/* Initialize your buttons */
static void button_init(void)
{
	/*Your code comes here*/
}

/* Will be called by the library to read the button */
static bool button_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{

	static uint8_t last_btn = 0;

	/*Get the pressed button's ID*/
	int8_t btn_act = button_get_pressed_id();

	if (btn_act >= 0)
	{
		data->state = LV_INDEV_STATE_PR;
		last_btn = btn_act;
	}
	else
	{
		data->state = LV_INDEV_STATE_REL;
	}

	/*Save the last pressed button's ID*/
	data->btn_id = last_btn;

	/*Return `false` because we are not buffering and no more data to read*/
	return false;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{
	uint8_t i;

	/*Check to buttons see which is being pressed (assume there are 2 buttons)*/
	for (i = 0; i < 2; i++)
	{
		/*Return the pressed button's ID*/
		if (button_is_pressed(i))
		{
			return i;
		}
	}

	/*No button pressed*/
	return -1;
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{

	/*Your code comes here*/

	return false;
}
#endif
#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
