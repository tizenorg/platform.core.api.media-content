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
static int __media_db_make_query(filter_h filter, attribute_h attr, char *select_query, int select_query_size, char **condition_query, char **option_query);

static char * __media_db_get_group_name(media_group_e group)
{
	switch (group) {
	case MEDIA_CONTENT_GROUP_DISPLAY_NAME:
		return (char *)DB_FIELD_MEDIA_DISPLAY_NAME;
	case MEDIA_CONTENT_GROUP_TYPE:
		return (char *)DB_FIELD_MEDIA_TYPE;
	case MEDIA_CONTENT_GROUP_MIME_TYPE:
		return (char *) DB_FIELD_MEDIA_MIME_TYPE;
	case MEDIA_CONTENT_GROUP_SIZE:
		return (char *) DB_FIELD_MEDIA_SIZE;
	case MEDIA_CONTENT_GROUP_ADDED_TIME:
		return (char *) DB_FIELD_MEDIA_ADDED_TIME;
	case MEDIA_CONTENT_GROUP_MODIFIED_TIME:
		return (char *) DB_FIELD_MEDIA_MODIFIED_TIME;
	case MEDIA_CONTENT_GROUP_TITLE:
		return (char *) DB_FIELD_MEDIA_TITLE;
	case MEDIA_CONTENT_GROUP_ARTIST:
		return (char *) DB_FIELD_MEDIA_ARTIST;
	case MEDIA_CONTENT_GROUP_ALBUM_ARTIST:
		return (char *) DB_FIELD_MEDIA_ALBUM_ARTIST;
	case MEDIA_CONTENT_GROUP_GENRE:
		return (char *) DB_FIELD_MEDIA_GENRE;
	case MEDIA_CONTENT_GROUP_COMPOSER:
		return (char *) DB_FIELD_MEDIA_COMPOSER;
	case MEDIA_CONTENT_GROUP_YEAR:
		return (char *) DB_FIELD_MEDIA_YEAR;
	case MEDIA_CONTENT_GROUP_RECORDED_DATE:
		return (char *) DB_FIELD_MEDIA_RECORDED_DATE;
	case MEDIA_CONTENT_GROUP_COPYRIGHT:
		return (char *) DB_FIELD_MEDIA_COPYRIGHT;
	case MEDIA_CONTENT_GROUP_TRACK_NUM:
		return (char *) DB_FIELD_MEDIA_TRACK_NUM;
	case MEDIA_CONTENT_GROUP_DESCRIPTION:
		return (char *) DB_FIELD_MEDIA_DESCRIPTION;
	case MEDIA_CONTENT_GROUP_LONGITUDE:
		return (char *) DB_FIELD_MEDIA_LONGITUDE;
	case MEDIA_CONTENT_GROUP_LATITUDE:
		return (char *) DB_FIELD_MEDIA_LATITUDE;
	case MEDIA_CONTENT_GROUP_ALTITUDE:
		return (char *) DB_FIELD_MEDIA_ALTITUDE;
	case MEDIA_CONTENT_GROUP_BURST_IMAGE:
		return (char *) DB_FIELD_MEDIA_BURST_ID;
	case MEDIA_CONTENT_GROUP_RATING:
		return (char *) DB_FIELD_MEDIA_RATING;
	case MEDIA_CONTENT_GROUP_AUTHOR:
		return (char *) DB_FIELD_MEDIA_AUTHOR;
	case MEDIA_CONTENT_GROUP_PROVIDER:
		return (char *) DB_FIELD_MEDIA_PROVIDER;
	case MEDIA_CONTENT_GROUP_CONTENT_NAME:
		return (char *) DB_FIELD_MEDIA_CONTENT_NAME;
	case MEDIA_CONTENT_GROUP_CATEGORY:
		return (char *) DB_FIELD_MEDIA_CATEGORY;
	case MEDIA_CONTENT_GROUP_LOCATION_TAG:
		return (char *) DB_FIELD_MEDIA_LOCATION_TAG;
	case MEDIA_CONTENT_GROUP_AGE_RATING:
		return (char *) DB_FIELD_MEDIA_AGE_RATING;
	case MEDIA_CONTENT_GROUP_KEYWORD:
		return (char *) DB_FIELD_MEDIA_KEYWORD;
	case MEDIA_CONTENT_GROUP_WEATHER:
		return (char *) DB_FIELD_MEDIA_WEATHER;
#ifdef _USE_TV_PROFILE
	case MEDIA_CONTENT_GROUP_MODIFIED_MONTH:
		return (char *) DB_FIELD_MEDIA_MODIFIED_DATE;
	case MEDIA_CONTENT_GROUP_MODIFIED_DATE:
		return (char *) DB_FIELD_MEDIA_MODIFIED_DATE;
#endif
#ifdef _USE_SENIOR_MODE
	case MEDIA_CONTENT_GROUP_CONTACT:
		return (char *) DB_FIELD_MEDIA_CONTACT;
#endif
#ifdef _USE_TV_PROFILE
	case MEDIA_CONTENT_GROUP_ALBUM:
		return (char *) DB_FIELD_MEDIA_ALBUM;
	case MEDIA_PVR_GROUP_DURATION:
		return (char *) DB_FIELD_PVR_DURATION;
	case MEDIA_PVR_GROUP_TIME_ZONE:
		return (char *) DB_FIELD_PVR_TIME_ZONE;
	case MEDIA_PVR_GROUP_PTC:
		return (char *) DB_FIELD_PVR_PTC;
	case MEDIA_PVR_GROUP_MAJOR:
		return (char *) DB_FIELD_PVR_MAJOR;
	case MEDIA_PVR_GROUP_MINOR:
		return (char *) DB_FIELD_PVR_MINOR;
	case MEDIA_PVR_GROUP_CHANNEL_TYPE:
		return (char *) DB_FIELD_PVR_CHANNEL_TYPE;
	case MEDIA_PVR_GROUP_CHANNEL_NAME:
		return (char *) DB_FIELD_PVR_CHANNEL_NAME;
	case MEDIA_PVR_GROUP_CHANNEL_NUM:
		return (char *) DB_FIELD_PVR_CHANNEL_NUM;
	case MEDIA_PVR_GROUP_PROGRAM_TITLE:
		return (char *) DB_FIELD_PVR_PROGRAM_TITLE;
	case MEDIA_PVR_GROUP_PROGRAM_NUM:
		return (char *) DB_FIELD_PVR_PROGRAM_NUM;
	case MEDIA_PVR_GROUP_PROGRAM_CRID:
		return (char *) DB_FIELD_PVR_PROGRAM_CRID;
	case MEDIA_PVR_GROUP_GUIDANCE:
		return (char *) DB_FIELD_PVR_GUIDANCE;
	case MEDIA_PVR_GROUP_SYNOPSIS:
		return (char *) DB_FIELD_PVR_SYNOPSIS;
	case MEDIA_PVR_GROUP_GENRE:
		return (char *) DB_FIELD_PVR_GENRE;
	case MEDIA_PVR_GROUP_LANGUAGE:
		return (char *) DB_FIELD_PVR_LANGUAGE;
	case MEDIA_PVR_GROUP_EMBARGO_TIME:
		return (char *) DB_FIELD_PVR_EMBARGO_TIME;
	case MEDIA_PVR_GROUP_EXPIRY_TIME:
		return (char *) DB_FIELD_PVR_EXPIRY_TIME;
	case MEDIA_PVR_GROUP_START_TIME:
		return (char *) DB_FIELD_PVR_START_TIME;
	case MEDIA_PVR_GROUP_PROGRAM_START_TIME:
		return (char *) DB_FIELD_PVR_PROGRAM_START_TIME;
	case MEDIA_PVR_GROUP_PROGRAM_END_TIME:
		return (char *) DB_FIELD_PVR_PROGRAM_END_TIME;
	case MEDIA_PVR_GROUP_PROGRAM_DATE:
		return (char *) DB_FIELD_PVR_PROGRAM_DATE;
	case MEDIA_PVR_GROUP_PARENTAL_RATING:
		return (char *) DB_FIELD_PVR_PARENTAL_RATING;
	case MEDIA_PVR_GROUP_TIMER_RECORD:
		return (char *) DB_FIELD_PVR_TIMER_RECORD;
	case MEDIA_PVR_GROUP_SERIES_RECORD:
		return (char *) DB_FIELD_PVR_SERIES_RECORD;
	case MEDIA_PVR_GROUP_HD:
		return (char *) DB_FIELD_PVR_HD;
	case MEDIA_PVR_GROUP_SUBTITLE:
		return (char *) DB_FIELD_PVR_SUBTITLE;
	case MEDIA_PVR_GROUP_TTX:
		return (char *) DB_FIELD_PVR_TTX;
	case MEDIA_PVR_GROUP_AD:
		return (char *) DB_FIELD_PVR_AD;
	case MEDIA_PVR_GROUP_HARDOF_HEARINGRADIO:
		return (char *) DB_FIELD_PVR_HARDOF_HEARINGRADIO;
	case MEDIA_PVR_GROUP_DATA_SERVICE:
		return (char *) DB_FIELD_PVR_DATA_SERVICE;
	case MEDIA_PVR_GROUP_CONTENT_LOCK:
		return (char *) DB_FIELD_PVR_CONTENT_LOCK;
	case MEDIA_PVR_GROUP_CONTENT_WATCH:
		return (char *) DB_FIELD_PVR_CONTENT_WATCH;
	case MEDIA_PVR_GROUP_HAS_AUDIO_ONLY:
		return (char *) DB_FIELD_PVR_HAS_AUDIO_ONLY;
	case MEDIA_PVR_GROUP_IS_LOCAL_RECORDED:
		return (char *) DB_FIELD_PVR_IS_LOCAL_RECORD;
	case MEDIA_PVR_GROUP_RESOLUTION:
		return (char *) DB_FIELD_PVR_RESOLUTION;
	case MEDIA_PVR_GROUP_ASPECTRATIO:
		return (char *) DB_FIELD_PVR_ASPECTRATIO;
	case MEDIA_PVR_GROUP_MODIFIED_MONTH:
		return (char *) DB_FIELD_PVR_MODIFIED_DATE;
	case MEDIA_PVR_GROUP_MODIFIED_DATE:
		return (char *) DB_FIELD_PVR_MODIFIED_DATE;
	case MEDIA_PVR_GROUP_SPORTS_TYPE:
		return (char *) DB_FIELD_PVR_SPORTS_TYPE;
	case MEDIA_PVR_GROUP_GUIDANCE_LENGTH:
		return (char *) DB_FIELD_PVR_GUIDANCE_LENGTH;
	case MEDIA_PVR_GROUP_TVMODE:
		return (char *) DB_FIELD_PVR_TVMODE;
	case MEDIA_PVR_GROUP_PLAY_COUNT:
		return (char *) DB_FIELD_PVR_PLAY_COUNT;
	case MEDIA_PVR_GROUP_PRIVATE_DATA:
		return (char *) DB_FIELD_PVR_PRIVATE_DATA;
	case MEDIA_UHD_GROUP_CONTENT_TITLE:
		return (char *) DB_FIELD_UHD_CONTENT_TITLE;
	case MEDIA_UHD_GROUP_RELEASE_DATE:
		return (char *) DB_FIELD_UHD_RELEASE_DATE;
	case MEDIA_UHD_GROUP_SUB_TYPE:
		return (char *) DB_FIELD_UHD_SUB_TYPE;
	case MEDIA_UHD_GROUP_FILE_NAME:
		return (char *) DB_FIELD_UHD_FILE_NAME;
	case MEDIA_UHD_GROUP_PLAYED_COUNT:
		return (char *) DB_FIELD_UHD_PLAYED_COUNT;
#endif
	default:
		return NULL;
	}

	return NULL;
}

