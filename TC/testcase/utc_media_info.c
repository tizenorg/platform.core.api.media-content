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


#include <tet_api.h>
#include <media_content.h>
#include <stdlib.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_media_info_insert_to_db_n(void);
static void utc_media_info_insert_to_db_p(void);
static void utc_media_info_set_display_name_n(void);
static void utc_media_info_set_display_name_p(void);
static void utc_media_info_set_favorite_n(void);
static void utc_media_info_set_favorite_p(void);
static void utc_media_info_set_rating_n(void);
static void utc_media_info_set_rating_p(void);
static void utc_media_info_set_category_n(void);
static void utc_media_info_set_category_p(void);
static void utc_media_info_set_location_tag_n(void);
static void utc_media_info_set_location_tag_p(void);
static void utc_media_info_set_provider_n(void);
static void utc_media_info_set_provider_p(void);
static void utc_media_info_set_content_name_n(void);
static void utc_media_info_set_content_name_p(void);
static void utc_media_info_set_description_n(void);
static void utc_media_info_set_description_p(void);
static void utc_media_info_set_author_n(void);
static void utc_media_info_set_author_p(void);
static void utc_media_info_set_age_rating_n(void);
static void utc_media_info_set_age_rating_p(void);
static void utc_media_info_set_added_time_n(void);
static void utc_media_info_set_added_time_p(void);
static void utc_media_info_set_keyword_n(void);
static void utc_media_info_set_keyword_p(void);
static void utc_media_info_set_altitude_n(void);
static void utc_media_info_set_altitude_p(void);
static void utc_media_info_set_latitude_n(void);
static void utc_media_info_set_latitude_p(void);
static void utc_media_info_set_longitude_n(void);
static void utc_media_info_set_longitude_p(void);
static void utc_media_info_update_to_db_n(void);
static void utc_media_info_update_to_db_p(void);
static void utc_media_info_move_media_to_db_n(void);
static void utc_media_info_move_media_to_db_p(void);
static void utc_media_info_delete_from_db_n(void);
static void utc_media_info_delete_from_db_p(void);
static void utc_media_info_foreach_media_from_db_n(void);
static void utc_media_info_foreach_media_from_db_p(void);
static void utc_media_info_refresh_metadata_to_db_n(void);
static void utc_media_info_refresh_metadata_to_db_p(void);
static void utc_media_info_destroy_n(void);
static void utc_media_info_destroy_p(void);
static void utc_media_info_clone_n(void);
static void utc_media_info_clone_p(void);
static void utc_media_info_get_media_id_n(void);
static void utc_media_info_get_media_id_p(void);
static void utc_media_info_get_file_path_n(void);
static void utc_media_info_get_file_path_p(void);
static void utc_media_info_get_display_name_n(void);
static void utc_media_info_get_display_name_p(void);
static void utc_media_info_get_media_type_n(void);
static void utc_media_info_get_media_type_p(void);
static void utc_media_info_get_mime_type_n(void);
static void utc_media_info_get_mime_type_p(void);
static void utc_media_info_get_thumbnail_path_n(void);
static void utc_media_info_get_thumbnail_path_p(void);
static void utc_media_info_get_modified_time_n(void);
static void utc_media_info_get_modified_time_p(void);
static void utc_media_info_get_size_n(void);
static void utc_media_info_get_size_p(void);
static void utc_media_info_get_description_n(void);
static void utc_media_info_get_description_p(void);
static void utc_media_info_get_rating_n(void);
static void utc_media_info_get_rating_p(void);
static void utc_media_info_get_location_tag_n(void);
static void utc_media_info_get_location_tag_p(void);
static void utc_media_info_get_provider_n(void);
static void utc_media_info_get_provider_p(void);
static void utc_media_info_get_content_name_n(void);
static void utc_media_info_get_content_name_p(void);
static void utc_media_info_get_category_n(void);
static void utc_media_info_get_category_p(void);
static void utc_media_info_get_age_rating_n(void);
static void utc_media_info_get_age_rating_p(void);
static void utc_media_info_get_keyword_n(void);
static void utc_media_info_get_keyword_p(void);
static void utc_media_info_get_author_n(void);
static void utc_media_info_get_author_p(void);
static void utc_media_info_get_added_time_n(void);
static void utc_media_info_get_added_time_p(void);
static void utc_media_info_get_altitude_n(void);
static void utc_media_info_get_altitude_p(void);
static void utc_media_info_get_latitude_n(void);
static void utc_media_info_get_latitude_p(void);
static void utc_media_info_get_longitude_n(void);
static void utc_media_info_get_longitude_p(void);
static void utc_media_info_get_storage_type_n(void);
static void utc_media_info_get_storage_type_p(void);
static void utc_media_info_is_drm_n(void);
static void utc_media_info_is_drm_p(void);
static void utc_media_info_get_media_from_db_n(void);
static void utc_media_info_get_media_from_db_p(void);
static void utc_media_info_get_image_n(void);
static void utc_media_info_get_image_p(void);
static void utc_media_info_get_video_n(void);
static void utc_media_info_get_video_p(void);
static void utc_media_info_get_audio_n(void);
static void utc_media_info_get_audio_p(void);
static void utc_media_info_foreach_tag_from_db_n(void);
static void utc_media_info_foreach_tag_from_db_p(void);
static void utc_media_info_get_favorite_n(void);
static void utc_media_info_get_favorite_p(void);
static void utc_media_info_foreach_bookmark_from_db_n(void);
static void utc_media_info_foreach_bookmark_from_db_p(void);
static void utc_media_info_get_bookmark_count_from_db_n(void);
static void utc_media_info_get_bookmark_count_from_db_p(void);
static void utc_media_info_get_media_count_from_db_n(void);
static void utc_media_info_get_media_count_from_db_p(void);
static void utc_media_info_get_tag_count_from_db_n(void);
static void utc_media_info_get_tag_count_from_db_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_media_info_insert_to_db_n, 1 },
	{ utc_media_info_insert_to_db_p, 1 },
	{ utc_media_info_set_display_name_n, 1 },
	{ utc_media_info_set_display_name_p, 1 },
	{ utc_media_info_set_favorite_n, 1 },
	{ utc_media_info_set_favorite_p, 1 },
	{ utc_media_info_set_rating_n, 1 },
	{ utc_media_info_set_rating_p, 1 },
	{ utc_media_info_set_category_n, 1 },
	{ utc_media_info_set_category_p, 1 },
	{ utc_media_info_set_location_tag_n, 1 },
	{ utc_media_info_set_location_tag_p, 1 },
	{ utc_media_info_set_provider_n, 1 },
	{ utc_media_info_set_provider_p, 1 },
	{ utc_media_info_set_content_name_n, 1 },
	{ utc_media_info_set_content_name_p, 1 },
	{ utc_media_info_set_description_n, 1 },
	{ utc_media_info_set_description_p, 1 },
	{ utc_media_info_set_author_n, 1 },
	{ utc_media_info_set_author_p, 1 },
	{ utc_media_info_set_age_rating_n, 1 },
	{ utc_media_info_set_age_rating_p, 1 },
	{ utc_media_info_set_added_time_n, 1 },
	{ utc_media_info_set_added_time_p, 1 },
	{ utc_media_info_set_keyword_n, 1 },
	{ utc_media_info_set_keyword_p, 1 },
	{ utc_media_info_set_altitude_n, 1 },
	{ utc_media_info_set_altitude_p, 1 },
	{ utc_media_info_set_longitude_n, 1 },
	{ utc_media_info_set_longitude_p, 1 },
	{ utc_media_info_set_latitude_n, 1 },
	{ utc_media_info_set_latitude_p, 1 },
	{ utc_media_info_update_to_db_n, 1 },
	{ utc_media_info_update_to_db_p, 1 },
	{ utc_media_info_move_media_to_db_n, 1 },
	{ utc_media_info_move_media_to_db_p, 1 },
	{ utc_media_info_delete_from_db_n, 1 },
	{ utc_media_info_delete_from_db_p, 1 },
	{ utc_media_info_foreach_media_from_db_n, 1 },
	{ utc_media_info_foreach_media_from_db_p, 1 },
	{ utc_media_info_refresh_metadata_to_db_n, 1 },
	{ utc_media_info_refresh_metadata_to_db_p, 1 },
	{ utc_media_info_clone_n, 2 },
	{ utc_media_info_clone_p, 2 },
	{ utc_media_info_destroy_n, 5 },
	{ utc_media_info_destroy_p, 5 },
	{ utc_media_info_get_media_id_n, 2 },
	{ utc_media_info_get_media_id_p, 2 },
	{ utc_media_info_get_file_path_n, 2 },
	{ utc_media_info_get_file_path_p, 2 },
	{ utc_media_info_get_display_name_n, 2 },
	{ utc_media_info_get_display_name_p, 2 },
	{ utc_media_info_get_thumbnail_path_n, 2 },
	{ utc_media_info_get_thumbnail_path_p, 2 },
	{ utc_media_info_get_modified_time_n, 2 },
	{ utc_media_info_get_modified_time_p, 2 },
	{ utc_media_info_get_media_type_n, 2 },
	{ utc_media_info_get_media_type_p, 2 },
	{ utc_media_info_get_size_n, 2 },
	{ utc_media_info_get_size_p, 2 },
	{ utc_media_info_get_description_n, 2 },
	{ utc_media_info_get_description_p, 2 },
	{ utc_media_info_get_rating_n, 2 },
	{ utc_media_info_get_rating_p, 2 },
	{ utc_media_info_get_location_tag_n, 2 },
	{ utc_media_info_get_location_tag_p, 2 },
	{ utc_media_info_get_provider_n, 2 },
	{ utc_media_info_get_provider_p, 2 },
	{ utc_media_info_get_content_name_n, 2 },
	{ utc_media_info_get_content_name_p, 2 },
	{ utc_media_info_get_category_n, 2 },
	{ utc_media_info_get_category_p, 2 },
	{ utc_media_info_get_age_rating_n, 2 },
	{ utc_media_info_get_age_rating_p, 2 },
	{ utc_media_info_get_keyword_n, 2 },
	{ utc_media_info_get_keyword_p, 2 },
	{ utc_media_info_get_author_n, 2 },
	{ utc_media_info_get_author_p, 2 },
	{ utc_media_info_get_altitude_n, 2 },
	{ utc_media_info_get_altitude_p, 2 },
	{ utc_media_info_get_longitude_n, 2 },
	{ utc_media_info_get_longitude_p, 2 },
	{ utc_media_info_get_latitude_n, 2 },
	{ utc_media_info_get_latitude_p, 2 },
	{ utc_media_info_get_storage_type_n, 2 },
	{ utc_media_info_get_storage_type_p, 2 },
	{ utc_media_info_get_added_time_n, 2 },
	{ utc_media_info_get_added_time_p, 2 },
	{ utc_media_info_get_mime_type_n, 2 },
	{ utc_media_info_get_mime_type_p, 2 },
	{ utc_media_info_is_drm_n, 2 },
	{ utc_media_info_is_drm_p, 2 },
	{ utc_media_info_get_media_from_db_n, 2 },
	{ utc_media_info_get_media_from_db_p, 2 },
	{ utc_media_info_get_image_n, 2 },
	{ utc_media_info_get_image_p, 2 },
	{ utc_media_info_get_video_n, 2 },
	{ utc_media_info_get_video_p, 2 },
	{ utc_media_info_get_audio_n, 2 },
	{ utc_media_info_get_audio_p, 2 },
	{ utc_media_info_get_favorite_n, 2 },
	{ utc_media_info_get_favorite_p, 2 },
	{ utc_media_info_foreach_tag_from_db_n, 3 },
	{ utc_media_info_foreach_tag_from_db_p, 3 },
	{ utc_media_info_foreach_bookmark_from_db_n, 3 },
	{ utc_media_info_foreach_bookmark_from_db_p, 3 },
	{ utc_media_info_get_bookmark_count_from_db_n, 3 },
	{ utc_media_info_get_bookmark_count_from_db_p, 3 },
	{ utc_media_info_get_media_count_from_db_n, 3 },
	{ utc_media_info_get_media_count_from_db_p, 3 },
	{ utc_media_info_get_tag_count_from_db_n, 3 },
	{ utc_media_info_get_tag_count_from_db_p, 3 },
	{ NULL, 0 },
};

