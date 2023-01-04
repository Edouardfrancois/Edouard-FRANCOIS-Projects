/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** Manage_Asset
*/

#ifndef MANAGE_ASSET_HPP_
#define MANAGE_ASSET_HPP_

#include <vector> 
#include <optional>

#include "Asset.hpp"

class Manage_Asset {
    public:
        Manage_Asset() {
            
        }

        std::shared_ptr<sf::Texture> addTexture(std::string src, size_t &id)
        {
            std::shared_ptr<sf::Texture> tmp;
            listText.emplace_back(src, tmp);
            id = listText.size() - 1;
            return tmp;
        }

        std::shared_ptr<sf::Image> addImage(std::string src, size_t &id)
        {
            std::shared_ptr<sf::Image> tmp;
            listImage.emplace_back(src, tmp);
            id = listText.size() - 1;
            return tmp;
        }

        Asset<sf::Texture> &getAssetTexture(size_t id) 
        {
            return listText[id];
        }

        Asset<sf::Image> &getAssetImage(size_t id) 
        {
            return listImage[id];
        }

        std::shared_ptr<sf::Texture> loadText(std::string src, size_t &id)
        {
            for (size_t i = 0; i < listText.size(); i++) {
                if (!src.compare(listText.at(i).get_src())) {
                    std::cerr << "MANAGE_ASSET TEX : Found Source in memory : " << src << std::endl;
                    id = i;
                    return listText.at(i).get_ptr();
                }
            }
            std::cerr << "MANAGE_ASSET TEX : Adding to memory : " << src << std::endl;
            return addTexture(src, id);
        }

        std::shared_ptr<sf::Image> loadImg(std::string src, size_t &id)
        {
            for (size_t i = 0; i < listImage.size(); i++) {
                if (!src.compare(listImage.at(i).get_src())) {
                    std::cerr << "MANAGE_ASSET IMG : Found Source in memory : " << src << std::endl;
                    id = i;
                    return listImage.at(i).get_ptr();
                }
            }
            std::cerr << "MANAGE_ASSET IMG : Adding to memory : " << src << std::endl;
            return addImage(src, id);
        }

    protected:
    private:
        std::vector<Asset<sf::Texture>> listText;
        std::vector<Asset<sf::Image>> listImage; 
};



#endif /* !MANAGE_ASSET_HPP_ */
