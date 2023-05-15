#include "Audio.h"

#include "core/Context.h"

namespace LUS {
void Audio::Init() {
    SetAudioBackend(DetermineAudioBackendFromConfig());
    switch (GetAudioBackend()) {
#ifdef _WIN32
        case AudioBackend::WASAPI:
            mAudioPlayer = std::make_shared<WasapiAudioPlayer>();
            break;
#endif
#if defined(__linux)
        case AudioBackend::PULSE:
            mAudioPlayer = std::make_shared<PulseAudioPlayer>();
            break;
#endif
        default:
            mAudioPlayer = std::make_shared<SDLAudioPlayer>();
    }

    if (mAudioPlayer) {
        if (!mAudioPlayer->Init()) {
            // Failed to initialize system audio player.
            // Fallback to SDL if the native system player does not work.
            SetAudioBackend(AudioBackend::SDL);
            mAudioPlayer = std::make_shared<SDLAudioPlayer>();
            mAudioPlayer->Init();
        }
    }
}

std::shared_ptr<AudioPlayer> Audio::GetAudioPlayer() {
    return mAudioPlayer;
}

AudioBackend Audio::GetAudioBackend() {
    return mAudioBackend;
}

void Audio::SetAudioBackend(AudioBackend backend) {
    std::string audioBackendName = DetermineAudioBackendNameFromBackend(backend);
    Context::GetInstance()->GetConfig()->setString("Window.AudioBackend", audioBackendName);
    mAudioBackend = backend;
}

AudioBackend Audio::DetermineAudioBackendFromConfig() {
    std::string backendName = Context::GetInstance()->GetConfig()->getString("Window.AudioBackend");
    if (backendName == "wasapi") {
        return AudioBackend::WASAPI;
    } else if (backendName == "pulse") {
        return AudioBackend::PULSE;
    } else if (backendName == "sdl") {
        return AudioBackend::SDL;
    } else {
#ifdef _WIN32
        return AudioBackend::WASAPI;
#elif defined(__linux)
        return AudioBackend::PULSE;
#else
        return AudioBackend::SDL;
#endif
    }
}

std::string Audio::DetermineAudioBackendNameFromBackend(AudioBackend backend) {
    switch (backend) {
        case AudioBackend::WASAPI:
            return "wasapi";
        case AudioBackend::PULSE:
            return "pulse";
        case AudioBackend::SDL:
            return "sdl";
        default:
            return "";
    }
}

} // namespace LUS