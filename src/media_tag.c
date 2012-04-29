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

//extern MediaSvcHandle* db_handle;


int media_tag_foreach_tag_from_db(media_tag_filter_h filter, media_tag_cb callback,void* user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	char limit_query[MIN_QUERY_SIZE];
	char search_query[DEFAULT_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	
	char order_query[MIN_QUERY_SIZE];

	sqlite3_stmt *stmt = NULL;


	media_tag_filter_s* _filter = NULL;
	

	if(callback == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}


	memset(limit_query,0x00,sizeof(limit_query));	
	memset(search_query,0x00,sizeof(search_query));	
	memset(select_query,0x00,sizeof(select_query));	
	memset(order_query,0x00,sizeof(order_query));	
	

	if(filter != NULL)
		 _filter = (media_tag_filter_s*)filter;
	else
	{
		media_tag_filter_create((media_tag_filter_h*)&_filter);
	}


	snprintf(select_query,sizeof(select_query),"%s", SELECT_TAG_LIST);


	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and tag_name like '%%%s%%'", _filter->keyword);
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_tag_filter_s*)filter != _filter)
				media_tag_filter_destroy((media_tag_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}

	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);


	if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_TAG_NAME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_TAG_NAME,QUERY_KEYWORD_DESC);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ID);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ID,QUERY_KEYWORD_DESC);		
	}


	if((media_tag_filter_s*)filter != _filter)
		media_tag_filter_destroy((media_tag_filter_h)_filter);
			
	if(select_query != NULL)
	{
		ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
			return ret;
	}


	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_tag_s* _tag = (media_tag_s*)calloc(1,sizeof(media_tag_s));

		if(_tag == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		memset(_tag,0x00,sizeof(media_tag_s));
		_tag->tag_id = (int)sqlite3_column_int(stmt,0);
		_tag->name= strdup((const char *)sqlite3_column_text(stmt, 1));
		if(callback((media_tag_h)_tag,user_data) == false)
		{
			media_tag_destroy((media_tag_h)_tag);
			break;
		}
		media_tag_destroy((media_tag_h)_tag);
		
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	
	return ret;
}



int media_tag_insert_to_db(const char* tag_name,media_tag_h* tag)
{
	
	int ret = MEDIA_CONTENT_ERROR_NONE;

		
	if(tag_name == NULL ||  strlen(tag_name) == 0)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	media_tag_s *_tag = (media_tag_s*)calloc(1,sizeof(media_tag_s));

	_tag->name = strdup(tag_name);

	if(_tag->name == NULL)
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
	}

	ret = minfo_add_tag(_content_get_db_handle(),NULL,tag_name);

	if(ret == MB_SVC_ERROR_NONE)
	{
		*tag = (media_tag_h)_tag;
	}

	return _content_error_capi(MEDIA_CONTENT_TYPE,ret);

}

int media_tag_delete_from_db(media_tag_h tag)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if(tag == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	
	media_tag_s* _tag = (media_tag_s*)tag;
	
	
	ret = minfo_delete_tag(_content_get_db_handle(), NULL, _tag->name);
	
	return _content_error_capi(MEDIA_CONTENT_TYPE,ret);

}

int media_tag_add_media_to_db(media_tag_h tag,media_info_h media)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;


	media_tag_s* _tag = (media_tag_s*)tag;
	media_info_s* _item = (media_info_s*)media;
	
	if(_tag == NULL || _item == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(_item->media_type == MEDIA_CONTENT_TYPE_AUDIO)
	{
		LOGE("[%s]_NOT_SUPPORTED_AUDIO(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO);

		return MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO;
	}
	
	if(_tag->name == NULL || strlen(_tag->name) == 0)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;	
	}
	
	ret = minfo_add_tag(_content_get_db_handle(), _item->item_id,_tag->name);

	return _content_error_capi(MEDIA_CONTENT_TYPE,ret);

}

