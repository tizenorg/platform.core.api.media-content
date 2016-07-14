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


#ifndef __TIZEN_MEDIA_UHD_H__
#define __TIZEN_MEDIA_UHD_H__

#include <media_content_internal.h>
#include <media_content_type.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int media_uhd_get_media_count_from_db(filter_h filter, int *media_count);
int media_uhd_foreach_media_from_db(filter_h filter, media_uhd_cb callback, void *user_data);
int media_uhd_destroy(media_uhd_h uhd);
int media_uhd_clone(media_uhd_h *dst, media_uhd_h src);

int media_uhd_get_uhd_from_db(const char *media_id, media_uhd_h *uhd);
int media_uhd_get_media_id(media_uhd_h uhd, char **media_id);
int media_uhd_get_storage_id(media_uhd_h uhd, char **storage_id);
int media_uhd_get_path(media_uhd_h uhd, char **path);
int media_uhd_get_size(media_uhd_h uhd, unsigned long long *size);
int media_uhd_get_content_id(media_uhd_h uhd, char **content_id);
int media_uhd_get_content_title(media_uhd_h uhd, char **content_title);
int media_uhd_get_file_name(media_uhd_h uhd, char **file_name);
int media_uhd_get_release_date(media_uhd_h uhd, char **release_date);
int media_uhd_get_modified_time(media_uhd_h uhd, time_t *modified_time);
int media_uhd_get_played_position(media_uhd_h uhd, int *played_position);
int media_uhd_get_sub_type(media_uhd_h uhd, int *sub_type);
int media_uhd_get_played_count(media_uhd_h uhd, int *played_count);

int media_uhd_set_played_position(media_uhd_h uhd, int played_position);
int media_uhd_set_content_title(media_uhd_h uhd, const char *content_title);
int media_uhd_set_release_date(media_uhd_h uhd, const char *release_date);
int media_uhd_set_sub_type(media_uhd_h uhd, int sub_type);
int media_uhd_set_played_count(media_uhd_h uhd, int played_count);

int media_uhd_update_to_db(media_uhd_h uhd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_UHD_H__ */
