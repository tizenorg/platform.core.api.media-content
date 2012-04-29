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
#include <visual-svc-error.h>
#include <visual-svc-types.h>
#include <visual-svc.h>
#include <media-svc.h>

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"

//extern MediaSvcHandle* db_handle;


int video_meta_destroy(video_meta_h video)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video)
	{
		if(_video->video_id)
		{
			free(_video->video_id);
		}
	
		if(_video->album)
		{
			free(_video->album);
		}
		if(_video->artist)
		{
			free(_video->artist);
		}
		if(_video->title)
		{
			free(_video->title);
		}
		if(_video->thumbnail)
		{
			free(_video->thumbnail);
		}

		free(_video);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}

#define DUPLICATE_STRING(destination, src)        \
{                                                 \
    char* tmp = src;                              \
    if(tmp != NULL && strlen(tmp) > 0)            \
    {                                             \
        char* new_str = strdup(tmp);              \
        destination = new_str;                \
    }                                             \
    else                                          \
    {                                             \
        destination = NULL;                       \
    }                                             \
}

#define DUPLICATE_FIELD(field) DUPLICATE_STRING(_dst->field, _src->field)




int video_meta_clone( video_meta_h* dst, video_meta_h src)
{
	int ret;
    	video_meta_s* _src;
    	video_meta_s* _dst;

	if((src != NULL))
	{
		_src = (video_meta_s*)src;
		_dst = (video_meta_s*)calloc(1,sizeof(video_meta_s));
		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		_dst->video_id = strdup(_src->video_id);
		_dst->longitude = _src->longitude;
		_dst->latitude= _src->latitude;
		_dst->time_played = _src->time_played;
		_dst->duration = _src->duration;
		_dst->width = _src->width;
		_dst->height = _src->height;
		_dst->orientation = _src->orientation;
		_dst->date_taken = _src->date_taken;


		if(_src->album != NULL)
		{
			_dst->album = (char*)strdup(_src->album);
			if(_dst->album == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				video_meta_destroy((video_meta_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		if(_src->artist != NULL)
		{
			_dst->artist = (char*)strdup(_src->artist);
			if(_dst->artist == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				video_meta_destroy((video_meta_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		if(_src->title != NULL)
		{
			_dst->title = (char*)strdup(_src->title);
			if(_dst->title == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				video_meta_destroy((video_meta_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		if(_src->description != NULL)
		{
			_dst->description = (char*)strdup(_src->description);
			if(_dst->description == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				video_meta_destroy((video_meta_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}	
		if(_src->thumbnail != NULL)
		{
			_dst->thumbnail = (char*)strdup(_src->thumbnail);
			if(_dst->thumbnail == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				video_meta_destroy((video_meta_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}		
		*dst =(video_meta_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;
	
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;


}


int video_meta_get_longitude(video_meta_h video, double* longitude)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && longitude)
	{
		*longitude = _video->longitude;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}
int video_meta_get_latitude(video_meta_h video, double* latitude)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && latitude)
	{
		*latitude = _video->latitude;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}

int video_meta_get_album(video_meta_h video, char** album)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;	
	if(_video) 
	{
		if((_video->album != NULL) && (strlen(_video->album) > 0))
		{
			char* new_string = strdup(_video->album);
			if(NULL == new_string)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
			*album = new_string;
		}
		else
		{
			*album = NULL;
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
int video_meta_get_artist(video_meta_h video, char** artist)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;	
	if(_video) 
	{
		if((_video->artist != NULL) && (strlen(_video->artist) > 0))
		{
			char* new_string = strdup(_video->artist);
			if(NULL == new_string)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
			*artist = new_string;
		}
		else
		{
			*artist = NULL;
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
int video_meta_get_title(video_meta_h video, char** title)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;	
	if(_video) 
	{
		if((_video->title != NULL) && (strlen(_video->title) > 0))
		{
			char* new_string = strdup(_video->title);
			if(NULL == new_string)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
			*title = new_string;
		}
		else
		{
			*title = NULL;
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
int video_meta_get_description(video_meta_h video, char** description)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;	
	if(_video) 
	{
		if((_video->description != NULL) && (strlen(_video->description) > 0))
		{
			char* new_string = strdup(_video->description);
			if(NULL == new_string)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
			*description = new_string;
		}
		else
		{
			*description = NULL;
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


int video_meta_get_time_played(video_meta_h video, int* time_played)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video)
	{
		*time_played = _video->time_played;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_meta_get_duration(video_meta_h video, int* duration)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && duration)
	{
		*duration = _video->duration;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_meta_get_width(video_meta_h video, int* width)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && width)
	{
		*width = _video->width;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_meta_get_height(video_meta_h video, int* height)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && height)
	{
		*height = _video->height;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_meta_get_orientation(video_meta_h video, media_content_orientation_e* orientation)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && orientation)
	{
		*orientation = _video->orientation;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_meta_get_date_taken(video_meta_h video, time_t* date_taken)
{
	int ret;
	video_meta_s* _video = (video_meta_s*)video;
	if(_video && date_taken)
	{
		*date_taken = _video->date_taken;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}

int video_meta_update_time_played_to_db(video_meta_h video, int time_played)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	video_meta_s* _video = (video_meta_s*)video;

	if(_video != NULL )
	{
		ret = minfo_update_video_meta_info_int(_content_get_db_handle(),_video->video_id,MINFO_VIDEO_META_BOOKMARK_LAST_PLAYED,time_played);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);		
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}


	return ret;

}



int video_bookmark_foreach_bookmark_from_db(video_meta_h video,video_bookmark_filter_h filter, video_bookmark_cb callback,void* user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char limit_query[MIN_QUERY_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;

	
	video_bookmark_filter_s* _filter = NULL;

	video_meta_s* _video = (video_meta_s*)video;


	if(_video == NULL || callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	memset(order_query,0x00,sizeof(order_query));	
	memset(limit_query,0x00,sizeof(limit_query));
	memset(select_query,0x00,sizeof(select_query));	

	
	if(filter != NULL)
		 _filter = (video_bookmark_filter_s*)filter;
	else
	{
		video_bookmark_filter_create((video_bookmark_filter_h*)&_filter);
	}


	snprintf(select_query,sizeof(select_query), SELECT_BOOKMARK_FROM_VIDEO,_video->video_id);
	
	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);


	if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_THUMBNAIL_PATH);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_NAME_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_THUMBNAIL_PATH,QUERY_KEYWORD_DESC);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_ASC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_MARKED_TIME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_MARKED_TIME,QUERY_KEYWORD_DESC);		
	}

	if((video_bookmark_filter_s*)filter != _filter)
		video_bookmark_filter_destroy((video_bookmark_filter_h)_filter);

	ret = _content_query_prepare(&stmt,select_query,NULL,NULL,limit_query,order_query);
	
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;


	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		video_bookmark_s* bookmark = (video_bookmark_s*)calloc(1,sizeof(video_bookmark_s));
		if(bookmark == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		bookmark->bookmark_id= (int)sqlite3_column_int(stmt,0);
		bookmark->video_id= strdup((const char *)sqlite3_column_text(stmt, 1));
		bookmark->time_marked = (int)sqlite3_column_int(stmt,2);
		bookmark->thumbnail= strdup((const char *)sqlite3_column_text(stmt, 3));
		if(callback((video_bookmark_h)bookmark,user_data) == false)
		{
			video_bookmark_destroy((video_bookmark_h)bookmark);
			break;
		}
		video_bookmark_destroy((video_bookmark_h)bookmark);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;



}


int video_bookmark_destroy(video_bookmark_h bookmark)
{
	int ret;
	video_bookmark_s* _bookmark = (video_bookmark_s*)bookmark;
	if(_bookmark)
	{
		if(_bookmark->video_id!= NULL)
			free(_bookmark->video_id);
		if(_bookmark->thumbnail != NULL)
			free(_bookmark->thumbnail);
		free(_bookmark);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}
int video_bookmark_clone(video_bookmark_h* dst, video_bookmark_h src)
{
	int ret;

	if((src != NULL))
	{
	    	video_bookmark_s* _src = (video_bookmark_s*)src;
	    	video_bookmark_s* _dst = (video_bookmark_s*)calloc(1,sizeof(video_bookmark_s));
	        if (NULL == _dst)
	        {
	        	LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
	            return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
	        }
		_dst->bookmark_id = _src->bookmark_id;
		_dst->video_id = strdup(_src->video_id);
		_dst->time_marked= _src->time_marked;

		if(_src->thumbnail != NULL)
		{
			_dst->thumbnail = (char*)strdup(_src->thumbnail);
			if(_dst->thumbnail == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				video_bookmark_destroy((video_bookmark_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}		

		ret = MEDIA_CONTENT_ERROR_NONE;
	        *dst = (video_bookmark_h)_dst;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}

int video_bookmark_get_time_marked(video_bookmark_h bookmark, time_t* time_marked)
{
	int ret;
	video_bookmark_s* _bookmark = (video_bookmark_s*)bookmark;
	if(_bookmark )
	{
		*time_marked = _bookmark->time_marked;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_bookmark_get_thumbnail_path(video_bookmark_h bookmark, char** thumbnail)
{
	int ret;
	video_bookmark_s* _bookmark = (video_bookmark_s*)bookmark;
	if(_bookmark)
	{
		if((_bookmark->thumbnail != NULL) && (strlen(_bookmark->thumbnail) > 0))
		{
			*thumbnail = strdup(_bookmark->thumbnail);
			if (NULL == *thumbnail)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		else
		{
			*thumbnail = NULL;
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




int video_bookmark_insert_to_db(video_meta_h video, time_t time, const char* thumbnail_path)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	video_meta_s* _video = (video_meta_s*)video;

	if(_video != NULL)
	{
		ret = minfo_add_bookmark(_content_get_db_handle(),_video->video_id,time,thumbnail_path);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);		
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int video_bookmark_delete_from_db(video_bookmark_h bookmark)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	video_bookmark_s* _bookmark = (video_bookmark_s*)bookmark;

	if( _bookmark != NULL)
	{
		ret = minfo_delete_bookmark(_content_get_db_handle(),_bookmark->bookmark_id);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);	
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}



