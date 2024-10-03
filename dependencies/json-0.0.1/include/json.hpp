/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** json
*/

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#define JSON_SEPARATOR " \t\n\r"

enum JsonType {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOL,
    JSON_NULL
};

class JsonValue {
    public:
        JsonValue() = default;
        JsonValue(const JsonType& type) : _type(type) {}

        virtual ~JsonValue() = default;

        JsonType getType() const
        {
            return _type;
        }

        std::shared_ptr<JsonValue> operator[](const std::string& key);

        std::shared_ptr<JsonValue> operator[](const size_t& index);

        double getNumberValue();

        std::string getStringValue();

        bool getBoolValue();
    protected:
        JsonType _type;
};

class JsonNull : public JsonValue {
    public:
        JsonNull()
        {
            _type = JSON_NULL;
        }
};

class JsonBool : public JsonValue {
    public:
        JsonBool()
        {
            _type = JSON_BOOL;
            _value = false;
        }

        JsonBool(bool value)
        {
            _type = JSON_BOOL;
            _value = value;
        }

        bool getValue() const
        {
            return _value;
        }

        void setValue(bool value)
        {
            _value = value;
        }

    protected:
        bool _value;
};

class JsonNumber : public JsonValue {
    public:
        JsonNumber()
        {
            _type = JSON_NUMBER;
            _value = 0.0F;
        }

        JsonNumber(double value)
        {
            _type = JSON_NUMBER;
            _value = value;
        }

        double getValue() const
        {
            return _value;
        }

        void setValue(double value)
        {
            _value = value;
        }

    protected:
        double _value;
};

class JsonString : public JsonValue {
    public:
        JsonString()
        {
            _type = JSON_STRING;
            _value = "";
        }

        JsonString(const std::string& value)
        {
            _type = JSON_STRING;
            _value = value;
        }

        std::string getValue() const
        {
            return _value;
        }

        void setValue(const std::string& value)
        {
            _value = value;
        }

    protected:
        std::string _value;
};

class JsonArray : public JsonValue {
    public:
        JsonArray()
        {
            _type = JSON_ARRAY;
        }

        std::vector<std::shared_ptr<JsonValue>> getValue() const
        {
            return _value;
        }

        void setValue(const std::vector<std::shared_ptr<JsonValue>>& value)
        {
            _value = value;
        }

        void addValue(const std::shared_ptr<JsonValue>& value)
        {
            _value.push_back(value);
        }

    protected:
        std::vector<std::shared_ptr<JsonValue>> _value;
};

class JsonObject : public JsonValue {
    public:
        JsonObject()
        {
            _type = JSON_OBJECT;
        }

        std::map<std::string, std::shared_ptr<JsonValue>> getValue() const
        {
            return _value;
        }

        void setValue(const std::map<std::string, std::shared_ptr<JsonValue>>& value)
        {
            _value = value;
        }

        void addValue(const std::string& key, const std::shared_ptr<JsonValue>& value)
        {
            _value[key] = value;
        }

    protected:
        std::map<std::string, std::shared_ptr<JsonValue>> _value;
};

class JsonParser {
    public:
        JsonParser(const std::string& path) {
            _path = path;
        }

        ~JsonParser() {}

        std::shared_ptr<JsonValue> getJsonValue(void)
        {
            return _root;
        }

