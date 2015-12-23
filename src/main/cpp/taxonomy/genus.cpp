#include "taxonomy/genus.hpp"

Nan::Persistent<v8::Function> Genus::constructor;

NAN_MODULE_INIT(Genus::Init) {
	v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Genus").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(tpl, "getName", GetName);
	Nan::SetPrototypeMethod(tpl, "setName", SetName);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Genus").ToLocalChecked(),
			Nan::GetFunction(tpl).ToLocalChecked());
}

Genus::Genus(std::string newName)
 		: regnum (         "Animalia" )
 		, phylum (regnum , "Chordata" )
		, classis(phylum , "Mammalia" )
		, ordo   (classis, "Carnivora")
		, familia(ordo   , "Canidae"  )
		, genus  (familia, newName    ) {
}

Genus::~Genus() {
}

NAN_METHOD(Genus::New) {
	if (info.IsConstructCall()) {
		std::string name = info[0]->IsUndefined()
				? std::string("")
				: std::string(*v8::String::Utf8Value(info[0]->ToString()));
		Genus *obj = new Genus(name);
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	} else {
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] = {info[0]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

NAN_METHOD(Genus::GetName) {
	Genus* obj = Nan::ObjectWrap::Unwrap<Genus>(info.This());
	info.GetReturnValue().Set(
			Nan::New(obj->genus.getName().c_str()).ToLocalChecked());
}

NAN_METHOD(Genus::SetName) {
	std::string name = info[0]->IsUndefined()
			? std::string("")
			: std::string(*v8::String::Utf8Value(info[0]->ToString()));
	Genus* obj = Nan::ObjectWrap::Unwrap<Genus>(info.This());
	obj->genus.setName(name);
	info.GetReturnValue().Set(
			Nan::New(obj->genus.getName().c_str()).ToLocalChecked());
}
