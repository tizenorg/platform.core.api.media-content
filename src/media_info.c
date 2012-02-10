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
#include <media-svc.h>
#include <audio-svc.h>
#include <audio-svc-error.h>
#include <audio-svc-types.h>

#include <visual-svc-error.h>
#include <visual-svc-types.h>
#include <visual-svc.h>

#include <drm-service.h>
#include <aul.h>

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"

extern MediaSvcHandle* db_handle;


#define SELECT_AUDIO_FROM_MEDIA "select audio_uuid,genre,album,artist,author,year,copyright,description,format,bitrate,track_num,duration,rating,played_count,last_played_time,added_time,size,category from audio_media where audio_uuid='%s' "
#define SELECT_TAG_LIST_FROM_MEDIA "select t._id, t.tag_name from (select _id, tag_name from visual_tag ORDER BY tag_name ASC ) t, ( select visual_uuid, tag_id from visual_tag_map where visual_uuid='%s' ) tm, ( select visual_uuid, folder_uuid from visual_media) m, ( select folder_uuid, lock_status from visual_folder where valid=1 ) f where tm.tag_id = t._id and m.visual_uuid = tm.visual_uuid and m.folder_uuid = f.folder_uuid and f.lock_status=0; "

int media_info_insert_to_db(media_content_type_e type,const char* path)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;
	int storage_type;
	int category=0;
	minfo_file_type _type;
	if(path == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	switch(type)
	{
		case MEDIA_CONTENT_TYPE_IMAGE:
			_type = MINFO_ITEM_IMAGE;
			ret = minfo_add_media(db_handle, path, _type);
			ret = _content_error_capi(MEDIA_CONTENT_TYPE, ret);
		break;
		case MEDIA_CONTENT_TYPE_VIDEO:
			_type = MINFO_ITEM_VIDEO;
			ret = minfo_add_media(db_handle, path, _type);
			ret = _content_error_capi(MEDIA_CONTENT_TYPE, ret);			
		break;

		case MEDIA_CONTENT_TYPE_AUDIO:
			storage_type = _content_get_storage_type(path);
			ret = _content_get_audio_category(path,&category);
			if(ret >= 0)
			{
				ret = audio_svc_insert_item(db_handle, storage_type,path,category);				
			}
			else
			{
				LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;			
			}
		break;

		default:
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
		break;

	}

	return ret;
}



