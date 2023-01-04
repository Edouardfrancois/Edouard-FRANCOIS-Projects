/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** exeptio
*/

#ifndef EXEPTIO_HPP_
#define EXEPTIO_HPP_

#include <exception>
#include <string>

namespace Exception {
    class Exception : public std::exception {
            public:
                Exception(): _message() {};
                Exception(std::string const& message): _message(message) {};

                char const *what() const throw() override
                {
                    return _message.c_str();
                }
            private:
                /**
                 * @brief Le message a afficher
                 * 
                 */
                std::string _message;
    };

    #define DEFF_EXEPTION_MSG(name) \
    class name : public Exception { \
        public: \
            name(std::string const &message) : Exception(message) {} \
    }

    #define DEFF_EXEPTION(name) \
    class name : public Exception { \
        public: \
            name() : Exception() {} \
    }

    DEFF_EXEPTION(TryPushBackWhenHaveWall);
    DEFF_EXEPTION(ImposibleToPutObj);
    DEFF_EXEPTION(CanOnlyMouveObjEntity);
    DEFF_EXEPTION(ObjectNotInPile);
    DEFF_EXEPTION_MSG(ImpossibleMouve);

    /**
     * @brief IA
     * 
     */
    DEFF_EXEPTION(ImposibleToSetThatObjectif);
    DEFF_EXEPTION(ImpossibleToMouve);

    /**
     * @brief Json
     * 
     */
    DEFF_EXEPTION_MSG(MapSizeZero);

    /**
     * @brief Generate Map
     * 
     */
    DEFF_EXEPTION(RongIndexForGenerateMap);
    DEFF_EXEPTION(ToMushSpawn);
    DEFF_EXEPTION(RemouveOneEntity);

    /**
     * @brief Inventory
     * 
     */
    DEFF_EXEPTION(ImPossibleToGiveEntityInsideEntity);
}

#endif /* !EXEPTIO_HPP_ */
