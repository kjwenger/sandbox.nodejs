#pragma once

#include <nan.h>
#include <string>

class Topic : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

private:
	explicit Topic(std::string newName = std::string(""));
	~Topic();

	static NAN_METHOD(New);
	static NAN_METHOD(GetName);
//	static NAN_METHOD(SetName);
	static Nan::Persistent<v8::Function> constructor;

	std::string name;
};
