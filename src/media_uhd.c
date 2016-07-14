 /*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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
#ifdef _USE_TV_PROFILE
#include <media_content.h>
#include <media_content_internal.h>
#include <media_info_private.h>
#include <media_util_private.h>
#include <media_uhd.h>

int media_uhd_get_media_count_from_db(filter_h filter, int *media_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if (media_count) {
		ret = _media_db_get_group_item_count(NULL, filter, MEDIA_GROUP_UHD, media_count);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_foreach_media_from_db(filter_h filter, media_uhd_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if (callback != NULL) {
		ret = _media_db_get_uhd(filter, callback, user_data);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_destroy(media_uhd_h uhd)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;
	if (_uhd) {
		SAFE_FREE(_uhd->media_id);
		SAFE_FREE(_uhd->storage_id);
		SAFE_FREE(_uhd->path);
		SAFE_FREE(_uhd->content_id);
		SAFE_FREE(_uhd->content_title);
		SAFE_FREE(_uhd->file_name);
		SAFE_FREE(_uhd->release_date);
		SAFE_FREE(_uhd);

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_clone(media_uhd_h *dst, media_uhd_h src)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_src = (media_uhd_s*)src;

	if (_src != NULL) {
		media_uhd_s *_dst = (media_uhd_s*)calloc(1, sizeof(media_uhd_s));
		if (_dst == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		if (STRING_VALID(_src->media_id)) {
			_dst->media_id = strdup(_src->media_id);
			if (_dst->media_id == NULL) {
				media_uhd_destroy((media_uhd_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->storage_id)) {
			_dst->storage_id = strdup(_src->storage_id);
			if (_dst->storage_id == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_uhd_destroy((media_uhd_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->path)) {
			_dst->path = strdup(_src->path);
			if (_dst->path == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_uhd_destroy((media_uhd_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->content_id)) {
			_dst->content_id = strdup(_src->content_id);
			if (_dst->content_id == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_uhd_destroy((media_uhd_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->content_title)) {
			_dst->content_title = strdup(_src->content_title);
			if (_dst->content_title == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_uhd_destroy((media_uhd_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->release_date)) {
			_dst->release_date = strdup(_src->release_date);
			if (_dst->release_date == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_uhd_destroy((media_uhd_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->file_name)) {
			_dst->file_name = strdup(_src->file_name);
			if (_dst->file_name == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_uhd_destroy((media_uhd_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		_dst->size = _src->size;
		_dst->modified_time = _src->modified_time;
		_dst->played_position = _src->played_position;
		_dst->sub_type = _src->sub_type;
		_dst->played_count = _src->played_count;
		*dst = (media_uhd_h)_dst;

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_uhd_from_db(const char *media_id, media_uhd_h *uhd)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *select_query = NULL;
	sqlite3_stmt *stmt = NULL;

	if (!STRING_VALID(media_id) || (uhd == NULL)) {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	select_query = sqlite3_mprintf(SELECT_UHD_FROM_UHD, media_id);

	ret = _content_query_prepare(&stmt, select_query, NULL, NULL);
	sqlite3_free(select_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	media_uhd_s *_uhd = NULL;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		if (_uhd)
			media_uhd_destroy((media_uhd_h)_uhd);

		_uhd = (media_uhd_s*)calloc(1, sizeof(media_uhd_s));

		if (_uhd == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_uhd_item_get_detail(stmt, (media_uhd_h)_uhd);

		*uhd = (media_uhd_h)_uhd;
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int media_uhd_get_media_id(media_uhd_h uhd, char **media_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && media_id) {
		if (STRING_VALID(_uhd->media_id)) {
			*media_id = strdup(_uhd->media_id);
			if (*media_id == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*media_id = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_storage_id(media_uhd_h uhd, char **storage_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && storage_id) {
		if (STRING_VALID(_uhd->storage_id)) {
			*storage_id = strdup(_uhd->storage_id);
			if (*storage_id == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*storage_id = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_path(media_uhd_h uhd, char **path)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && path) {
		if (STRING_VALID(_uhd->path)) {
			*path = strdup(_uhd->path);
			if (*path == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*path = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_size(media_uhd_h uhd, unsigned long long *size)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && size) {
		*size = _uhd->size;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_content_id(media_uhd_h uhd, char **content_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && content_id) {
		if (STRING_VALID(_uhd->content_id)) {
			*content_id = strdup(_uhd->content_id);
			if (*content_id == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*content_id = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_content_title(media_uhd_h uhd, char **content_title)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && content_title) {
		if (STRING_VALID(_uhd->content_title)) {
			*content_title = strdup(_uhd->content_title);
			if (*content_title == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*content_title = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_file_name(media_uhd_h uhd, char **file_name)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && file_name) {
		if (STRING_VALID(_uhd->file_name)) {
			*file_name = strdup(_uhd->file_name);
			if (*file_name == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*file_name = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_release_date(media_uhd_h uhd, char **release_date)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && release_date) {
		if (STRING_VALID(_uhd->release_date)) {
			*release_date = strdup(_uhd->release_date);
			if (*release_date == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*release_date = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_modified_time(media_uhd_h uhd, time_t *modified_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd && modified_time) {
		*modified_time = _uhd->modified_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_played_position(media_uhd_h uhd, int *played_position)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd) {
		*played_position = _uhd->played_position;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_sub_type(media_uhd_h uhd, int *sub_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd) {
		*sub_type = _uhd->sub_type;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_get_played_count(media_uhd_h uhd, int *played_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd) {
		*played_count = _uhd->played_count;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_set_played_position(media_uhd_h uhd, int played_position)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if ((_uhd != NULL) && (played_position >= 0)) {
		_uhd->played_position = played_position;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_set_content_title(media_uhd_h uhd, const char *content_title)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd != NULL && STRING_VALID(content_title)) {
		SAFE_FREE(_uhd->content_title);
		_uhd->content_title = strdup(content_title);
		if (_uhd->content_title == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_set_release_date(media_uhd_h uhd, const char *release_date)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd != NULL && STRING_VALID(release_date)) {
		SAFE_FREE(_uhd->release_date);
		_uhd->release_date = strdup(release_date);
		if (_uhd->release_date == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_set_sub_type(media_uhd_h uhd, int sub_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if ((_uhd != NULL) && (sub_type >= 0)) {
		_uhd->sub_type = sub_type;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_set_played_count(media_uhd_h uhd, int played_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (_uhd != NULL) {
		_uhd->played_count = played_count;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_uhd_update_to_db(media_uhd_h uhd)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_uhd_s *_uhd = (media_uhd_s*)uhd;
	char *update_query = NULL;

	if (_uhd != NULL && STRING_VALID(_uhd->media_id) && STRING_VALID(_uhd->path)) {
		update_query = sqlite3_mprintf(UPDATE_UHD_META_FROM_UHD, _uhd->content_title, _uhd->release_date, _uhd->played_position, _uhd->sub_type, _uhd->played_count, _uhd->media_id);

		ret = _content_query_sql(update_query);
		sqlite3_free(update_query);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}
#endif