static int __media_db_make_query(filter_h filter, attribute_h attr, char *select_query, int select_query_size, char **condition_query, char **option_query)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_s *_filter = NULL;
#ifdef _USE_TV_PROFILE
	g_mutex_lock(_content_get_db_mutex());
#endif
	if (filter != NULL) {
		_filter = (filter_s*)filter;

		if (STRING_VALID(_filter->condition)) {
			/*bracket should be added to condition. If application use "OR" condition, F/W restriction condition like "validity=1" is disregared
			ex) select path from media where validity=1 and media_type=3 or media_type=1;*/
			char bracket_added_condition[MAX_QUERY_SIZE] = {0, };
			memset(bracket_added_condition, 0x00, sizeof(bracket_added_condition));

			SAFE_STRLCAT(bracket_added_condition, QUERY_KEYWORD_OPEN_BRACKET, MAX_QUERY_SIZE);
			SAFE_STRLCAT(bracket_added_condition, _filter->condition, MAX_QUERY_SIZE);
			SAFE_STRLCAT(bracket_added_condition, QUERY_KEYWORD_BRACKET, MAX_QUERY_SIZE);

			ret = _media_filter_attribute_generate(attr, bracket_added_condition, _filter->condition_collate_type, condition_query);
#ifdef _USE_TV_PROFILE
			if (ret != MEDIA_CONTENT_ERROR_NONE) {
				g_mutex_unlock(_content_get_db_mutex());
				return ret;
			}
#else
			media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
#endif
		}

		ret = _media_filter_attribute_option_generate(attr, filter, option_query);
		if (ret != MEDIA_CONTENT_ERROR_NONE) {
			SAFE_FREE(*condition_query);
#ifdef _USE_TV_PROFILE
			g_mutex_unlock(_content_get_db_mutex());
#endif
			return ret;
		}

		if (STRING_VALID(*condition_query)) {
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, select_query_size);
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_AND, select_query_size);
		}
	}
#ifdef _USE_TV_PROFILE
	g_mutex_unlock(_content_get_db_mutex());
#endif

	return ret;
}

