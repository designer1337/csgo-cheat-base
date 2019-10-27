#pragma once
#include "../../source-sdk/structs/models.hpp"
#include "../../source-sdk/classes/studio.hpp"

class iv_model_info {
public:
	model_t* get_model(int index) {
		using original_fn = model_t * (__thiscall*)(iv_model_info*, int);
		return (*(original_fn * *)this)[1](this, index);
	}
	int get_model_index(const char* filename) {
		using original_fn = int(__thiscall*)(iv_model_info*, const char*);
		return (*(original_fn * *)this)[2](this, filename);
	}
	const char* get_model_name(const model_t* model) {
		using original_fn = const char* (__thiscall*)(iv_model_info*, const model_t*);
		return (*(original_fn * *)this)[3](this, model);
	}
	studio_hdr_t* get_studio_model(const model_t* model) {
		using original_fn = studio_hdr_t * (__thiscall*)(iv_model_info*, const model_t*);
		return (*(original_fn * *)this)[32](this, model);
	}
};