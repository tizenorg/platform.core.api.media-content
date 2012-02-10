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
#include <audio-svc.h>
#include <audio-svc-error.h>
#include <audio-svc-types.h>
#include <visual-svc-types.h>
#include <visual-svc.h>

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"



int media_folder_foreach_media_from_db(media_folder_h folder,media_info_filter_h filter,media_info_cb callback, void* user_data)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;
	char limit_query[MIN_QUERY_SIZE];
	char condition_query[DEFAULT_QUERY_SIZE];	
	char search_query[MAX_KEYWORD_SIZE];
	char condition_type[MIN_QUERY_SIZE];
	char select_query1[DEFAULT_QUERY_SIZE];	
	char order_query[MIN_QUERY_SIZE];

	sqlite3_stmt *stmt = NULL;
	media_info_filter_s* _filter = NULL;

	media_folder_s* _folder = (media_folder_s*)folder;

	if(_folder == NULL || callback == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
	{
		_filter = (media_info_filter_s*)filter;
		
		if(!(_filter->media_type & (MEDIA_CONTENT_TYPE_IMAGE | MEDIA_CONTENT_TYPE_VIDEO | MEDIA_CONTENT_TYPE_AUDIO)) )
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}	
	else
	{
		ret = media_info_filter_create((media_info_filter_h*)&_filter);

		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			return ret;
		}
				
		if(_filter->media_type == 0)
		{
			_filter->media_type = (MEDIA_CONTENT_TYPE_IMAGE | MEDIA_CONTENT_TYPE_VIDEO | MEDIA_CONTENT_TYPE_AUDIO);	
		}
	}

	memset(order_query,0x00,sizeof(order_query));	
	memset(condition_type,0x00,sizeof(condition_type));		
	memset(condition_query,0x00,sizeof(condition_query));	
	memset(limit_query,0x00,sizeof(limit_query));	
	memset(search_query,0x00,sizeof(search_query));		
	memset(select_query1,0x00,sizeof(select_query1));		

	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and display_name like '%%%s%%'", _filter->keyword);
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_info_filter_s*)filter != _filter)
				media_info_filter_destroy((media_info_filter_h)_filter);		
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}

	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	if(_filter->media_type & MEDIA_CONTENT_TYPE_IMAGE)
	{
		strncat(condition_type,CONDITION_TYPE_IMAGE,strlen(CONDITION_TYPE_IMAGE));
	}
	if(_filter->media_type & MEDIA_CONTENT_TYPE_VIDEO)
	{
		if(strlen(condition_type) > 0 )
		{
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));
			strncat(condition_type,QUERY_KEYWORD_OR, strlen(QUERY_KEYWORD_OR));
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));			
		}
		strncat(condition_type,CONDITION_TYPE_VIDEO,strlen(CONDITION_TYPE_VIDEO));

	}
	if(_filter->media_type & MEDIA_CONTENT_TYPE_AUDIO)
	{
		if(strlen(condition_type) > 0 )
		{
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));		
			strncat(condition_type,QUERY_KEYWORD_OR, strlen(QUERY_KEYWORD_OR));
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));			
		}
	
		strncat(condition_type,CONDITION_TYPE_AUDIO,strlen(CONDITION_TYPE_AUDIO));
	}


	snprintf(select_query1,sizeof(select_query1),"%s", SELECT_MEDIA_ITEM);


	snprintf(condition_query,sizeof(condition_query), "%s %s='%s' %s (%s)",
			QUERY_KEYWORD_AND, DB_FIELD_FOLDER_UID,_folder->folder_uid, QUERY_KEYWORD_AND, condition_type);
	


	if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_DISPLAY_NAME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_DISPLAY_NAME,QUERY_KEYWORD_DESC);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_MODIFIED_DATE);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_MODIFIED_DATE,QUERY_KEYWORD_DESC);		
	}

	if((media_info_filter_s*)filter != _filter)
		media_info_filter_destroy((media_info_filter_h)_filter);	
	
	ret = _content_query_prepare(&stmt,select_query1, condition_query,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		return ret;
	}

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item1 = (media_info_s*)calloc(1,sizeof(media_info_s));
		if(item1 == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_content_item_get_detail(stmt,(media_info_h)item1);
		if( callback((media_info_h)item1,user_data) == 0)
		{
			media_info_destroy((media_info_h)item1);
			break;
		}		
		media_info_destroy((media_info_h)item1);
		
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;
}

