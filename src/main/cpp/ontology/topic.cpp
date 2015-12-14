#include "ontology/topic.hpp"

Nan::Persistent<v8::Function> Topic::constructor;

NAN_MODULE_INIT(Topic::Init) {
	v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Topic").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(tpl, "GetName", GetName);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Topic").ToLocalChecked(),
			Nan::GetFunction(tpl).ToLocalChecked());
}

Topic::Topic(std::string newName) :
		name(name) {
}

Topic::~Topic() {
}

NAN_METHOD(Topic::New) {
	if (info.IsConstructCall()) {
		std::string name = info[0]->IsUndefined()
				? std::string("")
				: std::string(*v8::String::Utf8Value(info[0]->ToString()));
		Topic *obj = new Topic(name);
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	} else {
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] = {info[0]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

NAN_METHOD(Topic::GetName) {
	Topic* obj = Nan::ObjectWrap::Unwrap<Topic>(info.This());
	info.GetReturnValue().Set(Nan::New(obj->name.c_str()).ToLocalChecked());
}
