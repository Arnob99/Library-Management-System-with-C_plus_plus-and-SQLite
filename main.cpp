#include "main.h"

int main()
{
    splash_screen();

    check_admin_exists();
    if(!flag.admin_exists)
        first_time();
    if(!flag.admin_created){
        goodbye_screen();
        return 0;
    }
    else
        state = STATE::SIGN_IN;

    while(state != STATE::GOODBYE){
        if(state == STATE::SIGN_IN){
            sign_in_page();
        }
        else if(state == STATE::MAIN_MENU){
            show_home();
        }
    }

    goodbye_screen();
    return 0;
}
