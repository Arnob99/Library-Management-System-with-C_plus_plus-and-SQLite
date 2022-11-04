#include "BOOL.h"

BOOL::BOOL()
{
    admin_exists = 0;
    admin_created = 0;
    admin_logged_in = 0;

    user_logged_in = 0;

    particular_object_found = 0;
    object_is_unique = 0;
}
