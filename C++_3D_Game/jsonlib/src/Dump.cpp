/*
** EPITECH PROJECT, 2022
** jsonlib
** File description:
** Write
*/

#include "Json.hpp"

void Json::Json::Dump(const int fd, const std::size_t indentation, const char end_of_line, const size_t etat) const
{
    if (!this->_Mp.empty()) {
        if (end_of_line == '\0')
            dprintf(fd, "{");
        else
            dprintf(fd, "{%c", end_of_line);
        for (std::map<std::string, std::unique_ptr<Json>>::const_iterator it = this->_Mp.begin();;) {
            for (size_t i = 0; i != indentation * (etat + 1); ++i)
                dprintf(fd, " ");
            dprintf(fd, "\"%s\": ", it->first.c_str());
            it->second.get()->Dump(fd, indentation, end_of_line, etat + 1);
            if (++it == this->_Mp.end()) {
                if (end_of_line != '\0')
                    dprintf(fd, "%c", end_of_line);
                break;
            }
            if (end_of_line != '\0')
                dprintf(fd,",%c", end_of_line);
            else
                dprintf(fd, ",");
        }
        for (size_t i = 0; i != indentation * etat; ++i)
            dprintf(fd, " ");
        dprintf(fd,"}");
        return;
    } else if (!this->_Vt.empty()) {
        if (end_of_line != '\0')
            dprintf(fd, "[%c", end_of_line);
        else
            dprintf(fd, "[");
        for (std::map<std::size_t, std::unique_ptr<Json>>::const_iterator it = this->_Vt.begin();;) {
            for (size_t i = 0; i != indentation * (etat + 1); ++i)
                dprintf(fd, " ");
            it->second.get()->Dump(fd, indentation, end_of_line, etat + 1);
            if (++it == this->_Vt.end()) {
                if (end_of_line != '\0')
                    dprintf(fd, "%c", end_of_line);
                break;
            }
            if (end_of_line != '\0')
                dprintf(fd,",%c", end_of_line);
            else
                dprintf(fd, ",");
        }
        for (size_t i = 0; i != indentation * etat; ++i)
            dprintf(fd, " ");
        dprintf(fd,"]");
        return;
    } else if (this->_Value.type() == typeid(int))
        dprintf(fd, "%d", std::any_cast<int>(this->_Value));
    else if (this->_Value.type() == typeid(double)) {
        std::string Nb = std::to_string(std::any_cast<double>(this->_Value));
        while (1) {
            if (Nb.at(Nb.length() - 1) == '0' and Nb.at(Nb.length() - 2) == '.')
                break;
            if (Nb.at(Nb.length() - 1) == '0')
                Nb.pop_back();
            else
                break;
        }
        dprintf(fd, "%s", Nb.c_str());
    } else if (this->_Value.type() == typeid(std::string))
        dprintf(fd, "\"%s\"", std::any_cast<std::string>(this->_Value).c_str());
    else if (this->_Value.type() == typeid(bool)) {
        bool Value = std::any_cast<bool>(this->_Value);
        if (Value)
            dprintf(fd, "true");
        else
            dprintf(fd, "false");
    } else if (this->_Value.type() == typeid(nullptr))
        dprintf(fd, "null");
}