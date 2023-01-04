/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** Asset
*/

#ifndef ASSET_HPP_
#define ASSET_HPP_

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

template<class T>
class Asset {
    public:
        /**
         * @brief Construct a new Asset object can only take sf::Image Sf::Texture
         * 
         * @param src 
         * @param to_fill 
         */
        Asset(const std::string &src, std::shared_ptr<T> &to_fill);

        Asset() {};

        std::shared_ptr<T> get_ptr() {
            if (_cache.expired()) {
                return reload(); 
            }
            return _cache.lock();
        }
        bool is_cached() const {
            return !_cache.expired();
        }

        const std::string &get_src() const
        {
            return this->_src;
        }
    protected:
    private:

        /**
         * @brief reload a compatible asset,
         * if the asset isn't supported, not found or failed to load
         * returns NULL
         * 
         * @return std::shared_ptr<T> 
         */
        std::shared_ptr<T> reload();

        std::string _src;
        std::weak_ptr<T> _cache;
};

#endif /* !ASSET_HPP_ */