static media_info_h g_item;
static media_info_h g_vitem;
static media_info_h g_aitem;
static media_info_h g_inserted_media_handle;


char *g_item_media_id = NULL;
char *g_inserted_media_id = NULL;
const char *g_insert_path = "/opt/media/Downloads/test.jpg";
const char *g_origin_path = "/opt/media/Images/Default.jpg";
const char *g_move_dst_path = "/opt/media/Downloads/test1.jpg";

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");

	g_item = NULL;
	g_vitem = NULL;
	g_aitem = NULL;
	g_inserted_media_handle = NULL;

	int ret = media_content_connect();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		tet_printf("\n database connection is failed");
		return;
	}
	else
		tet_printf("\n database connection is success");

	char test_copy[256] = {0, };
	snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_origin_path, g_insert_path);
	system(test_copy);
}

static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");
	int ret = media_content_disconnect();
	
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		tet_printf("\n database disconnection is failed");
	else
		tet_printf("\n database disconnection is success");

	if(g_item_media_id != NULL)
		free(g_item_media_id);

	if(g_inserted_media_id != NULL)
		free(g_inserted_media_id);

	unlink(g_insert_path);
}


static void utc_media_info_insert_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_insert_to_db(NULL, NULL);

	dts_check_eq("utc_media_info_insert_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_insert_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_insert_to_db(g_insert_path, &g_inserted_media_handle);
	media_info_get_media_id(g_inserted_media_handle, &g_inserted_media_id);

	dts_check_eq("utc_media_info_insert_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to insert a item");
}

