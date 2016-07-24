#include "OSLSound.h"

bool OSLSound::init() {

    // Получаем объект, указав желаемые интерфейсы
    SLresult result = slCreateEngine(&engineObj, numOptions, NULL, numInterfaces, pInterfaceIDs, pInterfaceRequired);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound - Error slCreateEngine");
        return false;
    }

    // Реализовываем объект
    result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
    if(result != SL_RESULT_SUCCESS) {
        LOGE("OSLSound - Error engineObj Realize");
        return false;
    }

    // Получаем необходимые интерфейсы, с помощью которого мы будем иметь доступ к динамикам
    result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound - Error GetInterface");
        return false;
    }

    // slObjectItf – это объект, представляющий устройство вывода звука(динамик, наушники).
    result = (*engine)->CreateOutputMix(engine, &slObjectItf, outputMixIIDCount, outputMixIIDs, outputMixRequired);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound - Error CreateOutputMix");
        return false;
    }

    // Реализовываем объект
    result = (*slObjectItf)->Realize(slObjectItf, SL_BOOLEAN_FALSE);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound - Error slObjectItf Realize");
        return false;
    }

    aAssetManager = AAssetManager_fromJava(env, assetsManager);
    return true;
}

bool OSLSound::create(){
    bool isCreate = true;

    soundPack[SOUND_TYPE::BACKGROUND].resourseDescriptor = loadResourceDescriptor("sound/background.mp3");
    soundPack[SOUND_TYPE::BALL].resourseDescriptor = loadResourceDescriptor("sound/ball.mp3");
    soundPack[SOUND_TYPE::OUT].resourseDescriptor = loadResourceDescriptor("sound/out.mp3");

    for(int i = 0; i < SOUND_TYPE::SIZE; i++)
        if(createAudioPlayer(soundPack[i].soundObj, soundPack[i].soundPlayer, soundPack[i].soundSeek,  soundPack[i].resourseDescriptor) != SL_RESULT_SUCCESS){
            LOGE("OSLSound::createAudioPlayer: %d", i);
            isCreate = false;
        }

    (*soundPack[SOUND_TYPE::BACKGROUND].soundSeek)->SetLoop(soundPack[SOUND_TYPE::BACKGROUND].soundSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    return isCreate;
};

void OSLSound::play(OSLSound::SOUND_TYPE soundType){
    if(isSoundOn){
        SLuint32 isPlaying = NULL;
        (*soundPack[soundType].soundPlayer)->GetPlayState(soundPack[soundType].soundPlayer, &isPlaying);
        if(isPlaying != SL_PLAYSTATE_PLAYING){
            LOGI("OSLSound::play");
            (*soundPack[soundType].soundPlayer)->SetPlayState(soundPack[soundType].soundPlayer, SL_PLAYSTATE_PLAYING);
        }
    }
};

void OSLSound::stop(OSLSound::SOUND_TYPE soundType){
    if(isSoundOn){
        SLuint32 isStop = NULL;
        (*soundPack[soundType].soundPlayer)->GetPlayState(soundPack[soundType].soundPlayer, &isStop);
        if(isStop != SL_PLAYSTATE_STOPPED){
            LOGI("OSLSound::stop");
            (*soundPack[soundType].soundPlayer)->SetPlayState(soundPack[soundType].soundPlayer, SL_PLAYSTATE_STOPPED);
        }
    }
};

void OSLSound::stopAll(){
    for(int i = 0; i < SOUND_TYPE::SIZE; i++)
        (*soundPack[i].soundPlayer)->SetPlayState(soundPack[i].soundPlayer, SL_PLAYSTATE_STOPPED);
};

SLuint32 OSLSound::createAudioPlayer(SLObjectItf& playerObj, SLPlayItf& player, SLSeekItf& seek, ResourseDescriptor resourseDescriptor){
    SLDataLocator_AndroidFD lDataLocatorIn;
    lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    lDataLocatorIn.fd = resourseDescriptor.decriptor;
    lDataLocatorIn.offset = resourseDescriptor.start;
    lDataLocatorIn.length = resourseDescriptor.length;

    SLDataFormat_MIME lDataFormat;
    lDataFormat.formatType = SL_DATAFORMAT_MIME;
    lDataFormat.mimeType = NULL;
    lDataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

    SLDataSource lDataSource;
    lDataSource.pLocator = &lDataLocatorIn;
    lDataSource.pFormat = &lDataFormat;

    SLDataLocator_OutputMix lDataLocatorOut;
    lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    lDataLocatorOut.outputMix = slObjectItf;

    SLDataSink lDataSink;
    lDataSink.pLocator = &lDataLocatorOut;
    lDataSink.pFormat = NULL;

    const SLuint32 lBGMPlayerIIDCount = 2;
    const SLInterfaceID lBGMPlayerIIDs[] = {SL_IID_PLAY, SL_IID_SEEK};
    const SLboolean lBGMPlayerReqs[] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

    SLresult result = (*engine)->CreateAudioPlayer( engine,
                                                    &playerObj,
                                                    &lDataSource,
                                                    &lDataSink,
                                                    lBGMPlayerIIDCount,
                                                    lBGMPlayerIIDs,
                                                    lBGMPlayerReqs);

    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound::createAudioPlayer - can not CreateAudioPlayer %d", result);
        playerObj = NULL;
        return result;
    }

    result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound::createAudioPlayer - can not Realize playerObj");
        playerObj = NULL;
        return result;
    }

    result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound::createAudioPlayer - can not GetInterface player");
        destroy(playerObj);
        player = NULL;
        return result;
    }

    result = (*playerObj)->GetInterface(playerObj, SL_IID_SEEK, &seek);
    if(result != SL_RESULT_SUCCESS){
        LOGE("OSLSound::createAudioPlayer - can not GetInterface seek");
        destroy(playerObj);
        player = NULL;
        return result;
    }

    (*seek)->SetLoop(seek, SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
    (*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);

    return SL_RESULT_SUCCESS;
}

