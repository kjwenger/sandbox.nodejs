#include "ontology/topic.hpp"
#include "taxonomy/genus.hpp"
#include "taxonomy/species.hpp"

#include <nan.h>

NAN_MODULE_INIT(InitAll) {
	Topic::Init(target);

	Genus::Init(target);
	Species::Init(target);
}

NODE_MODULE(sandbox_cpp, InitAll)
