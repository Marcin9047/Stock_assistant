#include "user.h"

class user_base
{
        std::vector<user> all_users;
    public:
        user_base() = default;
        user log_in(std::string login, std::string password);
        // void log_out();
        friend void operator%(user_base& v1, user &player); 
        friend user operator <<(user_base& v1, std::vector<std::string>& data); 
        friend void operator >>(user_base& v1, user &player);
        std::vector<user> get_users();
        void add(user player);
};