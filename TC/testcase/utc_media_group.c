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

static void utc_media_album_get_album_count_from_db_n(void);
static void utc_media_album_get_album_count_from_db_p(void);
static void utc_media_album_foreach_album_from_db_n(void);
static void utc_media_album_foreach_album_from_db_p(void);
static void utc_media_album_get_media_count_from_db_n(void);
static void utc_media_album_get_media_count_from_db_p(void);
static void utc_media_album_foreach_media_from_db_n(void);
static void utc_media_album_foreach_media_from_db_p(void);
static void utc_media_album_get_album_from_db_n(void);
static void utc_media_album_get_album_from_db_p(void);
static void utc_media_album_get_album_id_n(void);
static void utc_media_album_get_album_id_p(void);
static void utc_media_album_get_name_n(void);
static void utc_media_album_get_name_p(void);
static void utc_media_album_get_artist_n(void);
static void utc_media_album_get_artist_p(void);
static void utc_media_album_get_album_art_n(void);
static void utc_media_album_get_album_art_p(void);
static void utc_media_album_clone_n(void);
static void utc_media_album_clone_p(void);
static void utc_media_album_destroy_n(void);
static void utc_media_album_destroy_p(void);

struct tet_testlist tet_testlist[] = {
	{ utc_media_album_get_album_count_from_db_n, 1 },
	{ utc_media_album_get_album_count_from_db_p, 1 },
	{ utc_media_album_foreach_album_from_db_n, 1 },
	{ utc_media_album_foreach_album_from_db_p, 1 },
	{ utc_media_album_get_media_count_from_db_n, 1 },
	{ utc_media_album_get_media_count_from_db_p, 1 },
	{ utc_media_album_foreach_media_from_db_n, 1 },
	{ utc_media_album_foreach_media_from_db_p, 1 },
	{ utc_media_album_get_album_from_db_n, 2},
	{ utc_media_album_get_album_from_db_p, 2},
	{ utc_media_album_get_album_id_n, 3},
	{ utc_media_album_get_album_id_p, 3},
	{ utc_media_album_get_name_n, 3},
	{ utc_media_album_get_name_p, 3},
	{ utc_media_album_get_artist_n, 3},
	{ utc_media_album_get_artist_p, 3},
	{ utc_media_album_get_album_art_n, 3},
	{ utc_media_album_get_album_art_p, 3},
	{ utc_media_album_clone_n, 3},
	{ utc_media_album_clone_p, 3},
	{ utc_media_album_destroy_n, 4},
	{ utc_media_album_destroy_p, 4},
	{ NULL, 0 },
};

static media_album_h g_album;
static media_album_h g_album_dst;
static filter_h g_filter;
static int g_album_id = 0;
static char *g_album_name = NULL;
static char *g_artist_name = NULL;
static char *g_genre_name = NULL;
static char *g_composer_name = NULL;
static char *g_year_name = NULL;

bool media_item_cb(media_info_h media, void *user_data)
{
	return true;
}

bool album_cb(media_album_h album, void *user_data)
{
	if(album != NULL)
	{
		media_album_get_album_id(album, &g_album_id);
		media_album_get_name(album, &g_album_name);
	}

	return true;
}

bool group_cb(const char *name, void *user_data)
{
	if(name != NULL)
	{
		if(!strcmp((char*)user_data, "artist"))
			g_artist_name = strdup(name);
		else if(!strcmp((char*)user_data, "genre"))
			g_genre_name = strdup(name);
		else if(!strcmp((char*)user_data, "composer"))
			g_composer_name = strdup(name);
		else if(!strcmp((char*)user_data, "year"))
			g_year_name = strdup(name);

		tet_printf("\n get group name success");
	}

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
	media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, "MEDIA_TITLE", MEDIA_CONTENT_COLLATE_DEFAULT);
	if(g_filter == NULL)
	{
		tet_printf("\n filter create failed");
		return;
	}

	tet_printf("\n TC start END");
}