int media_info_destroy(media_info_h item)
{

	int ret;
	media_info_s* _item = (media_info_s*)item;	
	if(_item) 
	{
		if(_item->item_id)
		{
			free(_item->item_id);
		}

		if(_item->file_path) 
		{
			free(_item->file_path);
		}						
		if(_item->display_name) 
		{
			free(_item->display_name);
		}			
		if(_item->thumbnail) 
		{
			free(_item->thumbnail);
		}
		free(_item);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;



}
int media_info_clone(media_info_h* dst, media_info_h src)
{
	int ret;
	media_info_s* _src = (media_info_s*)src;	


	if(_src != NULL )
		{
		media_info_s* _dst = (media_info_s*)calloc(1,sizeof(media_info_s));		

		if(_dst == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}
		
		_dst->item_id = strdup(_src->item_id);
		if(	_dst->item_id == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		_dst->date_modified= _src->date_modified;
		_dst->favorite = _src->favorite;
		_dst->media_type = _src->media_type;
		if((_src->file_path != NULL) && (strlen(_src->file_path) > 0))
		{
			_dst->file_path = strdup(_src->file_path);
			if(_dst->file_path == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_info_destroy((media_info_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}
		if((_src->display_name != NULL) && (strlen(_src->display_name) > 0))
		{
			_dst->display_name = strdup(_src->display_name);
			if(_dst->display_name == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_info_destroy((media_info_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;			
			}
		}
		if((_src->thumbnail != NULL) && (strlen(_src->thumbnail) > 0))
		{
			_dst->thumbnail = strdup(_src->thumbnail);
			if(_dst->thumbnail == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				media_info_destroy((media_info_h)_dst);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;			
			}

		}		
		*dst = (media_info_h)_dst;
		ret = MEDIA_CONTENT_ERROR_NONE;		
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	
		
	return ret;	
}

int media_info_get_file_path(media_info_h item, char** path)
{	
	int ret;
	media_info_s* _item = (media_info_s*)item;	
	
	if(_item) 
	{
		if((_item->file_path != NULL) && (strlen(_item->file_path) > 0))
		{
			*path = strdup(_item->file_path);
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
	

int media_info_get_display_name(media_info_h item, char** name)
{	
	int ret;
	media_info_s* _item = (media_info_s*)item;	
	if(_item) 
	{
		if((_item->display_name != NULL) && (strlen(_item->display_name) > 0))
		{
			*name = strdup(_item->display_name);
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
	

int media_info_get_thumbnail_path(media_info_h item, char** path)
{	
	int ret;
	media_info_s* _item = (media_info_s*)item;	
	if(_item) 
	{
		if((_item->thumbnail != NULL) && (strlen(_item->thumbnail) > 0))
		{
			*path = strdup(_item->thumbnail);
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
	

int media_info_get_date_modified(media_info_h item, time_t* time)
{
	int ret;
	media_info_s* _item = (media_info_s*)item;	
	if(_item) 
	{
		*time = _item->date_modified;
		ret = MEDIA_CONTENT_ERROR_NONE;	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	

	return ret;

}

int media_info_get_media_type(media_info_h item, int* type)
{
	int ret;
	media_info_s* _item = (media_info_s*)item;	
	if(_item) 
	{
		*type = _item->media_type;
		ret = MEDIA_CONTENT_ERROR_NONE;	
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}	

	return ret;

}

int media_info_get_favorite(media_info_h media, int* favorite)
{
	int ret;
	media_info_s* _media = (media_info_s*)media;
	if(_media)
	{

		*favorite = _media->favorite;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}


int media_info_update_favorite_to_db(media_info_h media, int favorite)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_s* _media = (media_info_s*)media;

	if(media != NULL)
	{
		if(_media->media_type == MEDIA_CONTENT_TYPE_AUDIO)
		{
			if(favorite)
			{
				ret = audio_svc_add_item_to_playlist( db_handle, AUDIO_SVC_FAVORITE_LIST_ID, _media->item_id);
			}
			else
			{
				ret = audio_svc_remove_item_from_playlist_by_audio_id(db_handle, AUDIO_SVC_FAVORITE_LIST_ID, _media->item_id);
			}
		}
		else
		{	
			ret = minfo_update_media_favorite(db_handle, _media->item_id,favorite);
		}
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;

	}
	return ret;

}



int media_info_foreach_media_from_db(media_info_filter_h filter,media_info_cb callback, void* user_data)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;

	char limit_query[MIN_QUERY_SIZE];
	char condition_query[DEFAULT_QUERY_SIZE];	
	char search_query[MAX_KEYWORD_SIZE];
	char condition_type[MIN_QUERY_SIZE];
	char select_query[DEFAULT_QUERY_SIZE];	
	char order_query[MIN_QUERY_SIZE];


	sqlite3_stmt *stmt = NULL;


	media_info_filter_s* _filter = NULL;
		
	if( callback == NULL )
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


	snprintf(select_query,sizeof(select_query),"%s", SELECT_MEDIA_ITEM);

	snprintf(condition_query,sizeof(condition_query), "%s (%s)", QUERY_KEYWORD_AND, condition_type);

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
		snprintf(order_query,sizeof(order_query),"%s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_DATE_MODIFIED);
	}
	else if(_filter->order == MEDIA_CONTENT_SORT_BY_DATE_DESC)
	{
		snprintf(order_query,sizeof(order_query),"%s %s %s",QUERY_KEYWORD_ORDER_BY,DB_FILED_DATE_MODIFIED,QUERY_KEYWORD_DESC);		
	}

	
	if((media_info_filter_s*)filter != _filter)
		media_info_filter_destroy((media_info_filter_h)_filter);		


	ret = _content_query_prepare(&stmt,select_query,condition_query, search_query,limit_query,order_query);
	if( ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	
	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_info_s* item1 = (media_info_s*)calloc(1,sizeof(media_info_s));

		if(item1 == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		_content_item_get_detail(stmt,(media_info_h)item1);

		if( callback((media_info_h)item1,user_data) == false)
		{
			media_info_destroy((media_info_h) item1);
			break;
		}
		media_info_destroy((media_info_h) item1);		
	}
	
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;

}



int media_info_get_image_from_db(media_info_h item, image_meta_h* image)
{
	int p_ret;
	int ret = MEDIA_CONTENT_ERROR_NONE;
	Mitem* p_item = NULL;
	image_meta_s* _image = NULL; 
	

	
	media_info_s* _item = (media_info_s*)item;

	if( _item == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(_item->media_type != MEDIA_CONTENT_TYPE_IMAGE)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	p_ret = minfo_get_item_by_id(db_handle, _item->item_id,&p_item);

	ret =  _content_error_capi(MEDIA_CONTENT_TYPE,p_ret);
	if( (ret == MEDIA_CONTENT_ERROR_NONE) && ( p_item != NULL))
	{
		ret = minfo_get_meta_info(db_handle, _item->item_id,&(p_item->meta_info));
		ret =  _content_error_capi(MEDIA_CONTENT_TYPE,p_ret);	

		if( ret != MEDIA_CONTENT_ERROR_NONE)
		{
			minfo_destroy_mtype_item(p_item);
			return ret;
		}
		_image = (image_meta_s*)calloc(1, sizeof(image_meta_s));
		if(_image == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			minfo_destroy_mtype_item(p_item);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;		

		}

		_image->image_id = strdup(p_item->uuid);
		if(p_item->thumb_url != NULL)
			_image->thumbnail = strdup(p_item->thumb_url);
		if(p_item->rate > 0)
			_image->favorite = true;
		else
			_image->favorite = false;

		if(p_item->meta_info != NULL)
		{
			_image->longitude = p_item->meta_info->longitude;
			_image->latitude = p_item->meta_info->latitude;
			_image->width = p_item->meta_info->width;
			_image->height = p_item->meta_info->height;
			_image->date_taken  = p_item->meta_info->datetaken;
			if(p_item->meta_info->description != NULL)
				_image->description = strdup(p_item->meta_info->description);		
		}
		if((p_item->meta_info != NULL) && (p_item->meta_info->image_info != NULL))
		{
			_image->orientation = p_item->meta_info->image_info->orientation;
		}
		
		*image = (image_meta_h)_image;
		p_ret = minfo_destroy_mtype_item(p_item);
		ret = _content_error_capi(MEDIA_CONTENT_TYPE,p_ret);
	}

	
	return ret;
}


int media_info_get_video_from_db(media_info_h item, video_meta_h* video)
{

	int p_ret;
	int ret = MEDIA_CONTENT_ERROR_NONE;
	Mitem* p_item = NULL;
	video_meta_s* _video = NULL;


	media_info_s* _item = (media_info_s*)item;	
	if( _item == NULL )
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(_item->media_type != MEDIA_CONTENT_TYPE_VIDEO)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	p_ret = minfo_get_item_by_id(db_handle, _item->item_id,&p_item);


	ret =  _content_error_capi(MEDIA_CONTENT_TYPE,p_ret);
	if( (ret == MEDIA_CONTENT_ERROR_NONE) && ( p_item != NULL))
	{
		ret = minfo_get_meta_info(db_handle, _item->item_id,&(p_item->meta_info));
		ret =  _content_error_capi(MEDIA_CONTENT_TYPE,p_ret);	
		if( ret != MEDIA_CONTENT_ERROR_NONE)
		{
			minfo_destroy_mtype_item(p_item);
			return ret;
		}

		_video = (video_meta_s*)calloc(1,sizeof(video_meta_s));
		if( _video == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			minfo_destroy_mtype_item(p_item);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}

		_video->video_id = strdup(p_item->uuid);
		if(p_item->thumb_url)
			_video->thumbnail = strdup(p_item->thumb_url);
		
		if(p_item->rate > 0)
			_video->favorite = true;
		else
			_video->favorite = false;


		if(p_item->meta_info != NULL)
		{
			_video->longitude = p_item->meta_info->longitude;
			_video->latitude = p_item->meta_info->latitude;
			_video->width = p_item->meta_info->width; 
			_video->height = p_item->meta_info->height;
			_video->date_taken = p_item->meta_info->datetaken;
			if(p_item->meta_info->description)
				_video->description = strdup(p_item->meta_info->description);			
		}			
		if((p_item->meta_info != NULL) && (p_item->meta_info->video_info != NULL))
		{
			if(p_item->meta_info->video_info->album_name != NULL)
			{
				_video->album = strdup(p_item->meta_info->video_info->album_name);
			}
			if(p_item->meta_info->video_info->artist_name != NULL)
				_video->artist = strdup(p_item->meta_info->video_info->artist_name);
			if(p_item->meta_info->video_info->title != NULL)
				_video->title = strdup(p_item->meta_info->video_info->title);

			
			_video->time_played = p_item->meta_info->video_info->last_played_pos;
			_video->duration = p_item->meta_info->video_info->duration;
		}
		*video = (video_meta_h)_video;
		p_ret = minfo_destroy_mtype_item(p_item);
		ret =  _content_error_capi(MEDIA_CONTENT_TYPE,p_ret);
	
	}
	return ret;
}

int media_info_get_audio_from_db(media_info_h item, audio_meta_h* audio)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	media_info_s* _item = (media_info_s*)item;
	
	char select_query[DEFAULT_QUERY_SIZE];
	sqlite3_stmt *stmt = NULL;

	if(_item == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if(_item->media_type != MEDIA_CONTENT_TYPE_AUDIO)
	{
		LOGE("[%s] the type of media is not an audio.",__func__);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	
	memset(select_query,0x00,sizeof(select_query)); 

	snprintf(select_query,sizeof(select_query), SELECT_AUDIO_FROM_MEDIA,_item->item_id);

	ret = _content_query_prepare(&stmt,select_query,NULL,NULL,NULL,NULL);


	if( ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	
	audio_meta_s* _audio = (audio_meta_s*)calloc(1,sizeof(audio_meta_s));
	if(_audio == NULL)
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
	}


	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		_audio->audio_id = strdup((const char *)sqlite3_column_text(stmt, 0));
		_audio->genre = strdup((const char *)sqlite3_column_text(stmt, 1));				
		_audio->album = strdup((const char *)sqlite3_column_text(stmt, 2));
		_audio->artist= strdup((const char *)sqlite3_column_text(stmt, 3));
		_audio->author= strdup((const char *)sqlite3_column_text(stmt, 4));
		_audio->year= strdup((const char *)sqlite3_column_text(stmt, 5));
		_audio->copyright= strdup((const char *)sqlite3_column_text(stmt, 6));
		_audio->description= strdup((const char *)sqlite3_column_text(stmt, 7));
		_audio->format= strdup((const char *)sqlite3_column_text(stmt, 8));
		_audio->bitrate = (int)sqlite3_column_int(stmt,9);
		_audio->track_num = (int)sqlite3_column_int(stmt,10);
		_audio->duration = (int)sqlite3_column_int(stmt,11);
		_audio->rating = (int)sqlite3_column_int(stmt,12);
		_audio->count_played = (int)sqlite3_column_int(stmt,13);
		_audio->time_played = (int)sqlite3_column_int(stmt,14);
		_audio->time_added = (int)sqlite3_column_int(stmt,15);
		_audio->size = (int)sqlite3_column_int(stmt,16);
		_audio->category = (int)sqlite3_column_int(stmt,17);
	}
	*audio = (audio_meta_h)_audio;
	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}
	

	return ret;
}



int media_info_foreach_tag_from_db(media_info_h item, media_tag_cb callback, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char select_query[DEFAULT_QUERY_SIZE];
	sqlite3_stmt *stmt = NULL;

	media_info_s* _item = (media_info_s*)item;	
	
	if(_item == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	if(callback == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	snprintf(select_query,sizeof(select_query),SELECT_TAG_LIST_FROM_MEDIA,_item->item_id);
	ret = _content_query_prepare(&stmt,select_query,NULL,NULL,NULL,NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	while( sqlite3_step(stmt) == SQLITE_ROW)
	{
		media_tag_s* _tag = (media_tag_s*)calloc(1,sizeof(media_tag_s));

		if(_tag == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;	
		}

		_tag->tag_id = (int)sqlite3_column_int(stmt,0);
		_tag->name = strdup((const char *)sqlite3_column_text(stmt, 1));	
		if(callback((media_tag_h)_tag,user_data) == false)
		{
			media_tag_destroy((media_tag_h) _tag);
			break;
		}
		media_tag_destroy((media_tag_h) _tag);
		
	}

	if(stmt != NULL)
	{
		sqlite3_finalize(stmt);
	}

	return ret;

}

void _content_item_get_detail(sqlite3_stmt* stmt, media_info_h item)
{
	//item_id, file_path, display_name, thumbnail, date_modified,content_type, valid
	media_info_s* _item = (media_info_s*)item;
	_item->item_id = strdup((const char *)sqlite3_column_text(stmt, 0));
	_item->file_path= strdup((const char *)sqlite3_column_text(stmt, 1));
	_item->display_name=strdup((const char *)sqlite3_column_text(stmt, 2));
	_item->thumbnail=strdup((const char *)sqlite3_column_text(stmt, 3));	
	_item->date_modified = (int)sqlite3_column_int(stmt,4);
	_item->media_type = (int)sqlite3_column_int(stmt,5);
	_item->media_type = _item->media_type==3?4:_item->media_type;
	_item->favorite = (int)sqlite3_column_int(stmt,6);
}

int _content_get_storage_type(const char* full_path)
{
	if (full_path != NULL) {		
		if (strncmp(full_path, MEDIA_CONTENT_PATH_PHONE , strlen(MEDIA_CONTENT_PATH_PHONE )) == 0) 
		{
			return MEDIA_CONTENT_STORAGE_INTERNAL;
		}
		else if (strncmp(full_path, MEDIA_CONTENT_PATH_MMC , strlen(MEDIA_CONTENT_PATH_MMC )) == 0) 
		{
			return MEDIA_CONTENT_STORAGE_EXTERNAL;
		}
	}
	
	return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
}


#define CONTENT_TYPE_NUM 4
#define FEX_CATEGORY_UNKNOWN	0x00000000	/**< Default */
#define FEX_CATEGORY_ETC		0x00000001	/**< ETC category */
#define FEX_CATEGORY_IMAGE	0x00000002	/**< Image category */
#define FEX_CATEGORY_VIDEO		0x00000004	/**< Video category */
#define FEX_CATEGORY_MUSIC	0x00000008	/**< Music category */
#define FEX_CATEGORY_SOUND	0x00000010	/**< Sound category */
#define FEX_CATEGORY_DRM		0x00000020	/**< DRM category */
#define SOUND_MIME_NUM 1
#define MINE_LENGTH 30
#define MUSIC_MIME_NUM 12


typedef struct
{
	char content_type[15];
	int  category_by_mime;
}fex_content_table_t;

static const fex_content_table_t content_category[CONTENT_TYPE_NUM] = {
	{"audio", FEX_CATEGORY_SOUND},
	{"image", FEX_CATEGORY_IMAGE},
	{"video", FEX_CATEGORY_VIDEO},
	{"application", FEX_CATEGORY_ETC},
};

static const char sound_mime_table[SOUND_MIME_NUM][MINE_LENGTH] = {
	"x-smaf",
};
static const char music_mime_table[MUSIC_MIME_NUM][MINE_LENGTH] = {
	"ac3",
	"mp2",
	"mpeg",
	"ogg",
	"vnd.rn-realaudio",
	"x-ape",
	"x-flac",
	"x-flac+ogg",
	"x-matroska",
	"x-ms-asx",
	"x-ms-wma",
	"x-vorbis+ogg",
};

#define FMS_DRM_CONTENT_TYPE_LENGTH 100

int _content_get_audio_category(const char* file_full_path,int* category)
{
	int i = 0;
	char mimetype[255] = {0,};
	int result = 0;
	bool is_drm = false;
	drm_content_info_t contentInfo = {0};

	if (file_full_path == NULL)
		return FEX_CATEGORY_UNKNOWN;


	if (drm_svc_is_drm_file(file_full_path) == DRM_TRUE)
	{

		// 2008.8.13 han. In this case, use drm_svc_get_content_info api.
		result = drm_svc_get_content_info(file_full_path, &contentInfo);
		if (result != DRM_RESULT_SUCCESS)
		{
			*category = FEX_CATEGORY_UNKNOWN;
		}

		strncpy(mimetype,  contentInfo.contentType, strlen(contentInfo.contentType)+1);
		*category = *category | FEX_CATEGORY_DRM;
		is_drm = true;
	}
	else
	{
		result = aul_get_mime_from_file(file_full_path, mimetype, sizeof(mimetype));
		if(result < 0)
		{
			*category = FEX_CATEGORY_UNKNOWN;
		}

	}

	for(i = 0; i < CONTENT_TYPE_NUM; i ++)
	{
		if (strstr(mimetype, content_category[i].content_type) != NULL)
		{
			*category = (*category | content_category[i].category_by_mime);
			break;
		}
	}
	if (*category & FEX_CATEGORY_ETC)
	{
		int prefix_len = strlen(content_category[0].content_type);

		for(i = 0; i < SOUND_MIME_NUM; i ++)
		{
			if (strstr(mimetype+prefix_len, sound_mime_table[i]) != NULL)
			{
				*category = FEX_CATEGORY_SOUND;
				break;
			}
		}

		if(is_drm)
			*category = *category | FEX_CATEGORY_DRM;;
	}

	if (!(*category & FEX_CATEGORY_SOUND))
	{
		return result;
	}
	else
	{
		if(is_drm) //if sound file is DRM, it is always music file.
		{
			*category = FEX_CATEGORY_MUSIC;
			*category = *category | FEX_CATEGORY_DRM;
		}
		else //check music file in sound files.
		{
			int prefix_len = strlen(content_category[0].content_type);

			for(i = 0; i < MUSIC_MIME_NUM; i ++)
			{
				if (strstr(mimetype+prefix_len, music_mime_table[i]) != NULL)
				{
					*category = FEX_CATEGORY_MUSIC;
					break;
				}
			}
		}
	}

	return result;



}