int _media_db_get_group_count(filter_h filter, group_list_e group_type, int *group_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	switch (group_type) {
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

		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_ALBUM_COUNT, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_ALBUM_COUNT, DB_TABLE_MEDIA_VIEW);

		break;
	case MEDIA_GROUP_FOLDER:
		attr = _content_get_alias_attirbute_handle();
		if (!SAFE_STRLCPY(select_query, SELECT_FOLDER_COUNT, sizeof(select_query))) {
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}

		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_FOLDER_COUNT_BY_STORAGE_ID, _filter->storage_id, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_FOLDER_COUNT, DB_TABLE_MEDIA_VIEW);

		break;
	case MEDIA_GROUP_PLAYLIST:
		if (!SAFE_STRLCPY(select_query, SELECT_PLAYLIST_COUNT, sizeof(select_query))) {
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
		break;
	case MEDIA_GROUP_TAG:
		if (!SAFE_STRLCPY(select_query, SELECT_TAG_COUNT, sizeof(select_query))) {
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
		break;
	case MEDIA_GROUP_BOOKMARK:
		attr = _content_get_alias_attirbute_handle();

		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_COUNT, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_COUNT, DB_TABLE_MEDIA_VIEW);

		break;
	case MEDIA_GROUP_STORAGE:
		if (!SAFE_STRLCPY(select_query, SELECT_STORAGE_COUNT, sizeof(select_query))) {
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
		break;
#ifdef _USE_TV_PROFILE
	case MEDIA_GROUP_PVR:
	case MEDIA_GROUP_UHD:
#endif
	default:
		{
			media_content_error("Invalid group type [%d]", group_type);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
		break;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW)
		*group_count = (int)sqlite3_column_int(stmt, 0);

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group_count(media_group_e group, filter_h filter, int *group_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));
#ifdef _USE_TV_PROFILE
	if (group < MEDIA_PVR_GROUP_DURATION) {	/*media content*/
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_COUNT, __media_db_get_group_name(group), _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_COUNT, __media_db_get_group_name(group), DB_TABLE_MEDIA_VIEW);
	} else if (group < MEDIA_UHD_GROUP_CONTENT_TITLE) { /*pvr content*/
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_PVR_GROUP_COUNT_BY_STORAGE_ID, __media_db_get_group_name(group), _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_PVR_GROUP_COUNT, __media_db_get_group_name(group));
	} else { /*uhd content*/
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_UHD_GROUP_COUNT_BY_STORAGE_ID, __media_db_get_group_name(group), _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_UHD_GROUP_COUNT, __media_db_get_group_name(group));
	}
#else
	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_COUNT, __media_db_get_group_name(group), _filter->storage_id);
	else
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_COUNT, __media_db_get_group_name(group), DB_TABLE_MEDIA_VIEW);
#endif
	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
	if (STRING_VALID(condition_query))
		SAFE_STRLCAT(select_query, condition_query, sizeof(select_query));
	if (STRING_VALID(option_query))
		SAFE_STRLCAT(select_query, option_query, sizeof(select_query));
	SAFE_STRLCAT(select_query, QUERY_KEYWORD_BRACKET, sizeof(select_query));

	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW)
		*group_count = (int)sqlite3_column_int(stmt, 0);

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group(media_group_e group, filter_h filter, media_group_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	char *name = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));
#ifdef _USE_TV_PROFILE
	if (group < MEDIA_PVR_GROUP_DURATION) {	/*media content */
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_LIST, __media_db_get_group_name(group), _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_LIST, __media_db_get_group_name(group), DB_TABLE_MEDIA_VIEW);
	} else if (group < MEDIA_UHD_GROUP_CONTENT_TITLE) { /*pvr content */
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_PVR_GROUP_LIST_BY_STORAGE_ID, __media_db_get_group_name(group), _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_PVR_GROUP_LIST, __media_db_get_group_name(group));
	} else { /* uhd content */
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_UHD_GROUP_LIST_BY_STORAGE_ID, __media_db_get_group_name(group), _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_UHD_GROUP_LIST, __media_db_get_group_name(group));
	}
#else
	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_LIST, __media_db_get_group_name(group), _filter->storage_id);
	else
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_LIST, __media_db_get_group_name(group), DB_TABLE_MEDIA_VIEW);
#endif
	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		name = g_strdup((const char *)sqlite3_column_text(stmt, 0));

		if (callback(name, user_data) == false) {
			SAFE_FREE(name);
			break;
		}

		SAFE_FREE(name);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#ifdef _USE_TV_PROFILE
