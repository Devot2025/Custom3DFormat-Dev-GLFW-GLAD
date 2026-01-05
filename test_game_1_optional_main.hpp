
#ifndef _TEST_GAME_1_OPTIONAL_MAIN_H_
#define _TEST_GAME_1_OPTIONAL_MAIN_H_
#include <sc_engine_libs.hpp>

class Test_Game_1_Optional final : public Gl_Option_Manager{
    public:
    Test_Game_1_Optional();
    void optional_main() override;
};

#endif /*TEST_GAME_1_OPTIONAL_MAIN*/
