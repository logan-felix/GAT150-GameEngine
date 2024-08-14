#include "Json.h"
#include "EFile.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Json
{
    bool Json::Load(const std::string& filename, rapidjson::Document& document)
    {
        std::string buffer;
        if (!File::ReadFile(filename, buffer))
        {
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        document.ParseStream(istream);
        if (!document.IsObject())
        {
            std::cerr << "Could not parse Json: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];

        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }
}
