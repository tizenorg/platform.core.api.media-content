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
#include <stdlib.h>
#include <media_content.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;


static void utc_media_playlist_insert_to_db_n(void);
static void utc_media_playlist_insert_to_db_p(void);
static void utc_media_playlist_delete_from_db_n(void);
static void utc_media_playlist_delete_from_db_p(void);
static void utc_media_playlist_get_playlist_count_from_db_n(void);
static void utc_media_playlist_get_playlist_count_from_db_p(void);
static void utc_media_playlist_foreach_playlist_from_db_n(void);
static void utc_media_playlist_foreach_playlist_from_db_p(void);
static void utc_media_playlist_get_media_count_from_db_n(void);
static void utc_media_playlist_get_media_count_from_db_p(void);
static void utc_media_playlist_foreach_media_from_db_n(void);
static void utc_media_playlist_foreach_media_from_db_p(void);
static void utc_media_playlist_destroy_n(void);
static void utc_media_playlist_destroy_p(void);
static void utc_media_playlist_clone_n(void);
static void utc_media_playlist_clone_p(void);
static void utc_media_playlist_get_playlist_from_db_n(void);
static void utc_media_playlist_get_playlist_from_db_p(void);
static void utc_media_playlist_get_playlist_id_n(void);
static void utc_media_playlist_get_playlist_id_p(void);
static void utc_media_playlist_get_name_n(void);
static void utc_media_playlist_get_name_p(void);
static void utc_media_playlist_get_play_order_n(void);
static void utc_media_playlist_get_play_order_p(void);
static void utc_media_playlist_update_to_db_n(void);
static void utc_media_playlist_update_to_db_p(void);
static void utc_media_playlist_set_name_n(void);
static void utc_media_playlist_set_name_p(void);
static void utc_media_playlist_set_play_order_n(void);
static void utc_media_playlist_set_play_order_p(void);

static void utc_media_playlist_add_media_n(void);
static void utc_media_playlist_add_media_p(void);
static void utc_media_playlist_remove_media_n(void);
static void utc_media_playlist_remove_media_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_media_playlist_insert_to_db_n, 1 },
	{ utc_media_playlist_insert_to_db_p, 1 },
	{ utc_media_playlist_get_playlist_count_from_db_n, 4 },
	{ utc_media_playlist_get_playlist_count_from_db_p, 4 },
	{ utc_media_playlist_foreach_playlist_from_db_n, 4 },
	{ utc_media_playlist_foreach_playlist_from_db_p, 4 },
	{ utc_media_playlist_get_media_count_from_db_n, 4 },
	{ utc_media_playlist_get_media_count_from_db_p, 4 },
	{ utc_media_playlist_foreach_media_from_db_n, 4 },
	{ utc_media_playlist_foreach_media_from_db_p, 4 },
	{ utc_media_playlist_get_playlist_from_db_n, 4 },
	{ utc_media_playlist_get_playlist_from_db_p, 4 },
	{ utc_media_playlist_get_playlist_id_n, 4 },
	{ utc_media_playlist_get_playlist_id_p, 4 },
	{ utc_media_playlist_get_name_n, 4 },
	{ utc_media_playlist_get_name_p, 4 },
	{ utc_media_playlist_get_play_order_n, 5 },
	{ utc_media_playlist_get_play_order_p, 5 },
	{ utc_media_playlist_update_to_db_n, 3 },
	{ utc_media_playlist_update_to_db_p, 3 },
	{ utc_media_playlist_set_name_n, 2 },
	{ utc_media_playlist_set_name_p, 2 },
	{ utc_media_playlist_set_play_order_n, 5 },
	{ utc_media_playlist_set_play_order_p, 5 },
	{ utc_media_playlist_add_media_n, 2 },
	{ utc_media_playlist_add_media_p, 2 },
	{ utc_media_playlist_remove_media_n, 6 },
	{ utc_media_playlist_remove_media_p, 6 },
	{ utc_media_playlist_clone_n, 7 },
	{ utc_media_playlist_clone_p, 7 },
	{ utc_media_playlist_delete_from_db_n, 8 },
	{ utc_media_playlist_delete_from_db_p, 8 },
	{ utc_media_playlist_destroy_n, 8 },
	{ utc_media_playlist_destroy_p, 8 },
	{ NULL, 0 },
};

static media_playlist_h g_playlist;
static media_playlist_h g_playlist_dst;

static filter_h g_filter;
static char *g_media_id = NULL;
static int g_playlist_id = 0;
static int g_playlist_member_id = 0;

bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL))
	{
		tet_printf("\n get media_id failed");
		return false;
	}

	return true;
}

bool playlist_item_cb(int playlist_member_id, media_info_h media, void *user_data)
{
	g_playlist_member_id = playlist_member_id;

	tet_printf("cb - member id : %d", g_playlist_member_id);
	return true;
}

bool playlist_cb(media_playlist_h playlist, void *user_data)
{
	return true;
}

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");

	int ret = media_content_connect();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		tet_printf("\n database connection is failed");
		return;
	}
	else
	{
		tet_printf("\n database connection is success");
	}

	char *condition = "MEDIA_TYPE=3";	//Music

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	//media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, "MEDIA_TITLE", MEDIA_CONTENT_COLLATE_DEFAULT);

	if(g_filter == NULL)
	{
		tet_printf("\n filter create failed");
		return;
	}

	ret = media_info_foreach_media_from_db(g_filter, media_item_cb, NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		tet_printf("\n get media_info failed");
		return;
	}

	tet_printf("\n TC start END");
}


