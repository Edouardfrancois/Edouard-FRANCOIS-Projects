/*
** EPITECH PROJECT, 2022
** lib
** File description:
** Exeption
*/

#ifndef JsEXEPTION_HPP_
#define JsEXEPTION_HPP_

#include <string>
#include <iostream>

namespace JsonExeption {
    enum class JsTypeError {
        /**
         * @brief Mauvais fichier
         * 
         */
        /**
         * @brief Error de parsing
         * 
         */
        JS_ERROR_PARSING,
        /**
         * @brief Error d'acces
         * 
         */
        JS_ERROR_ACESS,
        /**
         * @brief Error pour load le file
         * 
         */
        JS_ERROR_FILE,
        /**
         * @brief Le json est vide
         * 
         */
        JS_ERROR_EMPTY,
    };
        /**
         * @brief Class Execution pour le json
         * 
         */
    class Exception : public std::exception {
        public:
            Exception(JsTypeError type): _type(type), _message("") {};
            Exception(JsTypeError type, std::string const &message): _type(type), _message(message) {
                if (message.empty())
                    return;
                std::cerr << message;
            };

            char const *what() const throw() override
            {
                return _message.c_str();
            }

            JsTypeError const &getType() const
            {
                return _type;
            }
        private:
        /**
         * @brief Le type d'erreur
         * 
         */
        JsTypeError _type;

        /**
         * @brief Le message a afficher
         * 
         */
        std::string _message;
    };
    class JsonEmpty : public Exception {
        public:
            JsonEmpty() : Exception(JsTypeError::JS_ERROR_EMPTY) {}
    };
}

#endif /* !JsEXEPTION_HPP_ */
