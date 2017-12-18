#include "JsonData.h"

static JsonData* _jsondata = nullptr;

JsonData* JsonData::getJson()
{
	if (!_jsondata)
	{
		_jsondata = new JsonData();
	}
	return _jsondata;
}
