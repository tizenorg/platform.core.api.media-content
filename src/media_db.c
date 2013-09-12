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


#include <media_content.h>
#include <media_info_private.h>

static char * __media_db_get_group_name(media_group_e group);

static char * __media_db_get_group_name(media_group_e group)
{
	switch(group)
	{
		case MEDIA_CONTENT_GROUP_DISPLAY_NAME:
			return DB_FIELD_MEDIA_DISPLAY_NAME;
		case MEDIA_CONTENT_GROUP_TYPE:
			return DB_FIELD_MEDIA_TYPE;
		case MEDIA_CONTENT_GROUP_MIME_TYPE:
			return DB_FIELD_MEDIA_MIME_TYPE;
		case MEDIA_CONTENT_GROUP_SIZE:
			return DB_FIELD_MEDIA_SIZE;
		case MEDIA_CONTENT_GROUP_ADDED_TIME:
			return DB_FIELD_MEDIA_ADDED_TIME;
		case MEDIA_CONTENT_GROUP_MODIFIED_TIME:
			return DB_FIELD_MEDIA_MODIFIED_TIME;
		case MEDIA_CONTENT_GROUP_TITLE:
			return DB_FIELD_MEDIA_TITLE;
		case MEDIA_CONTENT_GROUP_ARTIST:
			return DB_FIELD_MEDIA_ARTIST;
		case MEDIA_CONTENT_GROUP_GENRE:
			return DB_FIELD_MEDIA_GENRE;
		case MEDIA_CONTENT_GROUP_COMPOSER:
			return DB_FIELD_MEDIA_COMPOSER;
		case MEDIA_CONTENT_GROUP_YEAR:
			return DB_FIELD_MEDIA_YEAR;
		case MEDIA_CONTENT_GROUP_RECORDED_DATE:
			return DB_FIELD_MEDIA_RECORDED_DATE;
		case MEDIA_CONTENT_GROUP_COPYRIGHT:
			return DB_FIELD_MEDIA_COPYRIGHT;
		case MEDIA_CONTENT_GROUP_TRACK_NUM:
			return DB_FIELD_MEDIA_TRACK_NUM;
		case MEDIA_CONTENT_GROUP_DESCRIPTION:
			return DB_FIELD_MEDIA_DESCRIPTION;
		case MEDIA_CONTENT_GROUP_LONGITUDE:
			return DB_FIELD_MEDIA_LONGITUDE;
		case MEDIA_CONTENT_GROUP_LATITUDE:
			return DB_FIELD_MEDIA_LATITUDE;
		case MEDIA_CONTENT_GROUP_ALTITUDE:
			return DB_FIELD_MEDIA_ALTITUDE;
		case MEDIA_CONTENT_GROUP_BURST_IMAGE:
			return DB_FIELD_MEDIA_BURST_ID;
		case MEDIA_CONTENT_GROUP_RATING:
			return DB_FIELD_MEDIA_RATING;
		case MEDIA_CONTENT_GROUP_AUTHOR:
			return DB_FIELD_MEDIA_AUTHOR;
		case MEDIA_CONTENT_GROUP_PROVIDER:
			return DB_FIELD_MEDIA_PROVIDER;
		case MEDIA_CONTENT_GROUP_CONTENT_NAME:
			return DB_FIELD_MEDIA_CONTENT_NAME;
		case MEDIA_CONTENT_GROUP_CATEGORY:
			return DB_FIELD_MEDIA_CATEGORY;
		case MEDIA_CONTENT_GROUP_LOCATION_TAG:
			return DB_FIELD_MEDIA_LOCATION_TAG;
		case MEDIA_CONTENT_GROUP_AGE_RATING:
			return DB_FIELD_MEDIA_AGE_RATING;
		case MEDIA_CONTENT_GROUP_KEYWORD:
			return DB_FIELD_MEDIA_KEYWORD;
		default:
			return NULL;
	}

	return NULL;
}