static void utc_media_info_set_display_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_display_name(NULL, "new name");

	dts_check_eq("utc_media_info_set_display_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_display_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_display_name(g_inserted_media_handle, "new name");

	dts_check_eq("utc_media_info_set_display_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set display name");
}

static void utc_media_info_set_favorite_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_favorite(NULL, true);

	dts_check_eq("utc_media_info_set_favorite_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_favorite_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_favorite(g_inserted_media_handle, true);

	dts_check_eq("utc_media_info_set_favorite_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set favorite ");
}

static void utc_media_info_set_altitude_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_altitude(NULL, 1000.0);

	dts_check_eq("utc_media_info_set_altitude_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_altitude_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_altitude(g_inserted_media_handle, 1000.0);

	dts_check_eq("utc_media_info_set_altitude_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set favorite ");
}

static void utc_media_info_set_latitude_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_latitude(NULL, 1000.0);

	dts_check_eq("utc_media_info_set_latitude_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_latitude_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_latitude(g_inserted_media_handle, 1000.0);

	dts_check_eq("utc_media_info_set_latitude_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set favorite ");
}

static void utc_media_info_set_longitude_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_longitude(NULL, 1000.0);

	dts_check_eq("utc_media_info_set_longitude_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_longitude_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_longitude(g_inserted_media_handle, 1000.0);

	dts_check_eq("utc_media_info_set_longitude_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set favorite ");
}

