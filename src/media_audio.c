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


#include <media_info_private.h>


int audio_meta_destroy(audio_meta_h audio)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		SAFE_FREE(_audio->media_id);
		SAFE_FREE(_audio->title);
		SAFE_FREE(_audio->album);
		SAFE_FREE(_audio->artist);
		SAFE_FREE(_audio->album_artist);
		SAFE_FREE(_audio->genre);
		SAFE_FREE(_audio->composer);
		SAFE_FREE(_audio->year);
		SAFE_FREE(_audio->recorded_date);
		SAFE_FREE(_audio->copyright);
		SAFE_FREE(_audio->track_num);
		SAFE_FREE(_audio);

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_clone(audio_meta_h *dst, audio_meta_h src)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_src = (audio_meta_s*)src;

	if (_src != NULL) {
		audio_meta_s *_dst = (audio_meta_s*)calloc(1, sizeof(audio_meta_s));
		media_content_retvm_if(_dst == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");

		if (_src->media_id != NULL) {
			_dst->media_id = strdup(_src->media_id);
			if (_dst->media_id == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->title != NULL) {
			_dst->title = strdup(_src->title);
			if (_dst->title == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->album != NULL) {
			_dst->album = strdup(_src->album);
			if (_dst->album == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->artist != NULL) {
			_dst->artist = strdup(_src->artist);
			if (_dst->artist == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->album_artist != NULL) {
			_dst->album_artist = strdup(_src->album_artist);
			if (_dst->album_artist == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->genre != NULL) {
			_dst->genre = strdup(_src->genre);
			if (_dst->genre == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->composer != NULL) {
			_dst->composer = strdup(_src->composer);
			if (_dst->composer == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->year != NULL) {
			_dst->year = strdup(_src->year);
			if (_dst->year == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->recorded_date != NULL) {
			_dst->recorded_date = strdup(_src->recorded_date);
			if (_dst->recorded_date == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->copyright != NULL) {
			_dst->copyright = strdup(_src->copyright);
			if (_dst->copyright == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		if (_src->track_num != NULL) {
			_dst->track_num = strdup(_src->track_num);
			if (_dst->track_num == NULL) {
				audio_meta_destroy((audio_meta_h)_dst);
				media_content_error("OUT_OF_MEMORY(0x%08x)", MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
				return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
			}
		}

		_dst->bitrate = _src->bitrate;
		_dst->bitpersample = _src->bitpersample;
		_dst->samplerate = _src->samplerate;
		_dst->channel = _src->channel;
		_dst->duration = _src->duration;
		_dst->played_count = _src->played_count;
		_dst->played_time = _src->played_time;
		_dst->played_position = _src->played_position;

		*dst = (audio_meta_h)_dst;

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_media_id(audio_meta_h audio, char **media_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;
	if (_audio) {
		if (STRING_VALID(_audio->media_id)) {
			*media_id = strdup(_audio->media_id);
			media_content_retvm_if(*media_id == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
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

int audio_meta_get_album(audio_meta_h audio, char **album)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;
	if (_audio) {
		if (_audio->album != NULL) {
			*album = strdup(_audio->album);		/*album can be empty string*/
			media_content_retvm_if(*album == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*album = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE;

	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_artist(audio_meta_h audio, char **artist)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->artist != NULL) {
			*artist = strdup(_audio->artist);	/*artist can be empty string*/
			media_content_retvm_if(*artist == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*artist = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE;

	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_album_artist(audio_meta_h audio, char **album_artist)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->album_artist != NULL) {
			*album_artist = strdup(_audio->album_artist);	/*album_artist can be empty string*/
			media_content_retvm_if(*album_artist == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*album_artist = NULL;
		}
		ret = MEDIA_CONTENT_ERROR_NONE;

	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_genre(audio_meta_h audio, char **genre)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->genre != NULL) {
			*genre = strdup(_audio->genre);	/*genre can be empty string*/
			media_content_retvm_if(*genre == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
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

int audio_meta_get_composer(audio_meta_h audio, char **composer)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->composer != NULL) {
			*composer = strdup(_audio->composer);	/*composer can be empty string*/
			media_content_retvm_if(*composer == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*composer = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_year(audio_meta_h audio, char **year)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->year != NULL) {
			*year = strdup(_audio->year);	/*year can be empty string*/
			media_content_retvm_if(*year == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*year = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_recorded_date(audio_meta_h audio, char **recorded_date)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->recorded_date != NULL) {
			*recorded_date = strdup(_audio->recorded_date);
			media_content_retvm_if(*recorded_date == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*recorded_date = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_copyright(audio_meta_h audio, char **copyright)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->copyright != NULL) {
			*copyright = strdup(_audio->copyright);	/*copyright can be empty string*/
			media_content_retvm_if(*copyright == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*copyright = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_track_num(audio_meta_h audio, char **track_num)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		if (_audio->track_num != NULL) {
			*track_num = strdup(_audio->track_num);	/*track_num can be empty string*/
			media_content_retvm_if(*track_num == NULL, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY, "OUT_OF_MEMORY");
		} else {
			*track_num = NULL;
		}

		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_bit_rate(audio_meta_h audio, int *bit_rate)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio && bit_rate) {
		*bit_rate = _audio->bitrate;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_bitpersample(audio_meta_h audio, int *bitpersample)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio && bitpersample) {
		*bitpersample = _audio->bitpersample;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_sample_rate(audio_meta_h audio, int *sample_rate)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio && sample_rate) {
		*sample_rate = _audio->samplerate;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_channel(audio_meta_h audio, int *channel)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio && channel) {
		*channel = _audio->channel;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_duration(audio_meta_h audio, int *duration)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		*duration = _audio->duration;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_played_count(audio_meta_h audio, int *played_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio && played_count) {
		*played_count = _audio->played_count;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_played_time(audio_meta_h audio, time_t* played_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		*played_time = _audio->played_time;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_get_played_position(audio_meta_h audio, int *played_position)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if (_audio) {
		*played_position = _audio->played_position;
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_set_played_count(audio_meta_h audio, int played_count)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if ((_audio != NULL) && (played_count >= 0)) {
		_audio->played_count = played_count;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_set_played_time(audio_meta_h audio, time_t played_time)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if ((_audio != NULL) && (played_time >= 0)) {
		_audio->played_time = played_time;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_set_played_position(audio_meta_h audio, int played_position)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;

	if ((_audio != NULL) && (played_position >= 0)) {
		_audio->played_position = played_position;
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}

int audio_meta_update_to_db(audio_meta_h audio)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_s *_audio = (audio_meta_s*)audio;
	char *sql = NULL;

	if (_audio != NULL && STRING_VALID(_audio->media_id)) {
		char storage_id[MEDIA_CONTENT_UUID_SIZE+1] = {0, };
		memset(storage_id, 0x00, sizeof(storage_id));

		ret = _media_db_get_storage_id_by_media_id(_audio->media_id, storage_id);
		media_content_retv_if(ret != MEDIA_CONTENT_ERROR_NONE, ret);

		sql = sqlite3_mprintf(UPDATE_AV_META_FROM_MEDIA, storage_id, _audio->played_count, _audio->played_time, _audio->played_position, _audio->media_id);
		ret = _content_query_sql(sql);
		SQLITE3_SAFE_FREE(sql);
	} else {
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return ret;
}