int _media_db_get_group_count(filter_h filter, group_list_e group_type, int *group_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	attribute_h attr;

	media_content_debug_func();

	memset(select_query, 0x00, sizeof(select_query));

	attr = _content_get_attirbute_handle();

	switch(group_type) {
		case MEDIA_GROUP_NONE:
		case MEDIA_GROUP_TAG_BY_MEDIA_ID:
		case MEDIA_GROUP_BOOKMARK_BY_MEDIA_ID:
			{
				media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
			break;
		case MEDIA_GROUP_ALBUM:
			attr = _content_get_alias_attirbute_handle();
			//snprintf(select_query, sizeof(select_query), SELECT_ALBUM_COUNT);
			if(!SAFE_STRLCPY(select_query, SELECT_ALBUM_COUNT, sizeof(select_query)))
			{
				media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}

			break;
		case MEDIA_GROUP_FOLDER:
			attr = _content_get_alias_attirbute_handle();
			//snprintf(select_query, sizeof(select_query), SELECT_FOLDER_COUNT);
			if(!SAFE_STRLCPY(select_query, SELECT_FOLDER_COUNT, sizeof(select_query)))
			{
				media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
			break;
		case MEDIA_GROUP_PLAYLIST:
			//attr = _content_get_alias_attirbute_handle();
			//snprintf(select_query, sizeof(select_query), SELECT_PLAYLIST_COUNT);
			if(!SAFE_STRLCPY(select_query, SELECT_PLAYLIST_COUNT, sizeof(select_query)))
			{
				media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
			break;
		case MEDIA_GROUP_TAG:
			//attr = _content_get_alias_attirbute_handle();
			//snprintf(select_query, sizeof(select_query), SELECT_TAG_COUNT);
			if(!SAFE_STRLCPY(select_query, SELECT_TAG_COUNT, sizeof(select_query)))
			{
				media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
			break;
		case MEDIA_GROUP_BOOKMARK:
			attr = _content_get_alias_attirbute_handle();
			//snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_COUNT);
			if(!SAFE_STRLCPY(select_query, SELECT_BOOKMARK_COUNT, sizeof(select_query)))
			{
				media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
			break;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(STRING_VALID(_filter->condition))
		{
			ret = _media_filter_attribute_generate(attr, _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(attr, filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		*group_count = (int)sqlite3_column_int(stmt, 0);
		media_content_debug("group count : [%d]", *group_count);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group_count(media_group_e group, filter_h filter, int *group_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;

	media_content_debug_func();

	memset(select_query, 0x00, sizeof(select_query));

	snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_COUNT, __media_db_get_group_name(group));

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(STRING_VALID(_filter->condition))
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}

		SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
		if(STRING_VALID(condition_query))
			SAFE_STRLCAT(select_query, condition_query, sizeof(select_query));
		if(STRING_VALID(option_query))
			SAFE_STRLCAT(select_query, option_query, sizeof(select_query));

		SAFE_FREE(condition_query);
		SAFE_FREE(option_query);
	}

	SAFE_STRLCAT(select_query, QUERY_KEYWORD_BRACKET, sizeof(select_query));

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		*group_count = (int)sqlite3_column_int(stmt, 0);
		media_content_debug("group count : [%d]", *group_count);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group(media_group_e group, filter_h filter, media_group_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	char *name = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	memset(select_query, 0x00, sizeof(select_query));

	snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_LIST, __media_db_get_group_name(group));

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 0)))
		{
			name = strdup((const char *)sqlite3_column_text(stmt, 0));
			media_content_debug("group name : [%s]", name);
		}

		if(callback(name, user_data) == false)
		{
			SAFE_FREE(name);
			break;
		}

		SAFE_FREE(name);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_album(filter_h filter, media_album_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	memset(select_query, 0x00, sizeof(select_query));

	//snprintf(select_query, sizeof(select_query), SELECT_ALBUM_LIST);
	if(!SAFE_STRLCPY(select_query, SELECT_ALBUM_LIST, sizeof(select_query)))
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_alias_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(_content_get_alias_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_album_s *album = (media_album_s*)calloc(1, sizeof(media_album_s));

		if(album == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		album->album_id = (int)sqlite3_column_int(stmt, 0);

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 1)))
			album->name = strdup((const char *)sqlite3_column_text(stmt, 1));

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 2)))
			album->artist = strdup((const char *)sqlite3_column_text(stmt, 2));

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 3)))
			album->album_art_path = strdup((const char *)sqlite3_column_text(stmt, 3));

		if(callback((media_album_h)album, user_data) == false)
		{
			media_album_destroy((media_album_h)album);
			break;
		}

		media_album_destroy((media_album_h)album);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_folder(filter_h filter, media_folder_cb callback, bool with_empty, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	memset(select_query, 0x00, sizeof(select_query));

	//snprintf(select_query, sizeof(select_query), SELECT_FOLDER_LIST);
	if(!SAFE_STRLCPY(select_query, with_empty ? SELECT_FOLDER_LIST_WITH_EMPTY : SELECT_FOLDER_LIST, sizeof(select_query)))
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_alias_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(_content_get_alias_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_folder_s *_folder = (media_folder_s*)calloc(1, sizeof(media_folder_s));

		if(_folder == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 0)))
			_folder->folder_id = strdup((const char *)sqlite3_column_text(stmt, 0));

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 1)))
			_folder->path = strdup((const char *)sqlite3_column_text(stmt, 1));

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 2)))
			_folder->name = strdup((const char *)sqlite3_column_text(stmt, 2));

		_folder->storage_type = (int)sqlite3_column_int(stmt,3);

		_folder->modified_time = (int)sqlite3_column_int(stmt,4);

		if(callback((media_folder_h)_folder, user_data) == false)
		{
			media_folder_destroy((media_folder_h) _folder);
			break;
		}

		media_folder_destroy((media_folder_h) _folder);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_playlist(filter_h filter, media_playlist_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	memset(select_query, 0x00, sizeof(select_query));

	//snprintf(select_query, sizeof(select_query), SELECT_PLAYLIST_LIST);
	if(!SAFE_STRLCPY(select_query, SELECT_PLAYLIST_LIST, sizeof(select_query)))
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}


	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			//ret = _media_filter_attribute_generate(_content_get_alias_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		//ret = _media_filter_attribute_option_generate(_content_get_alias_attirbute_handle(), filter, &option_query);
		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_playlist_s *_playlist = (media_playlist_s*)calloc(1, sizeof(media_playlist_s));

		if(_playlist == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_playlist->playlist_id = (int)sqlite3_column_int(stmt, 0);

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 1)))
			_playlist->name = strdup((const char *)sqlite3_column_text(stmt, 1));

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 2)))
			_playlist->thumbnail_path = strdup((const char *)sqlite3_column_text(stmt, 2));

		if(callback((media_playlist_h)_playlist, user_data) == false)
		{
			media_playlist_destroy((media_playlist_h)_playlist);
			break;
		}
		media_playlist_destroy((media_playlist_h)_playlist);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_playlist_item(int playlist_id, filter_h filter, playlist_member_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	memset(select_query, 0x00, sizeof(select_query));

	snprintf(select_query, sizeof(select_query), SELECT_PLAYLIST_ITEM_ID_FROM_PLAYLIST_VIEW, playlist_id);

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			//ret = _media_filter_attribute_generate(_content_get_alias_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		//ret = _media_filter_attribute_option_generate(_content_get_alias_attirbute_handle(), filter, &option_query);
		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		int playlist_member_id = 0;
		char media_uuid[MEDIA_CONTENT_UUID_SIZE+1];
		media_info_h media = NULL;
		memset(media_uuid, 0x00, sizeof(media_uuid));

		playlist_member_id = (int)sqlite3_column_int(stmt, 0);

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 1)))
			strncpy(media_uuid, (const char *)sqlite3_column_text(stmt, 1), MEDIA_CONTENT_UUID_SIZE);

		ret = media_info_get_media_from_db(media_uuid, &media);

		if(callback(playlist_member_id, media, user_data) == false)
		{
			media_info_destroy(media);
			break;
		}
		media_info_destroy(media);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