static void utc_media_info_set_rating_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_rating(NULL, 5);

	dts_check_eq("utc_media_info_set_rating_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_rating_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_rating(g_inserted_media_handle, 5);

	dts_check_eq("utc_media_info_set_rating_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set rating ");
}

static void utc_media_info_set_category_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_category(NULL, "new cate");

	dts_check_eq("utc_media_info_set_category_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_category_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_category(g_inserted_media_handle, "new cate");

	dts_check_eq("utc_media_info_set_category_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set category ");
}

static void utc_media_info_set_location_tag_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_favorite(NULL, "new location");

	dts_check_eq("utc_media_info_set_location_tag_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_location_tag_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_location_tag(g_inserted_media_handle, "new location");

	dts_check_eq("utc_media_info_set_location_tag_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set location tag ");
}

static void utc_media_info_set_provider_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_provider(NULL, "new provider");

	dts_check_eq("utc_media_info_set_provider_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_provider_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_provider(g_inserted_media_handle, "new provider");

	dts_check_eq("utc_media_info_set_provider_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set provider ");
}

static void utc_media_info_set_content_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_content_name(NULL, "new content");

	dts_check_eq("utc_media_info_set_content_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_content_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_content_name(g_inserted_media_handle, "new content");
	dts_check_eq("utc_media_info_set_content_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set content name ");
}

static void utc_media_info_set_description_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_description(NULL, "new description");

	dts_check_eq("utc_media_info_set_description_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_description_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_description(g_inserted_media_handle, "new description");

	dts_check_eq("utc_media_info_set_description_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set description ");
}

static void utc_media_info_set_author_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_author(NULL, "new author");

	dts_check_eq("utc_media_info_set_author_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_author_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_author(g_inserted_media_handle, "new author");

	dts_check_eq("utc_media_info_set_description_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set author ");
}

static void utc_media_info_set_age_rating_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_age_rating(NULL, "new rating");

	dts_check_eq("utc_media_info_set_age_rating_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_age_rating_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_age_rating(g_inserted_media_handle, "new rating");

	dts_check_eq("utc_media_info_set_age_rating_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set age rating ");
}

static void utc_media_info_set_added_time_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_added_time(NULL, 0);

	dts_check_eq("utc_media_info_set_added_time_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_added_time_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	time_t added_time;
	time(&added_time);

	ret = media_info_set_added_time(g_inserted_media_handle, added_time);

	dts_check_eq("utc_media_info_set_added_time_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set added time");
}

