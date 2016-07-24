
#ifndef GAME_PINGPONG_OSLSOUND_H
#define GAME_PINGPONG_OSLSOUND_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <stddef.h>
#include <android/asset_manager_jni.h>

#include "Common/LogGL.h"

struct WAVHeader {
    char                RIFF[4];
    unsigned long       ChunkSize;
    char                WAVE[4];
    char                fmt[4];
    unsigned long       Subchunk1Size;
    unsigned short      AudioFormat;
    unsigned short      NumOfChan;
    unsigned long       SamplesPerSec;
    unsigned long       bytesPerSec;
    unsigned short      blockAlign;
    unsigned short      bitsPerSample;
    char                Subchunk2ID[4];
    unsigned long       Subchunk2Size;
};

struct SoundBuffer {
    WAVHeader* header;
    char* buffer;
    int length;
};

struct ResourseDescriptor{
    int32_t decriptor;
    off_t start;
    off_t length;
};

class OSLSound {

    public:
        static const enum SOUND_TYPE {  BACKGROUND = 0,
                                        BALL = 1,
                                        OUT = 2,
                                        SIZE = 3 };

        OSLSound(JNIEnv * _env, jobject _assetsManager, bool _isSoundOn) :
                env(_env),
                assetsManager(_assetsManager),
                isSoundOn(_isSoundOn)
        {
            if(init())
                create();
        }

        void setSound(bool _isSoundOn){
            isSoundOn = _isSoundOn;
        }

        void play(SOUND_TYPE soundType);
        void stop(SOUND_TYPE soundType);
        void stopAll();

        ~OSLSound();

    private:
        AAssetManager * aAssetManager;
        JNIEnv * env;
        jobject assetsManager;

        bool init();
        bool create();
        void destroy(SLObjectItf & object);
        bool isSoundOn;

        SLuint32 createAudioPlayer(SLObjectItf& playerObj, SLPlayItf& player, SLSeekItf& seek, ResourseDescriptor resourseDescriptor);
        SoundBuffer * loadSoundFile(const char * filename);
        ResourseDescriptor loadResourceDescriptor(const char* path);

        SLObjectItf engineObj = NULL;
        SLEngineItf engine = NULL;
        SLObjectItf slObjectItf = NULL;

        struct SoundPack {
            ResourseDescriptor resourseDescriptor;
            SLObjectItf soundObj;
            SLPlayItf soundPlayer;
            SLSeekItf soundSeek;
        };

        SoundPack soundPack[SOUND_TYPE::SIZE];

        const SLuint32 numOptions = 0;
        const SLuint32 numInterfaces = 1;
        const SLInterfaceID pInterfaceIDs[1] = { SL_IID_ENGINE };
        const SLboolean pInterfaceRequired[1]  = { SL_BOOLEAN_TRUE };

        const SLuint32 outputMixIIDCount = 0;
        const SLInterfaceID outputMixIIDs[0] = {};
        const SLboolean outputMixRequired[0] = {};
};
#endif //GAME_PINGPONG_OSLSOUND_H
