/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** Asset_fun
*/

#include "Asset.hpp"

template<>
Asset<sf::Image>::Asset(const std::string &src, std::shared_ptr<sf::Image> &ptr)
{
    this->_src = std::string(src);
    ptr = std::make_shared<sf::Image>();
    if (ptr->loadFromFile(src))
        this->_cache = ptr;
}

template<>
Asset<sf::Texture>::Asset(const std::string &src, std::shared_ptr<sf::Texture> &ptr)
{
    this->_src = std::string(src);
    ptr = std::make_shared<sf::Texture>();
    if (ptr->loadFromFile(src))
        this->_cache = ptr;
}

// ------------ RELOAD -------------

template<>
std::shared_ptr<sf::Image> Asset<sf::Image>::reload()
{
    sf::Image img;
    if (!img.loadFromFile(_src))
        return std::shared_ptr<sf::Image>(nullptr);
    std::shared_ptr<sf::Image> shared = std::make_shared<sf::Image>(img);
    _cache = shared;
    return _cache.lock();
}

template<>
std::shared_ptr<sf::Texture> Asset<sf::Texture>::reload()
{
    sf::Texture tex;
    if (!tex.loadFromFile(_src))
        return std::shared_ptr<sf::Texture>(nullptr);
    std::shared_ptr<sf::Texture> shared = std::make_shared<sf::Texture>(tex);
    _cache = shared;
    return _cache.lock();
}
