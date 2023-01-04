/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Music
*/

#include "Music.hpp"

MyRaylib::MyMusic::MyMusic(char const *file_name)
{
    _music = LoadMusicStream(file_name);
    // SetVolume(0);
}

MyRaylib::MyMusic::~MyMusic()
{
    PauseMusicStream(_music);
    UnloadMusicStream(_music);
}

Music MyRaylib::MyMusic::SetMusicFromFile(char const *file_name)
{
    return LoadMusicStream(file_name);
}

void MyRaylib::MyMusic::SetVolume(float volume)
{
    SetMusicVolume(_music, volume);
}

void MyRaylib::MyMusic::Play()
{
    PlayMusicStream(_music);
}

void MyRaylib::MyMusic::Pause()
{
    PauseMusicStream(_music);
}

void MyRaylib::MyMusic::Update()
{
    UpdateMusicStream(_music);
}