        bool parseFile() {
            size_t index = 0;
            std::ifstream file(_path);
            if (!file.is_open()) {
                std::cerr << "Error: could not open file " << _path << std::endl;
                return false;
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            _content = buffer.str();
            file.close();
            return parseValue(index, _root);
        }

    private:
        void skipWhitespaces(size_t& index) {
            while (_sep.find(_content[index]) != std::string::npos) {
                index++;
            }
        }

        bool parseValue(size_t& index, std::shared_ptr<JsonValue>& value) {
            skipWhitespaces(index);
            switch (_content[index]) {
                case 'n':
                    parseNull(index, value);
                    break;
                case 'f':
                    parseBool(index, value);
                    break;
                case 't':
                    parseBool(index, value);
                    break;
                case '"':
                    parseString(index, value);
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '-':
                case '+':
                case '.':
                    parseNumber(index, value);
                    break;
                case '[':
                    parseArray(index, value);
                    break;
                case '{':
                    parseObject(index, value);
                    break;
                default:
                    std::cerr << "Json file is wrongly formatted." << std::endl;
                    return false;
            }
            return true;
        }
        bool parseNull(size_t& index, std::shared_ptr<JsonValue>& value) {
            if (_content.substr(index, 4) == "null") {
                value = std::make_shared<JsonNull>();
                index += 4;
                return true;
            }
            return false;
        }

        bool parseBool(size_t& index, std::shared_ptr<JsonValue>& value) {
            if (_content.substr(index, 4) == "true") {
                value = std::make_shared<JsonBool>(true);
                index += 4;
                return true;
            }
            if (_content.substr(index, 5) == "false") {
                value = std::make_shared<JsonBool>(false);
                index += 5;
                return true;
            }
            return false;
        }

        bool parseString(size_t& index, std::shared_ptr<JsonValue>& value) {
            std::string res;
            index++;
            for (index; _content[index] != '"'; index++) {
                if (_content[index] == '\0')
                    return false;
                res.push_back(_content[index]);
            }
            value = std::make_shared<JsonString>(res);
            index++;
            return true;
        }

        bool parseNumber(size_t& index, std::shared_ptr<JsonValue>& value) {
            std::string res;
            for (index; _content[index] != ',' && _content[index] != '}' && _content[index] != ']'; index++) {
                if (_content[index] == '\0')
                    return false;
                res.push_back(_content[index]);
            }
            value = std::make_shared<JsonNumber>(std::stod(res));
            return true;
        }

        bool parseArray(size_t& index, std::shared_ptr<JsonValue>& value) {
            index++;
            std::string currentValue;
            value = std::make_shared<JsonArray>();
            while (1) {
                if (_content[index] == '\0')
                    return false;
                skipWhitespaces(index);
                std::shared_ptr<JsonValue> tmp;
                if (!parseValue(index, tmp))
                    return false;
                dynamic_cast<JsonArray *>(value.get())->addValue(tmp);
                skipWhitespaces(index);
                if (_content[index] == ']')
                    break;
                if (_content[index] != ',')
                    return false;
                index++;
            }
            index++;
            return true;
        }

        bool parseObject(size_t& index, std::shared_ptr<JsonValue>& value) {
            index++;
            value = std::make_shared<JsonObject>();
            std::string key;
            while (1)  {
                if (_content[index] == '\0')
                    return false;
                skipWhitespaces(index);
                std::shared_ptr<JsonValue> tmp;
                if (!parseString(index, tmp))
                    return false;
                key = dynamic_cast<JsonString *>(tmp.get())->getValue();
                skipWhitespaces(index);
                if (_content[index] != ':')
                    return false;
                index++;
                skipWhitespaces(index);
                if (!parseValue(index, tmp))
                    return false;
                dynamic_cast<JsonObject *>(value.get())->addValue(key, tmp);
                skipWhitespaces(index);
                if (_content[index] == '}')
                    break;
                if (_content[index] != ',')
                    return false;
                index++;
            }
            index++;
            return true;
        }

        std::string _path;                      ///< Path to the parsed json file
        std::string _content;                   ///< Content of the parsed json file
        std::shared_ptr<JsonValue> _root;       ///< Root of the parsed json file
        std::string _sep = JSON_SEPARATOR;      ///< String containing the json separators
        std::string _errorMessage;              ///< The error message string
};

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

bool JsonValue::getBoolValue()
{
    if (_type != JSON_BOOL) {
        return false;
    }
    return dynamic_cast<JsonBool *>(this)->getValue();
}

/*
? main.cpp
#include "json.hpp"

int main(void)
{
    JsonParser p("./test.json");
    p.parseFile();
    if (p.getJsonValue()->getType() != JSON_OBJECT) {
        std::cout << " mal" << std::endl;
        return 84;
    }
    std::cout << "bon" << std::endl;
    std::shared_ptr<JsonValue> enemy = (*p.getJsonValue())["enemy"];
    std::shared_ptr<JsonValue> life = (*(*enemy)[0])["life"];
    std::cout << life->getNumberValue() << std::endl;
    return 0;
}
*/