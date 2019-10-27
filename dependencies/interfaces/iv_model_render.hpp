#pragma once
#include "../../source-sdk/structs/materials.hpp"
struct draw_model_state_t {
	studio_hdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	i_client_renderable* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	studio_decal_handle_t     m_decals;
	int                     m_drawFlags;
	int                     m_lod;
};

class iv_model_render {
public:
	void override_material(i_material* material) {
		using original_fn = void(__thiscall*)(iv_model_render*, i_material*, int, int);
		return (*(original_fn * *)this)[1](this, material, 0, 0);
	}
};