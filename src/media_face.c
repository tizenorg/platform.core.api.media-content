/*
* Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <media_face.h>
#include <media_info_private.h>

int media_face_clone(media_face_h *dst, media_face_h src)
{
	media_face_s *_src = (media_face_s*)src;

	media_content_retvm_if(src == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid src handle");

	media_face_s *_dst = (media_face_s *)calloc(1, sizeof(media_face_s));
	media_content_retvm_if(_dst == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");

	if (STRING_VALID(_src->face_id))
	{
		_dst->face_id = strdup(_src->face_id);
		if(_dst->face_id== NULL)
		{
			media_face_destroy((media_face_h)_dst);
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	}

	if (STRING_VALID(_src->media_id))
	{
		_dst->media_id = strdup(_src->media_id);
		if(_dst->media_id== NULL)
		{
			media_face_destroy((media_face_h)_dst);
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	}

	_dst->face_rect_x = _src->face_rect_x;
	_dst->face_rect_y = _src->face_rect_y;
	_dst->face_rect_w = _src->face_rect_w;
	_dst->face_rect_h = _src->face_rect_h;
	_dst->orientation = _src->orientation;

	if (STRING_VALID(_src->face_tag))
	{
		_dst->face_tag = strdup(_src->face_tag);
		if(_dst->face_tag== NULL)
		{
			media_face_destroy((media_face_h)_dst);
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	}

	*dst = (media_face_h)_dst;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_destroy(media_face_h face)
{
	media_face_s *_face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	SAFE_FREE(_face->face_id);
	SAFE_FREE(_face->media_id);
	SAFE_FREE(_face->face_tag);
	SAFE_FREE(_face);

	return MEDIA_CONTENT_ERROR_NONE;
} 

int media_face_get_face_id(media_face_h face, char **face_id)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	if(STRING_VALID(_face->face_id))
	{
		*face_id = strdup(_face->face_id);
		media_content_retvm_if(*face_id == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "Out of memory");
	}
	else
	{
		*face_id = NULL;
	}

	return MEDIA_CONTENT_ERROR_NONE;
}
 
int media_face_get_media_id(media_face_h face, char **media_id)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	if(STRING_VALID(_face->media_id))
	{
		*media_id = strdup(_face->media_id);
		media_content_retvm_if(*media_id == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "Out of memory");
	}
	else
	{
		*media_id = NULL;
	}

	return MEDIA_CONTENT_ERROR_NONE;
}
 
int media_face_get_face_rect(media_face_h face, unsigned int *rect_x, unsigned int *rect_y, unsigned int *rect_w, unsigned int *rect_h)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");
	media_content_retvm_if(!(rect_x && rect_y && rect_w && rect_h), MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid rect");

	*rect_x = _face->face_rect_x;
	*rect_y = _face->face_rect_y;
	*rect_w = _face->face_rect_w;
	*rect_h = _face->face_rect_h;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_get_orientation(media_face_h face, media_content_orientation_e *orientation)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");
	media_content_retvm_if(orientation == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid orientation");

	*orientation = _face->orientation;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_get_tag(media_face_h face, char **tag)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	if (STRING_VALID(_face->face_tag))
	{
		*tag = strdup(_face->face_tag);
		media_content_retvm_if(*tag == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "Out of memory");
	}
	else
	{
		*tag = NULL;
	}

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_create_handle(media_face_h *face)
{
	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	media_face_s* _face = calloc(1, sizeof(media_face_s));
	media_content_retvm_if(_face == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "Out of memory");

	*face = (media_face_h)_face;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_set_media_id(media_face_h face, const char *media_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_face_s* _face = (media_face_s*)face;
	char *query_str = NULL;
	sqlite3_stmt *stmt = NULL;
	int item_count = 0;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");
	media_content_retvm_if(!STRING_VALID(media_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "invalid media_id");

	query_str = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_MEDIA_BY_ID, media_id);
	ret = _content_query_prepare(&stmt, query_str, NULL, NULL);
	SQLITE3_SAFE_FREE(query_str);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		item_count = (int)sqlite3_column_int(stmt, 0);
	}
	SQLITE3_FINALIZE(stmt);

	media_content_retvm_if(item_count == 0, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid media_id");

	SAFE_FREE(_face->media_id);

	_face->media_id = strdup(media_id);
	media_content_retvm_if(_face->media_id == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "Out of memory");

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_set_face_rect(media_face_h face, unsigned int rect_x, unsigned int rect_y, unsigned int rect_w, unsigned int rect_h)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");
	media_content_retvm_if(rect_w == 0, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid rect_w");
	media_content_retvm_if(rect_h == 0, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid rect_h");

	_face->face_rect_x = rect_x;
	_face->face_rect_y = rect_y;
	_face->face_rect_w = rect_w;
	_face->face_rect_h = rect_h;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_set_orientation(media_face_h face, media_content_orientation_e orientation)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	_face->orientation = orientation;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_set_tag(media_face_h face, const char *tag)
{
	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");

	if (STRING_VALID(tag))
		_face->face_tag = strdup(tag);
	else
		_face->face_tag = NULL;

	return MEDIA_CONTENT_ERROR_NONE;
}

int media_face_insert_to_db(media_face_h face)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *query_str = NULL;
	char *face_uuid = NULL;

	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");
	media_content_retvm_if(_face->media_id == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid media_id");
	media_content_retvm_if(_face->face_rect_w == 0, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid rect_w");
	media_content_retvm_if(_face->face_rect_w == 0, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid rect_h");

	ret = media_svc_generate_uuid(&face_uuid);
	media_content_retvm_if(ret != MS_MEDIA_ERR_NONE, MEDIA_CONTENT_ERROR_INVALID_OPERATION, "Fail to generate face_id");

	SAFE_FREE(_face->face_id);
	_face->face_id = strdup(face_uuid);
	SAFE_FREE(face_uuid);

	query_str = sqlite3_mprintf(INSERT_FACE_TO_FACE, _face->face_id, _face->media_id, _face->face_rect_x, _face->face_rect_y, _face->face_rect_w, _face->face_rect_h, _face->orientation, _face->face_tag);

	ret = _content_query_sql(query_str);
	SQLITE3_SAFE_FREE(query_str);

	return ret;
}

int media_face_update_to_db(media_face_h face)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *query_str = NULL;

	media_face_s* _face = (media_face_s*)face;

	media_content_retvm_if(face == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid handle");
	media_content_retvm_if(_face->face_id == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid face_id");
	media_content_retvm_if(_face->media_id == NULL, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Invalid media_id");

	query_str = sqlite3_mprintf(UPDATE_FACE_TO_FACE, _face->face_rect_x, _face->face_rect_y, _face->face_rect_w, _face->face_rect_h, _face->orientation, _face->face_tag, _face->face_id);

	ret = _content_query_sql(query_str);
	SQLITE3_SAFE_FREE(query_str);

	return ret;
}

int media_face_delete_from_db(const char *face_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *query_str = NULL;

	media_content_retvm_if(!STRING_VALID(face_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "invalid face_id");

	query_str = sqlite3_mprintf(DELETE_FACE_FROM_FACE, face_id);

	ret = _content_query_sql(query_str);
	SQLITE3_SAFE_FREE(query_str);

	return ret;
}
