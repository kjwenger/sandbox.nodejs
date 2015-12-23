#include "taxonomy/species.hpp"

Nan::Persistent<v8::Function> Species::constructor;

NAN_MODULE_INIT(Species::Init) {
	v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Species").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(tpl, "getName", GetName);
	Nan::SetPrototypeMethod(tpl, "setName", SetName);
//	Nan::SetAccessor(tpl, Nan::New("name").ToLocalChecked(), GetName, SetName);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Species").ToLocalChecked(),
			Nan::GetFunction(tpl).ToLocalChecked());
}

Species::Species(Genus* genus, std::string newName)
		: species(genus->genus, newName) {
}

Species::~Species() {
}

NAN_METHOD(Species::New) {
	if (info.IsConstructCall()) {
		Nan::MaybeLocal<v8::Object> info0 = Nan::To<v8::Object>(info[0]);
		Genus* genus = Nan::ObjectWrap::Unwrap<Genus>(info0.ToLocalChecked());
		std::string name = info[1]->IsUndefined()
				? std::string("")
				: std::string(*v8::String::Utf8Value(info[1]->ToString()));
		Species *species = new Species(genus, name);
		species->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	} else {
		const int argc = 2;
		v8::Local<v8::Value> argv[argc] = {info[0], info[1]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

NAN_METHOD(Species::GetName) {
	Species* species = Nan::ObjectWrap::Unwrap<Species>(info.This());
	info.GetReturnValue().Set(
			Nan::New(species->species.getName().c_str()).ToLocalChecked());
}

NAN_METHOD(Species::SetName) {
	std::string name = info[0]->IsUndefined()
			? std::string("")
			: std::string(*v8::String::Utf8Value(info[0]->ToString()));
	Species* species = Nan::ObjectWrap::Unwrap<Species>(info.This());
	species->species.setName(name);
	info.GetReturnValue().Set(
			Nan::New(species->species.getName().c_str()).ToLocalChecked());
}
