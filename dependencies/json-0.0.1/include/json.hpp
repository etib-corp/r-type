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
#include <cstddef>

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

        std::string writeObject();

        std::string writeArray();

        std::string writeString();

        std::string writeNumber();

        std::string writeBool();

        std::string writeNull();

        std::string writeValue()
        {
            switch (_type) {
                case JSON_OBJECT:
                    return writeObject();
                case JSON_ARRAY:
                    return writeArray();
                case JSON_STRING:
                    return writeString();
                case JSON_NUMBER:
                    return writeNumber();
                case JSON_BOOL:
                    return writeBool();
                case JSON_NULL:
                    return writeNull();
                default:
                    return "";
            }
        }


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

        std::vector<std::shared_ptr<JsonValue>> getValue()
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
                _errorMessage += "Error: Couldn't open the file" + _path + "\n";
                return false;
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            _content = buffer.str();
            file.close();
            return parseValue(index, _root);
        }

        void writeInfile(const std::string& path)
        {
            std::ofstream file(path);

            file << _root->writeValue();
            file.close();
        }

        std::string getErrorMessage() const
        {
            return _errorMessage;
        }


    private:
        void skipWhitespaces(size_t& index) {
            while (_sep.find(_content[index]) != std::string::npos) {
                if (_content[index] == '\n')
                    _lineNumber++;
                index++;
            }
        }

        bool parseValue(size_t& index, std::shared_ptr<JsonValue>& value) {
            skipWhitespaces(index);
            switch (_content[index]) {
                case 'n':
                    return parseNull(index, value);
                case 'f':
                case 't':
                    return parseBool(index, value);
                case '"':
                    return parseString(index, value);
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
                    return parseNumber(index, value);
                case '[':
                    return parseArray(index, value);
                case '{':
                    return parseObject(index, value);
                default:
                    _errorMessage += "Json file is wrongly formatted at line " + std::to_string(_lineNumber) + "\n";
                    return false;
            }
        }

        bool parseNull(size_t& index, std::shared_ptr<JsonValue>& value) {
            std::string res = _content.substr(index, 4);
            if (res == "null") {
                value = std::make_shared<JsonNull>();
                index += 4;
                return true;
            }
            _errorMessage += "Json file is wrongly formatted. Expected null at line " + std::to_string(_lineNumber) + " but got " + res + "\n";
            return false;
        }

        bool parseBool(size_t& index, std::shared_ptr<JsonValue>& value) {
            if (_content[index] == 't') {
                std::string res = _content.substr(index, 4);
                if (res == "true") {
                    value = std::make_shared<JsonBool>(true);
                    index += 4;
                    return true;
                }
                _errorMessage += "Json file is wrongly formatted. Expected null at line " + std::to_string(_lineNumber) + " but got " + res + "\n";
            }
            if (_content[index] == 'f') {
                std::string res = _content.substr(index, 5);
                if (res == "false") {
                    value = std::make_shared<JsonBool>(false);
                    index += 5;
                    return true;
                }
                _errorMessage += "Json file is wrongly formatted. Expected null at line " + std::to_string(_lineNumber) + " but got " + res + "\n";
            }
            return false;
        }

        bool parseString(size_t& index, std::shared_ptr<JsonValue>& value) {
            std::string res;
            index++;
            for (index; _content[index] != '"'; index++) {
                if (_content[index] == '\0') {
                    _errorMessage += "Json file is wrongly formatted. Expected \" at line " + std::to_string(_lineNumber) + " but got unexpected end of file\n";
                    return false;
                }
                res.push_back(_content[index]);
            }
            value = std::make_shared<JsonString>(res);
            index++;
            return true;
        }

        bool parseNumber(size_t& index, std::shared_ptr<JsonValue>& value) {
            std::string res;
            for (index; _content[index] != ',' && _content[index] != '}' && _content[index] != ']'; index++) {
                res.push_back(_content[index]);
            }
            try {
                value = std::make_shared<JsonNumber>(std::stod(res));
            } catch (std::exception& e) {
                _errorMessage += "Json file is wrongly formatted. Expected a number at line " + std::to_string(_lineNumber) + " but got " + res + "\n";
                return false;
            }
            return true;
        }

        bool parseArray(size_t& index, std::shared_ptr<JsonValue>& value) {
            index++;
            std::string currentValue;
            value = std::make_shared<JsonArray>();
            while (1) {
                if (_content[index] == '\0') {
                    _errorMessage += "Json file is wrongly formatted. Expected ] at line " + std::to_string(_lineNumber) + " but got unexpected end of file\n";
                    return false;
                }
                skipWhitespaces(index);
                std::shared_ptr<JsonValue> tmp;
                if (!parseValue(index, tmp)) {
                    _errorMessage += "Json file is wrongly formatted at line " + std::to_string(_lineNumber) + "\n";
                    return false;
                }
                dynamic_cast<JsonArray *>(value.get())->addValue(tmp);
                skipWhitespaces(index);
                if (_content[index] == ']')
                    break;
                if (_content[index] != ',') {
                    _errorMessage += "Json file is wrongly formatted. Expected , at line " + std::to_string(_lineNumber) + " but got " + _content[index] + "\n";
                    return false;
                }
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
                if (!parseString(index, tmp)) {
                    _errorMessage += "Json file is wrongly formatted. Expected a string at line " + std::to_string(_lineNumber) + "\n";
                    return false;
                }
                key = dynamic_cast<JsonString *>(tmp.get())->getValue();
                skipWhitespaces(index);
                if (_content[index] != ':') {
                    _errorMessage += "Json file is wrongly formatted. Expected : at line " + std::to_string(_lineNumber) + " but got " + _content[index] + "\n";
                    return false;
                }
                index++;
                skipWhitespaces(index);
                if (!parseValue(index, tmp)) {
                    _errorMessage += "Json file is wrongly formatted. Expected a value at line " + std::to_string(_lineNumber) + "\n";
                    return false;
                }
                dynamic_cast<JsonObject *>(value.get())->addValue(key, tmp);
                skipWhitespaces(index);
                if (_content[index] == '}')
                    break;
                if (_content[index] != ',') {
                    _errorMessage += "Json file is wrongly formatted. Expected , at line " + std::to_string(_lineNumber) + " but got " + _content[index] + "\n";
                    return false;
                }
                index++;
            }
            index++;
            return true;
        }

        std::string _path;                      ///< Path to the parsed json file
        std::string _content;                   ///< Content of the parsed json file
        std::shared_ptr<JsonValue> _root;       ///< Root of the parsed json file
        std::string _sep = JSON_SEPARATOR;      ///< String containing the json separators
        size_t _lineNumber;                     ///< The current line number
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

// int main(void)
// {
//     JsonParser p("./test.json");
//     if (!p.parseFile()) {
//         std::cout << p.getErrorMessage() << std::endl;
//         return 84;
//     }
//     if (p.getJsonValue()->getType() != JSON_OBJECT) {
//         std::cout << " mal" << std::endl;
//         return 84;
//     }
//     std::cout << "bon" << std::endl;
//     // std::shared_ptr<JsonValue> enemy = (*p.getJsonValue())["enemy"];
//     // std::shared_ptr<JsonValue> life = (*(*enemy)[0])["life"];
//     // std::cout << life->getNumberValue() << std::endl;
//     p.writeInfile("./test2.json");
//     std::cout << "done" << std::endl;
//     return 0;
// }
