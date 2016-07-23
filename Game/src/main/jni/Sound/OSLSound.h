
#ifndef GAME_PINGPONG_OSLSOUND_H
#define GAME_PINGPONG_OSLSOUND_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <stddef.h>

class OSLSound {

    public:
        OSLSound(){

        }



    private:
        void init();

        SLObjectItf engineObj = NULL;
        const SLInterfaceID pIDs[1] = { SL_IID_ENGINE };
        const SLboolean pIDsRequired[1]  = { SL_BOOLEAN_TRUE };

};


#endif //GAME_PINGPONG_OSLSOUND_H
