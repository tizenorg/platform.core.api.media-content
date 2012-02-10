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
#include <media-svc.h>

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"


int media_info_filter_create(media_info_filter_h* filter)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if(filter == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	
	media_info_filter_s* _filter = (media_info_filter_s*)calloc(1, sizeof(media_info_filter_s));

	if(_filter == NULL)	
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		ret = MEDIA_CONTENT_ERROR_OUT_OF_MEMORY ;
	}	
	else {
		_filter->media_type = MEDIA_CONTENT_TYPE_ALL;		
		_filter->offset = -1;
		_filter->count = -1;
		_filter->order = MEDIA_CONTENT_SORT_NONE;
		_filter->search_type = MEDIA_INFO_SEARCH_NONE;
		_filter->keyword = NULL;

		*filter = (media_info_filter_h)_filter;
		
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	return ret;

}



int media_info_filter_destroy(media_info_filter_h filter)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		if(_filter->keyword) 
		{
			free(_filter->keyword);
		}						
		free(_filter);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{	
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}

int media_info_filter_set_offset(media_info_filter_h filter, int offset, int count)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		_filter->offset = offset;
		_filter->count = count;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_info_filter_set_search_keyword(media_info_filter_h filter,media_info_search_type_e search_type,const char *search_keyword)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;
	if(_filter) 
	{
		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			free(_filter->keyword);
			_filter->keyword = NULL;
		}

		if(search_type == MEDIA_INFO_SEARCH_BY_DISPLAY_NAME)
		{	
			if((search_keyword != NULL) && (strlen(search_keyword) > 0))
			{
				_filter->search_type = search_type;
				_filter->keyword = strdup(search_keyword);
				if(_filter->keyword == NULL)
				{
					LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
					return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
				}
			}
			else
			{
				LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
		}
		else if(search_type == MEDIA_INFO_SEARCH_NONE)
		{
			_filter->search_type = search_type;
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
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


int media_info_filter_set_order(media_info_filter_h filter, media_content_order_e order)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		_filter->order = order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

int media_info_filter_set_media_type(media_info_filter_h filter,int media_type)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		if( !(media_type & MEDIA_CONTENT_TYPE_ALL))
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		}
		
		_filter->media_type = media_type;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_info_filter_get_offset(media_info_filter_h filter, int* offset, int* count)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		
		*offset = _filter->offset;
		*count = _filter->count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_info_filter_get_search_keyword(media_info_filter_h filter,media_info_search_type_e* search_type, char **search_keyword)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;
	if(_filter && (search_type != NULL)) 
	{
		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			*search_keyword = strdup(_filter->keyword);
			if(*search_keyword == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
			*search_type = _filter->search_type;
		}
		else
		{
			*search_type = _filter->search_type;
			*search_keyword = NULL;
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


int media_info_filter_get_order(media_info_filter_h filter, media_content_order_e* order)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		*order = _filter->order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

int media_info_filter_get_media_type(media_info_filter_h filter,int* media_type)
{
	int ret;
	media_info_filter_s* _filter = (media_info_filter_s*)filter;	
	if(_filter) 
	{
		*media_type = _filter->media_type;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_folder_filter_create(media_folder_filter_h* filter)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;
	if(filter == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	media_folder_filter_s* _filter = (media_folder_filter_s*)calloc(1, sizeof(media_folder_filter_s));

	if(_filter == NULL)	
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		ret = MEDIA_CONTENT_ERROR_OUT_OF_MEMORY ;
	}	
	else 
	{
	
		_filter->offset = -1;
		_filter->count = -1;
		_filter->order = MEDIA_CONTENT_SORT_NONE;;
		_filter->search_type = MEDIA_FOLDER_SEARCH_NONE;
		_filter->keyword = NULL;
		
		*filter = (media_folder_filter_h)_filter;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}

	return ret;

}

int media_folder_filter_destroy(media_folder_filter_h filter)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;	
	if(_filter) 
	{
		if(_filter->keyword) 
		{
			free(_filter->keyword);
		}						
		free(_filter);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}



int media_folder_filter_set_offset(media_folder_filter_h filter, int offset, int count)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;	
	if(_filter) 
	{
		_filter->offset = offset;
		_filter->count = count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_folder_filter_set_search_keyword(media_folder_filter_h filter,media_folder_search_type_e search_type,const char *search_keyword)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;
	if(_filter) 
	{

		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			free(_filter->keyword);
			_filter->keyword = NULL;
		}
	
		if(search_type == MEDIA_FOLDER_SEARCH_BY_FOLDER_NAME)
		{	
			if((search_keyword != NULL) && (strlen(search_keyword) > 0))
			{
				_filter->search_type = search_type;
				_filter->keyword = strdup(search_keyword);
				if(_filter->keyword == NULL)
				{
					LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
					return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
				}
			}
			else
			{
				LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
		}
		else if(search_type == MEDIA_FOLDER_SEARCH_NONE)
		{
			_filter->search_type = search_type;
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
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


int media_folder_filter_set_order(media_folder_filter_h filter, media_content_order_e order)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;	
	if(_filter) 
	{
		_filter->order = order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


//-----------------------------------------
int media_folder_filter_get_offset(media_folder_filter_h filter, int* offset, int* count)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;	
	if(_filter) 
	{
		*offset = _filter->offset;
		*count = _filter->count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_folder_filter_get_search_keyword(media_folder_filter_h filter,media_folder_search_type_e* search_type, char **search_keyword)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;
	if(_filter && (search_type != NULL)) 
	{
		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			*search_keyword = strdup(_filter->keyword);
			if(*search_keyword == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}

			*search_type  =_filter->search_type;
		}
		else
		{
			*search_type = _filter->search_type;
			*search_keyword = NULL;
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


int media_folder_filter_get_order(media_folder_filter_h filter, media_content_order_e* order)
{
	int ret;
	media_folder_filter_s* _filter = (media_folder_filter_s*)filter;	
	if(_filter) 
	{
		*order = _filter->order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_tag_filter_create( media_tag_filter_h* filter)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;
	if(filter == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	media_tag_filter_s* _filter = (media_tag_filter_s*)calloc(1, sizeof(media_tag_filter_s));

	if(_filter == NULL)	
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		ret = MEDIA_CONTENT_ERROR_OUT_OF_MEMORY ;
	}	
	else 
	{
		_filter->offset = -1;
		_filter->count = -1;
		_filter->order = MEDIA_CONTENT_SORT_NONE;
		_filter->search_type = MEDIA_INFO_SEARCH_NONE;
		_filter->keyword = NULL;

		*filter = (media_tag_filter_h)_filter;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}

	return ret;

}

int media_tag_filter_destroy(media_tag_filter_h filter)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;	
	if(_filter) 
	{
		if(_filter->keyword) 
		{
			free(_filter->keyword);
		}						
		free(_filter);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}




int media_tag_filter_set_offset(media_tag_filter_h filter, int offset, int count)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;	
	if(_filter) 
	{
		_filter->offset = offset;
		_filter->count = count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_tag_filter_set_search_keyword(media_tag_filter_h filter,media_tag_search_type_e search_type,const char *search_keyword)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;
	if(_filter) 
	{

		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			free(_filter->keyword);
			_filter->keyword = NULL;
		}

		if(search_type == MEDIA_TAG_SEARCH_BY_TAG_NAME)
		{	
			if((search_keyword != NULL) && (strlen(search_keyword) > 0))
			{
				_filter->search_type = search_type;
				_filter->keyword = strdup(search_keyword);			
				if(_filter->keyword == NULL)
				{
					LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
					return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
				}
			}
			else
			{
				LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
		}
		else if(search_type == MEDIA_TAG_SEARCH_NONE)
		{
			_filter->search_type = search_type;
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
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


int media_tag_filter_set_order(media_tag_filter_h filter, media_content_order_e order)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;	
	if(_filter) 
	{
		_filter->order = order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_tag_filter_get_offset(media_tag_filter_h filter, int* offset, int* count)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;	
	if(_filter) 
	{
		*offset = _filter->offset;
		*count = _filter->count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_tag_filter_get_search_keyword(media_tag_filter_h filter,media_tag_search_type_e *search_type, char **search_keyword)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;
	if(_filter && (search_type != NULL)) 
	{
		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			*search_keyword = strdup(_filter->keyword);
			if(*search_keyword == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}

			*search_type = _filter->search_type;
		}
		else
		{
			*search_type = _filter->search_type;
			*search_keyword = NULL;
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


int media_tag_filter_get_order(media_tag_filter_h filter, media_content_order_e* order)
{
	int ret;
	media_tag_filter_s* _filter = (media_tag_filter_s*)filter;	
	if(_filter) 
	{
		*order = _filter->order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_audio_filter_create(media_audio_filter_h* filter)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;
	if(filter == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	media_audio_filter_s* _filter = (media_audio_filter_s*)calloc(1, sizeof(media_audio_filter_s));

	if(_filter == NULL)	
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		ret = MEDIA_CONTENT_ERROR_OUT_OF_MEMORY ;
	}	
	else 
	{
		_filter->offset = -1;
		_filter->count = -1;
		_filter->order = MEDIA_CONTENT_SORT_NONE;
		_filter->search_type = MEDIA_AUDIO_SEARCH_NONE;
		_filter->keyword = NULL;

		*filter = (media_audio_filter_h)_filter;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}

	return ret;

}


int media_audio_filter_destroy(media_audio_filter_h filter)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;	
	if(_filter) 
	{
		if(_filter->keyword) 
		{
			free(_filter->keyword);
		}						
		free(_filter);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}


int media_audio_filter_set_offset(media_audio_filter_h filter, int offset, int count)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;	
	if(_filter) 
	{
		_filter->offset = offset;
		_filter->count = count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_audio_filter_set_search_keyword(media_audio_filter_h filter,media_audio_search_type_e search_type,const char *search_keyword)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;
	if(_filter) 
	{


		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			free(_filter->keyword);
			_filter->keyword = NULL;
		}

		if((search_type == MEDIA_AUDIO_SEARCH_BY_PLAYLIST) || 
				(search_type == MEDIA_AUDIO_SEARCH_BY_ARTIST) ||
				(search_type == MEDIA_AUDIO_SEARCH_BY_GENRE) ||
				(search_type == MEDIA_AUDIO_SEARCH_BY_ALBUM) ||
				(search_type == MEDIA_AUDIO_SEARCH_BY_AUTHOR) ||
				(search_type == MEDIA_AUDIO_SEARCH_NONE) )
		{	
			if((search_keyword != NULL) && (strlen(search_keyword) > 0))
			{
				_filter->search_type = search_type;
				_filter->keyword = strdup(search_keyword);			
				if(_filter->keyword == NULL)
				{
					LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
					return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
				}
			}
			else
			{
				LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
				return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			}
		}
		else if(search_type == MEDIA_AUDIO_SEARCH_NONE)
		{
			_filter->search_type = search_type;
		}
		else
		{
			LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
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


int media_audio_filter_set_order(media_audio_filter_h filter, media_content_order_e order)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;	
	if(_filter) 
	{
		_filter->order = order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

int media_audio_filter_get_offset(media_audio_filter_h filter, int* offset, int* count)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;	
	if(_filter) 
	{
		*offset = _filter->offset;
		*count = _filter->count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{	
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int media_audio_filter_get_search_keyword(media_audio_filter_h filter,media_audio_search_type_e* search_type,char **keyword)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;
	if(_filter && (search_type != NULL)) 
	{
		if((_filter->keyword != NULL) && (strlen(_filter->keyword) > 0))
		{
			*keyword = strdup(_filter->keyword);
			if(*keyword == NULL)
			{
				LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}

			*search_type = _filter->search_type;
		}
		else
		{
			*search_type = _filter->search_type;
			*keyword = NULL;
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


int media_audio_filter_get_order(media_audio_filter_h filter, media_content_order_e* order)
{
	int ret;
	media_audio_filter_s* _filter = (media_audio_filter_s*)filter;	
	if(_filter) 
	{
		*order = _filter->order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}


int video_bookmark_filter_create(video_bookmark_filter_h* filter)
{
	int ret= MEDIA_CONTENT_ERROR_NONE;
	if(filter == NULL)
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	video_bookmark_filter_s* _filter = (video_bookmark_filter_s*)calloc(1, sizeof(video_bookmark_filter_s));

	if(_filter == NULL)	
	{
		LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
		ret = MEDIA_CONTENT_ERROR_OUT_OF_MEMORY ;
	}	
	else 
	{

		_filter->offset = -1;
		_filter->count = -1;
		_filter->order = MEDIA_CONTENT_SORT_NONE;

		*filter = (video_bookmark_filter_h)_filter;
		
		ret = MEDIA_CONTENT_ERROR_NONE;
	}

	return ret;

}


int video_bookmark_filter_destroy(video_bookmark_filter_h filter)
{
	int ret;
	video_bookmark_filter_s* _filter = (video_bookmark_filter_s*)filter;	
	if(_filter) 
	{				
		free(_filter);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}


int video_bookmark_filter_set_offset(video_bookmark_filter_h filter, int offset, int count)
{
	int ret;
	video_bookmark_filter_s* _filter = (video_bookmark_filter_s*)filter;	
	if(_filter) 
	{
		_filter->offset = offset;
		_filter->count = count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

int video_bookmark_filter_set_order(video_bookmark_filter_h filter, media_content_order_e order)
{
	int ret;
	video_bookmark_filter_s* _filter = (video_bookmark_filter_s*)filter;	
	if(_filter) 
	{
		_filter->order = order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

int video_bookmark_filter_get_offset(video_bookmark_filter_h filter, int* offset, int* count)
{
	int ret;
	video_bookmark_filter_s* _filter = (video_bookmark_filter_s*)filter;	
	if(_filter) 
	{
		*offset = _filter->offset;
		*count = _filter->count;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

int video_bookmark_filter_get_order(video_bookmark_filter_h filter, media_content_order_e* order)
{
	int ret;
	video_bookmark_filter_s* _filter = (video_bookmark_filter_s*)filter;	
	if(_filter) 
	{
		*order = _filter->order;

		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else 
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;	

}

