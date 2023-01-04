/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** InitJson
*/

#include "Indi.hpp"

void JsonConfig::_CheckMapJson()
{
    const auto& NbMap = this->_Js["config"]["map"].GetSize();

    if (NbMap == 0)
        throw Exception::MapSizeZero("No Map Found in Config");
}

void JsonConfig::_SetEntityConf()
{
    this->_ConfPlayer.Heal = this->_Js["config"]["Entity"]["Heal"].GetData<int>();
    this->_ConfPlayer.MaxItem = this->_Js["config"]["Entity"]["Max_Item"].GetData<int>();
    this->_ConfPlayer.Speed = this->_Js["config"]["Entity"]["Speed"].GetData<int>();
}

void JsonConfig::_SetItemConf()
{
    this->_ConfBomm.ExplosionSize = this->_Js["config"]["Item"]["Boom"]["Explosion_size"].GetData<int>();
    try {
        this->_ConfBomm.TimeBeaforeExplose = this->_Js["config"]["Item"]["Boom"]["Time_Beafore_explose"] .GetData<double>();
    } catch (std::bad_any_cast& e) {
        this->_ConfBomm.TimeBeaforeExplose = static_cast<double>(this->_Js["config"]["Item"]["Boom"]["Time_Beafore_explose"] .GetData<int>());
    }

    this->_ConfSpeed.AddSpeed = this->_Js["config"]["Item"]["Speed"]["Add_Speed"] .GetData<int>();
    try {
        this->_ConfSpeed.EffectDuration = this->_Js["config"]["Item"]["Speed"]["During"] .GetData<double>();
    } catch (std::bad_any_cast& e) {
        this->_ConfSpeed.EffectDuration = static_cast<double>(this->_Js["config"]["Item"]["Speed"]["During"].GetData<int>());
    }

}

bool JsonConfig::_SetupAllConfig()
{
    _CheckMapJson();
    try {
        _SetEntityConf();
    } catch (JsonExeption::Exception& e) {
        std::cerr << " Entity conf." << std::endl;
        return false;
    }
    try {
        _SetItemConf();
    } catch (JsonExeption::Exception& e) {
        std::cerr << " Item conf." << std::endl;
        return false;
    }
    return true;
}
