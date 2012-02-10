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
#include <media-svc.h>
#include <audio-svc.h>
#include <audio-svc-error.h>
#include <media_info_private.h>

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"

extern MediaSvcHandle* db_handle;

int audio_meta_destroy(audio_meta_h audio)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if(_audio->audio_id)
		{
			free(_audio->audio_id);
		}
		if(_audio->genre) 
		{
			free(_audio->genre);
		}			
		if(_audio->author) 
		{
			free(_audio->author);
		}			
		if(_audio->copyright) 
		{
			free(_audio->copyright);
		}			
		if(_audio->description) 
		{
			free(_audio->description);
		}			
		if(_audio->format) 
		{
			free(_audio->format);
		}	

		free(_audio);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	return ret;

}

int audio_meta_clone(audio_meta_h* dst, audio_meta_h src)
{
	int ret;
	audio_meta_s* _src = (audio_meta_s*)src;	

	if(_src != NULL)
	{
	
		audio_meta_s* _dst = (audio_meta_s*)calloc(1,sizeof(audio_meta_s));		

		if(_dst == NULL)
		{

			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		_dst->audio_id = strdup(_src->audio_id);
		if(_dst->audio_id == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_dst->year= _src->year;
		_dst->bitrate = _src->bitrate;
		_dst->track_num = _src->track_num ;
		_dst->duration = _src->duration;
		_dst->rating = _src->rating;
		_dst->count_played = _src->count_played;
		_dst->time_played = _src->time_played;
		_dst->time_added = _src->time_added;
		_dst->size = _src->size;
		_dst->category = _src->category;
		
					
		if((_src->genre != NULL) && (strlen(_src->genre) > 0))
		{
			_dst->genre = strdup(_src->genre);
			if(_dst->genre == NULL)
			{
				audio_meta_destroy((audio_meta_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if((_src->author != NULL) && (strlen(_src->author ) > 0))
		{
			_dst->author  = strdup(_src->author );
			if(_dst->author == NULL)
			{
				audio_meta_destroy((audio_meta_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);			
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		if((_src->copyright != NULL) && (strlen(_src->copyright) > 0))
		{
			_dst->copyright = strdup(_src->copyright);
			if(_dst->copyright == NULL)
			{
				audio_meta_destroy((audio_meta_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}	
		}
		if((_src->description != NULL) && (strlen(_src->description) > 0))
		{
			_dst->description = strdup(_src->description);
			if(_dst->description == NULL)
			{
				audio_meta_destroy((audio_meta_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}		
		}
		if((_src->format != NULL) && (strlen(_src->format) > 0))
		{
			_dst->format = strdup(_src->format);
			if(_dst->format == NULL)
			{
				audio_meta_destroy((audio_meta_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}		
		}
		*dst = (audio_meta_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	
		
	return ret;

}


int audio_meta_get_genre(audio_meta_h audio, char** name)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if((_audio->genre != NULL) && (strlen(_audio->genre) > 0))
		{
			*name = strdup(_audio->genre);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
	
}

int audio_meta_get_album(audio_meta_h audio, char **name)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if((_audio->album != NULL) && (strlen(_audio->album) > 0))
		{
			*name = strdup(_audio->album);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}
int audio_meta_get_artist(audio_meta_h audio, char **name)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if((_audio->artist != NULL) && (strlen(_audio->artist) > 0))
		{
			*name = strdup(_audio->artist);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;


}

int audio_meta_get_author(audio_meta_h audio, char** name)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if((_audio->author != NULL) && (strlen(_audio->author) > 0))
		{
			*name = strdup(_audio->author);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}


int audio_meta_get_year(audio_meta_h audio,char** year)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if((_audio->year != NULL) && (strlen(_audio->year) > 0))
		{
			*year = strdup(_audio->year);
			if(*year == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;					
			}
		}
		else
		{
			*year = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE; 				

	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}

int audio_meta_get_copyright(audio_meta_h audio, char** copyright)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		if((_audio->copyright != NULL) && (strlen(_audio->copyright) > 0))
		{
			*copyright = strdup(_audio->copyright);
			if(*copyright == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;					
			}
		}
		else
		{
			*copyright = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE; 				

	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}



int audio_meta_get_description(audio_meta_h audio, char** description)
{
		int ret;
		audio_meta_s* _audio = (audio_meta_s*)audio;	
		if(_audio) 
		{
			if((_audio->description != NULL) && (strlen(_audio->description) > 0))
			{
				*description = strdup(_audio->description);
				if(*description == NULL)
				{
					LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
					return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;					
				}
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
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
		}	
		return ret;
}


int audio_meta_get_format(audio_meta_h audio, char** format)
{
		int ret;
		audio_meta_s* _audio = (audio_meta_s*)audio;	
		if(_audio) 
		{
			if((_audio->format != NULL) && (strlen(_audio->format) > 0))
			{
				*format = strdup(_audio->format);
				if(*format == NULL)
				{
					LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
					return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;					
				}
			}
			else
			{
				*format = NULL;
			}
			ret = MEDIA_CONTENT_ERROR_NONE; 				
	
		}
		else 
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
		}	
	
		return ret;

}


int audio_meta_get_bitrate(audio_meta_h audio,int* bitrate)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio && bitrate) 
	{
		*bitrate = _audio->bitrate;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_track_num(audio_meta_h audio,int* track_num)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio && track_num) 
	{
		*track_num = _audio->track_num;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_duration(audio_meta_h audio,int* duration)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*duration = _audio->duration;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_rating(audio_meta_h audio,int* rating)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*rating= _audio->rating;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_count_played(audio_meta_h audio,int* count_played)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*count_played = _audio->count_played;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_time_played(audio_meta_h audio,int* time_played)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*time_played = _audio->time_played;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_time_added(audio_meta_h audio,time_t* time_added)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*time_added = _audio->time_added;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_size(audio_meta_h audio,int* size)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*size = _audio->size;
		ret = MEDIA_CONTENT_ERROR_NONE; 
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}


int audio_meta_get_category(audio_meta_h audio,audio_category_e* category)
{
	int ret;
	audio_meta_s* _audio = (audio_meta_s*)audio;	
	if(_audio) 
	{
		*category = _audio->category;
		ret = MEDIA_CONTENT_ERROR_NONE;	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}	


int audio_meta_update_count_played_to_db(audio_meta_h audio,int count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	audio_meta_s* _audio = (audio_meta_s*)audio;


	if(_audio != NULL)
	{
		ret  = audio_svc_update_item_metadata(db_handle,_audio->audio_id,AUDIO_SVC_TRACK_DATA_PLAYED_COUNT,count,-1);

		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	return ret;	
}


int audio_meta_update_time_played_to_db(audio_meta_h audio,time_t time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s* _audio = (audio_meta_s*)audio;

	
	if(_audio != NULL)
	{
		ret = audio_svc_update_item_metadata(db_handle,_audio->audio_id,AUDIO_SVC_TRACK_DATA_PLAYED_TIME,time,-1);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);		
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	return ret;	
}



int audio_playlist_foreach_playlist_from_db(media_audio_filter_h filter, audio_playlist_cb callback,  void* user_data )
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	


	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;

	if( callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}


	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}
	
	
	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));


	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and name like '%%%s%%'", _filter->keyword);
		}
		else
		{
			if((media_audio_filter_s*)filter != _filter)
			{
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			}
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query,sizeof(select_query),"%s", SELECT_PLAYLIST);


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
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME,QUERY_KEYWORD_DESC);		
	}


	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);

	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		return ret;
	}
	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		audio_playlist_s* playlist = (audio_playlist_s*)calloc(1,sizeof(audio_playlist_s));
		if(playlist == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
	
		playlist->playlist_id= (int)sqlite3_column_int(stmt,0);
		playlist->name= strdup((const char *)sqlite3_column_text(stmt, 1));
		if(callback((audio_playlist_h)playlist,user_data) == false)
		{
			audio_playlist_destroy((audio_playlist_h)playlist);
			break;
		}
		audio_playlist_destroy((audio_playlist_h)playlist);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	
	return ret;

}


int audio_playlist_foreach_media_from_db(audio_playlist_h playlist, media_audio_filter_h filter, media_info_cb callback, void* user_data )
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;
	
	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;

	if(_playlist == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	if(callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}
	

	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query),
				" and display_name like '%%%s%%' ",
				_filter->keyword);
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query, sizeof(select_query),SELECT_MEDIA_FROM_PLAYLIST, _playlist->playlist_id);


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

	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);
	
	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);

	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item = (media_info_s*)calloc(1,sizeof(media_info_s));
		if(item == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}
		
		_content_item_get_detail(stmt,(media_info_h)item);
		if(callback((media_info_h)item,user_data) == false )
		{
			media_info_destroy((media_info_h)item);
			break;
		}
		media_info_destroy((media_info_h)item);		

	}

	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}


	return ret;
}

int audio_playlist_get_media_count_from_db(audio_playlist_h playlist,int* count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;

	if(_playlist != NULL)
	{
		ret = audio_svc_count_playlist_item(db_handle,_playlist->playlist_id,NULL,NULL, count);

		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
		
	return ret;

}


int audio_playlist_insert_to_db(const char* name, audio_playlist_h* playlist)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_id;
	
	if(name != NULL)
	{
		audio_playlist_s* _playlist = (audio_playlist_s*)calloc(1,sizeof(audio_playlist_s));

		if( _playlist == NULL )
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
			
		ret = audio_svc_add_playlist(db_handle,name,&playlist_id);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			free(_playlist);
			return ret;
		}

		_playlist->playlist_id = playlist_id;
		_playlist->name = strdup(name);
		if(_playlist->name == NULL)
		{
			free(_playlist);
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		*playlist = (audio_playlist_h)_playlist;
	
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}


int audio_playlist_delete_from_db(audio_playlist_h playlist)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;

	if(_playlist != NULL)
	{
		ret = audio_svc_delete_playlist(db_handle,_playlist->playlist_id);

		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
		
	return ret;

}

int audio_playlist_destroy(audio_playlist_h playlist)
{
	int ret;
	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;	
	if(_playlist) 
	{
		if(_playlist->name) 
		{
			free(_playlist->name);
		}	

		free(_playlist);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	return ret;

}
int audio_playlist_clone(audio_playlist_h* dst, audio_playlist_h src)
{
	int ret;
	audio_playlist_s* _src = (audio_playlist_s*)src;	

	if(_src != NULL )
	{
		audio_playlist_s* _dst = (audio_playlist_s*)calloc(1,sizeof(audio_playlist_s));		
		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		_dst->playlist_id = _src->playlist_id;

		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				audio_playlist_destroy((audio_playlist_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		*dst = (audio_playlist_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	
		
	return ret;

}


int audio_playlist_get_name(audio_playlist_h playlist,char** name)
{
	int ret;
	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;	
	if(_playlist) 
	{
		if((_playlist->name!= NULL) && (strlen(_playlist->name) > 0))
		{
			*name = strdup(_playlist->name);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}



int audio_playlist_update_name_to_db(audio_playlist_h playlist,const char* name)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;	
	
	
	if(_playlist != NULL && name != NULL)
	{
		ret = audio_svc_update_playlist_name(db_handle,_playlist->playlist_id,name);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
		if(ret == MEDIA_CONTENT_ERROR_NONE)
		{
			free(_playlist->name);
			_playlist->name = strdup(name);
			if(_playlist->name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;			
			}
		}		
		
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}

	
	return ret;	
}

int audio_playlist_add_media_to_db(audio_playlist_h playlist, media_info_h item)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;	
	media_info_s* _item = (media_info_s*)item;

	if(_playlist != NULL && _item != NULL && _item->media_type == 4)
	{

		ret = audio_svc_add_item_to_playlist(db_handle,_playlist->playlist_id,_item->item_id);

		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	
	return ret;	
}


int audio_playlist_remove_media_from_db(audio_playlist_h playlist, media_info_h item)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	audio_playlist_s* _playlist = (audio_playlist_s*)playlist;	
	media_info_s* _item = (media_info_s*)item;

	if(_playlist != NULL && _item != NULL && _item->media_type == 4)
	{

		ret = audio_svc_remove_item_from_playlist_by_audio_id(db_handle,_playlist->playlist_id,_item->item_id);

		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}

		
	return ret;	
}

int audio_genre_foreach_genre_from_db(media_audio_filter_h filter, audio_genre_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	
	media_audio_filter_s* _filter = NULL;


	if(callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
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
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	snprintf(select_query,sizeof(select_query),"%s", SELECT_GENRE_LIST);
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
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME,QUERY_KEYWORD_DESC); 	
	}


	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		audio_genre_s* genre = (audio_genre_s*)calloc(1,sizeof(audio_genre_s));	
		memset(genre,0x00,sizeof(audio_genre_s));
		genre->name= strdup((const char *)sqlite3_column_text(stmt, 0));
		if(callback((audio_genre_h)genre,user_data) == false)
		{
			audio_genre_destroy((audio_genre_h)genre);
			break;
		}
		audio_genre_destroy((audio_genre_h)genre);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	
	return ret;

}

int audio_genre_foreach_media_from_db(audio_genre_h genre, media_audio_filter_h filter, media_info_cb callback,  void* user_data )
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	
	
	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;

	audio_genre_s* _genre = (audio_genre_s*)genre;
	

	if(_genre == NULL || callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}
	

	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and display_name like '%%%s%%'", _filter->keyword);
	
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);		
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	snprintf(select_query, sizeof(select_query),SELECT_MEDIA_FROM_GENRE, _genre->name);

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


	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret= _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item = (media_info_s*)calloc(1,sizeof(media_info_s));	

		_content_item_get_detail(stmt, (media_info_h)item);
		if(callback((media_info_h)item,user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}
		media_info_destroy((media_info_h)item);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	
	return ret;
}


int audio_genre_get_media_count_from_db(audio_genre_h genre,int* count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	audio_genre_s* _genre = (audio_genre_s*)genre;
	

	memset(select_query,0x00,sizeof(select_query));
	
	if(_genre == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return  MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	snprintf(select_query,sizeof(select_query),SELECT_MEDIA_COUNT_FROM_GENRE,_genre->name);


	ret = _content_query_prepare(&stmt,select_query,NULL,NULL,NULL,NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

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

int audio_genre_destroy(audio_genre_h genre)
{
	int ret;
	audio_genre_s* _genre = (audio_genre_s*)genre;	
	if(_genre) 
	{
		if(_genre->name) 
		{
			free(_genre->name);
		}	

		free(_genre);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	return ret;

}

int audio_genre_clone(audio_genre_h* dst,audio_genre_h src)
{
	int ret;
	audio_genre_s* _src = (audio_genre_s*)src;	


	if(_src != NULL)
	{
		audio_genre_s* _dst = (audio_genre_s*)calloc(1,sizeof(audio_genre_s));		
		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				audio_genre_destroy((audio_genre_h)_dst);
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		*dst = (audio_genre_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	
		
	return ret;

}

		
int audio_genre_get_name(audio_genre_h genre, char** name)
{
	int ret;
	audio_genre_s* _genre = (audio_genre_s*)genre;	
	if(_genre) 
	{
		if((_genre->name!= NULL) && (strlen(_genre->name) > 0))
		{
			*name = strdup(_genre->name);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}


int audio_album_foreach_album_from_db(media_audio_filter_h filter, audio_album_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	
	
	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;
	

	if(callback == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}
	
	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and name like '%%%s%%'",_filter->keyword);
			
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	
	snprintf(select_query,sizeof(select_query),"%s", SELECT_ALBUM_LIST);

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
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME,QUERY_KEYWORD_DESC);		
	}


	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		audio_album_s* album = (audio_album_s*)calloc(1,sizeof(audio_album_s));

		if(album == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		album->name= strdup((const char *)sqlite3_column_text(stmt, 0));
		if(callback((audio_album_h)album,user_data) == false)
		{
			audio_album_destroy((audio_album_h)album);
			break;
		}
		audio_album_destroy((audio_album_h)album);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	return ret;

}

int audio_album_foreach_media_from_db(audio_album_h album, media_audio_filter_h filter, media_info_cb callback,  void* user_data )
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;
	

	audio_album_s* _album = (audio_album_s*)album;


	if( _album == NULL || callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));


	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}

	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and display_name like '%%%s%%'", _filter->keyword);
	
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	


	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query, sizeof(select_query),SELECT_MEDIA_FROM_ALBUM, _album->name);


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

	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item = (media_info_s*)calloc(1,sizeof(media_info_s));	

		_content_item_get_detail(stmt, (media_info_h)item);
		if(callback((media_info_h)item,user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}
		media_info_destroy((media_info_h)item);		
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;


}


int audio_album_get_media_count_from_db(audio_album_h album,int* count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	audio_album_s* _album = (audio_album_s*)album;
	char select_query[DEFAULT_QUERY_SIZE];	
	
	memset(select_query,0x00,sizeof(select_query));

	if(_album == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return  MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	snprintf(select_query,sizeof(select_query),SELECT_MEDIA_COUNT_FROM_ALBUM,_album ->name);


	ret = _content_query_prepare(&stmt,select_query,NULL,NULL,NULL,NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

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

int audio_album_destroy(audio_album_h album )
{
	int ret;
	audio_album_s* _album = (audio_album_s*)album;	
	if(_album) 
	{
		if(_album->name) 
		{
			free(_album->name);
		}	

		free(_album);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	return ret;

}

int audio_album_clone(audio_album_h* dst,audio_album_h src)
{
	int ret;
	audio_album_s* _src = (audio_album_s*)src;	
	

	if(_src != NULL)
	{
		audio_album_s* _dst = (audio_album_s*)calloc(1,sizeof(audio_album_s));		

		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				audio_album_destroy((audio_album_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		*dst = (audio_album_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	
		
	return ret;

}
		
int audio_album_get_name(audio_album_h album, char** name)
{
	int ret;
	audio_album_s* _album = (audio_album_s*)album;	
	if(_album) 
	{
		if((_album->name!= NULL) && (strlen(_album->name) > 0))
		{
			*name = strdup(_album->name);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}


int audio_author_foreach_author_from_db(media_audio_filter_h filter, audio_author_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;

	if(callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
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
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	
	
	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query,sizeof(select_query),"%s", SELECT_AUTHOR_LIST);


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
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME,QUERY_KEYWORD_DESC);		
	}

	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);
	

	ret = _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;
	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		audio_author_s* author = (audio_author_s*)calloc(1,sizeof(audio_author_s));
		if(author == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		author->name= strdup((const char *)sqlite3_column_text(stmt, 0));
		if(callback((audio_author_h)author,user_data) == false)
		{
			audio_author_destroy((audio_author_h)author);
			break;
		}
		audio_author_destroy((audio_author_h)author);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	return ret;

}

int audio_author_foreach_media_from_db(audio_author_h author, media_audio_filter_h filter, media_info_cb callback,  void* user_data )
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;

	audio_author_s* _author = (audio_author_s*)author;
	

	if(_author == NULL || callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}

	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	
	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and display_name like '%%%s%%'", _filter->keyword);
	
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);		
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	
	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query, sizeof(select_query),SELECT_MEDIA_FROM_AUTHOR, _author->name);


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


	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret =_content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

		
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item = (media_info_s*)calloc(1,sizeof(media_info_s));
		if(item == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}
		
		_content_item_get_detail(stmt, (media_info_h)item);
		if(callback((media_info_h)item,user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}
		media_info_destroy((media_info_h)item);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;


}


int audio_author_get_media_count_from_db(audio_author_h author,int* count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	audio_author_s* _author = (audio_author_s*)author;
	char select_query[DEFAULT_QUERY_SIZE];

	
	memset(select_query,0x00,sizeof(select_query));

	if(_author == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return  MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}


	snprintf(select_query,sizeof(select_query),SELECT_MEDIA_COUNT_FROM_AUTHOR,_author ->name);

	ret = _content_query_prepare(&stmt,select_query,NULL,NULL,NULL,NULL);
	if(ret!= MEDIA_CONTENT_ERROR_NONE)
		return ret;

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

int audio_author_destroy(audio_author_h author )
{
	int ret;
	audio_author_s* _author = (audio_author_s*)author;	
	if(_author) 
	{
		if(_author->name) 
		{
			free(_author->name);
		}	

		free(_author);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	return ret;

}

int audio_author_clone(audio_author_h* dst,audio_author_h src)
{
	int ret;
	audio_author_s* _src = (audio_author_s*)src;	
	

	if(_src != NULL)
	{
		audio_author_s* _dst = (audio_author_s*)calloc(1,sizeof(audio_author_s));	

		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				audio_author_destroy((audio_author_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		*dst = (audio_author_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	
		
	return ret;

}
		
int audio_author_get_name(audio_author_h author, char** name)
{
	int ret;
	audio_author_s* _author = (audio_author_s*)author;	
	if(_author) 
	{
		if((_author->name!= NULL) && (strlen(_author->name) > 0))
		{
			*name = strdup(_author->name);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;

}



int audio_artist_foreach_artist_from_db(media_audio_filter_h filter, audio_artist_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;

	if(callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}

	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));
	
	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and name like '%%%s%%'", _filter->keyword);
			
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query,sizeof(select_query),"%s", SELECT_MEDIA_ARTIST_LIST);


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
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FIELD_ADDED_TIME,QUERY_KEYWORD_DESC);		
	}

	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);

	ret =_content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		audio_artist_s* artist = (audio_artist_s*)calloc(1,sizeof(audio_artist_s));
		if(artist == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		artist->name= strdup((const char *)sqlite3_column_text(stmt, 0));
		if(callback((audio_artist_h)artist,user_data) == false)
		{
			audio_artist_destroy((audio_artist_h)artist);	
			break;
		}
		audio_artist_destroy((audio_artist_h)artist);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;

}

int audio_artist_foreach_media_from_db(audio_artist_h artist, media_audio_filter_h filter, media_info_cb callback,  void* user_data )
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char search_query[MAX_KEYWORD_SIZE];
	char order_query[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	

	sqlite3_stmt *stmt = NULL;
	media_audio_filter_s* _filter = NULL;

	audio_artist_s* _artist = (audio_artist_s*)artist;


	if(_artist == NULL || callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}


	if(filter != NULL)
		 _filter = (media_audio_filter_s*)filter;
	else
	{
		media_audio_filter_create((media_audio_filter_h*)&_filter);
	}	

	memset(limit_query,0x00,sizeof(limit_query));
	memset(search_query,0x00,sizeof(search_query));
	memset(order_query,0x00,sizeof(order_query));
	memset(select_query,0x00,sizeof(select_query));

	if((_filter->keyword != NULL) && strlen(_filter->keyword) > 0)
	{
		if(strlen(_filter->keyword) < sizeof(search_query))
		{
			snprintf(search_query,sizeof(search_query)," and display_name like '%%%s%%'", _filter->keyword);
	
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			if((media_audio_filter_s*)filter != _filter)
				media_audio_filter_destroy((media_audio_filter_h)_filter);		
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		search_query[0] = ' ';
	}	

	snprintf(limit_query,sizeof(limit_query),"%s %d,%d",QUERY_KEYWORD_LIMIT,_filter->offset,_filter->count);

	snprintf(select_query, sizeof(select_query),SELECT_MEDIA_FROM_ARTIST, _artist->name);

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

	if((media_audio_filter_s*)filter != _filter)
		media_audio_filter_destroy((media_audio_filter_h)_filter);


	ret= _content_query_prepare(&stmt,select_query,NULL,search_query,limit_query,order_query);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	 	return ret;

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item = (media_info_s*)calloc(1,sizeof(media_info_s));
		if(item == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		_content_item_get_detail(stmt, (media_info_h)item);
		if(callback((media_info_h)item,user_data) == false)
		{
			media_info_destroy((media_info_h)item);
			break;
		}
		media_info_destroy((media_info_h)item);
	}
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;


}


int audio_artist_get_media_count_from_db(audio_artist_h artist,int* count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	sqlite3_stmt *stmt = NULL;
	audio_artist_s* _artist = (audio_artist_s*)artist;
	char select_query[DEFAULT_QUERY_SIZE];	

	
	memset(select_query,0x00,sizeof(select_query));
	if(_artist == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return  MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	snprintf(select_query,sizeof(select_query),SELECT_MEDIA_COUNT_FROM_ARTIST,_artist ->name);

	ret = _content_query_prepare(&stmt,select_query,NULL, NULL,NULL,NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

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

int audio_artist_destroy(audio_artist_h artist )
{
	int ret;
	audio_artist_s* _artist = (audio_artist_s*)artist;	
	if(_artist) 
	{
		if(_artist->name) 
		{
			free(_artist->name);
		}	

		free(_artist);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}
	return ret;

}

int audio_artist_clone(audio_artist_h* dst,audio_artist_h src)
{
	int ret;
	audio_artist_s* _src = (audio_artist_s*)src;	
	

	if(_src != NULL )
	{

		audio_artist_s* _dst = (audio_artist_s*)calloc(1,sizeof(audio_artist_s));		

		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		
		if((_src->name != NULL) && (strlen(_src->name) > 0))
		{
			_dst->name = strdup(_src->name);
			if(_dst->name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				audio_artist_destroy((audio_artist_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		*dst = (audio_artist_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	
		
	return ret;

}
		
int audio_artist_get_name(audio_artist_h artist, char** name)
{
	int ret;
	audio_artist_s* _artist = (audio_artist_s*)artist;	
	if(_artist) 
	{
		if((_artist->name!= NULL) && (strlen(_artist->name) > 0))
		{
			*name = strdup(_artist->name);
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER ;
	}	

	return ret;
}