int _media_db_get_media_group_and_count(media_group_e group, filter_h filter, media_group_and_count_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char group_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	char *name = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));
	memset(group_query, 0x00, sizeof(group_query));

	char* group_name = __media_db_get_group_name(group);
	if (!STRING_VALID(group_name)) {
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);
	}

	if (group < MEDIA_PVR_GROUP_DURATION) {	/*media content*/
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_AND_COUNT, group_name, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_GROUP_AND_COUNT, group_name, DB_TABLE_MEDIA_VIEW);
	} else if (group < MEDIA_UHD_GROUP_CONTENT_TITLE) {/*pvr content*/
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_PVR_GROUP_AND_COUNT_BY_STORAGE_ID, group_name, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_PVR_GROUP_AND_COUNT, group_name);
	} else {/*uhd content*/
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_UHD_GROUP_AND_COUNT_BY_STORAGE_ID, group_name, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_UHD_GROUP_AND_COUNT, group_name);
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	if (STRING_VALID(option_query))
		snprintf(group_query, sizeof(group_query), "GROUP BY %s %s", group_name, option_query);
	else
		snprintf(group_query, sizeof(group_query), "GROUP BY %s", group_name);

	ret = _content_query_prepare(&stmt, select_query, condition_query, group_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		if (STRING_VALID((const char *)sqlite3_column_text(stmt, 0)))
			name = strdup((const char *)sqlite3_column_text(stmt, 0));

		if (callback(name, sqlite3_column_int(stmt, 1), user_data) == false) {
			SAFE_FREE(name);
			break;
		}

		SAFE_FREE(name);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#endif
int _media_db_get_album(filter_h filter, media_album_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_alias_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_ALBUM_LIST, _filter->storage_id);
	else
		snprintf(select_query, sizeof(select_query), SELECT_ALBUM_LIST, DB_TABLE_MEDIA_VIEW);

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_album_s *album = (media_album_s*)calloc(1, sizeof(media_album_s));

		if (album == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		album->album_id = (int)sqlite3_column_int(stmt, 0);
		album->name = g_strdup((const char *)sqlite3_column_text(stmt, 1));
		album->artist = g_strdup((const char *)sqlite3_column_text(stmt, 2));
		album->album_art_path = g_strdup((const char *)sqlite3_column_text(stmt, 3));

		if (callback((media_album_h)album, user_data) == false) {
			media_album_destroy((media_album_h)album);
			break;
		}

		media_album_destroy((media_album_h)album);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_folder(filter_h filter, media_folder_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_alias_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_FOLDER_LIST_BY_STORAGE_ID, _filter->storage_id, _filter->storage_id);
	else
		snprintf(select_query, sizeof(select_query), SELECT_FOLDER_LIST, DB_TABLE_MEDIA_VIEW);

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);

	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_folder_s *_folder = (media_folder_s*)calloc(1, sizeof(media_folder_s));

		if (_folder == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_folder->folder_id = g_strdup((const char *)sqlite3_column_text(stmt, 0));
		_folder->path = g_strdup((const char *)sqlite3_column_text(stmt, 1));
		_folder->name = g_strdup((const char *)sqlite3_column_text(stmt, 2));
		_folder->storage_type = (int)sqlite3_column_int(stmt, 3);
		_folder->modified_time = (int)sqlite3_column_int(stmt, 4);
		_folder->storage_uuid = g_strdup((const char *)sqlite3_column_text(stmt, 5));
		_folder->folder_order = (int)sqlite3_column_int(stmt, 6);
		_folder->parent_folder_id = g_strdup((const char *)sqlite3_column_text(stmt, 7));

		if (callback((media_folder_h)_folder, user_data) == false) {
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
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (!SAFE_STRLCPY(select_query, SELECT_PLAYLIST_LIST, sizeof(select_query))) {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_playlist_s *_playlist = (media_playlist_s*)calloc(1, sizeof(media_playlist_s));

		if (_playlist == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_playlist->playlist_id = (int)sqlite3_column_int(stmt, 0);
		_playlist->name = g_strdup((const char *)sqlite3_column_text(stmt, 1));
		_playlist->thumbnail_path = g_strdup((const char *)sqlite3_column_text(stmt, 2));

		if (callback((media_playlist_h)_playlist, user_data) == false) {
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
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	/*snprintf(select_query, sizeof(select_query), SELECT_PLAYLIST_ITEM_ID_FROM_PLAYLIST_VIEW, playlist_id);*/
	snprintf(select_query, sizeof(select_query), SELECT_PLAYLIST_ITEM_ALL_FROM_PLAYLIST_VIEW, playlist_id);

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int playlist_member_id = 0;
		playlist_member_id = (int)sqlite3_column_int(stmt, MEDIA_INFO_ITEM_MAX);	/*MEDIA_INFO_ITEM_MAX is pm_id*/

		media_info_s *_media = (media_info_s*)calloc(1, sizeof(media_info_s));

		if (_media == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)_media);

		if (callback(playlist_member_id, (media_info_h)_media, user_data) == false) {
			media_info_destroy((media_info_h)_media);
			break;
		}
		media_info_destroy((media_info_h)_media);

	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_tag(const char *media_id, filter_h filter, media_tag_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (!STRING_VALID(media_id)) {
		if (!SAFE_STRLCPY(select_query, SELECT_TAG_LIST, sizeof(select_query))) {
			media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	} else
		snprintf(select_query, sizeof(select_query), SELECT_TAG_LIST_BY_MEDIA_ID, media_id);

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_tag_s *_tag = (media_tag_s*)calloc(1, sizeof(media_tag_s));

		if (_tag == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_tag->tag_id = (int)sqlite3_column_int(stmt, 0);
		_tag->name = g_strdup((const char *)sqlite3_column_text(stmt, 1));

		if (callback((media_tag_h)_tag, user_data) == false) {
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
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();

	memset(select_query, 0x00, sizeof(select_query));

	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_LIST_BY_MEDIA_ID, _filter->storage_id, media_id);
	else
		snprintf(select_query, sizeof(select_query), SELECT_BOOKMARK_LIST_BY_MEDIA_ID, DB_TABLE_MEDIA_VIEW, media_id);

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_bookmark_s *bookmark = (media_bookmark_s*)calloc(1, sizeof(media_bookmark_s));

		if (bookmark == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		bookmark->bookmark_id = (int)sqlite3_column_int(stmt, 0);
		bookmark->media_id = g_strdup((const char *)sqlite3_column_text(stmt, 1));
		bookmark->marked_time = (int)sqlite3_column_int(stmt, 2);
		bookmark->thumbnail_path = g_strdup((const char *)sqlite3_column_text(stmt, 3));

		if (callback((media_bookmark_h)bookmark, user_data) == false) {
			media_bookmark_destroy((media_bookmark_h)bookmark);
			break;
		}

		media_bookmark_destroy((media_bookmark_h)bookmark);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;

}

int _media_db_get_face(const char *media_id, filter_h filter, media_face_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();

	memset(select_query, 0x00, sizeof(select_query));

	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_FACE_LIST_BY_MEDIA_ID, _filter->storage_id, media_id);
	else
		snprintf(select_query, sizeof(select_query), SELECT_FACE_LIST_BY_MEDIA_ID, DB_TABLE_MEDIA_VIEW, media_id);

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_face_s *face = (media_face_s*)calloc(1, sizeof(media_face_s));

		if (face == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		face->face_id = g_strdup((const char *)sqlite3_column_text(stmt, 0));
		face->media_id = g_strdup((const char *)sqlite3_column_text(stmt, 1));
		face->face_rect_x = (int)sqlite3_column_int(stmt, 2);
		face->face_rect_y = (int)sqlite3_column_int(stmt, 3);
		face->face_rect_w = (int)sqlite3_column_int(stmt, 4);
		face->face_rect_h = (int)sqlite3_column_int(stmt, 5);
		face->orientation = (int)sqlite3_column_int(stmt, 6);
		face->face_tag = g_strdup((const char *)sqlite3_column_text(stmt, 7));

		if (callback((media_face_h)face, user_data) == false) {
			media_face_destroy((media_face_h)face);
			break;
		}

		media_face_destroy((media_face_h)face);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;

}

int _media_db_get_group_item_count_by_id(int group_id, filter_h filter, group_list_e group_type, int *item_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (group_type == MEDIA_GROUP_ALBUM) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_ALBUM, _filter->storage_id, group_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_ALBUM, DB_TABLE_MEDIA_VIEW, group_id);
	} else if (group_type == MEDIA_GROUP_PLAYLIST) {
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_PLAYLIST, group_id);
	} else if (group_type == MEDIA_GROUP_TAG) {
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_TAG, group_id);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW)
		*item_count = (int)sqlite3_column_int(stmt, 0);

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_group_item_count(const char *group_name, filter_h filter, group_list_e group_type, int *item_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *tmp_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	bool is_simple = FALSE;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (group_type == MEDIA_GROUP_NONE) {
		/* There are 2 ways to get count for media table for performance
			If user wants to set offset and count, use SQL SELECT_MEDIA_COUNT_FROM_MEDIA.
			If user wants to get count without setting count, SELECT_MEDIA_COUNT_FROM_MEDIA_SIMPLE */
		if (_filter && ((_filter->offset < 0) && (_filter->count < 0))) {
				if (STRING_VALID(_filter->storage_id))
					snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_MEDIA_SIMPLE, _filter->storage_id);
				else
					snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_MEDIA_SIMPLE, DB_TABLE_MEDIA_VIEW);
				is_simple = TRUE;
		} else {
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_MEDIA, DB_TABLE_MEDIA_VIEW);
		}
	} else if (group_type == MEDIA_GROUP_FOLDER) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_FOLDER, _filter->storage_id, group_name);
		else
			tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_FOLDER, DB_TABLE_MEDIA_VIEW, group_name);

		SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
	} else if (group_type == MEDIA_GROUP_TAG_BY_MEDIA_ID) {
		snprintf(select_query, sizeof(select_query), SELECT_TAG_COUNT_BY_MEDIA_ID, group_name);
	} else if (group_type == MEDIA_GROUP_BOOKMARK_BY_MEDIA_ID) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			tmp_query = sqlite3_mprintf(SELECT_BOOKMARK_COUNT_BY_MEDIA_ID, _filter->storage_id, group_name);
		else
			tmp_query = sqlite3_mprintf(SELECT_BOOKMARK_COUNT_BY_MEDIA_ID, DB_TABLE_MEDIA_VIEW, group_name);

		SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
	} else if (group_type == MEDIA_GROUP_STORAGE) {
		tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_STORAGE, group_name, group_name);

		SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
	} else if (group_type == MEDIA_GROUP_FACE_BY_MEDIA_ID) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			tmp_query = sqlite3_mprintf(SELECT_FACE_COUNT_BY_MEDIA_ID, _filter->storage_id, group_name);
		else
			tmp_query = sqlite3_mprintf(SELECT_FACE_COUNT_BY_MEDIA_ID, DB_TABLE_MEDIA_VIEW, group_name);

		SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
