#include "AudioEffects.hpp"

namespace rat
{
    AudioEffects::AudioEffects()
    {
        initScript();
        LOG_INFO(this, " : Module AudioEffects constructed");
    }

    void AudioEffects::initScript()
    {
        Script& script = getModule<Script>();
		auto module = script.newModule("AudioEffects");

        SCRIPT_SET_MODULE(AudioEffects, getGlobalEffects, cleanGlobalEffects);

        script.initClasses<Effect, Equalizer, Reverb, Echo>();
    }

    bool AudioEffects::globalEffects()
    {
        return (_globalEffects != nullptr);
    }

    Effect& AudioEffects::getGlobalEffects()
    {
        if(!_globalEffects)
             _globalEffects = std::make_unique<Effect>();
        return *(_globalEffects.get());
    }
    
    void AudioEffects::cleanGlobalEffects()
    {
        _globalEffects.reset(nullptr);
    }
}