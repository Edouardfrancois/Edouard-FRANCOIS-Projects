/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-mayeul.kergall
** File description:
** parc
*/

#include "Json.hpp"
#include "JsExeption.hpp"

void Json::Json::CreateString(std::string *file)
{
    int poscote;

    file->erase(0, 1);
    poscote = file->find_first_of('\"');
    if (poscote == -1)
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char \"");
    this->_Value = file->substr(0, poscote);
    file->erase(0, poscote);
    if (file->at(0) != '\"')
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char \"");
    file->erase(0, 1);
}

void Json::Json::CreateNb(std::string *file)
{
    std::string newNb;
    size_t size_nb = 0;
    bool isdouble = false;
    bool neg = false;

    if (file->at(0) == '-') {
        file->erase(0, 1);
        neg = true;
    }
    for (auto elem : *file) {
        if (elem == '.') {
            if (isdouble)
                throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Elem is not a number");
            isdouble = true;
            ++size_nb;
            continue;
        } else if (elem >= '0' and elem <= '9') {
            ++size_nb;
            continue;
        } else if (elem == ']' or elem == ',' or elem == '}')
            break;
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Elem is not a number");
    }
    newNb = file->substr(0, size_nb);
    if (neg)
        newNb.insert(0, "-");
    file->erase(0, size_nb);
    if (isdouble)
        this->_Value = std::stod(newNb.c_str());
    else
        this->_Value = std::atoi(newNb.c_str());
}

void Json::Json::CreateNull(std::string *file)
{
    this->_Value = nullptr;
    file->erase(0, 4);
}

void Json::Json::CreateTrue(std::string *file)
{
    this->_Value = true;
    file->erase(0, 4);
}

void Json::Json::CreateFalse(std::string *file)
{
    this->_Value = false;
    file->erase(0, 5);
}

void Json::Json::CreateTab(std::string *file)
{
    file->erase(0, 1);
    for(size_t index = 0; 1; ++index) {
        if (file->at(0) == '\"')
            this->operator[](index).CreateString(file);
        else if (file->at(0) == '[')
            this->operator[](index).CreateTab(file);
        else if (file->starts_with("null"))
            this->operator[](index).CreateNull(file);
        else if (file->starts_with("true"))
            this->operator[](index).CreateTrue(file);
        else if (file->starts_with("false"))
            this->operator[](index).CreateFalse(file);
        else if (file->at(0) == ']' and file->at(1) != ',')
            break;
        else if (file->at(0) == ']')
            break;
        else if ((file->at(0) >= '0' && file->at(0) <= '9') or file->at(0) == '-')
            this->operator[](index).CreateNb(file);
        else
            throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Unrecognized element in the table");
        if (file->at(0) != ',')
            break;
        file->erase(0, 1);
    }
    if (file->at(0) != ']')
        throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char ]");
    file->erase(0, 1);
}

void Json::Json::CreateObj(std::string *file)
{
    int poscote;
    std::string name;

    file->erase(0, 1);
    if (file->at(0) == '}')
        return;
    while (1) {
        if (file->at(0) != '\"')
            throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char \"");
        file->erase(0, 1);
        poscote = file->find_first_of('\"');
        if (poscote == -1)
            throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char \"");
        name = file->substr(0, poscote);
        file->erase(0, poscote);
        if (file->at(0) != '\"')
            throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char \"");
        file->erase(0, 1);
        if (file->at(0) != ':')
            throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Mistake a char :");
        file->erase(0, 1);
        if (file->at(0) == '}' and file->at(1) != ',')
            break;
        else if ((file->at(0) >= '0' && file->at(0) <= '9') or file->at(0) == '-')
            this->operator[](name).CreateNb(file);
        else if (file->starts_with("null"))
            this->operator[](name).CreateNull(file);
        else if (file->starts_with("true"))
            this->operator[](name).CreateTrue(file);
        else if (file->starts_with("false"))
            this->operator[](name).CreateFalse(file);
        else
            switch(file->at(0)) {
                case '[':
                    this->operator[](name).CreateTab(file);
                break;
                case '{':
                    this->operator[](name).CreateObj(file);
                break;
                case '\"':
                    this->operator[](name).CreateString(file);
                break;
                default:
                    throw JsonExeption::Exception(JsonExeption::JsTypeError::JS_ERROR_PARSING, "Unrecognized element in the object");
            }
        if (file->at(0) != ',')
            break;
        file->erase(0, 1);
    }
    file->erase(0, 1);
}