static void utc_media_info_set_keyword_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_keyword(NULL, "new keyword");

	dts_check_eq("utc_media_info_set_keyword_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_set_keyword_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_keyword(g_inserted_media_handle, "new keyword");

	dts_check_eq("utc_media_info_set_keyword_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set keyword ");
}

static void utc_media_info_update_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_update_to_db(NULL);

	dts_check_eq("utc_media_info_update_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_update_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_update_to_db(g_inserted_media_handle);
	tet_printf("Media Handle : 0x%x \n", g_inserted_media_handle);

	dts_check_eq("utc_media_info_update_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to update a item");
}

static void utc_media_info_move_media_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_move_media_to_db(NULL, g_move_dst_path);

	dts_check_eq("utc_media_info_move_media_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_move_media_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_move_media_to_db(g_inserted_media_handle, g_move_dst_path);
	tet_printf("Media Handle : 0x%x \n", g_inserted_media_handle);

	dts_check_eq("utc_media_info_move_media_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to update a item");
}

static void utc_media_info_delete_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_delete_from_db(NULL);

	dts_check_eq("utc_media_info_delete_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_delete_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	tet_printf("Media ID : %s \n", g_inserted_media_id);
	ret = media_info_delete_from_db(g_inserted_media_id);

	dts_check_eq("utc_media_info_delete_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to delete a item");
}

bool sub_item_cb(media_info_h media, void *user_data)
{
	media_content_type_e type = 0;
	char *name = NULL;

	media_info_get_media_type(media, &type);
	media_info_get_display_name(media, &name);
	if(g_item == NULL && type == MEDIA_CONTENT_TYPE_IMAGE)
	{
		media_info_clone(&g_item, media);
		media_info_get_media_id(media, &g_item_media_id);
		tet_printf("content name: %s \n", name);
	}

	if(g_vitem == NULL && type == MEDIA_CONTENT_TYPE_VIDEO)
	{
		tet_printf("MEDIA_CONTENT_TYPE_VIDEO \n");
		tet_printf("media name: %s \n", name);
		media_info_clone(&g_vitem, media);
		media_info_get_media_id(media, &g_item_media_id);
	}
	if(g_aitem == NULL && type == MEDIA_CONTENT_TYPE_MUSIC)
	{
		tet_printf("MEDIA_CONTENT_TYPE_MUSIC \n");
		tet_printf("media name: %s \n", name);
		media_info_clone(&g_aitem, media);
		media_info_get_media_id(media, &g_item_media_id);
	}
	return true;
}

static void utc_media_info_foreach_media_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	filter_h filter = NULL;
	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0 OR MEDIA_TYPE=1", MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_info_foreach_media_from_db(NULL, NULL, NULL);

	if(filter != NULL)
		media_filter_destroy(filter);


	dts_check_eq("utc_media_info_foreach_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_foreach_media_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0 OR MEDIA_TYPE=1 OR MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_info_foreach_media_from_db(filter, sub_item_cb, NULL);

	if(filter != NULL)
		media_filter_destroy(filter);

	dts_check_eq("utc_media_info_foreach_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to call callback fuction");
}

static void utc_media_info_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_destroy(NULL);
	
	dts_check_eq("utc_media_info_destroy_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_destroy(g_item);

	dts_check_eq("utc_media_info_destroy_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destroy iteminfo object");
}

static void utc_media_info_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h dst;

	ret = media_info_clone(&dst, NULL);
	
	dts_check_eq("utc_media_info_clone_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h dst;

	ret = media_info_clone(&dst, g_item);

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		media_info_destroy(dst);

	dts_check_eq("utc_media_info_clone_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone iteminfo object");
}

static void utc_media_info_get_media_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = media_info_get_media_id(NULL, &media_id);

	if(media_id != NULL)
		free(media_id);

	dts_check_eq("utc_media_info_get_media_id_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_media_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char *media_id = NULL;
	ret = media_info_get_media_id(g_item, &media_id);
	if(media_id != NULL)
		free(media_id);

	dts_check_eq("utc_media_info_get_media_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get media id ");
}

static void utc_media_info_get_file_path_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;
	ret = media_info_get_file_path(NULL, &path);

	if(path != NULL)
		free(path);
	
	dts_check_eq("utc_media_info_get_file_path_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_file_path_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char *path = NULL;
	ret = media_info_get_file_path(g_item, &path);
	tet_printf("\n get_file_path : %s\n", path);
	if(path != NULL)
		free(path);

	dts_check_eq("utc_media_info_get_file_path_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get file path");
}

