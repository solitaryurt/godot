/**************************************************************************/
/*  render_data_rd.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including  */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "render_data_rd.h"

#include "core/object/class_db.h"
#include "servers/rendering/renderer_rd/storage_rd/light_storage.h"

void RenderDataRD::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_directional_light_buffer"), &RenderDataRD::get_directional_light_buffer);
	ClassDB::bind_method(D_METHOD("get_directional_shadow_atlas_texture"), &RenderDataRD::get_directional_shadow_atlas_texture);
	ClassDB::bind_method(D_METHOD("get_directional_light_count"), &RenderDataRD::get_directional_light_count);
	ClassDB::bind_method(D_METHOD("get_omni_light_buffer"), &RenderDataRD::get_omni_light_buffer);
	ClassDB::bind_method(D_METHOD("get_spot_light_buffer"), &RenderDataRD::get_spot_light_buffer);
	ClassDB::bind_method(D_METHOD("get_shadow_atlas_texture"), &RenderDataRD::get_shadow_atlas_texture);
	ClassDB::bind_method(D_METHOD("get_omni_light_count"), &RenderDataRD::get_omni_light_count);
	ClassDB::bind_method(D_METHOD("get_spot_light_count"), &RenderDataRD::get_spot_light_count);
}

RID RenderDataRD::get_directional_light_buffer() const {
	RendererRD::LightStorage *light_storage = RendererRD::LightStorage::get_singleton();
	ERR_FAIL_NULL_V(light_storage, RID());
	return light_storage->get_directional_light_buffer();
}

RID RenderDataRD::get_directional_shadow_atlas_texture() const {
	RendererRD::LightStorage *light_storage = RendererRD::LightStorage::get_singleton();
	ERR_FAIL_NULL_V(light_storage, RID());
	if (directional_light_count == 0 || !light_storage->has_directional_shadows(directional_light_count)) {
		return RID();
	}
	return light_storage->directional_shadow_get_texture();
}

uint32_t RenderDataRD::get_directional_light_count() const {
	return directional_light_count;
}

RID RenderDataRD::get_omni_light_buffer() const {
	RendererRD::LightStorage *light_storage = RendererRD::LightStorage::get_singleton();
	ERR_FAIL_NULL_V(light_storage, RID());
	return light_storage->get_omni_light_buffer();
}

RID RenderDataRD::get_spot_light_buffer() const {
	RendererRD::LightStorage *light_storage = RendererRD::LightStorage::get_singleton();
	ERR_FAIL_NULL_V(light_storage, RID());
	return light_storage->get_spot_light_buffer();
}

RID RenderDataRD::get_shadow_atlas_texture() const {
	RendererRD::LightStorage *light_storage = RendererRD::LightStorage::get_singleton();
	ERR_FAIL_NULL_V(light_storage, RID());
	if (shadow_atlas.is_null()) {
		return RID();
	}
	return light_storage->shadow_atlas_get_texture(shadow_atlas);
}

uint32_t RenderDataRD::get_omni_light_count() const {
	return omni_light_count;
}

uint32_t RenderDataRD::get_spot_light_count() const {
	return spot_light_count;
}