#ifdef _USE_TV_PROFILE
	} else if (group_type == MEDIA_GROUP_PVR) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_PVR_COUNT_BY_STORAGE_ID, _filter->storage_id);
		else
			SAFE_STRLCAT(select_query, SELECT_PVR_COUNT, sizeof(select_query));
	} else if (group_type == MEDIA_GROUP_UHD) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_UHD_COUNT_BY_STORAGE_ID, _filter->storage_id);
		else
			SAFE_STRLCAT(select_query, SELECT_UHD_COUNT, sizeof(select_query));
#endif
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		if (tmp_query != NULL)
			SQLITE3_SAFE_FREE(tmp_query);
		return ret;
	}

	if (group_type == MEDIA_GROUP_NONE) {
		SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
		if (STRING_VALID(condition_query))
			SAFE_STRLCAT(select_query, condition_query, sizeof(select_query));
		if (STRING_VALID(option_query))
			SAFE_STRLCAT(select_query, option_query, sizeof(select_query));

		if (!is_simple)
			SAFE_STRLCAT(select_query, QUERY_KEYWORD_BRACKET, sizeof(select_query));

		SAFE_FREE(condition_query);
		SAFE_FREE(option_query);
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	if (tmp_query != NULL)
		SQLITE3_SAFE_FREE(tmp_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW)
		*item_count = (int)sqlite3_column_int(stmt, 0);

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_group_item_by_id(int group_id, filter_h filter, media_info_cb callback, void *user_data, group_list_e group_type)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (group_type == MEDIA_GROUP_ALBUM) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_ALBUM, _filter->storage_id, group_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_ALBUM, DB_TABLE_MEDIA_VIEW, group_id);
	} else if (group_type == MEDIA_GROUP_PLAYLIST) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_PLAYLIST, _filter->storage_id, group_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_PLAYLIST, DB_TABLE_MEDIA_VIEW, group_id);
	} else if (group_type == MEDIA_GROUP_TAG) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_TAG, _filter->storage_id, group_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_TAG, DB_TABLE_MEDIA_VIEW, group_id);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if (item == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if (callback((media_info_h)item, user_data) == false) {
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
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (group_type == MEDIA_GROUP_NONE) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_ITEM, _filter->storage_id);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_ITEM, DB_TABLE_MEDIA_VIEW);
	} else if (group_type == MEDIA_GROUP_FOLDER) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_FOLDER, _filter->storage_id, group_name);
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_FOLDER, DB_TABLE_MEDIA_VIEW, group_name);
	} else if (group_type == MEDIA_GROUP_STORAGE) {
		snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_STORAGE, group_name, group_name);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if (item == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if (callback((media_info_h)item, user_data) == false) {
			media_info_destroy((media_info_h)item);
			break;
		}

		media_info_destroy((media_info_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

#ifdef _USE_SENIOR_MODE
int _media_db_get_group_item_by_union_select(const char *group_name, filter_h filter1, filter_h filter2, media_info_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query1[MAX_QUERY_SIZE] = {0, };
	char *condition_query1 = NULL;
	char *option_query1 = NULL;
	char select_query2[MAX_QUERY_SIZE] = {0, };
	char *condition_query2 = NULL;
	char *option_query2 = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter1 = (filter_s*)filter1;
	filter_s *_filter2 = (filter_s*)filter2;

	attr = _content_get_attirbute_handle();

	memset(select_query1, 0x00, sizeof(select_query1));

	if ((_filter1 != NULL) && STRING_VALID(_filter1->storage_id))
		snprintf(select_query1, sizeof(select_query1), SELECT_MEDIA_FROM_FOLDER, _filter1->storage_id, group_name);
	else
		snprintf(select_query1, sizeof(select_query1), SELECT_MEDIA_FROM_FOLDER, DB_TABLE_MEDIA_VIEW, group_name);

	ret = __media_db_make_query(filter1, attr, select_query1, sizeof(select_query1), &condition_query1, &option_query1);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		SAFE_FREE(condition_query1);
		SAFE_FREE(option_query1);
		media_content_error("create select_query1 failed");
		return ret;
	}

	memset(select_query2, 0x00, sizeof(select_query2));

	if ((_filter2 != NULL) && STRING_VALID(_filter2->storage_id))
		snprintf(select_query2, sizeof(select_query2), SELECT_MEDIA_FROM_FOLDER, _filter2->storage_id, group_name);
	else
		snprintf(select_query2, sizeof(select_query2), SELECT_MEDIA_FROM_FOLDER, DB_TABLE_MEDIA_VIEW, group_name);

	ret = __media_db_make_query(filter2, attr, select_query2, sizeof(select_query2), &condition_query2, &option_query2);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		SAFE_FREE(condition_query1);
		SAFE_FREE(option_query1);
		SAFE_FREE(condition_query2);
		SAFE_FREE(option_query2);
		media_content_error("create select_query2 failed");
		return ret;
	}

	ret = _content_query_prepare_by_union_select(&stmt, select_query1, condition_query1, option_query1, select_query2, condition_query2, option_query2);
	SAFE_FREE(condition_query1);
	SAFE_FREE(option_query1);
	SAFE_FREE(condition_query2);
	SAFE_FREE(option_query2);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if (item == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if (callback((media_info_h)item, user_data) == false) {
			media_info_destroy((media_info_h)item);
			break;
		}

		media_info_destroy((media_info_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#endif

int _media_db_get_media_group_item_count(const char *group_name, filter_h filter, media_group_e group, int *item_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *tmp_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));
#ifdef _USE_TV_PROFILE
	if (group < MEDIA_PVR_GROUP_DURATION) { /*media content */
		if (group_name != NULL) {
			if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
				tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_GROUP, _filter->storage_id, __media_db_get_group_name(group), group_name);
			else
				tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_GROUP, DB_TABLE_MEDIA_VIEW, __media_db_get_group_name(group), group_name);

			SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
		} else {
			if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
				snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_GROUP_NULL, _filter->storage_id, __media_db_get_group_name(group));
			else
				snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_GROUP_NULL, DB_TABLE_MEDIA_VIEW, __media_db_get_group_name(group));
		}
	} else if (group < MEDIA_UHD_GROUP_CONTENT_TITLE) {/*pvr content*/
		if (group_name != NULL) {
			if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
				tmp_query = sqlite3_mprintf(SELECT_PVR_COUNT_FROM_GROUP_BY_STORAGE_ID, _filter->storage_id, __media_db_get_group_name(group), group_name);
			else
				tmp_query = sqlite3_mprintf(SELECT_PVR_COUNT_FROM_GROUP, __media_db_get_group_name(group), group_name);

			SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
		} else {
			if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
				snprintf(select_query, sizeof(select_query), SELECT_PVR_COUNT_FROM_GROUP_NULL_BY_STORAGE_ID, _filter->storage_id, __media_db_get_group_name(group));
			else
				snprintf(select_query, sizeof(select_query), SELECT_PVR_COUNT_FROM_GROUP_NULL, __media_db_get_group_name(group));
		}
	} else {/*uhd content*/
		if (group_name != NULL) {
			if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
				tmp_query = sqlite3_mprintf(SELECT_UHD_COUNT_FROM_GROUP_BY_STORAGE_ID, _filter->storage_id, __media_db_get_group_name(group), group_name);
			else
				tmp_query = sqlite3_mprintf(SELECT_UHD_COUNT_FROM_GROUP, __media_db_get_group_name(group), group_name);

			SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
		} else {
			if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
				snprintf(select_query, sizeof(select_query), SELECT_UHD_COUNT_FROM_GROUP_NULL_BY_STORAGE_ID, _filter->storage_id, __media_db_get_group_name(group));
			else
				snprintf(select_query, sizeof(select_query), SELECT_UHD_COUNT_FROM_GROUP_NULL, __media_db_get_group_name(group));
		}
	}
