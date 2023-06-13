#include "../implot/implot.h"
#include "../implot/implot_internal.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../data/user.h"


extern bool show_login_window;
extern bool show_profile_data;
extern bool show_stock;
extern bool show_registration;

class window {
protected:
    const char* window_title;
    public:
public:
    void show();
    window(const char* title);
};

class login_window: public window {
public:
    login_window();
    void show();
};

class profile_window: public window {
public:
    profile_window();
    void show();
};

class stock_window: public window {
public:
    stock_window();
    void show();
};

class registration_window: public window {
public:
    registration_window();
    void show();
};