static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");

	if(g_album_name != NULL)
		free(g_album_name);

	if(g_artist_name != NULL)
		free(g_artist_name);

	if(g_genre_name != NULL)
		free(g_genre_name);

	if(g_composer_name != NULL)
		free(g_composer_name);

	if(g_year_name != NULL)
		free(g_year_name);

	if(g_filter != NULL)
		media_filter_destroy(g_filter);

	if(g_album != NULL)
		media_album_destroy(g_album);

	int ret = media_content_disconnect();

	if(ret != MEDIA_CONTENT_ERROR_NONE)
		tet_printf("\n database disconnection is failed");
	else
		tet_printf("\n database disconnection is success");

}


static void utc_media_album_get_album_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_count_from_db(g_filter, NULL);

	dts_check_eq("utc_media_album_get_album_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_album_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int album_count = 0;

	ret = media_album_get_album_count_from_db(g_filter, &album_count);

	dts_check_eq("utc_media_album_get_album_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album count");
}

static void utc_media_album_foreach_album_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_album_from_db(g_filter, NULL, NULL);

	dts_check_eq("utc_media_album_foreach_album_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_foreach_album_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_album_from_db(g_filter, album_cb, NULL);

	dts_check_eq("utc_media_album_foreach_album_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album media");
}

static void utc_media_album_get_media_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_album_get_media_count_from_db(0, g_filter, &media_count);

	dts_check_eq("utc_media_album_get_media_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_media_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_album_get_media_count_from_db(g_album_id, g_filter, &media_count);

	dts_check_eq("utc_media_album_get_media_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album media count");
}

static void utc_media_album_foreach_media_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_media_from_db(0, g_filter, media_item_cb, NULL);

	dts_check_eq("utc_media_album_foreach_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_foreach_media_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_media_from_db(g_album_id, g_filter, media_item_cb, NULL);

	dts_check_eq("utc_media_album_foreach_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album media count");
}

static void utc_media_album_get_album_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_from_db(-1, &g_album);

	dts_check_eq("utc_media_album_get_album_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_album_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_from_db(g_album_id, &g_album);

	dts_check_eq("utc_media_album_get_album_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album by album_id");
}

static void utc_media_album_get_album_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_id(g_album, NULL);

	dts_check_eq("utc_media_album_get_album_id_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_album_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int album_id = 0;

	ret = media_album_get_album_id(g_album, &album_id);

	dts_check_eq("utc_media_album_get_album_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album id");
}

static void utc_media_album_get_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_name(NULL, NULL);

	dts_check_eq("utc_media_album_get_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_name = NULL;

	ret = media_album_get_name(g_album, &album_name);

	if(album_name)
		free(album_name);

	dts_check_eq("utc_media_album_get_album_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album name");
}

static void utc_media_album_get_artist_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_artist(NULL, NULL);

	dts_check_eq("utc_media_album_get_artist_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_artist_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist_name = NULL;

	ret = media_album_get_artist(g_album, &artist_name);

	if(artist_name)
		free(artist_name);

	dts_check_eq("utc_media_album_get_artist_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get artist name");
}

static void utc_media_album_get_album_art_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_art(NULL, NULL);

	dts_check_eq("utc_media_album_get_album_art_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_get_album_art_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_art = NULL;

	ret = media_album_get_album_art(g_album, &album_art);

	if(album_art)
		free(album_art);

	dts_check_eq("utc_media_album_get_album_art_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get album_art path");
}

static void utc_media_album_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_clone(NULL, NULL);

	dts_check_eq("utc_media_album_clone_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_clone(&g_album_dst, g_album);

	dts_check_eq("utc_media_album_clone_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone album");
}

static void utc_media_album_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_destroy(NULL);

	dts_check_eq("utc_media_album_destroy_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_album_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_destroy(g_album_dst);

	dts_check_eq("utc_media_album_destroy_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destroy album");
}