static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");

	if(g_media_id != NULL)
		free(g_media_id);

	if(g_filter != NULL)
		media_filter_destroy(g_filter);

	if(g_playlist != NULL)
		media_playlist_destroy(g_playlist);

	int ret = media_content_disconnect();

	if(ret != MEDIA_CONTENT_ERROR_NONE)
		tet_printf("\n database disconnection is failed");
	else
		tet_printf("\n database disconnection is success");

}

static void utc_media_playlist_insert_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_insert_to_db(NULL, &g_playlist);

	dts_check_eq("utc_media_playlist_insert_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_insert_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_insert_to_db("test_playlist_1", &g_playlist);

	ret = media_playlist_get_playlist_id(g_playlist, &g_playlist_id);

	dts_check_eq("utc_media_playlist_insert_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to insert the playlist");
}

static void utc_media_playlist_delete_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_delete_from_db(-1);

	dts_check_eq("utc_media_playlist_delete_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_delete_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_delete_from_db(g_playlist_id);

	dts_check_eq("utc_media_playlist_delete_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to delete the playlist");
}

static void utc_media_playlist_get_playlist_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_playlist_count_from_db(g_filter, NULL);

	dts_check_eq("utc_media_playlist_get_playlist_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_get_playlist_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_count = 0;

	ret = media_playlist_get_playlist_count_from_db(g_filter, &playlist_count);

	dts_check_eq("utc_media_playlist_get_playlist_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get playlist count");
}

static void utc_media_playlist_foreach_playlist_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_playlist_from_db(g_filter, NULL, NULL);

	dts_check_eq("utc_media_playlist_foreach_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_foreach_playlist_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_playlist_from_db(g_filter, playlist_cb, NULL);

	dts_check_eq("utc_media_playlist_foreach_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get list of playlist");
}

static void utc_media_playlist_get_media_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_media_count_from_db(0, g_filter, NULL);

	dts_check_eq("utc_media_playlist_get_media_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_get_media_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_playlist_get_media_count_from_db(g_playlist_id, g_filter, &media_count);

	dts_check_eq("utc_media_playlist_get_media_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the item count");
}

static void utc_media_playlist_foreach_media_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_media_from_db(0, g_filter, playlist_item_cb, NULL);

	dts_check_eq("utc_media_playlist_foreach_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_foreach_media_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_media_from_db(g_playlist_id, g_filter, playlist_item_cb, NULL);

	dts_check_eq("utc_media_playlist_foreach_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the list of item");
}

static void utc_media_playlist_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_destroy(NULL);

	dts_check_eq("utc_media_playlist_destroy_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_destroy(g_playlist_dst);

	dts_check_eq("utc_media_playlist_destroy_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destory the playlist");
}

static void utc_media_playlist_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_clone(&g_playlist_dst, NULL);

	dts_check_eq("utc_media_playlist_clone_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_clone(&g_playlist_dst, g_playlist);

	dts_check_eq("utc_media_playlist_clone_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone the playlist");
}

static void utc_media_playlist_get_playlist_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_playlist_h playlist;

	ret = media_playlist_get_playlist_from_db(0, g_filter, &playlist);

	dts_check_eq("utc_media_playlist_get_playlist_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_get_playlist_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_playlist_h playlist;

	ret = media_playlist_get_playlist_from_db(g_playlist_id, g_filter, &playlist);

	dts_check_eq("utc_media_playlist_get_playlist_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get playlist");
}

static void utc_media_playlist_get_playlist_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_playlist_id(NULL, NULL);

	dts_check_eq("utc_media_playlist_get_id_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_get_playlist_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_id = 0;

	ret = media_playlist_get_playlist_id(g_playlist, &playlist_id);

	dts_check_eq("utc_media_playlist_get_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the name of playlist");
}

static void utc_media_playlist_get_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_playlist_get_name(NULL, &name);

	dts_check_eq("utc_media_playlist_get_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_get_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_playlist_get_name(g_playlist, &name);

	if(name != NULL)
		free(name);

	dts_check_eq("utc_media_playlist_get_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the name of playlist");
}

static void utc_media_playlist_get_play_order_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_play_order(NULL, g_playlist_member_id, NULL);

	dts_check_eq("utc_media_playlist_get_play_order_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_get_play_order_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_order = 0;

	ret = media_playlist_get_play_order(g_playlist, g_playlist_member_id, &playlist_order);

	dts_check_eq("utc_media_playlist_get_play_order_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the name of playlist");
}

static void utc_media_playlist_update_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_update_to_db(NULL);

	dts_check_eq("media_playlist_update_to_db", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_update_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_update_to_db(g_playlist);

	dts_check_eq("utc_media_playlist_update_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to update name of playlist");
}

static void utc_media_playlist_set_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_name(NULL, NULL);

	dts_check_eq("utc_media_playlist_set_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_set_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_name(g_playlist, "myPlaylist");

	dts_check_eq("utc_media_playlist_set_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set name of playlist");
}

static void utc_media_playlist_set_play_order_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_play_order(NULL, g_playlist_member_id, 3);

	dts_check_eq("utc_media_playlist_set_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_set_play_order_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_play_order(g_playlist, g_playlist_member_id, 3);

	dts_check_eq("utc_media_playlist_set_play_order_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set name of playlist");
}

static void utc_media_playlist_add_media_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_add_media(NULL, g_media_id);

	dts_check_eq("utc_media_playlist_add_media_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_add_media_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_add_media(g_playlist, g_media_id);

	dts_check_eq("utc_media_playlist_add_media_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to add the item to playlist");
}

static void utc_media_playlist_remove_media_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	tet_printf("member id : %d", g_playlist_member_id);
	ret = media_playlist_remove_media(NULL, g_playlist_member_id);

	dts_check_eq("utc_media_playlist_remove_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_playlist_remove_media_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_remove_media(g_playlist, g_playlist_member_id);

	dts_check_eq("utc_media_playlist_remove_media_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to remove the item in playlist");
}