int media_folder_foreach_folder_from_db(media_folder_filter_h filter,media_folder_cb callback, void* user_data)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;

	char order_query[MIN_QUERY_SIZE];
	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	
	char condition_query[DEFAULT_QUERY_SIZE];	
	

	sqlite3_stmt *stmt = NULL;
	media_folder_filter_s* _filter = NULL;
	
	
	if( callback == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	
	memset(order_query,0x00,sizeof(order_query));	
	memset(limit_query,0x00,sizeof(limit_query));	
	memset(search_query,0x00,sizeof(search_query));
	memset(select_query,0x00,sizeof(select_query));		
	memset(condition_query,0x00,sizeof(condition_query));	


	if(filter != NULL)
		_filter = (media_folder_filter_s*)filter;
	else
	{
		media_folder_filter_create((media_folder_filter_h*)&_filter);
	}	

	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and name like '%%%s%%'", _filter->keyword);
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_folder_filter_s*)filter != _filter)
				media_folder_filter_destroy((media_folder_filter_h)_filter);		
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}

	snprintf(select_query,sizeof(select_query),"%s",SELECT_ALL_FOLDER);
	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);


	if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_NAME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_NAME,QUERY_KEYWORD_DESC);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_MODIFIED_DATE);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_MODIFIED_DATE,QUERY_KEYWORD_DESC);		
	}
	
	if((media_folder_filter_s*)filter != _filter)
		media_folder_filter_destroy((media_folder_filter_h)_filter);	

	if(select_query != NULL)
	{
		ret = _content_query_prepare(&stmt,select_query,condition_query,search_query,limit_query,order_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			return ret;
		}
	}

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_folder_s* _folder = (media_folder_s*)calloc(1,sizeof(media_folder_s));

		if(_folder == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		_content_folder_get_detail(stmt,(media_folder_h)_folder);
		if(callback((media_folder_h)_folder,user_data) == false)
		{
			media_folder_destroy((media_folder_h) _folder);

			break;

		}			

		media_folder_destroy((media_folder_h) _folder);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	
	return ret;
}
int media_folder_get_media_count_from_db(media_folder_h folder,media_content_type_e type, int* count)
{
	int _tmp;

	int ret= MEDIA_CONTENT_ERROR_NONE;

	char condition_query[MIN_QUERY_SIZE];
	char condition_type[MIN_QUERY_SIZE];	
	char select_query[DEFAULT_QUERY_SIZE];
	sqlite3_stmt *stmt = NULL;

	media_folder_s* _folder = (media_folder_s*)folder;

	if(_folder == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	memset(condition_type, 0x00,sizeof(condition_type));
	memset(condition_query, 0x00,sizeof(condition_query));
	memset(select_query, 0x00,sizeof(select_query));	



	if(type & MEDIA_CONTENT_TYPE_IMAGE)
	{
		strncat(condition_type,CONDITION_TYPE_IMAGE,strlen(CONDITION_TYPE_IMAGE));
	}
	if(type & MEDIA_CONTENT_TYPE_VIDEO)
	{
		if(strlen(condition_type) > 0 )
		{
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));
			strncat(condition_type,QUERY_KEYWORD_OR, strlen(QUERY_KEYWORD_OR));
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));			
		}
		strncat(condition_type,CONDITION_TYPE_VIDEO,strlen(CONDITION_TYPE_VIDEO));

	}
	if(type & MEDIA_CONTENT_TYPE_AUDIO)
	{
		if(strlen(condition_type) > 0 )
		{
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));		
			strncat(condition_type,QUERY_KEYWORD_OR, strlen(QUERY_KEYWORD_OR));
			strncat(condition_type,QUERY_KEYWORD_SPACE, strlen(QUERY_KEYWORD_SPACE));			
		}
	
		strncat(condition_type,CONDITION_TYPE_AUDIO,strlen(CONDITION_TYPE_AUDIO));
	}
	
	snprintf(condition_query,sizeof(condition_query), "%s %s='%s' %s (%s)",
			QUERY_KEYWORD_AND, DB_FIELD_FOLDER_UID,_folder->folder_uid, QUERY_KEYWORD_AND, condition_type);

	snprintf(select_query,sizeof(select_query),"%s", SELECT_COUNT_ITEM);

	
	_tmp = _content_query_prepare(&stmt,select_query,condition_query,NULL,NULL,NULL);

	if(_tmp != MEDIA_CONTENT_ERROR_NONE)
		return _tmp;
	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		*count = (int)sqlite3_column_int(stmt,0);
	}	
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;

}


