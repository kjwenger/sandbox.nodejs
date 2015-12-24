#pragma once

#include "genus.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Species.hpp"

#include <nan.h>
#include <string>

class Species : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

private:
	explicit Species(Genus* genus, std::string newName = std::string(""));
	~Species();

	static NAN_METHOD(New);
	static NAN_METHOD(GetName);
	static NAN_METHOD(SetName);
	static NAN_GETTER(NameGet);
//	static NAN_SETTER(NameSet);
	static Nan::Persistent<v8::Function> constructor;

	com::u14n::sandbox::cpp::model::taxonomy::Species species;
};
