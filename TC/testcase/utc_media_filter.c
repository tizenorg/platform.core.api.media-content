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

static void utc_media_filter_create_n(void);
static void utc_media_filter_create_p(void);
static void utc_media_filter_destroy_n(void);
static void utc_media_filter_destroy_p(void);
static void utc_media_filter_set_offset_n(void);
static void utc_media_filter_set_offset_p(void);
static void utc_media_filter_set_condition_n(void);
static void utc_media_filter_set_condition_p(void);
static void utc_media_filter_set_order_n(void);
static void utc_media_filter_set_order_p(void);
//static void utc_media_filter_set_collate_n(void);
//static void utc_media_filter_set_collate_p(void);
static void utc_media_filter_get_offset_n(void);
static void utc_media_filter_get_offset_p(void);
static void utc_media_filter_get_condition_n(void);
static void utc_media_filter_get_condition_p(void);
static void utc_media_filter_get_order_n(void);
static void utc_media_filter_get_order_p(void);
//static void utc_media_filter_get_collate_n(void);
//static void utc_media_filter_get_collate_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_media_filter_create_n, 1 },
	{ utc_media_filter_create_p, 1 },
	{ utc_media_filter_destroy_n, 4 },
	{ utc_media_filter_destroy_p, 4 },
	{ utc_media_filter_set_offset_n, 2 },
	{ utc_media_filter_set_offset_p, 2},
	{ utc_media_filter_set_condition_n, 2 },
	{ utc_media_filter_set_condition_p, 2 },
	{ utc_media_filter_set_order_n, 2 },
	{ utc_media_filter_set_order_p, 2 },
//	{ utc_media_filter_set_collate_n, 2 },
//	{ utc_media_filter_set_collate_p, 2 },
	{ utc_media_filter_get_offset_n, 3 },
	{ utc_media_filter_get_offset_p, 3},
	{ utc_media_filter_get_condition_n, 3 },
	{ utc_media_filter_get_condition_p, 3 },
	{ utc_media_filter_get_order_n, 3 },
	{ utc_media_filter_get_order_p, 3 },
//	{ utc_media_filter_get_collate_n, 3 },
//	{ utc_media_filter_get_collate_p, 3 },
	{ NULL, 0 },
};


//media_folder_h g_folder = NULL;
static filter_h g_filter = NULL;

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
}


static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");
}



/**
 * @brief Negative test case of media_filter_create()
 */
static void utc_media_filter_create_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_create(NULL);

	dts_check_eq("utc_media_filter_create_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_filter_create()
 */
static void utc_media_filter_create_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	ret = media_filter_create(&g_filter);

	dts_check_eq("utc_media_filter_create_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to create the filter");
}

/**
 * @brief Negative test case of media_filter_destroy()
 */
static void utc_media_filter_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_destroy(NULL);

	dts_check_eq("utc_media_filter_destroy_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_filter_destroy()
 */
static void utc_media_filter_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_destroy(g_filter);

	dts_check_eq("utc_media_filter_destroy_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destroy filter");
}

/**
 * @brief Negative test case of media_filter_get_offset()
 */
static void utc_media_filter_set_offset_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_offset(NULL, 0, 3);

	dts_check_eq("utc_media_filter_set_offset_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_filter_get_offset()
 */
static void utc_media_filter_set_offset_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_offset(g_filter, 0, 3);

	dts_check_eq("utc_media_filter_set_offset_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set the offset");
}

/**
 * @brief Negative test case of utc_media_filter_get_display_name()
 */
static void utc_media_filter_set_condition_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_condition(NULL, "MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_DEFAULT);

	dts_check_eq("utc_media_filter_set_condition_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of utc_media_filter_get_display_name()
 */
static void utc_media_filter_set_condition_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_condition(g_filter, "MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_DEFAULT);

	dts_check_eq("utc_media_filter_set_condition_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set display name");
}

/**
 * @brief Negative test case of media_filter_set_order()
 */
static void utc_media_filter_set_order_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_order(NULL, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);

	dts_check_eq("utc_media_filter_set_order_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_filter_set_order()
 */
static void utc_media_filter_set_order_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);

	dts_check_eq("utc_media_filter_set_order_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set the order");
}

/**
 * @brief Negative test case of media_filter_get_offset()
 */
static void utc_media_filter_get_offset_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int offset = 0;
	int count = 0;

	ret = media_filter_get_offset(NULL, &offset, &count);

	dts_check_eq("utc_media_filter_get_offset_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_filter_get_offset()
 */
static void utc_media_filter_get_offset_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int offset = 0;
	int count = 0;

	ret = media_filter_get_offset(g_filter, &offset, &count);

	dts_check_eq("utc_media_filter_get_offset_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the offset");
}

/**
 * @brief Negative test case of utc_media_filter_get_display_name()
 */
static void utc_media_filter_get_condition_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *condition = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_get_condition(NULL, &condition, &collate_type);

	dts_check_eq("utc_media_filter_get_display_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of utc_media_filter_get_display_name()
 */
static void utc_media_filter_get_condition_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *condition = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_get_condition(g_filter, &condition, &collate_type);

	if(condition != NULL)
		free(condition);

	dts_check_eq("utc_media_filter_get_display_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get display name");
}

/**
 * @brief Negative test case of media_filter_get_order()
 */
static void utc_media_filter_get_order_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_order_e order;
	char *order_keyword = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_get_order(NULL, &order, &order_keyword, &collate_type);

	dts_check_eq("utc_media_filter_get_order_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_filter_get_order()
 */
static void utc_media_filter_get_order_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_order_e order = 0;
	char *order_keyword = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_get_order(g_filter, &order, &order_keyword, &collate_type);

	if(order_keyword != NULL)
		free(order_keyword);

	dts_check_eq("utc_media_filter_get_order_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the order");
}