int media_folder_destroy(media_folder_h folder)
{
	int ret;
	media_folder_s* _folder = (media_folder_s*)folder;	
	if(_folder) 
	{
		if(_folder->path) 
		{
			free(_folder->path);
		}						
		if(_folder->name) 
		{
			free(_folder->name);
		}			
		if(_folder->folder_uid)
		{
			free(_folder->folder_uid);
		}
		free(_folder);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}
int media_folder_clone(media_folder_h* dst, media_folder_h src)
{
	int ret;
	media_folder_s* _src = (media_folder_s*)src;	


	if(_src != NULL)
	{
		media_folder_s* _dst = (media_folder_s*)calloc(1,sizeof(media_folder_s));		
		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;		
		}
		_dst->folder_uid = strdup(_src->folder_uid);
		if(_dst->folder_uid == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;

		}
		_dst->storage_type = _src->storage_type;
		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_folder_destroy((media_folder_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		if((_src->path != NULL) && (strlen(_src->path) > 0))
		{
			_dst->path = strdup(_src->path);
			if(_dst->path == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_folder_destroy((media_folder_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;			
			}
		}

		*dst = (media_folder_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	
		
	return ret;
}

int media_folder_get_path(media_folder_h folder, char** path)
{
	int ret;
	media_folder_s* _folder = (media_folder_s*)folder;	
	if(_folder) 
	{
		if((_folder->path != NULL) && (strlen(_folder->path) > 0))
		{
			*path = strdup(_folder->path);
			if(*path == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		else
		{
			*path = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE; 				

	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	

	return ret;

}

int media_folder_get_name(media_folder_h folder, char** name)
{	
	int ret;
	media_folder_s* _folder = (media_folder_s*)folder;	
	if(_folder) 
	{
		if((_folder->name != NULL) && (strlen(_folder->name) > 0))
		{
			*name = strdup(_folder->name);
			if(*name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;			
			}
		}
		else
		{
			*name = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE; 				

	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	

	return ret;
}
	
int media_folder_get_storage_type(media_folder_h folder, media_content_storage_e* storage_type)
{
	int ret;
	media_folder_s* _folder = (media_folder_s*)folder;	
	if(_folder) 
	{
		*storage_type = _folder->storage_type;
		ret = MEDIA_CONTENT_ERROR_NONE;	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	

	return ret;

}


int media_folder_get_date_modified(media_folder_h folder, time_t* time)
{
	int ret;
	media_folder_s* _folder = (media_folder_s*)folder;	
	if(_folder) 
	{
		*time = _folder->date_modified;
		ret = MEDIA_CONTENT_ERROR_NONE;	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	

	return ret;

}

void _content_folder_get_detail(sqlite3_stmt* stmt, media_folder_h folder)
{
	media_folder_s* _folder = (media_folder_s*)folder;
	_folder->folder_uid = strdup((const char *)sqlite3_column_text(stmt, 0));
	_folder->path= strdup((const char *)sqlite3_column_text(stmt, 1));
	_folder->name=strdup((const char *)sqlite3_column_text(stmt, 2));
	_folder->storage_type=(int)sqlite3_column_int(stmt,3);
	_folder->date_modified=(int)sqlite3_column_int(stmt,4);	
}


