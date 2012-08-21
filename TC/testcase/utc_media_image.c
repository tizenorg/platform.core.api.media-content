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

static void utc_image_meta_destroy_n(void);
static void utc_image_meta_destroy_p(void);
static void utc_image_meta_clone_n(void);
static void utc_image_meta_clone_p(void);
static void utc_image_meta_get_media_id_n(void);
static void utc_image_meta_get_media_id_p(void);
static void utc_image_meta_get_width_n(void);
static void utc_image_meta_get_width_p(void);
static void utc_image_meta_get_height_n(void);
static void utc_image_meta_get_height_p(void);
static void utc_image_meta_get_orientation_n(void);
static void utc_image_meta_get_orientation_p(void);
static void utc_image_meta_get_date_taken_n(void);
static void utc_image_meta_get_date_taken_p(void);
static void utc_image_meta_set_orientation_n(void);
static void utc_image_meta_set_orientation_p(void);
static void utc_image_meta_update_to_db_n(void);
static void utc_image_meta_update_to_db_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_image_meta_destroy_n, 5 },
	{ utc_image_meta_destroy_p, 5 },
	{ utc_image_meta_clone_n, 4 },
	{ utc_image_meta_clone_p, 4 },
	{ utc_image_meta_get_media_id_n, 1 },
	{ utc_image_meta_get_media_id_p, 1 },
	{ utc_image_meta_get_width_n, 1 },
	{ utc_image_meta_get_width_p, 1 },
	{ utc_image_meta_get_height_n, 1 },
	{ utc_image_meta_get_height_p, 1 },
	{ utc_image_meta_get_orientation_n, 1 },
	{ utc_image_meta_get_orientation_p, 1 },
	{ utc_image_meta_get_date_taken_n, 1 },
	{ utc_image_meta_get_date_taken_p, 1 },
	{ utc_image_meta_set_orientation_n, 2 },
	{ utc_image_meta_set_orientation_p, 2 },
	{ utc_image_meta_update_to_db_n, 3 },
	{ utc_image_meta_update_to_db_p, 3 },
	{ NULL, 0 },
};

static image_meta_h g_image;
static image_meta_h g_image_dst;
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

	ret = media_info_get_image(media, &g_image);
	if((ret != MEDIA_CONTENT_ERROR_NONE) || (g_image == NULL))
	{
		tet_printf("\n get image_meta failed");
		return false;
	}

	return true;
}

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
	filter_h filter;
	g_image = NULL;

	int ret = media_content_connect();
	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		tet_printf("\n database connection is failed");
		return;
	}
	else
		tet_printf("\n database connection is success");

	char *condition = "MEDIA_TYPE=0";	//Image

	media_filter_create(&filter);
	media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_DISPLAY_NAME, MEDIA_CONTENT_COLLATE_DEFAULT);
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

	if(g_media_id != NULL)
		free(g_media_id);

	if(g_image != NULL)
		image_meta_destroy(g_image);

	int ret = media_content_disconnect();
	
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		tet_printf("\n database disconnection is failed");
	else
		tet_printf("\n database disconnection is success");
}


/**
 * @brief Negative test case of content_image_meta_destroy()
 */
static void utc_image_meta_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_destroy(NULL);

	dts_check_eq("utc_image_meta_destroy", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}


/**
 * @brief Positive test case of content_image_meta_destroy()
 */
static void utc_image_meta_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_destroy(g_image_dst);

	dts_check_eq("utc_image_meta_destroy", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destroy imageinfo object");
}

/**
 * @brief Negative test case of image_meta_clone()
 */
static void utc_image_meta_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	ret = image_meta_clone(&g_image_dst, NULL);

	dts_check_eq("utc_image_meta_clone", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of image_meta_clone()
 */
static void utc_image_meta_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	ret = image_meta_clone(&g_image_dst, g_image);

	dts_check_eq("utc_image_meta_clone", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone imageinfo object");
}

/**
 * @brief Negative test case of image_meta_get_media_id()
 */
static void utc_image_meta_get_media_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = image_meta_get_media_id(NULL, &media_id);

	dts_check_eq("utc_image_meta_get_media_id", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of image_meta_get_media_id()
 */
static void utc_image_meta_get_media_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = image_meta_get_media_id(g_image, &media_id);

	dts_check_eq("utc_image_meta_get_media_id", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the media_id");
}

/**
 * @brief Negative test case of image_meta_get_width()
 */
static void utc_image_meta_get_width_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = image_meta_get_width(NULL, &width);

	dts_check_eq("utc_image_meta_get_width", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of image_meta_get_width()
 */
static void utc_image_meta_get_width_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = image_meta_get_width(g_image, &width);

	dts_check_eq("utc_image_meta_get_width", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the width");
}

/**
 * @brief Negative test case of sim_get_image_meta_get_height()
 */
static void utc_image_meta_get_height_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = image_meta_get_height(NULL, &height);

	dts_check_eq("utc_image_meta_get_height", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of sim_get_image_meta_get_height()
 */
static void utc_image_meta_get_height_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = image_meta_get_height(g_image, &height);

	dts_check_eq("utc_image_meta_get_height", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get height");
}

/**
 * @brief Negative test case of sim_get_image_meta_get_orientation()
 */
static void utc_image_meta_get_orientation_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orientation = 0;

	ret = image_meta_get_orientation(NULL, &orientation);

	dts_check_eq("utc_image_meta_get_orientation", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of sim_get_image_meta_get_orientation()
 */
static void utc_image_meta_get_orientation_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orientation = 0;

	ret = image_meta_get_orientation(g_image, &orientation);

	dts_check_eq("utc_image_meta_get_orientation", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get orientation");
}

static void utc_image_meta_get_date_taken_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *date_taken = NULL;

	ret = image_meta_get_date_taken(NULL, &date_taken);

	dts_check_eq("utc_image_meta_get_date_taken", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_image_meta_get_date_taken_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *date_taken = NULL;

	ret = image_meta_get_date_taken(g_image, &date_taken);

	dts_check_eq("utc_image_meta_get_date_taken", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get date_taken");
}

static void utc_image_meta_set_orientation_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_set_orientation(NULL, MEDIA_CONTENT_ORIENTATION_NORMAL);

	dts_check_eq("utc_image_meta_set_orientation_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_image_meta_set_orientation_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_set_orientation(g_image, MEDIA_CONTENT_ORIENTATION_NORMAL);

	dts_check_eq("utc_image_meta_set_orientation_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get date_taken");
}

static void utc_image_meta_update_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_update_to_db(NULL);

	dts_check_eq("utc_image_meta_update_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_image_meta_update_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_update_to_db(g_image);

	dts_check_eq("utc_image_meta_update_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get date_taken");
}
