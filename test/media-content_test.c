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

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <media_content.h>
#include <media_info_private.h>
#include <dlog.h>
#include <pthread.h>
#include <glib.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_N_MEDIACONTENT"

filter_h g_filter = NULL;
filter_h g_filter_g = NULL;	//filter for group like folder, tag, playlist, album, year ...


#define test_audio_id	"0f999626-6218-450c-a4ad-181a3bab6ebf"
#define test_video_id	"c1a92494-cc5b-4d74-aa7d-253199234548"
#define test_image_id "db1c184c-6f31-43b4-b924-8c00ac5b6197"

bool get_audio_meta(audio_meta_h audio)
{
	char *c_value = NULL;
	int i_value = 0;
	time_t t_value = 0;

	media_content_debug("=== audio meta === \n");

	audio_meta_get_media_id(audio, &c_value);
	media_content_debug("audio_id : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_title(audio, &c_value);
	media_content_debug("title : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_album(audio, &c_value);
	media_content_debug("album : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_artist(audio, &c_value);
	media_content_debug("artist : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_genre(audio, &c_value);
	media_content_debug("genre : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_composer(audio, &c_value);
	media_content_debug("composer : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_year(audio, &c_value);
	media_content_debug("year : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_recorded_date(audio, &c_value);
	media_content_debug("recorded_date : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_copyright(audio, &c_value);
	media_content_debug("copyright : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_track_num(audio, &c_value);
	media_content_debug("track_num : [%s] \n", c_value);
	SAFE_FREE(c_value);

	audio_meta_get_bit_rate(audio, &i_value);
	media_content_debug("bitrate : [%d] \n", i_value);

	audio_meta_get_sample_rate(audio, &i_value);
	media_content_debug("samplerate : [%d] \n", i_value);

	audio_meta_get_channel(audio, &i_value);
	media_content_debug("channel : [%d] \n", i_value);

	audio_meta_get_duration(audio, &i_value);
	media_content_debug("duration : [%d] \n", i_value);

	audio_meta_get_played_count(audio, &i_value);
	media_content_debug("played_count : [%d] \n", i_value);

	audio_meta_get_played_time(audio, &t_value);
	media_content_debug("played_time : [%d] \n", t_value);

	audio_meta_get_played_position(audio, &i_value);
	media_content_debug("played_position : [%d] \n", i_value);

	return true;
}

bool get_video_meta(video_meta_h video)
{
	char *c_value = NULL;
	int i_value = 0;
	time_t t_value = 0;

	media_content_debug("=== video meta === \n");

	video_meta_get_media_id(video, &c_value);
	media_content_debug("video_id : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_title(video, &c_value);
	media_content_debug("title : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_album(video, &c_value);
	media_content_debug("album : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_artist(video, &c_value);
	media_content_debug("artist : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_genre(video, &c_value);
	media_content_debug("genre : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_composer(video, &c_value);
	media_content_debug("omposer : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_year(video, &c_value);
	media_content_debug("year : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_recorded_date(video, &c_value);
	media_content_debug("recorded_date : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_copyright(video, &c_value);
	media_content_debug("copyright : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_track_num(video, &c_value);
	media_content_debug("track_num : [%s] \n", c_value);
	SAFE_FREE(c_value);

	video_meta_get_bit_rate(video, &i_value);
	media_content_debug("bitrate : [%d] \n", i_value);

	video_meta_get_duration(video, &i_value);
	media_content_debug("duration : [%d] \n", i_value);

	video_meta_get_width(video, &i_value);
	media_content_debug("width : [%d] \n", i_value);

	video_meta_get_height(video, &i_value);
	media_content_debug("height : [%d] \n", i_value);

	video_meta_get_played_count(video, &i_value);
	media_content_debug("played_count : [%d] \n", i_value);

	video_meta_get_played_time(video, &t_value);
	media_content_debug("played_time : [%d] \n", t_value);

	video_meta_get_played_position(video, &i_value);
	media_content_debug("played_position : [%d] \n", i_value);

	return true;
}

bool gallery_folder_list_cb(media_folder_h folder, void *user_data)
{
	media_folder_h new_folder = NULL;
	media_folder_clone(&new_folder, folder);

	GList **list = (GList**)user_data;
	*list = g_list_append(*list, new_folder);

	return true;
}

bool gallery_media_item_cb(media_info_h media, void *user_data)
{
	media_info_h new_media = NULL;
	media_info_clone(&new_media, media);

	GList **list = (GList**)user_data;
	*list = g_list_append(*list, new_media);

	return true;
}

bool gallery_tag_item_cb(media_tag_h tag, void *user_data)
{
	media_tag_h new_tag = NULL;
	media_tag_clone(&new_tag, tag);

	GList **list = (GList**)user_data;
	*list = g_list_append(*list, new_tag);

	return true;
}

bool gallery_bookmarks_cb(media_bookmark_h bookmark, void *user_data)
{
	media_bookmark_h new_bm = NULL;
	media_bookmark_clone(&new_bm, bookmark);

	GList **list = (GList**)user_data;
	*list = g_list_append(*list, new_bm);

	return true;
}

bool media_item_cb(media_info_h media, void *user_data)
{
	char *c_value = NULL;
	char *media_id = NULL;
	int i_value = 0;
	time_t t_value = 0;
	bool b_value = false;
	media_content_type_e media_type = 0;
	unsigned long long size = 0;

	if(media == NULL)
	{
		media_content_debug("NO Item \n");
		return true;
	}

	media_info_get_media_type(media, &media_type);
	media_content_debug("media_type : [%d] \n", media_type);

	media_info_get_media_id(media, &media_id);
	media_content_debug("media_id : [%s] \n", media_id);

#if 1
	if(media_type == MEDIA_CONTENT_TYPE_MUSIC)
	{
		audio_meta_h audio;

		if(media_info_get_audio(media, &audio) == MEDIA_CONTENT_ERROR_NONE)
		{
			get_audio_meta(audio);
			audio_meta_destroy(audio);
		}
		else
			media_content_error("[audio_error] \n");

	}
	else if(media_type == MEDIA_CONTENT_TYPE_IMAGE)
	{
		image_meta_h image;
		media_content_orientation_e orientation = 0;

		if(media_info_get_image(media, &image) == MEDIA_CONTENT_ERROR_NONE)
		{
			image_meta_get_orientation(image, &orientation);
			media_content_debug("[image] orientation : %d\n", orientation);
			image_meta_destroy(image);
		}
		else
			media_content_error("[image_error] \n");

	}
	else if(media_type == MEDIA_CONTENT_TYPE_VIDEO)
	{
		video_meta_h video;

		if(media_info_get_video(media, &video) == MEDIA_CONTENT_ERROR_NONE)
		{
			get_video_meta(video);
			video_meta_destroy(video);
		}
		else
			media_content_error("[video_error] \n");

	}
	else
	{
		media_content_debug("Other Content");
	}

	media_content_debug("=== media_info === \n");
	media_info_get_file_path(media, &c_value);
	media_content_debug("file_path : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_display_name(media, &c_value);
	media_content_debug("display_name : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_mime_type(media, &c_value);
	media_content_debug("mime_type : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_thumbnail_path(media, &c_value);
	media_content_debug("thumbnail_path : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_description(media, &c_value);
	media_content_debug("description : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_author(media, &c_value);
	media_content_debug("author : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_provider(media, &c_value);
	media_content_debug("provider : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_content_name(media, &c_value);
	media_content_debug("content_name : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_category(media, &c_value);
	media_content_debug("category : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_location_tag(media, &c_value);
	media_content_debug("location_tag : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_age_rating(media, &c_value);
	media_content_debug("age_rating : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_keyword(media, &c_value);
	media_content_debug("keyword : [%s] \n", c_value);
	SAFE_FREE(c_value);

	media_info_get_size(media, &size);
	media_content_debug("size : [%lld] \n", size);

	media_info_get_added_time(media, &t_value);
	media_content_debug("added_time : [%d] \n", t_value);

	media_info_get_modified_time(media, &t_value);
	media_content_debug("modified_time : [%d] \n", t_value);

	media_info_get_rating(media, &i_value);
	media_content_debug("rating : [%d] \n", i_value);

	media_info_get_favorite(media, &b_value);
	media_content_debug("favorite : [%d] \n", b_value);

	media_info_is_drm(media, &b_value);
	media_content_debug("is_drm : [%d] \n", b_value);

	media_info_set_location_tag(media, "Test location tag");
	media_info_update_to_db(media);
	SAFE_FREE(media_id);
#endif
	return true;
}

bool folder_list_cb(media_folder_h folder, void *user_data)
{
	int item_count;
	char *folder_id = NULL;
	char *folder_path = NULL;
	char *folder_name = NULL;
	media_content_storage_e storage_type;
	bool ret;
	media_folder_h *_folder = (media_folder_h*)user_data;

	if(folder != NULL)
	{
		media_folder_clone(_folder, folder);

		if(media_folder_get_folder_id(folder, &folder_id) != MEDIA_CONTENT_ERROR_NONE)
		{
			media_content_error("[ERROR] media_folder_get_folder_id is failed\n");
			return false;
		}
		media_content_debug("folder_id = [%s] \n", folder_id);

		if(media_folder_get_path(folder, &folder_path) != MEDIA_CONTENT_ERROR_NONE)
		{
			media_content_error("[ERROR] media_folder_get_path is failed\n");
			return false;
		}
		media_content_debug("folder_path = [%s] \n", folder_path);
		SAFE_FREE(folder_path);

		if(media_folder_get_name(folder, &folder_name) != MEDIA_CONTENT_ERROR_NONE)
		{
			media_content_error("[ERROR] media_folder_get_name is failed\n");
			return false;
		}
		media_content_debug("folder_name = [%s] \n", folder_name);
		SAFE_FREE(folder_name);

		if(media_folder_get_storage_type(folder, &storage_type) != MEDIA_CONTENT_ERROR_NONE)
		{
			media_content_error("[ERROR] media_folder_get_storage_type is failed\n");
			return false;
		}
		media_content_debug("storage_type = [%d] \n", storage_type);

		if(media_folder_get_media_count_from_db(folder_id, g_filter, &item_count) != MEDIA_CONTENT_ERROR_NONE)
		{
			media_content_error("[ERROR] media_folder_get_media_count_from_db is failed\n");
			return false;
		}

		media_folder_foreach_media_from_db(folder_id, g_filter, media_item_cb, NULL);

		SAFE_FREE(folder_id);
		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool test_album_from_db(int album_id)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_album_h album_h;
	int test_album_id = 0;
	char *album_name = NULL;
	char *artist = NULL;

	ret = media_album_get_album_from_db(album_id, &album_h);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		media_content_error("error when get album \n");
		return false;
	}

	if(media_album_get_album_id(album_h, &test_album_id) != MEDIA_CONTENT_ERROR_NONE)
		return false;

	media_content_debug("test_album_id : [%d] \n", test_album_id);

	if(media_album_get_name(album_h, &album_name) != MEDIA_CONTENT_ERROR_NONE)
		return false;

	media_content_debug("album_name : [%s] \n", album_name);

	if(media_album_get_artist(album_h, &artist) != MEDIA_CONTENT_ERROR_NONE)
		return false;

	media_content_debug("artist : [%s] \n", artist);

	SAFE_FREE(album_name);
	SAFE_FREE(artist);

	media_album_destroy(album_h);

	return true;
}

bool playlist_list_cb(media_playlist_h playlist, void *user_data)
{
	int playlist_id = 0;
	char *playlist_name = NULL;
	media_playlist_h playlist_h;

	media_content_debug("playlist_list_cb ====== \n");

	GList **list = (GList**)user_data;

	if(playlist == NULL)
	{
		media_content_debug(" playlist handle is NULL \n");
		return false;
	}

	media_playlist_get_playlist_id(playlist, &playlist_id);
	media_content_debug("playlist_id : %d \n", playlist_id);

	if(user_data != NULL)
		*list = g_list_append(*list, (gpointer)playlist_id);

	media_playlist_get_name(playlist, &playlist_name);
	media_content_debug("playlist_name : %s \n", playlist_name);
	SAFE_FREE(playlist_name);

	media_playlist_get_playlist_from_db(playlist_id, NULL, &playlist_h);

	media_playlist_destroy(playlist_h);

	return true;
}

bool tag_list_cb(media_tag_h tag, void *user_data)
{
	int tag_id = 0;
	char *tag_name = NULL;

	if(tag == NULL)
	{
		media_content_debug(" tag handle is NULL \n");
		return false;
	}

	media_tag_get_tag_id(tag, &tag_id);
	media_content_debug("tag_id : %d \n", tag_id);

	media_tag_get_name(tag, &tag_name);
	media_content_debug("tag_name : %s \n", tag_name);
	SAFE_FREE(tag_name);

	return true;
}

bool bookmarks_cb(media_bookmark_h bookmark, void *user_data)
{
	media_bookmark_h *_bookmark = (media_bookmark_h*)bookmark;

	if(_bookmark != NULL)
	{
		char *name = NULL;
		time_t time = 0;
		int bookmark_id = 0;

		media_bookmark_get_bookmark_id(bookmark, &bookmark_id);
		media_content_debug("bookmark_id : %d \n", bookmark_id);

		media_bookmark_get_thumbnail_path(bookmark, &name);
		media_content_debug("bookmark thumbnail_path : %s \n", name);
		SAFE_FREE(name);

		media_bookmark_get_marked_time(bookmark, &time);
		media_content_debug("bookmark marked_time : %d \n", time);
	}

	return true;
}

bool album_list_cb(media_album_h album, void *user_data)
{
	int album_id = 0;
	char *album_name = NULL;
	char *artist = NULL;
	char *album_art = NULL;
	int media_count = 0;
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter;

	/*Set Filter*/
	char *condition = "MEDIA_TYPE=3";	/*MEDIA_TYPE 0-image, 1-video, 2-sound, 3-music, 4-other*/

	ret = media_filter_create(&filter);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to create filter \n");
		return ret;
	}
	ret = media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to set condition \n");
		return ret;
	}
	ret = media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_NOCASE);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to set order \n");
		return ret;
	}

	if(album != NULL)
	{
		if(media_album_get_album_id(album, &album_id) != MEDIA_CONTENT_ERROR_NONE)
			return false;

		media_content_debug("album_id : [%d] \n", album_id);

		if(media_album_get_name(album, &album_name) != MEDIA_CONTENT_ERROR_NONE)
			return false;

		media_content_debug("album_name : [%s] \n", album_name);

		if(media_album_get_artist(album, &artist) != MEDIA_CONTENT_ERROR_NONE)
			return false;

		media_content_debug("artist : [%s] \n", artist);

		if(media_album_get_album_art(album, &album_art) != MEDIA_CONTENT_ERROR_NONE)
			return false;

		media_content_debug("album_art : [%s] \n", album_art);

		SAFE_FREE(album_name);
		SAFE_FREE(artist);
		SAFE_FREE(album_art);

		if(media_album_get_media_count_from_db(album_id, filter, &media_count) != MEDIA_CONTENT_ERROR_NONE)
			return false;

		media_content_debug("media_count : [%d] \n", media_count);

		if(media_album_foreach_media_from_db(album_id, filter, media_item_cb, NULL) != MEDIA_CONTENT_ERROR_NONE)
			return false;

		test_album_from_db(album_id);
	}
	else
	{
		media_content_error("album item not Found!!\n");
		return true;
	}

	return true;
}

bool group_list_cb(const char *group_name, void *user_data)
{
	int media_count = 0;
	int *idx = user_data;

	media_content_debug("group item : [%s] [%d]\n", group_name, *idx);

	if(media_group_get_media_count_from_db(group_name, *idx, g_filter, &media_count) != MEDIA_CONTENT_ERROR_NONE)
		return false;

	media_content_debug("media_count : [%d] \n", media_count);

	if(media_group_foreach_media_from_db(group_name, *idx, g_filter, media_item_cb, NULL) != MEDIA_CONTENT_ERROR_NONE)
		return false;

	return true;
}

bool playlist_item_cb(int playlist_member_id, media_info_h media, void *user_data)
{
	media_content_debug("playlist_member_id : [%d] \n", playlist_member_id);

	GList **list = (GList**)user_data;
	*list = g_list_append(*list, (gpointer)playlist_member_id);

	//media_item_cb(media, user_data);

	return true;
}

int test_filter_create(void)
{
	media_content_debug("\n============Filter Create============\n\n");

	int ret = MEDIA_CONTENT_ERROR_NONE;

	/* Filter for media */
	char *condition = "MEDIA_TYPE=3";	/*MEDIA_TYPE 0-image, 1-video, 2-sound, 3-music, 4-other*/

	ret = media_filter_create(&g_filter);

	/* Set condition and collate
	 * Condition string : You can make where statement of sql.
	 * Colation : You can use collation when comparing.
	 * Ex) In case of FILE_NAME='Samsung' as condition string,
	 *     if you want to compare with NOCASE collation,
	 *     call media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_NOCASE);
	 *     if you want to compare in case-sensitive,
	 *     call media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	 */
	ret = media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);

	/* Collation of ordering
	 * If you want to get list, which is sorted by NOCASE,
	 * call media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_ARTIST, MEDIA_CONTENT_COLLATE_NOCASE);
	 * Or,
	 * call media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_ARTIST, MEDIA_CONTENT_COLLATE_DEFAULT);
	 */
	ret = media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_ARTIST, MEDIA_CONTENT_COLLATE_DEFAULT);

	/* Filter for group */
	char *g_condition = "TAG_NAME like \"\%my\%\"";
	//char *g_condition = "BOOKMARK_MARKED_TIME > 300";

	ret = media_filter_create(&g_filter_g);

	ret = media_filter_set_condition(g_filter_g, g_condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	ret = media_filter_set_order(g_filter_g, MEDIA_CONTENT_ORDER_DESC, TAG_NAME, MEDIA_CONTENT_COLLATE_DEFAULT);

	return ret;
}

int test_filter_destroy(void)
{
	media_content_debug("\n============Filter Create============\n\n");

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_destroy(g_filter);

	return ret;
}

int test_connect_database(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	media_content_debug("\n============DB Connection Test============\n\n");

	ret = media_content_connect();

	if(ret == MEDIA_CONTENT_ERROR_NONE)
	{
		media_content_debug("connection is success\n\n");
	}
	else
		media_content_error("connection is failed\n\n");

	return ret;
}

int test_gallery_scenario(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int i;
	filter_h filter = NULL;

	int count;
	GList *folder_list = NULL;
	media_folder_h folder_handle = NULL;

	/* First, Get folder list */
	ret = media_folder_foreach_folder_from_db(filter, gallery_folder_list_cb, &folder_list);
	if(ret < 0) {
		media_content_error("media_folder_foreach_folder_from_db failed: %d", ret);
		return -1;
	} else {
		media_content_debug("media_folder_foreach_folder_from_db success!!");
		char *folder_id;
		char *folder_name;
		char *folder_path;

		for(i = 0; i < g_list_length(folder_list); i++) {
			folder_handle = (media_folder_h)g_list_nth_data(folder_list, i);

			media_folder_get_folder_id(folder_handle, &folder_id);
			media_folder_get_name(folder_handle, &folder_name);
			media_folder_get_path(folder_handle, &folder_path);

			media_content_debug("folder_id [%d] : %s\n", i, folder_id);
			media_content_debug("folder_name [%d] : %s\n", i, folder_name);
			media_content_debug("folder_path [%d] : %s\n", i, folder_path);


			ret = media_folder_get_media_count_from_db(folder_id, filter, &count);
			/* User should free these string */
			SAFE_FREE(folder_id);
			SAFE_FREE(folder_name);
			SAFE_FREE(folder_path);
			if(ret < 0) {
				media_content_error("media_folder_get_media_count_from_db failed: %d", ret);
				return -1;
			} else {
				media_content_debug("media count [%d] : %d\n", i, count);
			}
		}
	}

	/* To check performance */
	struct timeval start, end;
	gettimeofday(&start, NULL);

	/* Second, Get all item list */
	media_info_h media_handle = NULL;
	GList *all_item_list = NULL;

	media_content_collation_e collate_type = MEDIA_CONTENT_COLLATE_NOCASE;
	media_content_order_e order_type = MEDIA_CONTENT_ORDER_DESC;
	media_filter_create(&filter);
	//media_filter_set_condition(filter, "MEDIA_TYPE = 0", collate_type);
	media_filter_set_order(filter, order_type, MEDIA_DISPLAY_NAME, collate_type);
	//media_filter_set_collate(filter, collate_type);

	ret = media_info_foreach_media_from_db(filter, gallery_media_item_cb, &all_item_list);
	if(ret < 0) {
		media_content_error("media_info_foreach_media_from_db failed: %d", ret);
		return -1;
	} else {
		media_content_debug("media_info_foreach_media_from_db success");
		media_content_type_e media_type;
		char *media_id = NULL;
		char *media_name = NULL;
		char *media_path = NULL;

		for(i = 0; i < g_list_length(all_item_list); i++) {
			media_handle = (media_info_h)g_list_nth_data(all_item_list, i);

			media_info_get_media_id(media_handle, &media_id);
			media_info_get_media_type(media_handle, &media_type);
			media_info_get_display_name(media_handle, &media_name);
			media_info_get_file_path(media_handle, &media_path);

			if(media_type == MEDIA_CONTENT_TYPE_IMAGE) {
				image_meta_h image_handle;
				int width, height;
				media_content_orientation_e orientation;
				char *datetaken;

				ret = media_info_get_image(media_handle, &image_handle);
				if(ret < 0) {
					media_content_error("media_info_get_image failed: %d", ret);
				} else {
					image_meta_get_width(image_handle, &width);
					image_meta_get_height(image_handle, &height);
					image_meta_get_orientation(image_handle, &orientation);
					image_meta_get_date_taken(image_handle, &datetaken);

					media_content_debug("This is Image\n");
					media_content_debug("Width : %d, Height : %d, Orientation : %d, Date taken : %s\n", width, height, orientation, datetaken);
				}

				SAFE_FREE(datetaken);
				image_meta_destroy(image_handle);

			} else if(media_type == MEDIA_CONTENT_TYPE_VIDEO) {
				video_meta_h video_handle;
				char *title, *artist, *album;
				int duration;
				time_t time_played;

				ret = media_info_get_video(media_handle, &video_handle);
				if(ret < 0) {
					media_content_error("media_info_get_video failed: %d", ret);
				} else {
					video_meta_get_title(video_handle, &title);
					video_meta_get_artist(video_handle, &artist);
					video_meta_get_album(video_handle, &album);
					video_meta_get_duration(video_handle, &duration);
					video_meta_get_played_time(video_handle, &time_played);

					media_content_debug("This is Video\n");
					media_content_debug("Title: %s, Album: %s, Artist: %s\nDuration: %d, Played time: %d\n", title, artist, album, duration, time_played);
				}

				SAFE_FREE(title);
				SAFE_FREE(artist);
				SAFE_FREE(album);

				video_meta_destroy(video_handle);
			}
			//media_content_debug("media_id [%d] : %s\n", i, media_id);
			//media_content_debug("media_name [%d] : %s\n", i, media_name);
			//media_content_debug("media_path [%d] : %s\n", i, media_path);

			SAFE_FREE(media_id);
			SAFE_FREE(media_name);
			SAFE_FREE(media_path);
		}
	}

	media_filter_destroy(filter);
	filter = NULL;

	/* To check performance */
	gettimeofday(&end, NULL);
	long time = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	printf("Time : %ld\n", time);

	/* Third, Get item list of a folder */
	GList *item_list = NULL;

	for(i = 0; i < g_list_length(folder_list); i++) {
		int j;
		char *folder_name;
		char *folder_id;
		folder_handle = (media_folder_h)g_list_nth_data(folder_list, i);

		media_folder_get_folder_id(folder_handle, &folder_id);
		media_folder_get_name(folder_handle, &folder_name);

		ret = media_folder_foreach_media_from_db(folder_id, filter, gallery_media_item_cb, &item_list);
		SAFE_FREE(folder_id);
		SAFE_FREE(folder_name);

		if(ret < 0) {
			media_content_error("media_folder_foreach_media_from_db failed: %d", ret);
			return -1;
		} else {
			media_content_error("media_folder_foreach_media_from_db success!", ret);
			char *media_id = NULL;
			char *media_name = NULL;
			char *media_path = NULL;
			media_content_type_e media_type = 0;

			for(j = 0; j < g_list_length(item_list); j++) {
				media_handle = (media_info_h)g_list_nth_data(item_list, j);

				media_info_get_media_id(media_handle, &media_id);
				media_info_get_display_name(media_handle, &media_name);
				media_info_get_file_path(media_handle, &media_path);
				media_info_get_media_type(media_handle, &media_type);

				media_content_debug("[%s] media_id [%d] : %s\n", folder_name, j, media_id);
				media_content_debug("[%s] media_type [%d] : %d\n", folder_name, j, media_type);
				media_content_debug("[%s] media_name [%d] : %s\n", folder_name, j, media_name);
				media_content_debug("[%s] media_path [%d] : %s\n", folder_name, j, media_path);

				if(media_type == MEDIA_CONTENT_TYPE_IMAGE) {
					image_meta_h image_handle;
					int width, height;
					media_content_orientation_e orientation;
					char *datetaken;

					ret = media_info_get_image(media_handle, &image_handle);
					if(ret < 0) {
						media_content_error("media_info_get_image failed: %d", ret);
					} else {
						image_meta_get_width(image_handle, &width);
						image_meta_get_height(image_handle, &height);
						image_meta_get_orientation(image_handle, &orientation);
						image_meta_get_date_taken(image_handle, &datetaken);

						media_content_debug("This is Image\n");
						media_content_debug("Width : %d, Height : %d, Orientation : %d, Date taken : %s\n", width, height, orientation, datetaken);
					}

					SAFE_FREE(datetaken);
					image_meta_destroy(image_handle);

				} else if(media_type == MEDIA_CONTENT_TYPE_VIDEO) {
					video_meta_h video_handle;
					char *title, *artist, *album;
					int duration;
					time_t time_played;

					ret = media_info_get_video(media_handle, &video_handle);
					if(ret < 0) {
						media_content_error("media_info_get_video failed: %d", ret);
					} else {
						video_meta_get_title(video_handle, &title);
						video_meta_get_artist(video_handle, &artist);
						video_meta_get_album(video_handle, &album);
						video_meta_get_duration(video_handle, &duration);
						video_meta_get_played_time(video_handle, &time_played);

						media_content_debug("This is Video\n");
						media_content_debug("Title: %s, Album: %s, Artist: %s\nDuration: %d, Played time: %d\n", title, artist, album, duration, time_played);
					}

					SAFE_FREE(title);
					SAFE_FREE(artist);
					SAFE_FREE(album);

					video_meta_destroy(video_handle);

					/* Get bookmar list in case of video */
					media_bookmark_h bm_handle;
					GList *bm_list = NULL;

					ret = media_info_foreach_bookmark_from_db(media_id, filter, gallery_bookmarks_cb, &bm_list);
					if(ret < 0) {
						media_content_error("media_info_foreach_bookmark_from_db failed: %d", ret);
					} else {
						media_content_error("media_info_foreach_bookmark_from_db success");
						int k;

						for(k = 0; k < g_list_length(bm_list); k++) {
							bm_handle = (media_bookmark_h)g_list_nth_data(bm_list, k);
							time_t marked_time;
							char *thumb_path = NULL;

							media_bookmark_get_marked_time(bm_handle, &marked_time);
							media_bookmark_get_thumbnail_path(bm_handle, &thumb_path);

							media_content_error("Bookmark time : %d\nBookmar thumb: %s\n", marked_time, thumb_path);
							SAFE_FREE(thumb_path);
						}

						/* Remove bookmark list */
						int l = 0;
						if(bm_list) {
							for(l = 0; l < g_list_length(bm_list); l++) {
								bm_handle = (media_bookmark_h)g_list_nth_data(bm_list, l);
								media_bookmark_destroy(bm_handle);
							}

							g_list_free(bm_list);
						}

					}
				}

				SAFE_FREE(media_id);
				SAFE_FREE(media_name);
				SAFE_FREE(media_path);
			}
		}
	}

	/* Get tag list */
	media_tag_h tag_handle = NULL;
	GList *tag_list = NULL;
	GList *media_list_in_tag = NULL;

	ret = media_tag_foreach_tag_from_db (filter, gallery_tag_item_cb, &tag_list);

	if(ret < 0) {
		media_content_error("media_tag_foreach_tag_from_db failed: %d", ret);
		return -1;
	} else {
		media_content_error("media_tag_foreach_tag_from_db success");
		char *tag_name;
		int tag_id;

		for(i = 0; i < g_list_length(tag_list); i++) {
			tag_handle = (media_tag_h)g_list_nth_data(tag_list, i);
			media_tag_get_tag_id(tag_handle, &tag_id);
			media_tag_get_name(tag_handle, &tag_name);

			printf("[%d] %s", tag_id, tag_name);

			ret = media_tag_foreach_media_from_db(tag_id, filter, gallery_media_item_cb, &media_list_in_tag);
			if(ret < 0) {
				media_content_error("media_tag_foreach_media_from_db failed: %d", ret);
				return -1;
			} else {
				media_content_error("media_tag_foreach_media_from_db success");
				int j = 0;
				media_info_h tag_media_handle;
				char *media_id = NULL;
				char *media_name = NULL;
				char *media_path = NULL;
				media_content_type_e media_type = 0;

				for(j = 0; j < g_list_length(media_list_in_tag); j++) {
					tag_media_handle = (media_info_h)g_list_nth_data(media_list_in_tag, j);
					media_info_get_media_id(tag_media_handle, &media_id);
					media_info_get_display_name(tag_media_handle, &media_name);
					media_info_get_file_path(tag_media_handle, &media_path);
					media_info_get_media_type(tag_media_handle, &media_type);

					media_content_debug("[%s] media_id [%d] : %s\n", tag_name, j, media_id);
					media_content_debug("[%s] media_type [%d] : %d\n", tag_name, j, media_type);
					media_content_debug("[%s] media_name [%d] : %s\n", tag_name, j, media_name);
					media_content_debug("[%s] media_path [%d] : %s\n", tag_name, j, media_path);
				}
				SAFE_FREE(media_id);
				SAFE_FREE(media_name);
				SAFE_FREE(media_path);
			}
			SAFE_FREE(tag_name);
		}
	}

	/* Remove folder list */
	if(folder_list) {
		for(i = 0; i < g_list_length(folder_list); i++) {
			folder_handle = (media_folder_h)g_list_nth_data(folder_list, i);
			media_folder_destroy(folder_handle);
		}

		g_list_free(folder_list);
	}

	/* Remove all items list */
	if(all_item_list) {
		for(i = 0; i < g_list_length(all_item_list); i++) {
			media_handle = (media_info_h)g_list_nth_data(all_item_list, i);
			media_info_destroy(media_handle);
		}

		g_list_free(all_item_list);
	}

	/* Remove items list */
	if(item_list) {
		for(i = 0; i < g_list_length(item_list); i++) {
			media_handle = (media_info_h)g_list_nth_data(item_list, i);
			media_info_destroy(media_handle);
		}

		g_list_free(item_list);
	}

	/* Remove tag list */
	if(tag_list) {
		for(i = 0; i < g_list_length(tag_list); i++) {
			tag_handle = (media_tag_h)g_list_nth_data(tag_list, i);
			media_tag_destroy(tag_handle);
		}

		g_list_free(tag_list);
	}

	/* Remove media list in a tag */
	if(media_list_in_tag) {
		for(i = 0; i < g_list_length(media_list_in_tag); i++) {
			media_handle = (media_info_h)g_list_nth_data(media_list_in_tag, i);
			media_info_destroy(media_handle);
		}

		g_list_free(media_list_in_tag);
	}

	return MEDIA_CONTENT_ERROR_NONE;
}

/*Get All Music file. sort by Title and not case sensitive*/
int test_get_all_music_files(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;
	filter_h filter;

	/*Set Filter*/
	char *condition = "MEDIA_TYPE=3";	/*0-image, 1-video, 2-sound, 3-music, 4-other*/

	ret = media_filter_create(&filter);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to create filter \n");
		return ret;
	}
	ret = media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to set condition \n");
		return ret;
	}
	ret = media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_NOCASE);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to set order \n");
		return ret;
	}

	/*Get Media Count*/
	ret = media_info_get_media_count_from_db(filter, &media_count);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_filter_destroy(filter);
		media_content_error("Fail to get media count \n");
		return ret;
	}

	media_content_debug("media_count : [%d],\n", media_count);

	ret = media_info_foreach_media_from_db(filter, media_item_cb, NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_filter_destroy(filter);
		media_content_error("Fail to get media \n");
		return ret;
	}

	return ret;
}

int test_media_info_operation(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	media_content_debug("\n============Media info Test============\n\n");

	test_filter_create();

	media_info_get_media_count_from_db(g_filter, &media_count);
	media_content_debug("media_count : [%d],\n", media_count);

	ret = media_info_foreach_media_from_db(g_filter, media_item_cb, NULL);

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		media_content_debug("media_info_foreach_media_from_db is success\n\n");
	else
		media_content_error("media_info_foreach_media_from_db is failed\n\n");

	test_filter_destroy();

	return ret;
}

int test_media_info_operation_2(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bookmark_count = 0;

	media_content_debug("\n============Media info Test 2============\n\n");

	test_filter_create();

#if 0
	/* Bookmark */
	char *thumbnail_path1 = "/opt/media/Images and videos/My video clips/teat11.jpg";
	media_bookmark_insert_to_db(test_video_id, 100, thumbnail_path1);
	media_bookmark_insert_to_db(test_video_id, 200, thumbnail_path1);

	media_info_get_bookmark_count_from_db(test_video_id, g_filter_g, &bookmark_count);

	media_content_debug("bookmark_count : [%d],\n", bookmark_count);

	ret = media_info_foreach_bookmark_from_db(test_video_id, g_filter_g, bookmarks_cb, NULL);
#endif

	/* Tag */
	media_info_get_tag_count_from_db(test_audio_id, g_filter_g, &bookmark_count);

	media_content_debug("tag_count : [%d],\n", bookmark_count);

	ret = media_info_foreach_tag_from_db(test_audio_id, g_filter_g, tag_list_cb, NULL);

	test_filter_destroy();

	return ret;
}

int test_folder_operation(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter;
	media_folder_h folder = NULL;
	char *folder_id = NULL;
	int folder_count = 0;

	media_content_debug("\n============Folder Test============\n\n");

	test_filter_create();

	ret = media_filter_create(&filter);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		media_content_error("[ERROR] media_folder_filter_create is failed\n");
		return ret;
	}

	media_filter_set_condition(filter, "(MEDIA_TYPE = 0 or MEDIA_TYPE = 1) and MEDIA_STORAGE_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);	/*MEDIA_TYPE 0-image, 1-video, 2-sound, 3-music, 4-other*/
	media_filter_set_offset(filter, 0,5);
	media_filter_set_order(filter,MEDIA_CONTENT_ORDER_DESC, MEDIA_PATH, MEDIA_CONTENT_COLLATE_NOCASE);

	ret = media_folder_get_folder_count_from_db(filter, &folder_count);
	media_content_debug("Folder count : %d", folder_count);

	ret = media_folder_foreach_folder_from_db(filter, folder_list_cb, &folder);

	//test.3 get the media list in first folder
	filter_h m_filter = NULL;
	ret = media_filter_create(&m_filter);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		media_content_error("[ERROR] media_info_filter_create is failed\n");
		return ret;
	}

	media_filter_set_condition(m_filter, "MEDIA_TYPE=1 and MEDIA_STORAGE_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);	/*MEDIA_TYPE 0-image, 1-video, 2-sound, 3-music, 4-other*/
	media_filter_set_offset(m_filter, 0,5);
	media_filter_set_order(m_filter,MEDIA_CONTENT_ORDER_DESC, MEDIA_PATH, MEDIA_CONTENT_COLLATE_NOCASE);

	media_folder_get_folder_id(folder, &folder_id);
	media_content_debug("folder_id : %s", folder_id);

	ret = media_folder_foreach_media_from_db(folder_id, m_filter, media_item_cb, NULL);

	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		media_content_error("[ERROR] media_folder_foreach_media_from_db is failed, error code : %d\n", ret);
	}

	media_filter_destroy(filter);
	media_filter_destroy(m_filter);

	test_filter_create();

	return ret;
}

int test_playlist_operation(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_playlist_h playlist_1 = NULL;
	media_playlist_h playlist_2 = NULL;
	media_playlist_h playlist_3 = NULL;
	int playlist_id_1 = 0;
	int playlist_id_2 = 0;
	int playlist_id_3 = 0;
	char *playlist_name_1 = "myPlaylist_1";
	char *playlist_name_2 = "myPlaylist_2";
	char *playlist_name_3 = "myPlaylist_3";
	int playlist_count = 0;
	int media_count = 0;
	int order_1 = 0;
	int order_2 = 0;
	int order_3 = 0;
	int order_4 = 0;
	int order_5 = 0;
	filter_h filter = NULL;
	filter_h m_filter = NULL;

	media_content_debug("\n============Playlist Test============\n\n");

	/* Filter for playlist */

	char *condition = "(MEDIA_TYPE=1 or MEDIA_TYPE=3)";	/*0-image, 1-video, 2-sound, 3-music, 4-other*/
#if 0
	ret = media_filter_create(&filter);

	ret = media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_NOCASE);

	ret = media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, PLAYLIST_NAME, MEDIA_CONTENT_COLLATE_NOCASE);
#endif

	/* Create Playlist */
	media_playlist_insert_to_db(playlist_name_1, &playlist_1);
	media_playlist_insert_to_db(playlist_name_2, &playlist_2);
	media_playlist_insert_to_db(playlist_name_3, &playlist_3);

	if(playlist_1 != NULL)
	{
		/* Add media to Playlist */
		media_playlist_add_media(playlist_1, test_audio_id);
		media_playlist_add_media(playlist_1, test_audio_id);
		media_playlist_add_media(playlist_1, test_video_id);
		media_playlist_update_to_db(playlist_1);
	}

	if(playlist_2 != NULL)
	{
		media_playlist_add_media(playlist_2, test_audio_id);
		media_playlist_add_media(playlist_2, test_audio_id);
		media_playlist_update_to_db(playlist_2);
	}

	/* Get Playlist Count*/
	media_playlist_get_playlist_count_from_db(filter, &playlist_count);
	media_content_debug("playlist_count [%d] \n", playlist_count);

	/* Get Playlist*/
	GList *playlist_id_list = NULL;
	media_playlist_foreach_playlist_from_db(filter, playlist_list_cb, &playlist_id_list);

	/* Get Playlist id*/
	playlist_id_1 = (int)g_list_nth_data(playlist_id_list, 0);
	playlist_id_2 = (int)g_list_nth_data(playlist_id_list, 1);
	playlist_id_3 = (int)g_list_nth_data(playlist_id_list, 2);
	media_content_debug("playlist_id_1 [%d] \n", playlist_id_1);
	media_content_debug("playlist_id_2 [%d] \n", playlist_id_2);
	media_content_debug("playlist_id_3 [%d] \n", playlist_id_3);

	/* Filter for media*/
	ret = media_filter_create(&m_filter);

	ret = media_filter_set_condition(m_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_filter_set_order(m_filter, MEDIA_CONTENT_ORDER_ASC, PLAYLIST_MEMBER_ORDER, MEDIA_CONTENT_COLLATE_DEFAULT);

	/* Get media count */
	media_playlist_get_media_count_from_db(playlist_id_1, m_filter, &media_count);
	media_content_debug("playlist_1_media_count [%d] \n", media_count);

	media_playlist_get_media_count_from_db(playlist_id_2, m_filter, &media_count);
	media_content_debug("playlist_2_media_count [%d] \n", media_count);

	media_playlist_get_media_count_from_db(playlist_id_3, m_filter, &media_count);
	media_content_debug("playlist_3_media_count [%d] \n", media_count);

	/* Get media of playlist */
	GList *playlist_member_id_list = NULL;
	GList *playlist_member_id_list_1 = NULL;

	media_playlist_foreach_media_from_db(playlist_id_1, m_filter, playlist_item_cb, &playlist_member_id_list);
	media_playlist_foreach_media_from_db(playlist_id_2, m_filter, playlist_item_cb, &playlist_member_id_list_1);

	int playlist_member_id_1_1 =0;
	int playlist_member_id_1_2 =0;
	int playlist_member_id_1_3 =0;
	int playlist_member_id_2_1 =0;
	int playlist_member_id_2_2 =0;

	playlist_member_id_1_1 = (int)g_list_nth_data(playlist_member_id_list, 0);
	playlist_member_id_1_2 = (int)g_list_nth_data(playlist_member_id_list, 1);
	playlist_member_id_1_3 = (int)g_list_nth_data(playlist_member_id_list, 2);
	playlist_member_id_2_1 = (int)g_list_nth_data(playlist_member_id_list_1, 0);
	playlist_member_id_2_2 = (int)g_list_nth_data(playlist_member_id_list_1, 1);

	media_content_debug("playlist_member_id_1_1 [%d] \n", playlist_member_id_1_1);
	media_content_debug("playlist_member_id_1_2 [%d] \n", playlist_member_id_1_2);
	media_content_debug("playlist_member_id_1_3 [%d] \n", playlist_member_id_1_3);
	media_content_debug("playlist_member_id_2_1 [%d] \n", playlist_member_id_2_1);
	media_content_debug("playlist_member_id_2_2 [%d] \n", playlist_member_id_2_2);

	media_playlist_get_play_order(playlist_1, playlist_member_id_1_1, &order_1);
	media_playlist_get_play_order(playlist_1, playlist_member_id_1_2, &order_2);
	media_playlist_get_play_order(playlist_1, playlist_member_id_1_3, &order_3);
	media_playlist_get_play_order(playlist_2, playlist_member_id_2_1, &order_4);
	media_playlist_get_play_order(playlist_2, playlist_member_id_2_2, &order_5);
	media_content_debug("order_1 [%d] order_2 [%d] order_3 [%d] order_4 [%d] order_5 [%d]\n", order_1, order_2, order_3, order_4, order_5);

	/* Update Playlist */
	media_playlist_remove_media(playlist_2, playlist_member_id_2_1);
	media_playlist_add_media(playlist_2, test_video_id);
	media_playlist_set_name(playlist_2, "test_playlist");
	media_playlist_set_play_order(playlist_2, playlist_member_id_2_2, order_5+100);
	media_playlist_update_to_db(playlist_2);

	/* Get Updated Playlist*/
	media_playlist_foreach_playlist_from_db(filter, playlist_list_cb, NULL);

	/* deletes the playlist */
	//media_playlist_delete_from_db(playlist_id_1);
	//media_playlist_delete_from_db(playlist_id_2);

	if(playlist_1 != NULL)
		media_playlist_destroy(playlist_1);
	if(playlist_2 != NULL)
		media_playlist_destroy(playlist_2);
	if(playlist_3 != NULL)
		media_playlist_destroy(playlist_3);

	g_list_free(playlist_id_list);
	g_list_free(playlist_member_id_list);
	g_list_free(playlist_member_id_list_1);

	if(filter != NULL)
		ret = media_filter_destroy(filter);
	if(m_filter != NULL)
		ret = media_filter_destroy(m_filter);

	return ret;
}

int test_tag_operation(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_tag_h tag_1;
	media_tag_h tag_2;
	media_tag_h tag_3;
	int tag_id_1 = 0;
	int tag_id_2 = 0;
	int tag_id_3 = 0;
	char *tag_name_1 = "myTag_1";
	char *tag_name_2 = "myTag_2";
	char *tag_name_3 = "myTag_3";
	int tag_count = 0;
	int media_count = 0;
	filter_h filter;

	media_content_debug("\n============Tag Test============\n\n");

	char *g_condition = "TAG_NAME like \"%%my%%\"";

	ret = media_filter_create(&filter);

	ret = media_filter_set_condition(filter, g_condition, MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_filter_set_order(filter, MEDIA_CONTENT_ORDER_DESC, TAG_NAME, MEDIA_CONTENT_COLLATE_DEFAULT);

	/* Create Tag */
	media_tag_insert_to_db(tag_name_1, &tag_1);
	media_tag_insert_to_db(tag_name_2, &tag_2);
	media_tag_insert_to_db(tag_name_3, &tag_3);

	/* Add media to Tag */
	media_tag_add_media(tag_1, test_audio_id);
	media_tag_add_media(tag_1, test_video_id);
	media_tag_update_to_db(tag_1);

	media_tag_add_media(tag_2, test_audio_id);
	media_tag_update_to_db(tag_2);

	/* Get Tag Count*/
	media_tag_get_tag_count_from_db(filter, &tag_count);
	media_content_debug("tag_count [%d] \n", tag_count);

	/* Get Tag*/
	media_tag_foreach_tag_from_db(filter, tag_list_cb, NULL);

	/* Get Tag id*/
	media_tag_get_tag_id(tag_1, &tag_id_1);
	media_content_debug("tag_id_1 [%d] \n", tag_id_1);

	media_tag_get_tag_id(tag_2, &tag_id_2);
	media_content_debug("tag_id_2 [%d] \n", tag_id_2);

	media_tag_get_tag_id(tag_3, &tag_id_3);
	media_content_debug("tag_id_3 [%d] \n", tag_id_3);

	/* Get media count */
	media_tag_get_media_count_from_db(tag_id_1, NULL, &media_count);
	media_content_debug("tag_1_media_count [%d] \n", media_count);

	media_tag_get_media_count_from_db(tag_id_2, NULL, &media_count);
	media_content_debug("tag_2_media_count [%d] \n", media_count);

	/* Get media of Tag */
	media_tag_foreach_media_from_db(tag_id_1, NULL, media_item_cb, NULL);
	media_tag_foreach_media_from_db(tag_id_2, NULL, media_item_cb, NULL);

	/* Update Tag */
	media_tag_add_media(tag_2, test_video_id);
	media_tag_set_name(tag_2, "test_tag");
	media_tag_update_to_db(tag_2);

	/* Get Updated Tag*/
	media_tag_foreach_tag_from_db(filter, tag_list_cb, NULL);

	/* deletes the tag */
	media_tag_delete_from_db(tag_id_1);
	media_tag_delete_from_db(tag_id_2);

	media_tag_destroy(tag_1);
	media_tag_destroy(tag_2);

	ret = media_filter_destroy(filter);

	return ret;
}


int test_bookmark_operation(void)
{
	//bookmark is only supported for video information.
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bookmark_count = 0;
	filter_h filter;

	media_content_debug("\n============Bookmark Test============\n\n");

	char *g_condition = "BOOKMARK_MARKED_TIME > 300";

	ret = media_filter_create(&filter);

	ret = media_filter_set_condition(filter, g_condition, MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_filter_set_order(filter, MEDIA_CONTENT_ORDER_DESC, BOOKMARK_MARKED_TIME, MEDIA_CONTENT_COLLATE_DEFAULT);

	//insert bookmark to video
	char *thumbnail_path1 = "/opt/media/Images and videos/My video clips/teat11.jpg";
	media_bookmark_insert_to_db(test_video_id, 400, thumbnail_path1);
	media_bookmark_insert_to_db(test_video_id, 600, thumbnail_path1);

	media_bookmark_get_bookmark_count_from_db(filter, &bookmark_count);
	media_content_debug("bookmark_count = [%d]\n", bookmark_count);

	media_filter_destroy(filter);

	return ret;
}

int test_album_list(void)
{
	media_content_debug("\n============Album Test============\n\n");

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int album_count = 0;
	filter_h filter;

	/*Set Filter*/
	char *condition = "MEDIA_TYPE=3";	/*0-image, 1-video, 2-sound, 3-music, 4-other*/

	ret = media_filter_create(&filter);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to create filter \n");
		return ret;
	}
	ret = media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to set condition \n");
		return ret;
	}
	ret = media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_ALBUM, MEDIA_CONTENT_COLLATE_NOCASE);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("Fail to set order \n");
		return ret;
	}

	ret = media_album_get_album_count_from_db(filter, &album_count);
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_filter_destroy(filter);
		return ret;
	} else {
		media_content_debug("album_count [%d] \n", album_count);
	}

	ret = media_album_foreach_album_from_db(filter, album_list_cb, NULL);

	ret = media_filter_destroy(filter);

	return ret;
}

int test_group_operation(void)
{
	media_content_debug("\n============Group Test============\n\n");

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int group_count = 0;
	int idx = 0;

	ret = test_filter_create();
	if(ret != MEDIA_CONTENT_ERROR_NONE) {
		media_content_error("[%d]error(0x%08x)", __LINE__, ret);
		return ret;
	}

	for(idx = 0; idx <= MEDIA_CONTENT_GROUP_KEYWORD; idx++)
	{
		ret = media_group_get_group_count_from_db(g_filter, idx, &group_count);
		if(ret != MEDIA_CONTENT_ERROR_NONE) {
			test_filter_destroy();
			media_content_error("media_group_get_group_count_from_db fail. idx=[%d]", ret, idx);
			return ret;
		} else {
			media_content_debug("[%2d]group_count [%d] \n", idx, group_count);
		}

		ret = media_group_foreach_group_from_db(g_filter, idx, group_list_cb, &idx);
	}
	ret = test_filter_destroy();

	return ret;
}

int test_update_operation()
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int i;
	media_info_h media_handle = NULL;
	GList *all_item_list = NULL;

	/* Get all item list */
	ret = media_info_foreach_media_from_db(NULL, gallery_media_item_cb, &all_item_list);
	if(ret < 0) {
		media_content_error("media_info_foreach_media_from_db failed: %d", ret);
		return -1;
	} else {
		media_content_debug("media_info_foreach_media_from_db success");
		char *media_id = NULL;
		char *media_path = NULL;
		media_content_type_e media_type = 0;

		for(i = 0; i < g_list_length(all_item_list); i++) {
			media_handle = (media_info_h)g_list_nth_data(all_item_list, i);

			media_info_get_media_id(media_handle, &media_id);
			media_info_get_file_path(media_handle, &media_path);
			media_info_get_media_type(media_handle, &media_type);

			media_content_debug("media_id [%d] : %s\n", i, media_id);
			media_content_debug("media_type [%d] : %d\n", i, media_type);
			media_content_debug("media_path [%d] : %s\n", i, media_path);
#if 0
			if(media_type == MEDIA_CONTENT_TYPE_IMAGE) {
				image_meta_h image_handle;
				media_content_orientation_e orientation;

				ret = media_info_get_image_from_db(media_id, &image_handle);
				if(ret < 0) {
					media_content_error("media_info_get_image_from_db failed: %d", ret);
				} else {
					media_content_debug("media_info_get_image_from_db success");

					//update image meta
					orientation = MEDIA_CONTENT_ORIENTATION_ROT_180;
					image_meta_set_orientation(image_handle, orientation);

					ret = image_meta_update_to_db(image_handle);
					if(ret < 0) {
						media_content_error("image_meta_update_to_db failed: %d", ret);
					} else {
						media_content_debug("image_meta_update_to_db success");
					}
				}

			} else if(media_type == MEDIA_CONTENT_TYPE_VIDEO) {
				video_meta_h video_handle;

				ret = media_info_get_video_from_db(media_id, &video_handle);
				if(ret < 0) {
					media_content_error("media_info_get_video_from_db failed: %d", ret);
				} else {
					media_content_debug("media_info_get_video_from_db success");

					//update video meta
					video_meta_set_played_count(video_handle,5);
					video_meta_set_played_time(video_handle,5);
					video_meta_set_played_position(video_handle,5);
					video_meta_update_to_db(video_handle);

					ret = video_meta_update_to_db(video_handle);
					if(ret < 0) {
						media_content_error("video_meta_update_to_db failed: %d", ret);
					} else {
						media_content_debug("video_meta_update_to_db success");
					}
				}
			} else if(media_type == MEDIA_CONTENT_TYPE_MUSIC) {//update audio meta
				audio_meta_h audio_handle = NULL;
				ret = media_info_get_audio_from_db(media_id, &audio_handle);
				if(ret < 0) {
					media_content_error("media_info_get_audio_from_db failed: %d", ret);
				} else {
					media_content_debug("media_info_get_audio_from_db success");

					audio_meta_set_played_count(audio_handle,5);
					audio_meta_set_played_time(audio_handle,1000);
					audio_meta_set_played_position(audio_handle,180);

					ret = audio_meta_update_to_db(audio_handle);
					if(ret < 0) {
						media_content_error("audio_meta_update_to_db failed: %d", ret);
					} else {
						media_content_debug("audio_meta_update_to_db success");
					}
				}

			}
#endif
		}
	}

	return MEDIA_CONTENT_ERROR_NONE;
}

int test_insert(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	//char *path = "/opt/media/Images/Default.jpg";
	char *path = "/opt/media/Others/other.txt";
	//char *path = NULL;
	media_info_h media_item = NULL;
	media_content_debug("\n============DB Insert Test============\n\n");

	ret = media_info_insert_to_db(path, &media_item);

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		media_content_debug("Insertion is success\n\n");
	else
		media_content_error("Insertion is failed\n\n");

	char *media_id = NULL;

	media_info_get_media_id(media_item, &media_id);

	printf("Media ID: %s\n", media_id);

	ret = media_info_update_to_db(media_item);
	if(ret == MEDIA_CONTENT_ERROR_NONE)
		media_content_debug("media_info_update_to_db is success\n");
	else
		media_content_error("media_info_update_to_db is failed\n");

	return ret;
}

int test_move(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	const char *move_media_id = "60aea677-4742-408e-b5f7-f2628062d06d";
	char *dst_path = "/opt/media/Images/XX/Default1.jpg";
	media_info_h move_media = NULL;

	ret = media_info_get_media_from_db(move_media_id, &move_media);
	if(ret == MEDIA_CONTENT_ERROR_NONE)
		media_content_debug("media_info_get_media_from_db success\n\n");
	else
		media_content_error("media_info_get_media_from_db failed: %d\n\n", ret);

	media_content_debug("\n============DB Move Test============\n\n");

	if(move_media) {
		ret = media_info_move_media_to_db(move_media, dst_path);

		if(ret == MEDIA_CONTENT_ERROR_NONE)
			media_content_debug("Move is success\n\n");
		else
			media_content_error("Move is failed\n\n");
	} else {
		media_content_debug("There is no item : %s\n", move_media_id);
	}

	return ret;
}

int test_disconnect_database(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_debug("\n============DB Disconnection Test============\n\n");

	ret = media_content_disconnect();

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		media_content_debug("disconnection is success\n\n");
	else
		media_content_error("disconnection is failed\n\n");

	return ret;
}

int g_total_photo_size = 0;
int g_total_video_size = 0;
int g_total_mp3_size = 0;
int g_total_voice_memo_size = 0;

bool dft_cb(media_info_h media, void *user_data)
{
	unsigned long long file_size = 0;
	media_content_type_e media_type = -1;
	char *mime_type = NULL;

	if(media == NULL)
	{
		return true;
	}

	media_info_get_media_type(media, &media_type);
	media_info_get_size(media, &file_size);
	media_info_get_mime_type(media, &mime_type);

	if(media_type == MEDIA_CONTENT_TYPE_IMAGE)
	{
		g_total_photo_size += file_size;
	}
	else if(media_type == MEDIA_CONTENT_TYPE_VIDEO)
	{
		g_total_video_size += file_size;
	}
	else if(media_type == MEDIA_CONTENT_TYPE_SOUND)
	{
		g_total_voice_memo_size += file_size;
	}
	else if(media_type == MEDIA_CONTENT_TYPE_MUSIC)
	{
		if((mime_type != NULL) && (!strcmp("audio/mpeg", mime_type)))
		{
			g_total_mp3_size += file_size;
		}
		else
		{
			g_total_voice_memo_size += file_size;
		}
	}
	else
	{
		printf("invalid media_type\n");
	}

	if(mime_type != NULL)
		free(mime_type);

	return true;

}

int DFT_test(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	printf("\n============DFT_test============\n\n");

	filter_h filter = NULL;
	int media_cnt = 0;

	/*MEDIA_TYPE 0-image, 1-video, 2-sound, 3-music, 4-other*/

	ret = media_filter_create(&filter);

/*Internal Memory*/
	printf("[Internal Memory]\n");
	/*1. Photo ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=0 AND MEDIA_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get Photo Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("Photo count = [%d]\n", media_cnt);

	/*Get Photo Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("Photo size = [%d]\n", g_total_photo_size);

	/*2. Video ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=0 AND MEDIA_TYPE=1", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get Video Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("Video count = [%d]\n", media_cnt);

	/*Get Video Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("Video size = [%d]\n", g_total_video_size);

	/*3. MP3 ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=0 AND MEDIA_TYPE=3 AND MEDIA_MIME_TYPE=\"audio/mpeg\"", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get MP3 Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("MP3 count = [%d]\n", media_cnt);

	/*Get MP3 Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("MP3 size = [%d]\n", g_total_mp3_size);

	/*4. Voice Memo ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=0 AND (MEDIA_MIME_TYPE=\"audio/AMR\" OR MEDIA_MIME_TYPE=\"audio/mp4\")", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get Voice Memo Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("Voice Memo count = [%d]\n", media_cnt);

	/*Get Voice Memo Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("Voice Memo size = [%d]\n", g_total_voice_memo_size);

	g_total_photo_size = 0;
	g_total_video_size = 0;
	g_total_mp3_size = 0;
	g_total_voice_memo_size = 0;

/*External Memory*/
	printf("\n[External Memory]\n");
	/*1. Photo ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=1 AND MEDIA_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get Photo Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("Photo count = [%d]\n", media_cnt);

	/*Get Photo Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("Photo size = [%d]\n", g_total_photo_size);

	/*2. Video ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=1 AND MEDIA_TYPE=1", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get Video Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("Video count = [%d]\n", media_cnt);

	/*Get Video Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("Video size = [%d]\n", g_total_video_size);

	/*3. MP3 ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=1 AND MEDIA_TYPE=3 AND MEDIA_MIME_TYPE=\"audio/mpeg\"", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get MP3 Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("MP3 count = [%d]\n", media_cnt);

	/*Get MP3 Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("MP3 size = [%d]\n", g_total_mp3_size);

	/*4. Voice Memo ============================================================*/
	ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=1 AND (MEDIA_MIME_TYPE=\"audio/AMR\" OR MEDIA_MIME_TYPE=\"audio/mp4\")", MEDIA_CONTENT_COLLATE_DEFAULT);

	/*Get Voice Memo Count*/
	ret = media_info_get_media_count_from_db(filter, &media_cnt);
	printf("Voice Memo count = [%d]\n", media_cnt);

	/*Get Voice Memo Size*/
	ret = media_info_foreach_media_from_db(filter, dft_cb, NULL);
	printf("Voice Memo size = [%d]\n", g_total_voice_memo_size);
	ret = media_filter_destroy(filter);

	return 0;
}

int main(int argc, char *argv[])
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	media_content_debug("--- content manager test start ---\n\n");

	ret = test_connect_database();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return MEDIA_CONTENT_ERROR_NONE;

#if 0
	ret = test_move();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_gallery_scenario();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_get_all_music_files();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_media_info_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_folder_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_playlist_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_tag_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_bookmark_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_album_list();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_group_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_update_operation();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_insert();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = test_move();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	ret = DFT_test();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;
#endif

	ret = test_disconnect_database();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		return ret;

	media_content_debug("--- content manager test end ---\n");

	return ret;
}
