#pragma once

#include "v8cppwrapper.h"
#include "com/u14n/sandbox/cpp/model/ontology/Topic.hpp"

//using namespace com::u14n::sandbox::cpp::model::ontology;

struct Topic {
public:
    Topic() {
    }
    ~Topic() {
    }

};

v8::CppWrapper<Topic> topic_wrapper;
//topic_wrapper.SetAccessor<std::string>("name", &Topic::getName, &Topic::setName);
