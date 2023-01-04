/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Music
*/

#include <vector>
#include "MyRaylib.hpp"

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

namespace MyRaylib {
    class MyMusic {
        public:
            MyMusic(char const *file_name);
            ~MyMusic();
            Music SetMusicFromFile(char const *file_name);
            void SetVolume(float volume);
            void Play();
            void Pause();
            void Update();
        protected:
        private:
            Music _music;
    };
}

#endif /* !MUSIC_HPP_ */