#else
	if (group_name != NULL) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id)) {
			tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_GROUP, _filter->storage_id, __media_db_get_group_name(group), group_name);
			SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
		} else {
			tmp_query = sqlite3_mprintf(SELECT_MEDIA_COUNT_FROM_GROUP, DB_TABLE_MEDIA_VIEW, __media_db_get_group_name(group), group_name);
			SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
		}
	} else {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_GROUP_NULL, _filter->storage_id, __media_db_get_group_name(group));
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_COUNT_FROM_GROUP_NULL, DB_TABLE_MEDIA_VIEW, __media_db_get_group_name(group));
	}
#endif
	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		if (tmp_query != NULL)
			SQLITE3_SAFE_FREE(tmp_query);
		return ret;
	}

	SAFE_STRLCAT(select_query, QUERY_KEYWORD_SPACE, sizeof(select_query));
	if (STRING_VALID(condition_query))
		SAFE_STRLCAT(select_query, condition_query, sizeof(select_query));
	if (STRING_VALID(option_query))
		SAFE_STRLCAT(select_query, option_query, sizeof(select_query));
	SAFE_STRLCAT(select_query, QUERY_KEYWORD_BRACKET, sizeof(select_query));

	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	if (tmp_query != NULL)
		SQLITE3_SAFE_FREE(tmp_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW)
		*item_count = (int)sqlite3_column_int(stmt, 0);

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_media_group_item(const char *group_name, filter_h filter, media_group_e group, media_info_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[MAX_QUERY_SIZE] = {0, };
	char *tmp_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (group_name != NULL) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			tmp_query = sqlite3_mprintf(SELECT_MEDIA_FROM_GROUP, _filter->storage_id, __media_db_get_group_name(group), group_name);
		else
			tmp_query = sqlite3_mprintf(SELECT_MEDIA_FROM_GROUP, DB_TABLE_MEDIA_VIEW, __media_db_get_group_name(group), group_name);

		SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
	} else {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_GROUP_NULL, _filter->storage_id, __media_db_get_group_name(group));
		else
			snprintf(select_query, sizeof(select_query), SELECT_MEDIA_FROM_GROUP_NULL, DB_TABLE_MEDIA_VIEW, __media_db_get_group_name(group));
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		if (tmp_query != NULL)
			SQLITE3_SAFE_FREE(tmp_query);
		return ret;
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	if (tmp_query != NULL)
		SQLITE3_SAFE_FREE(tmp_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_info_s *item = (media_info_s*)calloc(1, sizeof(media_info_s));
		if (item == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_info_item_get_detail(stmt, (media_info_h)item);

		if (callback((media_info_h)item, user_data) == false) {
			media_info_destroy((media_info_h)item);
			break;
		}

		media_info_destroy((media_info_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

int _media_db_get_storage(filter_h filter, media_storage_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (!SAFE_STRLCPY(select_query, SELECT_STORAGE_LIST, sizeof(select_query))) {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_storage_s *_storage = (media_storage_s*)calloc(1, sizeof(media_storage_s));

		if (_storage == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_storage->storage_id = g_strdup((const char *)sqlite3_column_text(stmt, 0));
		_storage->storage_name = g_strdup((const char *)sqlite3_column_text(stmt, 1));
		_storage->storage_path = g_strdup((const char *)sqlite3_column_text(stmt, 2));
		_storage->storage_account = g_strdup((const char *)sqlite3_column_text(stmt, 3));
		_storage->storage_type = (int)sqlite3_column_int(stmt, 4);

		if (callback((media_storage_h)_storage, user_data) == false) {
			media_storage_destroy((media_storage_h) _storage);
			break;
		}

		media_storage_destroy((media_storage_h) _storage);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#ifdef _USE_TV_PROFILE
int _media_db_get_pvr_group_item(const char *group_name, filter_h filter, media_group_e group, media_pvr_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *tmp_query = NULL;
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if (group_name != NULL) {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			tmp_query = sqlite3_mprintf(SELECT_PVR_FROM_GROUP_BY_STORAGE_ID, _filter->storage_id, __media_db_get_group_name(group), group_name);
		else
			tmp_query = sqlite3_mprintf(SELECT_PVR_FROM_GROUP, __media_db_get_group_name(group), group_name);

		SAFE_STRLCAT(select_query, tmp_query, sizeof(select_query));
	} else {
		if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
			snprintf(select_query, sizeof(select_query), SELECT_PVR_FROM_GROUP_NULL_BY_STORAGE_ID, _filter->storage_id, __media_db_get_group_name(group));
		else
			snprintf(select_query, sizeof(select_query), SELECT_PVR_FROM_GROUP_NULL, __media_db_get_group_name(group));
	}

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		if (tmp_query != NULL)
			sqlite3_free(tmp_query);
		return ret;
	}

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	if (tmp_query != NULL)
		sqlite3_free(tmp_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_pvr_s *item = (media_pvr_s*)calloc(1, sizeof(media_pvr_s));
		if (item == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_pvr_item_get_detail(stmt, (media_pvr_h)item);

		if (callback((media_pvr_h)item, user_data) == false) {
			media_info_destroy((media_pvr_h)item);
			break;
		}

		media_pvr_destroy((media_pvr_h)item);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}

typedef enum {
	MEDIA_PVR_MEDIA_ID = 0,
	MEDIA_PVR_STORAGE_ID,
	MEDIA_PVR_PATH,
	MEDIA_PVR_SIZE,
	MEDIA_PVR_DURATION,
	MEDIA_PVR_TIME_ZONE,
	MEDIA_PVR_PTC,
	MEDIA_PVR_MAJOR,
	MEDIA_PVR_MINOR,
	MEDIA_PVR_CHANNEL_TYPE,
	MEDIA_PVR_CHANNEL_NAME,
	MEDIA_PVR_CHANNEL_NUM,
	MEDIA_PVR_PROGRAM_TITLE,
	MEDIA_PVR_PROGRAM_NUM,
	MEDIA_PVR_PROGRAM_CRID,
	MEDIA_PVR_GUIDANCE,
	MEDIA_PVR_SYNOPSIS,
	MEDIA_PVR_GENRE,
	MEDIA_PVR_LANGUAGE,
	MEDIA_PVR_EMBARGO_TIME,
	MEDIA_PVR_EXPIRY_TIME,
	MEDIA_PVR_START_TIME,
	MEDIA_PVR_PROGRAM_START_TIME,
	MEDIA_PVR_PROGRAM_END_TIME,
	MEDIA_PVR_PROGRAM_DATE,
	MEDIA_PVR_PARENTAL_RATING,
	MEDIA_PVR_TIMER_RECORD,
	MEDIA_PVR_SERIES_RECORD,
	MEDIA_PVR_HD,
	MEDIA_PVR_SUBTITLE,
	MEDIA_PVR_TTX,
	MEDIA_PVR_AD,
	MEDIA_PVR_HARDOF_HEARINGRADIO,
	MEDIA_PVR_DATA_SERVICE,
	MEDIA_PVR_CONTENT_LOCK,
	MEDIA_PVR_CONTENT_WATCH,
	MEDIA_PVR_HAS_AUDIO_ONLY,
	MEDIA_PVR_IS_LOCAL_RECORDED,
	MEDIA_PVR_RESOLUTION,
	MEDIA_PVR_ASPECTRATIO,
	MEDIA_PVR_MODIFIED_MONTH,
	MEDIA_PVR_SPORTS_TYPE,
	MEDIA_PVR_GUIDANCE_LENGTH,
	MEDIA_PVR_TVMODE,
	MEDIA_PVR_PLAY_COUNT,
	MEDIA_PVR_PRIVATE_DATA,
	MEDIA_PVR_HIGHLIGHT,
} media_pvr_field_e;

void _media_pvr_item_get_detail(sqlite3_stmt* stmt, media_pvr_h pvr)
{
	media_pvr_s *_pvr = (media_pvr_s*)pvr;

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_MEDIA_ID)))
		_pvr->media_id = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_MEDIA_ID));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_STORAGE_ID)))
		_pvr->storage_id = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_STORAGE_ID));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PATH)))
		_pvr->path = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PATH));

	_pvr->size = (unsigned long long)sqlite3_column_int64(stmt, MEDIA_PVR_SIZE);

	_pvr->duration = (int)sqlite3_column_int(stmt, MEDIA_PVR_DURATION);

	_pvr->timezone = (int)sqlite3_column_int(stmt, MEDIA_PVR_TIME_ZONE);

	_pvr->ptc = (int)sqlite3_column_int(stmt, MEDIA_PVR_PTC);

	_pvr->major = (int)sqlite3_column_int(stmt, MEDIA_PVR_MAJOR);

	_pvr->minor = (int)sqlite3_column_int(stmt, MEDIA_PVR_MINOR);

	_pvr->channel_type = (int)sqlite3_column_int(stmt, MEDIA_PVR_CHANNEL_TYPE);

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_CHANNEL_NAME)))
		_pvr->channel_name = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_CHANNEL_NAME));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_CHANNEL_NUM)))
		_pvr->channel_num = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_CHANNEL_NUM));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PROGRAM_TITLE)))
		_pvr->program_title = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PROGRAM_TITLE));

	_pvr->program_num = (int)sqlite3_column_int(stmt, MEDIA_PVR_PROGRAM_NUM);

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PROGRAM_CRID)))
		_pvr->program_crid = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PROGRAM_CRID));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_GUIDANCE)))
		_pvr->guidance = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_GUIDANCE));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_SYNOPSIS)))
		_pvr->synopsis = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_SYNOPSIS));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_GENRE)))
		_pvr->genre = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_GENRE));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_LANGUAGE)))
		_pvr->language = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_LANGUAGE));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_MODIFIED_MONTH)))
		_pvr->modified_month = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_MODIFIED_MONTH));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PRIVATE_DATA)))
		_pvr->private_data = strdup((const char *)sqlite3_column_text(stmt, MEDIA_PVR_PRIVATE_DATA));

	_pvr->embargo_time = (int)sqlite3_column_int(stmt, MEDIA_PVR_EMBARGO_TIME);

	_pvr->expiry_time = (int)sqlite3_column_int(stmt, MEDIA_PVR_EXPIRY_TIME);

	_pvr->start_time = (int)sqlite3_column_int(stmt, MEDIA_PVR_START_TIME);

	_pvr->program_start_time = (int)sqlite3_column_int(stmt, MEDIA_PVR_PROGRAM_START_TIME);

	_pvr->program_end_time = (int)sqlite3_column_int(stmt, MEDIA_PVR_PROGRAM_END_TIME);

	_pvr->program_date = (int)sqlite3_column_int(stmt, MEDIA_PVR_PROGRAM_DATE);

	_pvr->parental_rating = (int)sqlite3_column_int(stmt, MEDIA_PVR_PARENTAL_RATING);

	_pvr->timer_record = (int)sqlite3_column_int(stmt, MEDIA_PVR_TIMER_RECORD);

	_pvr->series_record = (int)sqlite3_column_int(stmt, MEDIA_PVR_SERIES_RECORD);

	_pvr->hd = (int)sqlite3_column_int(stmt, MEDIA_PVR_HD);

	_pvr->subtitle = (int)sqlite3_column_int(stmt, MEDIA_PVR_SUBTITLE);

	_pvr->ttx = (int)sqlite3_column_int(stmt, MEDIA_PVR_TTX);

	_pvr->ad = (int)sqlite3_column_int(stmt, MEDIA_PVR_AD);

	_pvr->hard_of_hearing_radio = (int)sqlite3_column_int(stmt, MEDIA_PVR_HARDOF_HEARINGRADIO);

	_pvr->data_service = (int)sqlite3_column_int(stmt, MEDIA_PVR_DATA_SERVICE);

	_pvr->content_lock = (int)sqlite3_column_int(stmt, MEDIA_PVR_CONTENT_LOCK);

	_pvr->content_watch = (int)sqlite3_column_int(stmt, MEDIA_PVR_CONTENT_WATCH);

	_pvr->has_audio_only = (int)sqlite3_column_int(stmt, MEDIA_PVR_HAS_AUDIO_ONLY);

	_pvr->is_local_record = (int)sqlite3_column_int(stmt, MEDIA_PVR_IS_LOCAL_RECORDED);

	_pvr->resolution = (int)sqlite3_column_int(stmt, MEDIA_PVR_RESOLUTION);

	_pvr->aspectratio = (int)sqlite3_column_int(stmt, MEDIA_PVR_ASPECTRATIO);

	_pvr->sports_type = (int)sqlite3_column_int(stmt, MEDIA_PVR_SPORTS_TYPE);

	_pvr->guidance_length = (int)sqlite3_column_int(stmt, MEDIA_PVR_GUIDANCE_LENGTH);

	_pvr->tvmode = (int)sqlite3_column_int(stmt, MEDIA_PVR_TVMODE);

	_pvr->play_count = (int)sqlite3_column_int(stmt, MEDIA_PVR_PLAY_COUNT);

	_pvr->highlight = (int)sqlite3_column_int(stmt, MEDIA_PVR_HIGHLIGHT);

	return;
}