//same as _media_db_get_playlist
int _media_db_get_tag(const char *media_id, filter_h filter, media_tag_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	attribute_h attr;

	memset(select_query, 0x00, sizeof(select_query));

	if(!STRING_VALID(media_id))
	{
		//attr = _content_get_alias_attirbute_handle();
		attr = _content_get_attirbute_handle();
		//snprintf(select_query, sizeof(select_query), SELECT_TAG_LIST);
		if(!SAFE_STRLCPY(select_query, SELECT_TAG_LIST, sizeof(select_query)))
		{
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		attr = _content_get_attirbute_handle();
		snprintf(select_query, sizeof(select_query), SELECT_TAG_LIST_BY_MEDIA_ID, media_id);
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(attr, _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(attr, filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_tag_s *_tag = (media_tag_s*)calloc(1, sizeof(media_tag_s));

		if(_tag == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_tag->tag_id = (int)sqlite3_column_int(stmt, 0);

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 1)))
			_tag->name = strdup((const char *)sqlite3_column_text(stmt, 1));

		if(callback((media_tag_h)_tag, user_data) == false)
		{
			media_tag_destroy((media_tag_h)_tag);
			break;
		}
		media_tag_destroy((media_tag_h)_tag);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_bookmark(const char *media_id, filter_h filter, media_bookmark_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	attribute_h attr;

	memset(select_query, 0x00, sizeof(select_query));

	if(!STRING_VALID(media_id))
	{
		attr = _content_get_alias_attirbute_handle();
		//snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_LIST);
		if(!SAFE_STRLCPY(select_query, SELECT_BOOKMARK_LIST, sizeof(select_query)))
		{
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		attr = _content_get_attirbute_handle();
		snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_LIST_BY_MEDIA_ID_USUAL, media_id);
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(attr, _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(attr, filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_bookmark_s *bookmark = (media_bookmark_s*)calloc(1, sizeof(media_bookmark_s));

		if(bookmark == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		bookmark->bookmark_id = (int)sqlite3_column_int(stmt, 0);

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 1)))
			bookmark->media_id = strdup((const char *)sqlite3_column_text(stmt, 1));

		bookmark->marked_time = (int)sqlite3_column_int(stmt, 2);

		if(STRING_VALID((const char *)sqlite3_column_text(stmt, 3)))
			bookmark->thumbnail_path = strdup((const char *)sqlite3_column_text(stmt, 3));

		if(callback((media_bookmark_h)bookmark, user_data) == false)
		{
			media_bookmark_destroy((media_bookmark_h)bookmark);
			break;
		}

		media_bookmark_destroy((media_bookmark_h)bookmark);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;

}

int _media_db_get_group_item_count_by_id(int group_id, filter_h filter, group_list_e group_type, int *item_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	attribute_h attr = NULL;

	media_content_debug_func();

	memset(select_query, 0x00, sizeof(select_query));

	if(group_type == MEDIA_GROUP_ALBUM)
	{
		attr = _content_get_attirbute_handle();
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_ALBUM, group_id);
	}
	else if(group_type == MEDIA_GROUP_PLAYLIST)
	{
		//attr = _content_get_alias_attirbute_handle();
		attr = _content_get_attirbute_handle();
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_PLAYLIST, group_id);
	}
	else if(group_type == MEDIA_GROUP_TAG)
	{
		attr = _content_get_attirbute_handle();
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_TAG, group_id);
	}
	else
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(attr, _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(attr, filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}
/*
	if((group_type == MEDIA_GROUP_PLAYLIST) || (group_type == MEDIA_GROUP_TAG))
	{
		strncat(select_query, QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));

		if(STRING_VALID(condition_query))
			strncat(select_query, condition_query, strlen(condition_query));
		if(STRING_VALID(option_query))
			strncat(select_query, option_query, strlen(option_query));

		strncat(select_query, QUERY_KEYWORD_BRACKET, strlen(QUERY_KEYWORD_BRACKET));

		SAFE_FREE(condition_query);
		SAFE_FREE(option_query);
	}
*/
	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		*item_count = (int)sqlite3_column_int(stmt, 0);
		media_content_debug("group item count : [%d]", *item_count);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_group_item_count(const char *group_name, filter_h filter, group_list_e group_type, int *item_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	char complete_select_query[DEFAULT_QUERY_SIZE];
	char *select_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	bool is_simple = FALSE;

	media_content_debug_func();

	if(group_type == MEDIA_GROUP_NONE)
	{
		/* There are 2 ways to get count for media table for performance 
			If user wants to set offset and count, use SQL SELECT_MEDIA_COUNT_FROM_MEDIA.
			If user wants to get count without setting count, SELECT_MEDIA_COUNT_FROM_MEDIA_SIMPLE */
		_filter = (filter_s *)filter;
		if (_filter) {
			if ((_filter->offset < 0) && (_filter->count < 0)) {
				select_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_MEDIA_SIMPLE);
				is_simple = TRUE;
			} else {
				select_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_MEDIA);
			}
		} else {
			select_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_MEDIA);
		}
	}
	else if(group_type == MEDIA_GROUP_FOLDER)
	{
		select_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_FOLDER, group_name);
	}
	else if(group_type == MEDIA_GROUP_TAG_BY_MEDIA_ID)
	{
		select_query = sqlite3_mprintf(SELECT_TAG_COUNT_BY_MEDIA_ID, group_name);
	}
	else if(group_type == MEDIA_GROUP_BOOKMARK_BY_MEDIA_ID)
	{
		select_query = sqlite3_mprintf(SELECT_BOOKMARK_COUNT_BY_MEDIA_ID, group_name);
	}
	else
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			if(ret != MEDIA_CONTENT_ERROR_NONE)
			{
				sqlite3_free(select_query);
				return ret;
			}
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			sqlite3_free(select_query);
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s %s", select_query, QUERY_KEYWORD_AND);
		}
		else
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
		}
	} else {
		snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
	}

	if(group_type == MEDIA_GROUP_NONE)
	{
		SAFE_STRLCAT(complete_select_query, QUERY_KEYWORD_SPACE, sizeof(complete_select_query));
		if(STRING_VALID(condition_query))
			SAFE_STRLCAT(complete_select_query, condition_query, sizeof(complete_select_query));
		if(STRING_VALID(option_query))
			SAFE_STRLCAT(complete_select_query, option_query, sizeof(complete_select_query));

		if (!is_simple)
			SAFE_STRLCAT(complete_select_query, QUERY_KEYWORD_BRACKET, sizeof(complete_select_query));

		SAFE_FREE(condition_query);
		SAFE_FREE(option_query);
	}

	ret = _content_query_prepare(&stmt, complete_select_query, condition_query, option_query);
	sqlite3_free(select_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		*item_count = (int)sqlite3_column_int(stmt, 0);
		media_content_debug("group item count : [%d]", *item_count);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_group_item_by_id(int group_id, filter_h filter, media_info_cb callback, void *user_data, group_list_e group_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	memset(select_query, 0x00, sizeof(select_query));

	if(group_type == MEDIA_GROUP_ALBUM)
	{
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_ALBUM, group_id);
	}
	else if(group_type == MEDIA_GROUP_PLAYLIST)
	{
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_PLAYLIST, group_id);
	}
	else if(group_type == MEDIA_GROUP_TAG)
	{
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_TAG, group_id);
	}
	else
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, sizeof(select_query));
		}
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if(item == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if(callback((media_info_h)item, user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}

		media_info_destroy((media_info_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_group_item(const char *group_name, filter_h filter, media_info_cb callback, void *user_data, group_list_e group_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char complete_select_query[DEFAULT_QUERY_SIZE];
	char *select_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	if(group_type == MEDIA_GROUP_NONE)
	{
		select_query = sqlite3_mprintf(SELECT_MEDIA_ITEM);
	}
	else if(group_type == MEDIA_GROUP_FOLDER)
	{
		select_query = sqlite3_mprintf(SELECT_MEDIA_FROM_FOLDER, group_name);
	}
	else if(group_type == MEDIA_GROUP_BOOKMARK_BY_MEDIA_ID)
	{
		select_query = sqlite3_mprintf(SELECT_BOOKMARK_LIST_BY_MEDIA_ID, group_name);
	}
	else
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			if(ret != MEDIA_CONTENT_ERROR_NONE)
			{
				sqlite3_free(select_query);
				return ret;
			}
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			sqlite3_free(select_query);
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s %s", select_query, QUERY_KEYWORD_AND);
		}
		else
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
		}
	} else {
		snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
	}

	ret = _content_query_prepare(&stmt, complete_select_query, condition_query, option_query);
	sqlite3_free(select_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if(item == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if(callback((media_info_h)item, user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}

		media_info_destroy((media_info_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group_item_count(const char *group_name, media_group_e group, filter_h filter, int *item_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;
	char complete_select_query[DEFAULT_QUERY_SIZE];
	char *select_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;

	media_content_debug_func();

	if(group_name != NULL)
		select_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_GROUP, __media_db_get_group_name(group), group_name);
	else
		select_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_GROUP_NULL, __media_db_get_group_name(group));

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			if(ret != MEDIA_CONTENT_ERROR_NONE)
			{
				sqlite3_free(select_query);
				return ret;
			}
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			sqlite3_free(select_query);
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s %s", select_query, QUERY_KEYWORD_AND);
		}
		else
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
		}
	} else {
		snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
	}

	SAFE_STRLCAT(complete_select_query, QUERY_KEYWORD_SPACE, sizeof(complete_select_query));
	if(STRING_VALID(condition_query))
		SAFE_STRLCAT(complete_select_query, condition_query, sizeof(complete_select_query));
	if(STRING_VALID(option_query))
		SAFE_STRLCAT(complete_select_query, option_query, sizeof(complete_select_query));

	SAFE_STRLCAT(complete_select_query, QUERY_KEYWORD_BRACKET, sizeof(complete_select_query));

	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);

	ret = _content_query_prepare(&stmt, complete_select_query, condition_query, option_query);
	sqlite3_free(select_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		*item_count = (int)sqlite3_column_int(stmt, 0);
		media_content_debug("group item count : [%d]", *item_count);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group_item(const char *group_name, media_group_e group, filter_h filter, media_info_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char complete_select_query[DEFAULT_QUERY_SIZE];
	char *select_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	filter_s *_filter = NULL;

	media_content_debug_func();

	if(group_name != NULL)
		select_query = sqlite3_mprintf(SELECT_MEDIA_FROM_GROUP, __media_db_get_group_name(group), group_name);
	else
		select_query = sqlite3_mprintf(SELECT_MEDIA_FROM_GROUP_NULL, __media_db_get_group_name(group));

	if(filter != NULL)
	{
		_filter = (filter_s*)filter;

		if(_filter->condition)
		{
			ret = _media_filter_attribute_generate(_content_get_attirbute_handle(), _filter->condition, _filter->condition_collate_type, &condition_query);
			if(ret != MEDIA_CONTENT_ERROR_NONE)
			{
				sqlite3_free(select_query);
				return ret;
			}
		}

		ret = _media_filter_attribute_option_generate(_content_get_attirbute_handle(), filter, &option_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			sqlite3_free(select_query);
			SAFE_FREE(condition_query);
			return ret;
		}

		if(STRING_VALID(condition_query))
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s %s", select_query, QUERY_KEYWORD_AND);
		}
		else
		{
			snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
		}
	} else {
		snprintf(complete_select_query, sizeof(complete_select_query), "%s", select_query);
	}

	ret = _content_query_prepare(&stmt, complete_select_query, condition_query, option_query);
	sqlite3_free(select_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if(item == NULL)
		{
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if(callback((media_info_h)item, user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}

		media_info_destroy((media_info_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
