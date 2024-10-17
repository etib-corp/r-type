/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** etibjson
*/

#include "etibjson.hpp"

std::shared_ptr<JsonValue> JsonValue::operator[](const std::string& key)
{
    if (_type != JSON_OBJECT) {
        return nullptr;
    }
    return dynamic_cast<JsonObject *>(this)->getValue()[key];
}

std::shared_ptr<JsonValue> JsonValue::operator[](const size_t& index)
{
    if (_type != JSON_ARRAY) {
        return nullptr;
    }
    return dynamic_cast<JsonArray *>(this)->getValue()[index];
}

double JsonValue::getNumberValue()
{
    if (_type != JSON_NUMBER) {
        return 0.0;
    }
    return dynamic_cast<JsonNumber *>(this)->getValue();
}

std::string JsonValue::getStringValue()
{
    if (_type != JSON_STRING) {
        return "";
    }
    return dynamic_cast<JsonString *>(this)->getValue();
}

std::vector<std::shared_ptr<JsonValue>> JsonValue::getArrayValue()
{
    if (_type != JSON_ARRAY) {
        return {};
    }
    return dynamic_cast<JsonArray *>(this)->getValue();
}

std::map<std::string, std::shared_ptr<JsonValue>> JsonValue::getObjectValue()
{
    if (_type != JSON_OBJECT) {
        return {};
    }
    return dynamic_cast<JsonObject *>(this)->getValue();
}

bool JsonValue::getBoolValue()
{
    if (_type != JSON_BOOL) {
        return false;
    }
    return dynamic_cast<JsonBool *>(this)->getValue();
}

std::string JsonValue::writeObject()
{
    std::string res = "{";
    auto objectValue = dynamic_cast<JsonObject *>(this)->getValue();
    for (auto it = objectValue.begin(); it != objectValue.end(); it++) {
        res += "\"" + it->first + "\":" + it->second->writeValue();
        if (std::next(it) != objectValue.end())
            res += ",";
    }
    res += "}";
    return res;
}

std::string JsonValue::writeArray()
{
    std::string res = "[";
    auto arraySize = dynamic_cast<JsonArray *>(this)->getValue().size();
    for (size_t i = 0; i < arraySize; i++) {
        res += dynamic_cast<JsonArray *>(this)->getValue()[i]->writeValue();
        if (i + 1 < dynamic_cast<JsonArray *>(this)->getValue().size())
            res += ",";
    }
    res += "]";
    return res;
}

std::string JsonValue::writeString()
{
    return "\"" + dynamic_cast<JsonString *>(this)->getValue() + "\"";
}

std::string JsonValue::writeNumber()
{
    return std::to_string(dynamic_cast<JsonNumber *>(this)->getValue());
}

std::string JsonValue::writeBool()
{
    return dynamic_cast<JsonBool *>(this)->getValue() ? "true" : "false";
}

std::string JsonValue::writeNull()
{
    return "null";
}