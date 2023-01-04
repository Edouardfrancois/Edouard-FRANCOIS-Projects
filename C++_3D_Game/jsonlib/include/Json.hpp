/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-mayeul.kergall
** File description:
** Json
*/

#ifndef JSON_HPP_
#define JSON_HPP_

#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <any>

#include "./Exeption/JsExeption.hpp"

namespace Json {
    class Json {
        public:
            Json();
            Json(const std::string& filename);
            ~Json();
            Json &operator[](const std::string &);
            Json &operator[](std::size_t index);
            std::any GetValueAsAny() const;
            std::size_t GetSize() const;

            void Dump(const int fd = 1, const std::size_t indentation = 4, const char end_of_line = '\n', const size_t etat = 0) const;

            void CreateObj(std::string *file);
            void CreateTab(std::string *file);
            void CreateString(std::string *file);
            void CreateNb(std::string *file);
            void CreateNull(std::string *file);
            void CreateTrue(std::string *file);
            void CreateFalse(std::string *file);

            template <typename T>
            Json &operator=(T value) {
                this->_Value = value;
                return *this;
            }

            template <typename T>
            T GetData() {
                if (!this->_Value.has_value())
                    throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_ACESS, "Impossible to get Data in json:");
                return std::any_cast<T>(this->_Value);
            }

        private:
            std::map<std::string, std::unique_ptr<Json>> _Mp;
            std::map<std::size_t, std::unique_ptr<Json>> _Vt;
            std::any _Value;
            std::size_t _Size = 0;
    };
}

std::ostream &operator<<(std::ostream& os, Json::Json &js);

#endif /* !JSON_HPP_ */
