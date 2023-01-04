/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** SoundManager.hpp
*/

#ifndef SOUND_MANAGER_HPP_
#define SOUND_MANAGER_HPP_

#include <iostream>

#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>

#include <map>
#include <optional>

namespace mySound {

    enum mySoundType {
        Fire,
        Connexion_Friend,
        Connexion_Lobby,
        Death,
        // add more Sound Type
    };

    //static std::vector<std::string> myType_string {
    //    "Fire",
    //    "Connection_Friend",
    //    "Connection_Lobby",
    //    "Death",
    //};

    static std::vector<std::string> mySources {
        "assets/sounds_effects/tire.ogg",
        "assets/sounds_effects/connexion_ami.ogg",
        "assets/sounds_effects/connexion_lobbymp3.ogg",
        "assets/sounds_effects/mort.ogg",
        // add More Sources
    };

    class SoundManager
    {
    private:
        /* data */
        //sf::SoundBuffer::
        std::map<int, sf::SoundBuffer> _mySounds;
        sf::Sound _SFX;
        float _vol_SFX;
    
        sf::Music _bg_music;
        float _vol_Music;
    public:
        SoundManager() {
        
        }
    
        ~SoundManager() {
        
        }
    
        bool initSFX() {
            try{
                for (int i = 0; i < mySources.size(); i += 1) {
                    sf::SoundBuffer tmp;
                    if (tmp.loadFromFile(mySources.at(i))) {
                        this->_mySounds.insert(std::pair<int, sf::SoundBuffer>(i, tmp));
                    } else {
                        this->_mySounds.emplace(i, sf::SoundBuffer());
                        std::cerr << "SOUND_MANAGER : FAILED TO LOAD ->" << mySources.at(i) << std::endl;
                    }
                }
                return true;
            } catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
                return false;
            }
        }
    
        /**
         * @brief pause the music then
         * tries to load a new Music
         * 
         * @param src 
         * @return true if successfully loaded
         * @return false 
         */
        bool load_Music(std::string src)
        {
            this->_bg_music.pause();
            if (!this->_bg_music.openFromFile(src)) {
                return false;
            }
            return true;
        }
    
        /**
         * @brief Set the Music should loop or not
         * 
         * @param isLooping 
         */
        void set_MusicLoop(bool isLooping) {
            this->_bg_music.setLoop(isLooping);
        }
    
        /**
         * @brief play Music
         * 
         */
        void play_Music() {
            this->_bg_music.play();
        }
    
        /**
         * @brief pause Music
         * 
         */
        void pause_Music() {
            this->_bg_music.pause();
        }
    
        /**
         * @brief Set the Music Volume
         * 
         * @param vol between 0 - 100
         */
        void set_MusicVolume(float vol)
        {
            this->_bg_music.setVolume(vol);
        }
    
        bool playSound(const mySoundType &selected) {
            sf::Time empty;
            if (this->_mySounds[selected].getDuration() > empty.Zero) {
                this->_SFX.setBuffer(this->_mySounds[selected]);
                if (this->_SFX.getStatus() != sf::Sound::Playing) {
                    this->_SFX.setVolume(this->_vol_SFX);
                    this->_SFX.play();
                }
                return true;
            }
            return false;
        }
    
        /**
         * @brief Set if the SFX should loop or not
         * 
         * @param islooping 
         */
        void set_SFXloop(bool islooping)
        {
            this->_SFX.setLoop(islooping);
        }
    
        /**
         * @brief Set the SFX Volume
         * 
         * @param vol between 0 - 100
         */
        void set_SFXVolume(float vol)
        {
            this->_vol_SFX = vol;
        }
    };

}

#endif