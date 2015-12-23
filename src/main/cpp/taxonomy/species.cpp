#include "taxonomy/species.hpp"

Nan::Persistent<v8::Function> Species::constructor;

NAN_MODULE_INIT(Species::Init) {
	v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Species").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(tpl, "getName", GetName);
	Nan::SetPrototypeMethod(tpl, "setName", SetName);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Species").ToLocalChecked(),
			Nan::GetFunction(tpl).ToLocalChecked());
}

Species::Species(std::string newName)
 		: regnum (         "Animalia" )
 		, phylum (regnum , "Chordata" )
		, classis(phylum , "Mammalia" )
		, ordo   (classis, "Carnivora")
		, familia(ordo   , "Canidae"  )
		, genus  (familia, "Canis"    )
		, species(genus  , newName    ) {
}

Species::~Species() {
}

NAN_METHOD(Species::New) {
	if (info.IsConstructCall()) {
		std::string name = info[0]->IsUndefined()
				? std::string("")
				: std::string(*v8::String::Utf8Value(info[0]->ToString()));
		Species *obj = new Species(name);
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	} else {
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] = {info[0]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

NAN_METHOD(Species::GetName) {
	Species* obj = Nan::ObjectWrap::Unwrap<Species>(info.This());
	info.GetReturnValue().Set(
			Nan::New(obj->species.getName().c_str()).ToLocalChecked());
}

NAN_METHOD(Species::SetName) {
	std::string name = info[0]->IsUndefined()
			? std::string("")
			: std::string(*v8::String::Utf8Value(info[0]->ToString()));
	Species* obj = Nan::ObjectWrap::Unwrap<Species>(info.This());
	obj->species.setName(name);
	info.GetReturnValue().Set(
			Nan::New(obj->species.getName().c_str()).ToLocalChecked());
}
