#include "Object.h"

void Object::Read(const json_t& value)
{
	READ_DATA(value, name);
	READ_DATA(value, active);
}

void Object::Write(json_t& value)
{

}