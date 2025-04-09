#include "speech.hpp"
#include <cstdlib>
#include <string>

void speakGesture(const std::string& gesture_label) {
#if defined(_WIN32)
    std::string command = "PowerShell -Command \"Add-Type –AssemblyName System.Speech; "
                          "$speak = New-Object System.Speech.Synthesis.SpeechSynthesizer; "
                          "$speak.Speak('" + gesture_label + "');\"";
#elif defined(__APPLE__)
    std::string command = "say \"" + gesture_label + "\"";
#else
    std::string command = "espeak \"" + gesture_label + "\"";
#endif
    system(command.c_str());
}
