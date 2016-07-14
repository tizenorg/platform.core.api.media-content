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


#ifndef __TIZEN_MEDIA_PVR_H__
#define __TIZEN_MEDIA_PVR_H__

#include <media_content_internal.h>
#include <media_content_type.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* The enumerations of PVR content Resolution*/
typedef enum {
	MEDIA_PVR_RESOLUTION_DEFAULT = 0,
	MEDIA_PVR_RESOLUTION_288I,
	MEDIA_PVR_RESOLUTION_480I,
	MEDIA_PVR_RESOLUTION_480P,
	MEDIA_PVR_RESOLUTION_576I,
	MEDIA_PVR_RESOLUTION_576P,
	MEDIA_PVR_RESOLUTION_720P,
	MEDIA_PVR_RESOLUTION_1080I,
	MEDIA_PVR_RESOLUTION_1080P,
	MEDIA_PVR_RESOLUTION_AUDIO_ONLY,
	MEDIA_PVR_RESOLUTION_MAX
} media_pvr_resolution_e;

/* The enumerations of PVR content aspectratio*/
typedef enum {
	MEDIA_PVR_ASPECTRATIO_UNKNOWN	= 0,
	MEDIA_PVR_ASPECTRATIO_100_100		= 1, /* 1:1 */
	MEDIA_PVR_ASPECTRATIO_300_400		= 2, /* 3:4 */
	MEDIA_PVR_ASPECTRATIO_900_1600	= 3, /* 9:16 */
	MEDIA_PVR_ASPECTRATIO_100_221		= 4, /* 1:2.21 */
} media_pvr_aspectratio_e;

int media_pvr_get_media_count_from_db(filter_h filter, int *media_count);
int media_pvr_foreach_media_from_db(filter_h filter, media_pvr_cb callback, void *user_data);
int media_pvr_destroy(media_pvr_h pvr);
int media_pvr_clone(media_pvr_h *dst, media_pvr_h src);
int media_pvr_get_pvr_from_db(const char *media_id, media_pvr_h *pvr);
int media_pvr_get_media_id(media_pvr_h pvr, char **media_id);
int media_pvr_get_channel_name(media_pvr_h pvr, char **channel_name);
int media_pvr_get_channel_num(media_pvr_h pvr, char **channel_num);
int media_pvr_get_program_title(media_pvr_h pvr, char **program_title);
int media_pvr_get_program_crid(media_pvr_h pvr, char **program_crid);
int media_pvr_get_guidance(media_pvr_h pvr, char **guidance);
int media_pvr_get_synopsis(media_pvr_h pvr, char **synopsis);
int media_pvr_get_genre(media_pvr_h pvr, char **genre);
int media_pvr_get_language(media_pvr_h pvr, char **language);
int media_pvr_get_path(media_pvr_h pvr, char **path);
int media_pvr_get_storage_id(media_pvr_h pvr, char **storage_id);
int media_pvr_get_size(media_pvr_h pvr, unsigned long long *size);
int media_pvr_get_timezone(media_pvr_h pvr, int *timezone);
int media_pvr_get_ptc(media_pvr_h pvr, int *ptc);
int media_pvr_get_major(media_pvr_h pvr, int *major);
int media_pvr_get_minor(media_pvr_h pvr, int *minor);
int media_pvr_get_channel_type(media_pvr_h pvr, int *channel_type);
int media_pvr_get_program_num(media_pvr_h pvr, int *program_num);
int media_pvr_get_duration(media_pvr_h pvr, int *duration);
int media_pvr_get_embargo_time(media_pvr_h pvr, int *embaro_time);
int media_pvr_get_expiry_time(media_pvr_h pvr, int *expiry_time);
int media_pvr_get_parental_rating(media_pvr_h pvr, int *parental_rating);
int media_pvr_get_start_time(media_pvr_h pvr, int *start_time);
int media_pvr_get_program_start_time(media_pvr_h pvr, int *program_start_time);
int media_pvr_get_program_end_time(media_pvr_h pvr, int *end_time);
int media_pvr_get_program_date(media_pvr_h pvr, int *program_date);
int media_pvr_get_timer_record(media_pvr_h pvr, bool* timer_record);
int media_pvr_get_series_record(media_pvr_h pvr, bool* series_record);
int media_pvr_get_hd(media_pvr_h pvr, int* hd);
int media_pvr_get_subtitle(media_pvr_h pvr, bool* subtitle);
int media_pvr_get_ttx(media_pvr_h pvr, bool* ttx);
int media_pvr_get_ad(media_pvr_h pvr, bool* ad);
int media_pvr_get_hard_of_hearing_radio(media_pvr_h pvr, bool* hardOfHearingRadio);
int media_pvr_get_data_service(media_pvr_h pvr, bool* data_service);
int media_pvr_get_content_lock(media_pvr_h pvr, bool* content_lock);
int media_pvr_get_content_watch(media_pvr_h pvr, bool* content_watch);
int media_pvr_get_has_audio_only(media_pvr_h pvr, bool* has_audio_only);
int media_pvr_get_is_local_record(media_pvr_h pvr, bool* is_local_record);
int media_pvr_get_resolution(media_pvr_h pvr, media_pvr_resolution_e* resolution);
int media_pvr_get_aspectratio(media_pvr_h pvr, media_pvr_aspectratio_e* aspectratio);
int media_pvr_get_modified_month(media_pvr_h pvr, char **modified_month);
int media_pvr_get_sports_type(media_pvr_h pvr, int* sports_type);
int media_pvr_get_guidance_length(media_pvr_h pvr, int* guidance_length);
int media_pvr_get_tvmode(media_pvr_h pvr, int* tvmode);
int media_pvr_get_play_count(media_pvr_h pvr, int* play_count);
int media_pvr_get_private_data(media_pvr_h pvr, char **private_data);
int media_pvr_get_highlight(media_pvr_h pvr, int *highlight);
int media_pvr_set_play_count(media_pvr_h pvr, int play_count);
int media_pvr_set_program_title(media_pvr_h pvr, const char *program_title);
int media_pvr_set_content_lock(media_pvr_h pvr, bool content_lock);
int media_pvr_set_content_watch(media_pvr_h pvr, bool content_watch);
int media_pvr_set_highlight(media_pvr_h pvr, bool highlight);
int media_pvr_update_to_db(media_pvr_h pvr);
int media_pvr_group_foreach_media_from_db(const char *group_name, media_group_e group, filter_h filter, media_pvr_cb callback, void *user_data);
int media_pvr_set_is_local_record(const char *pvr_path, bool is_local_record);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_PVR_H__ */