static void utc_media_info_get_display_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	char *name = NULL;
	ret = media_info_get_display_name(NULL, &name);

	if(name != NULL)
		free(name);

	dts_check_eq("utc_media_info_get_display_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_display_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;
	ret = media_info_get_display_name(g_item, &name);
	tet_printf("\n media_info_get_display_name : %s\n", name);

	if(name != NULL)
		free(name);

	dts_check_eq("utc_media_info_get_display_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get display_name");
}

static void utc_media_info_get_media_type_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_type_e type = 0;

	ret = media_info_get_media_type(NULL, &type);

	dts_check_eq("utc_media_info_get_media_type_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_media_type_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_type_e type = 0;
	tet_printf("item : %p\n", g_item);

	ret = media_info_get_media_type(g_item, &type);

	dts_check_eq("utc_media_info_get_media_type_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get content type");
}

static void utc_media_info_get_mime_type_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *mime_type;

	ret = media_info_get_author(NULL, &mime_type);
	if(mime_type != NULL)
		free(mime_type);

	dts_check_eq("utc_media_info_get_mime_type_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_mime_type_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *mime_type;

	ret = media_info_get_mime_type(g_item, &mime_type);
	if(mime_type != NULL)
		free(mime_type);

	dts_check_eq("utc_media_info_get_mime_type_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get mime_type ");
}

static void utc_media_info_get_thumbnail_path_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *thumbnail_path = NULL;
	ret = media_info_get_thumbnail_path(NULL, &thumbnail_path);

	if(thumbnail_path != NULL)
		free(thumbnail_path);

	dts_check_eq("utc_media_info_get_thumbnail_path_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_thumbnail_path_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *thumbnail_path = NULL;
	ret = media_info_get_thumbnail_path(g_item, &thumbnail_path);
	tet_printf("\n media_info_get_thumbnail_path : %s\n", thumbnail_path);

	if(thumbnail_path != NULL)
		free(thumbnail_path);

	dts_check_eq("utc_media_info_get_thumbnail_path_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get thumbail path");
}

static void utc_media_info_get_modified_time_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t date_modi;
	ret = media_info_get_modified_time(NULL, &date_modi);

	dts_check_eq("utc_media_info_get_modified_time_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_modified_time_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	tet_printf("item : %p\n", g_item);
	time_t date_modi;
	ret = media_info_get_modified_time(g_item, &date_modi);

	dts_check_eq("utc_media_info_get_modified_time_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get date modified");
}

static void utc_media_info_get_size_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned long long size;

	ret = media_info_get_size(NULL, &size);

	dts_check_eq("utc_media_info_get_size_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_size_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned long long size;

	ret = media_info_get_size(g_item, &size);

	dts_check_eq("utc_media_info_get_size_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get size ");

}

static void utc_media_info_get_storage_type_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e storage_type;

	ret = media_info_get_storage_type(NULL, &storage_type);

	dts_check_eq("utc_media_info_get_storage_type_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_storage_type_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e storage_type;

	ret = media_info_get_storage_type(g_item, &storage_type);

	dts_check_eq("utc_media_info_get_storage_type_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get size ");

}

static void utc_media_info_is_drm_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool is_drm;

	ret = media_info_is_drm(NULL, &is_drm);

	dts_check_eq("utc_media_info_is_drm_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_is_drm_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool is_drm;

	ret = media_info_is_drm(g_item, &is_drm);

	dts_check_eq("utc_media_info_get_is_drm_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get size ");

}

static void utc_media_info_get_altitude_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double altitude;

	ret = media_info_get_altitude(NULL, &altitude);

	dts_check_eq("utc_media_info_get_altitude_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_altitude_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double altitude;

	ret = media_info_get_altitude(g_item, &altitude);

	dts_check_eq("utc_media_info_get_altitude_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get size ");

}

static void utc_media_info_get_latitude_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double latitude;

	ret = media_info_get_altitude(NULL, &latitude);

	dts_check_eq("utc_media_info_get_latitude_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_latitude_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double latitude;

	ret = media_info_get_latitude(g_item, &latitude);

	dts_check_eq("utc_media_info_get_latitude_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get size ");

}

