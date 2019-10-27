#pragma once

#include "imageformats.h"
enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	//	MATERIAL_VAR_UNUSED					  = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
										   //	MATERIAL_VAR_UNUSED					  = (1 << 18),
										   MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
										   MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
										   MATERIAL_VAR_TRANSLUCENT = (1 << 21),
										   MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
										   MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
										   MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
										   MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
										   MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
										   MATERIAL_VAR_HALFLAMBERT = (1 << 27),
										   MATERIAL_VAR_WIREFRAME = (1 << 28),
										   MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
										   MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
										   MATERIAL_VAR_VERTEXFOG = (1 << 31),

										   // NOTE: Only add flags here that either should be read from
										   // .vmts or can be set directly from client code. Other, internal
										   // flags should to into the flag enum in IMaterialInternal.h
};

enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};

typedef int ImageFormat;
class IMaterialVar;
typedef int VertexFormat_t;
typedef int MaterialPropertyTypes_t;
class i_material_var;
/* declarations */
struct model_t;
class i_material;
class c_studio_hdr;
class c_key_values;
class i_material_var;
struct studiohwdata_t;
struct color_mesh_info_t;
struct draw_model_info_t;
class i_client_renderable;
class data_cache_handle_t;
class i_mat_render_context;
struct material_lighting_state_t;

/* defs */
typedef int vertex_format_t;
typedef void* light_cache_handle_t;
typedef void* studio_decal_handle_t;
typedef int material_property_types_t;
typedef unsigned short model_instance_handle_t;
using material_handle_t = unsigned short;

class i_material {
public:
	virtual const char* get_name() const = 0;
	virtual const char* GetTextureGroupName() const = 0;
	virtual PreviewImageRetVal_t get_preview_image_properties(int* width, int* height, image_format* imageFormat, bool* isTranslucent) const = 0;
	virtual PreviewImageRetVal_t get_preview_image(unsigned char* data, int width, int height, image_format imageFormat) const = 0;
	virtual int get_mapping_width() = 0;
	virtual int get_mapping_height() = 0;
	virtual int get_num_animation_frames() = 0;
	virtual bool in_material_page(void) = 0;
	virtual void get_material_offset(float* pOffset) = 0;
	virtual void get_material_scale(float* pScale) = 0;
	virtual i_material* get_material_page(void) = 0;
	virtual i_material_var* find_var(const char* varName, bool* found, bool complain = true) = 0;
	virtual void increment_reference_count(void) = 0;
	virtual void decrement_reference_count(void) = 0;
	inline void add_ref() { increment_reference_count(); }
	inline void release() { decrement_reference_count(); }
	virtual int get_enumeration_id(void) const = 0;
	virtual void get_low_res_color_sample(float s, float t, float* color) const = 0;
	virtual void recompute_state_snapshots() = 0;
	virtual bool is_translucent() = 0;
	virtual bool is_alpha_tested() = 0;
	virtual bool is_vertex_lit() = 0;
	virtual vertex_format_t get_vertex_format() const = 0;
	virtual bool has_proxy(void) const = 0;
	virtual bool uses_env_cubemap(void) = 0;
	virtual bool needs_tangent_space(void) = 0;
	virtual bool needs_power_of_two_frame_buffer_texture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool needs_full_frame_buffer_texture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool needs_software_skinning(void) = 0;
	virtual void alpha_modulate(float alpha) = 0;
	virtual void color_modulate(float r, float g, float b) = 0;
	virtual void set_material_var_flag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool get_material_var_flag(MaterialVarFlags_t flag) const = 0;
	virtual void get_reflectivity(vec3_t& reflect) = 0;
	virtual bool get_property_flag(material_property_types_t  type) = 0;
	virtual bool is_two_sided() = 0;
	virtual void set_shader(const char* pShaderName) = 0;
	virtual int get_num_passes(void) = 0;
	virtual int get_texture_memory_bytes(void) = 0;
	virtual void refresh() = 0;
	virtual bool needs_lightmap_blend_alpha(void) = 0;
	virtual bool needs_software_lighting(void) = 0;
	virtual int shader_param_count() const = 0;
	virtual i_material_var** get_shader_params(void) = 0;
	virtual bool is_error_material() const = 0;
	virtual void unused() = 0;
	virtual float get_alpha_modulation() = 0;
	virtual void get_color_modulation(float* r, float* g, float* b) = 0;
	virtual bool is_translucent_under_modulation(float fAlphaModulation = 1.0f) const = 0;
	virtual i_material_var* find_var_fast(char const* pVarName, unsigned int* pToken) = 0;
	virtual void set_shader_and_params(c_key_values* pKeyValues) = 0;
	virtual const char* get_shader_name() const = 0;
	virtual void delete_if_unreferenced() = 0;
	virtual bool is_sprite_card() = 0;
	virtual void call_bind_proxy(void* proxyData) = 0;
	virtual void refresh_preserving_material_vars() = 0;
	virtual bool was_reloaded_from_whitelist() = 0;
	virtual bool set_temp_excluded(bool bSet, int nExcludedDimensionLimit) = 0;
	virtual int get_reference_count() const = 0;
};