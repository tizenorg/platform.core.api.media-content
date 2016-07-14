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
#include <media_pvr.h>


int media_pvr_get_media_count_from_db(filter_h filter, int *media_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if (media_count) {
		ret = _media_db_get_group_item_count(NULL, filter, MEDIA_GROUP_PVR, media_count);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_foreach_media_from_db(filter_h filter, media_pvr_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if (callback != NULL) {
		ret = _media_db_get_pvr(filter, callback, user_data);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_destroy(media_pvr_h pvr)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;
	if (_pvr) {
		SAFE_FREE(_pvr->media_id);
		SAFE_FREE(_pvr->storage_id);
		SAFE_FREE(_pvr->channel_name);
		SAFE_FREE(_pvr->channel_num);
		SAFE_FREE(_pvr->program_title);
		SAFE_FREE(_pvr->program_crid);
		SAFE_FREE(_pvr->guidance);
		SAFE_FREE(_pvr->synopsis);
		SAFE_FREE(_pvr->genre);
		SAFE_FREE(_pvr->language);
		SAFE_FREE(_pvr->path);
		SAFE_FREE(_pvr->modified_month);
		SAFE_FREE(_pvr->private_data);
		SAFE_FREE(_pvr);

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_clone(media_pvr_h *dst, media_pvr_h src)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_src = (media_pvr_s*)src;

	if (_src != NULL) {
		media_pvr_s *_dst = (media_pvr_s*)calloc(1, sizeof(media_pvr_s));
		if (_dst == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		if (STRING_VALID(_src->media_id)) {
			_dst->media_id = strdup(_src->media_id);
			if (_dst->media_id == NULL) {
				media_pvr_destroy((media_pvr_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->channel_name)) {
			_dst->channel_name = strdup(_src->channel_name);
			if (_dst->channel_name == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->channel_num)) {
			_dst->channel_num = strdup(_src->channel_num);
			if (_dst->channel_num == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->program_title)) {
			_dst->program_title = strdup(_src->program_title);
			if (_dst->program_title == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->program_crid)) {
			_dst->program_crid = strdup(_src->program_crid);
			if (_dst->program_crid == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->guidance)) {
			_dst->guidance = strdup(_src->guidance);
			if (_dst->guidance == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->synopsis)) {
			_dst->synopsis = strdup(_src->synopsis);
			if (_dst->synopsis == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->genre)) {
			_dst->genre = strdup(_src->genre);
			if (_dst->genre == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->language)) {
			_dst->language = strdup(_src->language);
			if (_dst->language == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->path)) {
			_dst->path = strdup(_src->path);
			if (_dst->path == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->storage_id)) {
			_dst->storage_id = strdup(_src->storage_id);
			if (_dst->storage_id == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->modified_month)) {
			_dst->modified_month = strdup(_src->modified_month);
			if (_dst->modified_month == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (STRING_VALID(_src->private_data)) {
			_dst->private_data = strdup(_src->private_data);
			if (_dst->private_data == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_pvr_destroy((media_pvr_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		_dst->duration = _src->duration;
		_dst->timezone = _src->timezone;
		_dst->ptc = _src->ptc;
		_dst->major = _src->major;
		_dst->minor = _src->minor;
		_dst->channel_type = _src->channel_type;
		_dst->program_num = _src->program_num;
		_dst->timer_record = _src->timer_record;
		_dst->series_record = _src->series_record;
		_dst->hd = _src->hd;
		_dst->subtitle = _src->subtitle;
		_dst->ttx = _src->ttx;
		_dst->ad = _src->ad;
		_dst->hard_of_hearing_radio = _src->hard_of_hearing_radio;
		_dst->data_service = _src->data_service;
		_dst->content_lock = _src->content_lock;
		_dst->embargo_time = _src->embargo_time;
		_dst->expiry_time = _src->expiry_time;
		_dst->size = _src->size;
		_dst->parental_rating = _src->parental_rating;
		_dst->start_time = _src->start_time;
		_dst->program_start_time = _src->program_start_time;
		_dst->program_end_time = _src->program_end_time;
		_dst->program_date = _src->program_date;
		_dst->content_watch = _src->content_watch;
		_dst->has_audio_only = _src->has_audio_only;
		_dst->is_local_record = _src->is_local_record;
		_dst->resolution = _src->resolution;
		_dst->aspectratio = _src->aspectratio;
		_dst->sports_type = _src->sports_type;
		_dst->guidance_length = _src->guidance_length;
		_dst->tvmode = _src->tvmode;
		_dst->play_count = _src->play_count;

		*dst = (media_pvr_h)_dst;

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_pvr_from_db(const char *media_id, media_pvr_h *pvr)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *select_query = NULL;
	sqlite3_stmt *stmt = NULL;

	if (!STRING_VALID(media_id) || (pvr == NULL)) {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	select_query = sqlite3_mprintf(SELECT_PVR_FROM_PVR, media_id);

	ret = _content_query_prepare(&stmt, select_query, NULL, NULL);
	sqlite3_free(select_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	media_pvr_s *_pvr = NULL;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		if (_pvr)
			media_pvr_destroy((media_pvr_h)_pvr);

		_pvr = (media_pvr_s*)calloc(1, sizeof(media_pvr_s));

		if (_pvr == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_pvr_item_get_detail(stmt, (media_pvr_h)_pvr);

		*pvr = (media_info_h)_pvr;
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int media_pvr_get_media_id(media_pvr_h pvr, char **media_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && media_id) {
		if (STRING_VALID(_pvr->media_id)) {
			*media_id = strdup(_pvr->media_id);
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

int media_pvr_get_channel_name(media_pvr_h pvr, char **channel_name)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && channel_name) {
		if (STRING_VALID(_pvr->channel_name)) {
			*channel_name = strdup(_pvr->channel_name);
			if (*channel_name == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*channel_name = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_channel_num(media_pvr_h pvr, char **channel_num)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && channel_num) {
		if (STRING_VALID(_pvr->channel_num)) {
			*channel_num = strdup(_pvr->channel_num);
			if (*channel_num == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*channel_num = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_program_title(media_pvr_h pvr, char **program_title)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && program_title) {
		if (STRING_VALID(_pvr->program_title)) {
			*program_title = strdup(_pvr->program_title);
			if (*program_title == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*program_title = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_program_crid(media_pvr_h pvr, char **program_crid)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && program_crid) {
		if (STRING_VALID(_pvr->program_crid)) {
			*program_crid = strdup(_pvr->program_crid);
			if (*program_crid == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*program_crid = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_guidance(media_pvr_h pvr, char **guidance)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && guidance) {
		if (STRING_VALID(_pvr->guidance)) {
			*guidance = strdup(_pvr->guidance);
			if (*guidance == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*guidance = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_synopsis(media_pvr_h pvr, char **synopsis)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && synopsis) {
		if (STRING_VALID(_pvr->synopsis)) {
			*synopsis = strdup(_pvr->synopsis);
			if (*synopsis == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*synopsis = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_genre(media_pvr_h pvr, char **genre)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && genre) {
		if (STRING_VALID(_pvr->genre)) {
			*genre = strdup(_pvr->genre);
			if (*genre == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*genre = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_language(media_pvr_h pvr, char **language)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && language) {
		if (STRING_VALID(_pvr->language)) {
			*language = strdup(_pvr->language);
			if (*language == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*language = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_path(media_pvr_h pvr, char **path)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && path) {
		if (STRING_VALID(_pvr->path)) {
			*path = strdup(_pvr->path);
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

int media_pvr_get_storage_id(media_pvr_h pvr, char **storage_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && storage_id) {
		if (STRING_VALID(_pvr->storage_id)) {
			*storage_id = strdup(_pvr->storage_id);
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

int media_pvr_get_size(media_pvr_h pvr, unsigned long long *size)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && size) {
		*size = _pvr->size;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_timezone(media_pvr_h pvr, int *timezone)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && timezone) {
		*timezone = _pvr->timezone;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_ptc(media_pvr_h pvr, int *ptc)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && ptc) {
		*ptc = _pvr->ptc;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_major(media_pvr_h pvr, int *major)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && major) {
		*major = _pvr->major;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_minor(media_pvr_h pvr, int *minor)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && minor) {
		*minor = _pvr->minor;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_channel_type(media_pvr_h pvr, int *channel_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && channel_type) {
		*channel_type = _pvr->channel_type;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_program_num(media_pvr_h pvr, int *program_num)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && program_num) {
		*program_num = _pvr->program_num;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_duration(media_pvr_h pvr, int *duration)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && duration) {
		*duration = _pvr->duration;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_embargo_time(media_pvr_h pvr, int *embargo_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && embargo_time) {
		*embargo_time = _pvr->embargo_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_expiry_time(media_pvr_h pvr, int *expiry_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && expiry_time) {
		*expiry_time = _pvr->expiry_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_parental_rating(media_pvr_h pvr, int *parental_rating)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && parental_rating) {
		*parental_rating = _pvr->parental_rating;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_start_time(media_pvr_h pvr, int *start_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && start_time) {
		*start_time = _pvr->start_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_program_start_time(media_pvr_h pvr, int *program_start_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && program_start_time) {
		*program_start_time = _pvr->program_start_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_program_end_time(media_pvr_h pvr, int *end_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && end_time) {
		*end_time = _pvr->program_end_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_program_date(media_pvr_h pvr, int *program_date)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && program_date) {
		*program_date = _pvr->program_date;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_timer_record(media_pvr_h pvr, bool* timer_record)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && timer_record) {
		*timer_record = _pvr->timer_record;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_series_record(media_pvr_h pvr, bool* series_record)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && series_record) {
		*series_record = _pvr->series_record;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_hd(media_pvr_h pvr, int* hd)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && hd) {
		*hd = _pvr->hd;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_subtitle(media_pvr_h pvr, bool* subtitle)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && subtitle) {
		*subtitle = _pvr->subtitle;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_ttx(media_pvr_h pvr, bool* ttx)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && ttx) {
		*ttx = _pvr->ttx;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_ad(media_pvr_h pvr, bool* ad)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && ad) {
		*ad = _pvr->ad;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_hard_of_hearing_radio(media_pvr_h pvr, bool* hard_of_hearing_radio)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && hard_of_hearing_radio) {
		*hard_of_hearing_radio = _pvr->hard_of_hearing_radio;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_data_service(media_pvr_h pvr, bool* data_service)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && data_service) {
		*data_service = _pvr->data_service;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_content_lock(media_pvr_h pvr, bool* content_lock)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && content_lock) {
		*content_lock = _pvr->content_lock;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_content_watch(media_pvr_h pvr, bool* content_watch)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && content_watch) {
		*content_watch = _pvr->content_watch;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_has_audio_only(media_pvr_h pvr, bool* has_audio_only)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && has_audio_only) {
		*has_audio_only = _pvr->has_audio_only;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_is_local_record(media_pvr_h pvr, bool* is_local_record)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && is_local_record) {
		*is_local_record = _pvr->is_local_record;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_resolution(media_pvr_h pvr, media_pvr_resolution_e* resolution)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && resolution) {
		*resolution = _pvr->resolution;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_aspectratio(media_pvr_h pvr, media_pvr_aspectratio_e* aspectratio)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && aspectratio) {
		*aspectratio = _pvr->aspectratio;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_modified_month(media_pvr_h pvr, char **modified_month)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && modified_month) {
		if (STRING_VALID(_pvr->modified_month)) {
			*modified_month = strdup(_pvr->modified_month);
			if (*modified_month == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*modified_month = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_sports_type(media_pvr_h pvr, int* sports_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && sports_type) {
		*sports_type = _pvr->sports_type;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_guidance_length(media_pvr_h pvr, int* guidance_length)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && guidance_length) {
		*guidance_length = _pvr->guidance_length;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_tvmode(media_pvr_h pvr, int* tvmode)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && tvmode) {
		*tvmode = _pvr->tvmode;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_play_count(media_pvr_h pvr, int* play_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && play_count) {
		*play_count = _pvr->play_count;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_private_data(media_pvr_h pvr, char **private_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && private_data) {
		if (STRING_VALID(_pvr->private_data)) {
			*private_data = strdup(_pvr->private_data);
			if (*private_data == NULL) {
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		} else {
			*private_data = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_get_highlight(media_pvr_h pvr, bool *highlight)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr && highlight) {
		*highlight = _pvr->highlight;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_set_play_count(media_pvr_h pvr, int play_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr != NULL) {
		_pvr->play_count = play_count;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_set_program_title(media_pvr_h pvr, const char *program_title)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr != NULL && STRING_VALID(program_title)) {
		SAFE_FREE(_pvr->program_title);
		_pvr->program_title = strdup(program_title);
		if (_pvr->program_title == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_set_content_lock(media_pvr_h pvr, bool content_lock)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr != NULL) {
		_pvr->content_lock = content_lock;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_set_content_watch(media_pvr_h pvr, bool content_watch)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr != NULL) {
		_pvr->content_watch = content_watch;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_set_highlight(media_pvr_h pvr, bool highlight)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (_pvr != NULL) {
		_pvr->highlight = highlight;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_update_to_db(media_pvr_h pvr)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_pvr_s *_pvr = (media_pvr_s*)pvr;
	char *update_query = NULL;

	if (_pvr != NULL && STRING_VALID(_pvr->media_id) && STRING_VALID(_pvr->path)) {
		update_query = sqlite3_mprintf(UPDATE_PVR_META_FROM_PVR, _pvr->program_title, _pvr->content_lock, _pvr->content_watch, _pvr->play_count, _pvr->highlight, _pvr->media_id);

		ret = _content_query_sql(update_query);
		sqlite3_free(update_query);

		if (ret == MEDIA_CONTENT_ERROR_NONE)
			media_svc_update_pvr_info(_content_get_db_handle(), _pvr->path, _pvr->program_title, _pvr->content_lock);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int media_pvr_group_foreach_media_from_db(const char *group_name, media_group_e group, filter_h filter, media_pvr_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if ((callback == NULL) || (group < MEDIA_PVR_GROUP_DURATION) || (group >= MEDIA_GROUP_MAX)) {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	} else {
		ret = _media_db_get_pvr_group_item(group_name, filter, group, callback, user_data);
	}

	return ret;
}

int media_pvr_set_is_local_record(const char *pvr_path, bool is_local_record)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *update_query = NULL;
	char storage_id[MEDIA_CONTENT_UUID_SIZE+1] = {0,};

	if (pvr_path == NULL) {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	} else {

		/*get the storage uuid*/
		ret = media_svc_get_storage_id(_content_get_db_handle(), pvr_path, storage_id);
		if (ret == MS_MEDIA_ERR_NONE) {
			media_content_error("storage uuid [%s]", storage_id);
			update_query = sqlite3_mprintf(UPDATE_PVR_LOCAL_RECORD_PVR, is_local_record, pvr_path, storage_id);

			ret = _content_query_sql(update_query);
			sqlite3_free(update_query);
		} else {
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			media_content_error("pvr path[%s] error[%d]", pvr_path, ret);
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}

	return ret;
}
#endif