int _media_db_get_pvr(filter_h filter, media_pvr_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_PVR_LIST_BY_STORAGE_ID, _filter->storage_id);
	else
		SAFE_STRLCAT(select_query, SELECT_PVR_LIST, sizeof(select_query));

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_pvr_s *_pvr = (media_pvr_s*)calloc(1, sizeof(media_pvr_s));

		if (_pvr == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_pvr_item_get_detail(stmt, (media_pvr_h)_pvr);

		if (callback((media_pvr_h)_pvr, user_data) == false) {
			media_pvr_destroy((media_pvr_h) _pvr);
			break;
		}

		media_pvr_destroy((media_pvr_h) _pvr);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#endif

int _media_db_get_storage_id_by_media_id(const char *media_id, char *storage_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	char *select_query = NULL;

	select_query = sqlite3_mprintf(SELECT_MEDIA_STORAGE_ID_BY_ID, media_id);

	ret = _content_query_prepare(&stmt, select_query, NULL, NULL);
	SQLITE3_SAFE_FREE(select_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		if (STRING_VALID((const char *)sqlite3_column_text(stmt, 0)))
			strncpy(storage_id, (const char *)sqlite3_column_text(stmt, 0), MEDIA_CONTENT_UUID_SIZE);
	} else {
		media_content_error("There's no media!!");
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#ifdef _USE_TV_PROFILE
typedef enum {
	MEDIA_UHD_MEDIA_ID = 0,
	MEDIA_UHD_STORAGE_ID,
	MEDIA_UHD_PATH,
	MEDIA_UHD_SIZE,
	MEDIA_UHD_CONTENT_ID,
	MEDIA_UHD_CONTENT_TITLE,
	MEDIA_UHD_FILE_NAME,
	MEDIA_UHD_FOLDER_ID,
	MEDIA_UHD_RELEASE_DATE,
	MEDIA_UHD_MODIFIED_TIME,
	MEDIA_UHD_PLAYED_POSITION,
	MEDIA_UHD_SUB_TYPE,
	MEDIA_UHD_PLAYED_COUNT,
} media_uhd_field_e;

void _media_uhd_item_get_detail(sqlite3_stmt* stmt, media_uhd_h uhd)
{
	media_uhd_s *_uhd = (media_uhd_s*)uhd;

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_MEDIA_ID)))
		_uhd->media_id = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_MEDIA_ID));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_STORAGE_ID)))
		_uhd->storage_id = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_STORAGE_ID));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_PATH)))
		_uhd->path = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_PATH));

	_uhd->size = (unsigned long long)sqlite3_column_int64(stmt, MEDIA_UHD_SIZE);

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_CONTENT_ID)))
		_uhd->content_id = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_CONTENT_ID));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_CONTENT_TITLE)))
		_uhd->content_title = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_CONTENT_TITLE));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_FILE_NAME)))
		_uhd->file_name = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_FILE_NAME));

	if (STRING_VALID((const char *)sqlite3_column_text(stmt, MEDIA_UHD_RELEASE_DATE)))
		_uhd->release_date = strdup((const char *)sqlite3_column_text(stmt, MEDIA_UHD_RELEASE_DATE));

	_uhd->modified_time = (int)sqlite3_column_int(stmt, MEDIA_UHD_MODIFIED_TIME);
	_uhd->played_position = (int)sqlite3_column_int(stmt, MEDIA_UHD_PLAYED_POSITION);
	_uhd->sub_type = (int)sqlite3_column_int(stmt, MEDIA_UHD_SUB_TYPE);
	_uhd->played_count = (int)sqlite3_column_int(stmt, MEDIA_UHD_PLAYED_COUNT);

	return;
}