static void utc_media_info_get_longitude_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double longitude;

	ret = media_info_get_longitude(NULL, &longitude);

	dts_check_eq("utc_media_info_get_longitude_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_longitude_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double longitude;

	ret = media_info_get_longitude(g_item, &longitude);

	dts_check_eq("utc_media_info_get_longitude_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get size ");

}
static void utc_media_info_get_description_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *description;

	ret = media_info_get_description(NULL, &description);
	if(description != NULL)
		free(description);

	dts_check_eq("utc_media_info_get_description_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_description_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *description;

	ret = media_info_get_description(g_item, &description);
	if(description != NULL)
		free(description);

	dts_check_eq("utc_media_info_get_description_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get description ");

}

static void utc_media_info_get_rating_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int raitng;

	ret = media_info_get_rating(NULL, &raitng);

	dts_check_eq("utc_media_info_get_rating_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_rating_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int raitng;

	ret = media_info_get_rating(g_item, &raitng);

	dts_check_eq("utc_media_info_get_rating_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get raitng ");
}


static void utc_media_info_get_location_tag_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *location;

	ret = media_info_get_location_tag(NULL, &location);
	if(location != NULL)
		free(location);

	dts_check_eq("utc_media_info_get_location_tag_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_location_tag_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *location;

	ret = media_info_get_location_tag(g_item, &location);
	if(location != NULL)
		free(location);

	dts_check_eq("utc_media_info_get_location_tag_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get location ");
}

static void utc_media_info_get_provider_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *provider;

	ret = media_info_get_provider(NULL, &provider);
	if(provider != NULL)
		free(provider);

	dts_check_eq("utc_media_info_get_provider_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_provider_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *provider;

	ret = media_info_get_provider(g_item, &provider);
	if(provider != NULL)
		free(provider);

	dts_check_eq("utc_media_info_get_provider_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get provider ");
}

static void utc_media_info_get_content_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *content_name;

	ret = media_info_get_content_name(NULL, &content_name);
	if(content_name != NULL)
		free(content_name);

	dts_check_eq("utc_media_info_get_content_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_content_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *content_name;

	ret = media_info_get_content_name(g_item, &content_name);
	if(content_name != NULL)
		free(content_name);

	dts_check_eq("utc_media_info_get_content_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get content_name ");
}

static void utc_media_info_get_category_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *category;

	ret = media_info_get_category(NULL, &category);
	if(category != NULL)
		free(category);

	dts_check_eq("utc_media_info_get_category_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_category_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *category;

	ret = media_info_get_category(g_item, &category);
	if(category != NULL)
		free(category);

	dts_check_eq("utc_media_info_get_category_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get category ");
}

static void utc_media_info_get_age_rating_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *age_rating;

	ret = media_info_get_age_rating(NULL, &age_rating);
	if(age_rating != NULL)
		free(age_rating);

	dts_check_eq("utc_media_info_get_age_rating_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_age_rating_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *age_rating;

	ret = media_info_get_age_rating(g_item, &age_rating);
	if(age_rating != NULL)
		free(age_rating);

	dts_check_eq("utc_media_info_get_age_rating_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get age_rating ");
}

static void utc_media_info_get_keyword_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *keyword;

	ret = media_info_get_keyword(NULL, &keyword);
	if(keyword != NULL)
		free(keyword);

	dts_check_eq("utc_media_info_get_keyword_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_keyword_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *keyword;

	ret = media_info_get_keyword(g_item, &keyword);
	if(keyword != NULL)
		free(keyword);

	dts_check_eq("utc_media_info_get_keyword_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get keyword ");
}

static void utc_media_info_get_author_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *author;

	ret = media_info_get_author(NULL, &author);
	if(author != NULL)
		free(author);

	dts_check_eq("utc_media_info_get_author_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_author_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *author;

	ret = media_info_get_author(g_item, &author);
	if(author != NULL)
		free(author);

	dts_check_eq("utc_media_info_get_author_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get author ");
}

static void utc_media_info_get_added_time_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t added_time;

	ret = media_info_get_added_time(NULL, &added_time);

	dts_check_eq("utc_media_info_get_added_time_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_added_time_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t added_time;

	ret = media_info_get_added_time(g_item, &added_time);

	dts_check_eq("utc_media_info_get_added_time_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get added_time ");

}

static void utc_media_info_get_favorite_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool fav;
	ret = media_info_get_favorite(NULL, &fav);

	dts_check_eq("utc_media_info_get_favorite_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_favorite_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	tet_printf("item : %p\n", g_item);
	bool fav;
	ret = media_info_get_favorite(g_item, &fav);

	dts_check_eq("utc_media_info_get_favorite_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get favorite");
}