int media_tag_remove_media_from_db(media_tag_h tag,media_info_h media)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char *query_string = NULL;
	
	media_tag_s* _tag = (media_tag_s*)tag;
	media_info_s* _item = (media_info_s*)media;	
	if(_tag == NULL || _item == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	if(_item->media_type == MEDIA_CONTENT_TYPE_AUDIO)
	{
		LOGE("[%s]_NOT_SUPPORTED_AUDIO(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO);
		return MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO;
	}


	if(_tag->name == NULL || strlen(_tag->name) == 0)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	query_string = sqlite3_mprintf("DELETE FROM visual_tag_map WHERE visual_uuid=%s and tag_name=%d",
			      _item->item_id, _tag->name);

	
	_content_query_sql(query_string);

	sqlite3_free(query_string);

	return _content_error_capi(MEDIA_CONTENT_TYPE,ret);	

}


int media_tag_destroy(media_tag_h tag)
{
	int ret;
	media_tag_s* _tag = (media_tag_s*)tag;	
	if(_tag) 
	{
		if(_tag->name) 
		{
			free(_tag->name);
		}			

		free(_tag);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}
int media_tag_clone(media_tag_h* dst, media_tag_h src)
{
	int ret;
	media_tag_s* _src = (media_tag_s*)src;	
	media_tag_s* _dst = NULL;


	if((_src != NULL))
	{
		_dst = (media_tag_s*)calloc(1,sizeof(media_tag_s));	       
		
		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	
		_dst->tag_id = _src->tag_id;
				
		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				free(_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		*dst = (media_tag_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	
		
	return ret;	
}

int media_tag_get_name(media_tag_h tag, char** name)
{
	int ret;
	media_tag_s* _tag = (media_tag_s*)tag;	
	if(_tag) 
	{
		if((_tag->name != NULL) && (strlen(_tag->name) > 0))
		{
			*name = strdup(_tag->name);
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
int media_tag_update_name_to_db(media_tag_h tag, const char* name)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	media_tag_s* _tag = (media_tag_s*)tag;
	if(_tag == NULL || name == NULL || strlen(name) <= 0)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	ret = minfo_rename_tag(_content_get_db_handle(),_tag->name,name);

	if(ret == MB_SVC_ERROR_NONE)
	{
		free(_tag->name);
		_tag->name = strdup(name);
		if(_tag->name == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	}
		
	return _content_error_capi(MEDIA_CONTENT_TYPE,ret);
}

int media_tag_foreach_media_from_db(media_tag_h tag,media_info_filter_h filter, media_info_cb callback,void* user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char* media_id = NULL;
	Mitem *mitem = NULL;
	char select_query[DEFAULT_QUERY_SIZE];	
	char search_query[MAX_KEYWORD_SIZE];
	char limit_query[MIN_QUERY_SIZE];
	char order_query[MIN_QUERY_SIZE];

	media_tag_filter_s* _filter = NULL;
	
	sqlite3_stmt *stmt = NULL;

	memset(select_query,0x00,sizeof(select_query));	
	memset(search_query,0x00,sizeof(search_query)); 
	memset(limit_query,0x00,sizeof(limit_query)); 
	memset(order_query,0x00,sizeof(order_query)); 

	media_tag_s* _tag = (media_tag_s*)tag;	
	
	if(_tag == NULL || callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	if(filter != NULL)
		 _filter = (media_tag_filter_s*)filter;
	else
	{
		media_tag_filter_create((media_tag_filter_h*)&_filter);
	}

	
	snprintf(select_query,sizeof(select_query),SELECT_MEDIA_FROM_TAG,_tag->name);


	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and display_name like '%%%s%%'", _filter->keyword);
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_tag_filter_s*)filter != _filter)
				media_tag_filter_destroy((media_tag_filter_h)_filter);		
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}


	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	

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


	if((media_tag_filter_s*)filter != _filter)
		media_tag_filter_destroy((media_tag_filter_h)_filter);

	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;


	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* _item = (media_info_s*)calloc(1,sizeof(media_info_s));

		if(_item == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}
		memset(_item,0x00,sizeof(media_info_s));
		media_id = (char*)sqlite3_column_text(stmt, 1);
		ret = minfo_get_item_by_id(_content_get_db_handle(),media_id, &mitem);

		if(ret < 0)
		{
			if(stmt != NULL)
			{
				sqlite3_finalize(stmt);
			}
			media_info_destroy((media_info_h)_item);
			return _content_error_capi(MEDIA_CONTENT_TYPE,ret);
		}
		_item->item_id = strdup(media_id);
		_item->file_path = strdup(mitem->file_url);
		_item->display_name = strdup(mitem->display_name);
		_item->thumbnail = strdup(mitem->thumb_url);
		_item->date_modified = mitem->mtime;
		_item->media_type = mitem->type;	
		if(callback((media_info_h)_item,user_data) == false)
		{
			media_info_destroy((media_info_h)_item);
			break;
		}
		media_info_destroy((media_info_h)_item);
	}
		
	if(mitem != NULL)
		minfo_destroy_mtype_item(mitem);
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;
}

