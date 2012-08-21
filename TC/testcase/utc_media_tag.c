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


static void utc_media_tag_insert_to_db_n(void);
static void utc_media_tag_insert_to_db_p(void);
static void utc_media_tag_delete_from_db_n(void);
static void utc_media_tag_delete_from_db_p(void);
static void utc_media_tag_get_tag_count_from_db_n(void);
static void utc_media_tag_get_tag_count_from_db_p(void);
static void utc_media_tag_foreach_tag_from_db_n(void);
static void utc_media_tag_foreach_tag_from_db_p(void);
static void utc_media_tag_get_media_count_from_db_n(void);
static void utc_media_tag_get_media_count_from_db_p(void);
static void utc_media_tag_foreach_media_from_db_n(void);
static void utc_media_tag_foreach_media_from_db_p(void);
static void utc_media_tag_destroy_n(void);
static void utc_media_tag_destroy_p(void);
static void utc_media_tag_clone_n(void);
static void utc_media_tag_clone_p(void);
static void utc_media_tag_update_to_db_n(void);
static void utc_media_tag_update_to_db_p(void);
static void utc_media_tag_add_media_n(void);
static void utc_media_tag_add_media_p(void);
static void utc_media_tag_remove_media_n(void);
static void utc_media_tag_remove_media_p(void);
static void utc_media_tag_set_name_n(void);
static void utc_media_tag_set_name_p(void);
static void utc_media_tag_get_tag_id_n(void);
static void utc_media_tag_get_tag_id_p(void);
static void utc_media_tag_get_name_n(void);
static void utc_media_tag_get_name_p(void);
static void utc_media_tag_get_tag_from_db_n(void);
static void utc_media_tag_get_tag_from_db_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_media_tag_insert_to_db_n, 1 },
	{ utc_media_tag_insert_to_db_p, 1 },
	{ utc_media_tag_delete_from_db_n, 5 },
	{ utc_media_tag_delete_from_db_p, 5 },
	{ utc_media_tag_get_tag_count_from_db_n, 2 },
	{ utc_media_tag_get_tag_count_from_db_p, 2 },
	{ utc_media_tag_foreach_tag_from_db_n, 2 },
	{ utc_media_tag_foreach_tag_from_db_p, 2 },
	{ utc_media_tag_get_media_count_from_db_n, 4 },
	{ utc_media_tag_get_media_count_from_db_p, 4 },
	{ utc_media_tag_foreach_media_from_db_n, 4 },
	{ utc_media_tag_foreach_media_from_db_p, 4 },
	{ utc_media_tag_destroy_n, 7 },
	{ utc_media_tag_destroy_p, 7 },
	{ utc_media_tag_clone_n, 6 },
	{ utc_media_tag_clone_p, 6 },
	{ utc_media_tag_update_to_db_n, 4 },
	{ utc_media_tag_update_to_db_p, 4 },
	{ utc_media_tag_add_media_n, 3 },
	{ utc_media_tag_add_media_p, 3 },
	{ utc_media_tag_remove_media_n, 2 },
	{ utc_media_tag_remove_media_p, 2 },
	{ utc_media_tag_set_name_n, 3 },
	{ utc_media_tag_set_name_p, 3 },
	{ utc_media_tag_get_tag_id_n, 2 },
	{ utc_media_tag_get_tag_id_p, 2 },
	{ utc_media_tag_get_name_n, 2 },
	{ utc_media_tag_get_name_p, 2 },
	{ utc_media_tag_get_tag_from_db_n, 5 },
	{ utc_media_tag_get_tag_from_db_p, 5 },
	{ NULL, 0 },
};

static media_tag_h g_tag;
static media_tag_h g_tag_dst;
static int g_tag_id;
static char *g_media_id = NULL;

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

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
	filter_h filter;
	g_tag = NULL;
	g_tag_dst = NULL;

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

	char *condition = "MEDIA_TYPE=1";	//Video

	media_filter_create(&filter);
	media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	if(filter == NULL)
	{
		tet_printf("\n filter create failed");
		return;
	}

	ret = media_info_foreach_media_from_db(filter, media_item_cb, NULL);
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		tet_printf("\n get media_info failed");
		return;
	}

	media_filter_destroy(filter);

	tet_printf("\n TC start END");

}

static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");

	if(g_tag != NULL)
		media_tag_destroy(g_tag);

	int ret = media_content_disconnect();

	if(ret != MEDIA_CONTENT_ERROR_NONE)
		tet_printf("\n database disconnection is failed");
	else
		tet_printf("\n database disconnection is success");
}

bool tag_cb(media_tag_h tag, void *user_data)
{
	char *name = NULL;
	
	if(tag != NULL)
	{	
		media_tag_get_name(tag, &name);

		if(name != NULL)
		{
			printf(" tag name : %s \n", name);
			free(name);
		}
		
	}

	return true;
}