SoundBuffer * OSLSound::loadSoundFile(const char * filename){
    SoundBuffer* result = new SoundBuffer();
    AAsset* asset = AAssetManager_open(aAssetManager, filename, AASSET_MODE_UNKNOWN);
    off_t length = AAsset_getLength(asset);
    result->length = length - sizeof(WAVHeader);
    result->header = new WAVHeader();
    result->buffer = new char[result->length];
    AAsset_read(asset, result->header, sizeof(WAVHeader));
    AAsset_read(asset, result->buffer, result->length);
    AAsset_close(asset);
    return result;
}

ResourseDescriptor OSLSound::loadResourceDescriptor(const char * path){
    AAsset * asset = AAssetManager_open(aAssetManager, path, AASSET_MODE_UNKNOWN);
    ResourseDescriptor resourceDescriptor;
    resourceDescriptor.decriptor = AAsset_openFileDescriptor(asset, &resourceDescriptor.start, &resourceDescriptor.length);
    AAsset_close(asset);
    return resourceDescriptor;
}

void OSLSound::destroy(SLObjectItf & object){
    if(object){
        (*object)->Destroy(object);
        object = NULL;
    }
}

OSLSound::~OSLSound(){
    LOGI("~OSLSound");
    for(int i = 0; i < SOUND_TYPE::SIZE; i++){
        if(soundPack[i].soundPlayer){
            (*soundPack[i].soundPlayer)->SetPlayState(soundPack[i].soundPlayer, SL_PLAYSTATE_STOPPED);
            soundPack[i].soundPlayer = NULL;
            soundPack[i].soundSeek = NULL;
        }

        destroy(soundPack[i].soundObj);
    }

    destroy(slObjectItf);
    destroy(engineObj);
};
