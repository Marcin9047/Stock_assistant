#include "user.h"

class user_base
{
        
        std::string name;
    public:
        user_base(std::string name1);
        std::vector<user*> all_users;
        // void log_out();
        friend void operator%(user_base& v1, user* player); 
        friend user* operator <<(user_base& v1, std::vector<std::string>& data); 
        friend void operator >>(user_base& v1, user* player);
        std::vector<user*> get_users();
        void add(user* player);

        void writeJsonToFile();
        void LoadFromJson();
};