static void utc_media_info_get_media_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h media = NULL;

	ret = media_info_get_media_from_db(NULL, &media);

	if(media != NULL)
		media_info_destroy(media);

	dts_check_eq("utc_media_info_get_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_media_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h media = NULL;

	ret = media_info_get_media_from_db(g_item_media_id, &media);

	if(media != NULL)
		media_info_destroy(media);

	dts_check_eq("utc_media_info_get_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get mediainfo ");
}

static void utc_media_info_get_image_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	image_meta_h image = NULL;

	ret = media_info_get_image(NULL, &image);

	if(image != NULL)
		image_meta_destroy(image);

	dts_check_eq("utc_media_info_get_image_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_image_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	image_meta_h image = NULL;

	ret = media_info_get_image(g_item, &image);

	if(image != NULL)
		image_meta_destroy(image);

	dts_check_eq("utc_media_info_get_image_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get imageinfo ");
}

static void utc_media_info_get_video_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	video_meta_h video = NULL;

	ret = media_info_get_video(NULL, &video);

	if(video != NULL)
		video_meta_destroy(video);

	dts_check_eq("utc_media_info_get_video_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_video_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	video_meta_h video = NULL;

	ret = media_info_get_video(g_vitem, &video);

	if(video != NULL)
		video_meta_destroy(video);

	dts_check_eq("utc_media_info_get_video_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get videoinfo");
}

static void utc_media_info_get_audio_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_h audio = NULL;

	ret = media_info_get_audio(NULL, &audio);

	if(audio != NULL)
		audio_meta_destroy(audio);

	dts_check_eq("utc_media_info_get_audio_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_audio_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_h audio = NULL;

	ret = media_info_get_audio(g_aitem, &audio);

	if(audio != NULL)
		audio_meta_destroy(audio);


	dts_check_eq("utc_media_info_get_audio_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get audio");
}

static void utc_media_info_refresh_metadata_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_refresh_metadata_to_db(NULL);

	dts_check_eq("utc_media_info_refresh_metadata_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_refresh_metadata_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_info_refresh_metadata_to_db(g_item_media_id);

	dts_check_eq("utc_media_info_refresh_metadata_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to refresh metadata");
}

bool sub_tag_cb(media_tag_h tag, void *user_data)
{
	char *name;
	if(tag != NULL)
	{
		media_tag_get_name(tag, &name);
		tet_printf("tag name : %s \n", name);
	}

	return false;
}

bool sub_bookmark_cb(media_bookmark_h bookmark, void *user_data)
{
	int bm_id;

	if(bookmark != NULL)
	{
		media_bookmark_get_bookmark_id(bookmark, &bm_id);
		tet_printf("bookmark id : %d \n", bm_id);
	}

	return false;
}

static void utc_media_info_foreach_tag_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_foreach_tag_from_db(NULL, filter, NULL, NULL);

	dts_check_eq("utc_media_info_foreach_tag_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_foreach_tag_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	media_filter_create(&filter);

	ret = media_info_foreach_tag_from_db(g_item_media_id, filter, sub_tag_cb, NULL);

	dts_check_eq("utc_media_info_foreach_tag_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to call callback function");
}

static void utc_media_info_foreach_bookmark_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_foreach_tag_from_db(NULL, filter, NULL, NULL);

	dts_check_eq("utc_media_info_foreach_bookmark_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_foreach_bookmark_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	media_filter_create(&filter);

	ret = media_info_foreach_bookmark_from_db(g_item_media_id, filter, sub_bookmark_cb, NULL);

	dts_check_eq("utc_media_info_foreach_bookmark_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to call callback function");
}

static void utc_media_info_get_bookmark_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	ret = media_info_get_bookmark_count_from_db(NULL, filter, &count);

	dts_check_eq("utc_media_info_get_bookmark_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_bookmark_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_bookmark_count_from_db(g_item_media_id, filter, &count);

	dts_check_eq("utc_media_info_get_bookmark_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to call callback function");
}

static void utc_media_info_get_media_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_get_media_count_from_db(filter, NULL);

	dts_check_eq("utc_media_info_get_media_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_media_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_media_count_from_db(filter, &count);

	dts_check_eq("utc_media_info_get_media_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to call callback function");
}

static void utc_media_info_get_tag_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	ret = media_info_get_tag_count_from_db(NULL, filter, &count);

	dts_check_eq("utc_media_info_get_tag_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_info_get_tag_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_tag_count_from_db(g_item_media_id, filter, &count);

	dts_check_eq("utc_media_info_get_tag_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to call callback function");
}

