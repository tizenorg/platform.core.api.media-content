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



#include <media_image.h>
#include <media_content.h>
#include <media_info_private.h>
#include <visual-svc-types.h>
#include <visual-svc.h>
#include <media-svc.h>

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"



#define DUPLICATE_STRING(destination, src)        \
{                                                 \
    char* tmp = src;                              \
    if(tmp != NULL && strlen(tmp) > 0)            \
    {                                             \
        char* new_str = strdup(tmp);              \
        destination = new_str;      	          \
    }                                             \
    else                                          \
    {                                             \
        destination = NULL;                       \
    }                                             \
}

#define DUPLICATE_FIELD(field) DUPLICATE_STRING(_dst->field, _src->field)

int image_meta_destroy(image_meta_h image)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image)
	{
	        if(_image->image_id)
			free(_image->image_id);
        	if(_image->thumbnail)
			free(_image->thumbnail);
		if(_image->description)
			free(_image->description);

		free(_image);
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return ret;

}


int image_meta_clone(image_meta_h* dst, image_meta_h src)
{
	int ret;
	image_meta_s* _src = (image_meta_s*)src;

	if(_src != NULL)
	{
	
		image_meta_s* _dst = (image_meta_s*)calloc(1,sizeof(image_meta_s));
		if (NULL == _dst)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		_dst->image_id = strdup(_src->image_id);
		_dst->longitude = _src->longitude;
		_dst->latitude= _src->latitude;
		_dst->width = _src->width;
		_dst->height = _src->height;
		_dst->orientation = _src->orientation;
		_dst->date_taken = _src->date_taken;

	       	DUPLICATE_FIELD(thumbnail)
	        DUPLICATE_FIELD(description)

		ret = MEDIA_CONTENT_ERROR_NONE;
        	*dst = (image_meta_h)_dst;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
      	ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}

int image_meta_get_longitude(image_meta_h image, double* longitude)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image && longitude)
	{
		*longitude= _image->longitude;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int image_meta_get_latitude(image_meta_h image, double* latitude)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image && latitude)
	{
		*latitude = _image->latitude;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}

int image_meta_get_description(image_meta_h image, char** description)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image && description)
	{
		if((_image->description != NULL) && (strlen(_image->description) > 0))
		{
			*description = strdup(_image->description);
			if (NULL == *description)
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
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int image_meta_get_width(image_meta_h image, int* width)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image && width)
	{
		*width = _image->width;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int image_meta_get_height(image_meta_h image, int* height)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image && height)
	{
		*height = _image->height;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int image_meta_get_orientation(image_meta_h image, media_content_orientation_e* orientation)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image)
	{
		*orientation = _image->orientation;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}
int image_meta_get_date_taken(image_meta_h image,time_t* date_taken)
{
	int ret;
	image_meta_s* _image = (image_meta_s*)image;
	if(_image && date_taken)
	{
		*date_taken = _image->date_taken;
		ret = MEDIA_CONTENT_ERROR_NONE;
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;

}


