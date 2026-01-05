#include "test_game_1_optional_main.hpp"
#include "test_game_1_contents_main.hpp"

int main(void){
    try{
        Test_Game_1_Optional game_optional;
        GL_Sys_Main_Manager game_sys_main(1600, 900, "test_game_1", game_optional);
        Test_Game_1_Main_Loop game_loop;
        game_sys_main.run_gl_loop(game_loop);
    }
    catch(const std::exception& e){
        std::cerr << 
        "An error occurred during the initialization the gl system.\n" << 
        "Force terminate and dump to error log." << 
        std::endl;
        std::ofstream errf("test_game_1_err.log");
        errf << e.what();
        return -2;
    }
    return 0;
}