static void utc_media_tag_insert_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_insert_to_db(NULL, &g_tag);

	dts_check_eq("utc_media_tag_insert_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_insert_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_insert_to_db("tag_test_1", &g_tag);
	media_tag_get_tag_id(g_tag, &g_tag_id);

	dts_check_eq("utc_media_tag_insert_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to insert the tag");
}

static void utc_media_tag_delete_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_delete_from_db(-1);

	dts_check_eq("utc_media_tag_delete_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_delete_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_delete_from_db(g_tag_id);

	dts_check_eq("utc_media_tag_delete_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to delete the name");
}

static void utc_media_tag_get_tag_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_get_tag_count_from_db(NULL, NULL);

	dts_check_eq("utc_media_tag_get_tag_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}
static void utc_media_tag_get_tag_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int tag_count = 0;

	ret = media_tag_get_tag_count_from_db(NULL, &tag_count);
	dts_check_eq("utc_media_tag_get_tag_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get tag count");
}

static void utc_media_tag_foreach_tag_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_tag_from_db(NULL, NULL, NULL);

	dts_check_eq("utc_media_tag_foreach_tag_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_foreach_tag_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_tag_from_db(NULL, tag_cb, NULL);

	dts_check_eq("utc_media_tag_foreach_tag_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the tag lists");
}

static void utc_media_tag_get_media_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_get_media_count_from_db(g_tag_id, NULL, NULL);

	dts_check_eq("utc_media_tag_get_media_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_get_media_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_tag_get_media_count_from_db(g_tag_id, NULL, &media_count);

	dts_check_eq("utc_media_tag_get_media_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get media count");
}

static void utc_media_tag_foreach_media_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_media_from_db(g_tag_id, NULL, NULL, NULL);

	dts_check_eq("utc_media_tag_foreach_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_foreach_media_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_media_from_db(g_tag_id, NULL, media_item_cb, NULL);

	dts_check_eq("utc_media_tag_foreach_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the media list in tag");
}

static void utc_media_tag_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_destroy(NULL);

	dts_check_eq("utc_media_tag_destroy_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_destroy(g_tag_dst);

	dts_check_eq("utc_media_tag_destroy_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destory the tag");
}

static void utc_media_tag_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_clone(&g_tag_dst, NULL);

	dts_check_eq("utc_media_tag_clone_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_clone(&g_tag_dst, g_tag);

	dts_check_eq("utc_media_tag_clone_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone the tag");
}

static void utc_media_tag_update_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_update_to_db(NULL);

	dts_check_eq("utc_media_tag_clone_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_update_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_update_to_db(g_tag);

	dts_check_eq("utc_media_tag_clone_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to update tag");
}

static void utc_media_tag_add_media_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_add_media(NULL, g_media_id);

	dts_check_eq("utc_media_tag_add_media_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_add_media_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_add_media(g_tag, g_media_id);

	dts_check_eq("utc_media_tag_add_media_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to add the tag to media");
}

static void utc_media_tag_remove_media_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_remove_media(NULL, g_media_id);

	dts_check_eq("utc_media_tag_remove_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_remove_media_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_remove_media(g_tag, g_media_id);

	dts_check_eq("utc_media_tag_remove_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to remove the media from tag");

}

static void utc_media_tag_set_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_set_name(NULL, "myTag");

	dts_check_eq("utc_media_tag_set_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_set_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_set_name(g_tag, "myTag");

	dts_check_eq("utc_media_tag_set_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to remove set tag name");
}

static void utc_media_tag_get_tag_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int tag_id = 0;

	ret = media_tag_get_tag_id(NULL, &tag_id);

	dts_check_eq("utc_media_tag_set_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_get_tag_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int tag_id = 0;

	ret = media_tag_get_tag_id(g_tag, &tag_id);

	dts_check_eq("utc_media_tag_get_tag_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get tag id");
}

static void utc_media_tag_get_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_tag_get_name(NULL, &name);

	dts_check_eq("utc_media_tag_get_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_get_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_tag_get_name(g_tag, &name);

	if(name != NULL)
		free(name);

	dts_check_eq("utc_media_tag_get_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the tag name");
}

static void utc_media_tag_get_tag_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_tag_h tag;

	ret = media_tag_get_tag_from_db(0, &tag);

	dts_check_eq("utc_media_tag_get_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_media_tag_get_tag_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_tag_h tag = NULL;

	ret = media_tag_get_tag_from_db(g_tag_id, &tag);
	media_tag_destroy(tag);

	dts_check_eq("utc_media_tag_get_tag_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the tag");
}
