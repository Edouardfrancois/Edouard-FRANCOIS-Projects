/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-mayeul.kergall
** File description:
** Json
*/

#include <fstream>

#include "Json.hpp"

/**
 * @brief Construct a new Json:: Json:: Json object
 * 
 */
Json::Json::Json()
{
}

/**
 * @brief Construct a new Json:: Json:: Json object
 * 
 * @param filename 
 */
Json::Json::Json(const std::string& filename)
{
    std::ifstream indata(filename);
    char c = '\0';
    std::string file;

    if (!indata)
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_FILE, filename + ": Error when try open it");
    while (!indata.eof()) {
        // printf("%c", c);
        indata >> c;
        file += c;
    }
    // printf("\n");
    file.pop_back();
    if (file[0] == '{')
        CreateObj(&file);
    else if (file[0] == '[')
        CreateTab(&file);
    else if (file.empty())
        throw JsonExeption::JsonEmpty();
    else
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_FILE, filename + ": Error when try Load it");
}

/**
 * @brief Destroy the Json:: Json:: Json object
 * 
 */
Json::Json::~Json()
{
}

Json::Json& Json::Json::operator[](const std::string &str)
{
    if (this->_Vt.size() != 0)
        this->_Vt.clear();
    else if (!this->_Value.has_value())
        this->_Value.reset();
    if (this->_Mp.count(str) == 0) {
        this->_Mp.insert({str, std::make_unique<Json>()});
        ++this->_Size;
    }
    return *this->_Mp.find(str)->second.get();
}

Json::Json &Json::Json::operator[](std::size_t index)
{
    if (this->_Mp.size() != 0)
        this->_Mp.clear();
    else if (!this->_Value.has_value())
        this->_Value.reset();
    if (this->_Vt.count(index) == 0) {
        this->_Vt.insert({index, std::make_unique<Json>()});
        ++this->_Size;
    }
    return *this->_Vt.find(index)->second.get();
}

std::any Json::Json::GetValueAsAny() const
{
    return this->_Value;
}

std::size_t Json::Json::GetSize() const
{
    return this->_Size;
}

std::ostream &operator<<(std::ostream& os, Json::Json &js)
{
    std::any a = js.GetValueAsAny();

    if (!a.has_value())
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_ACESS, "Rong acces in json object");
    else if (a.type() == typeid(int))
        os << std::any_cast<int>(a);
    else if (a.type() == typeid(double))
        os << std::any_cast<double>(a);
    else if (a.type() == typeid(std::string))
        os << std::any_cast<std::string>(a);
    else if (a.type() == typeid(bool))
        os << std::any_cast<bool>(a);
    return os;
}
