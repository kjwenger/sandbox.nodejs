#pragma once

#include "com/u14n/sandbox/cpp/model/taxonomy/Regnum.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Phylum.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Classis.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Ordo.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Familia.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Genus.hpp"
#include "com/u14n/sandbox/cpp/model/taxonomy/Species.hpp"

#include <nan.h>
#include <string>

class Species : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

private:
	explicit Species(std::string newName = std::string(""));
	~Species();

	static NAN_METHOD(New);
	static NAN_METHOD(GetName);
//	static NAN_METHOD(SetName);
	static Nan::Persistent<v8::Function> constructor;

	com::u14n::sandbox::cpp::model::taxonomy::Regnum regnum;
	com::u14n::sandbox::cpp::model::taxonomy::Phylum phylum;
	com::u14n::sandbox::cpp::model::taxonomy::Classis classis;
	com::u14n::sandbox::cpp::model::taxonomy::Ordo ordo;
	com::u14n::sandbox::cpp::model::taxonomy::Familia familia;
	com::u14n::sandbox::cpp::model::taxonomy::Genus genus;
	com::u14n::sandbox::cpp::model::taxonomy::Species species;
};