int _media_db_get_uhd(filter_h filter, media_uhd_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	char *condition_query = NULL;
	char *option_query = NULL;
	sqlite3_stmt *stmt = NULL;
	attribute_h attr = NULL;
	filter_s *_filter = (filter_s*)filter;

	attr = _content_get_attirbute_handle();
	memset(select_query, 0x00, sizeof(select_query));

	if ((_filter != NULL) && STRING_VALID(_filter->storage_id))
		snprintf(select_query, sizeof(select_query), SELECT_UHD_LIST_BY_STORAGE_ID, _filter->storage_id);
	else
		SAFE_STRLCAT(select_query, SELECT_UHD_LIST, sizeof(select_query));

	ret = __media_db_make_query(filter, attr, select_query, sizeof(select_query), &condition_query, &option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	ret = _content_query_prepare(&stmt, select_query, condition_query, option_query);
	SAFE_FREE(condition_query);
	SAFE_FREE(option_query);
	media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		media_uhd_s *_uhd = (media_uhd_s*)calloc(1, sizeof(media_uhd_s));

		if (_uhd == NULL) {
			media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			SQLITE3_FINALIZE(stmt);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_media_uhd_item_get_detail(stmt, (media_uhd_h)_uhd);

		if (callback((media_uhd_h)_uhd, user_data) == false) {
			media_uhd_destroy((media_uhd_h) _uhd);
			break;
		}
		media_uhd_destroy((media_uhd_h) _uhd);
	}

	SQLITE3_FINALIZE(stmt);

	return ret;
}
#endif
