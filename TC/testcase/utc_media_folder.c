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

static void utc_media_folder_foreach_folder_from_db_n(void);
static void utc_media_folder_foreach_folder_from_db_p(void);
static void utc_media_folder_get_media_count_from_db_n(void);
static void utc_media_folder_get_media_count_from_db_p(void);
static void utc_media_folder_foreach_media_from_db_n(void);
static void utc_media_folder_foreach_media_from_db_p(void);
static void utc_media_folder_destroy_n(void);
static void utc_media_folder_destroy_p(void);
static void utc_media_folder_clone_n(void);
static void utc_media_folder_clone_p(void);
static void utc_media_folder_get_path_n(void);
static void utc_media_folder_get_path_p(void);
static void utc_media_folder_get_name_n(void);
static void utc_media_folder_get_name_p(void);
static void utc_media_folder_get_date_modified_n(void);
static void utc_media_folder_get_date_modified_p(void);
static void utc_media_folder_get_storage_type_n(void);
static void utc_media_folder_get_storage_type_p(void);
static void utc_media_folder_update_to_db_n(void);
static void utc_media_folder_update_to_db_p(void);
static void utc_media_folder_set_name_n(void);
static void utc_media_folder_set_name_p(void);
static void utc_media_folder_get_folder_id_n(void);
static void utc_media_folder_get_folder_id_p(void);
static void utc_media_folder_get_folder_from_db_n(void);
static void utc_media_folder_get_folder_from_db_p(void);
static void utc_media_folder_get_folder_count_from_db_n(void);
static void utc_media_folder_get_folder_count_from_db_p(void);

struct tet_testlist tet_testlist[] = {
	{ utc_media_folder_foreach_folder_from_db_n, 1 },
	{ utc_media_folder_foreach_folder_from_db_p, 1 },
	{ utc_media_folder_get_media_count_from_db_n, 2 },
	{ utc_media_folder_get_media_count_from_db_p, 2 },
	{ utc_media_folder_foreach_media_from_db_n, 2 },
	{ utc_media_folder_foreach_media_from_db_p, 2 },
	{ utc_media_folder_destroy_n, 3 },
	{ utc_media_folder_destroy_p, 3 },
	{ utc_media_folder_clone_n, 2 },
	{ utc_media_folder_clone_p, 2 },
	{ utc_media_folder_get_path_n, 2 },
	{ utc_media_folder_get_path_p, 2 },
	{ utc_media_folder_get_path_p, 2 },
	{ utc_media_folder_get_name_n, 2 },
	{ utc_media_folder_get_name_p, 2 },	
	{ utc_media_folder_get_date_modified_n, 2 },
	{ utc_media_folder_get_date_modified_p, 2 },
	{ utc_media_folder_get_storage_type_n, 2 },
	{ utc_media_folder_get_storage_type_p, 2 },
	{ utc_media_folder_set_name_n, 2 },
	{ utc_media_folder_set_name_p, 2 },
	{ utc_media_folder_update_to_db_n, 2 },
	{ utc_media_folder_update_to_db_p, 2 },
	{ utc_media_folder_get_folder_id_n, 2 },
	{ utc_media_folder_get_folder_id_p, 2 },
	{ utc_media_folder_get_folder_from_db_n, 2 },
	{ utc_media_folder_get_folder_from_db_p, 2 },
	{ utc_media_folder_get_folder_count_from_db_n, 2 },
	{ utc_media_folder_get_folder_count_from_db_p, 2 },
	{ NULL, 0 },
};


media_folder_h g_folder = NULL;
media_folder_h g_test_folder = NULL;
const char *g_test_folder_path = "/opt/media/Images/test";
const char *g_default_folder_path = "/opt/media/Images";
const char *g_origin_item_path = "/opt/media/Images/Default.jpg";
const char *g_test_item_path = "/opt/media/Images/test/test.jpg";
char *g_folder_path = NULL;

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	ret = media_content_connect();

	char mkdir_str[256] = {0, };
	char test_copy[256] = {0, };
	snprintf(mkdir_str, sizeof(mkdir_str), "/bin/mkdir %s", g_test_folder_path);
	snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_origin_item_path, g_test_item_path);

	system(mkdir_str);
	system(test_copy);

	sleep(1);
}

static void cleanup(void)
{
	/* end of TC */
	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_content_disconnect();

	unlink(g_test_item_path);

	char rmdir_str[256] = {0, };
	snprintf(rmdir_str, sizeof(rmdir_str), "/bin/rmdir %s", g_test_folder_path);
	system(rmdir_str);
	tet_printf("\n TC end");

	media_folder_destroy(g_folder);
	media_folder_destroy(g_test_folder);

	if (g_folder_path) free(g_folder_path);
	g_folder_path = NULL;
}

bool capi_folder_list_cb(media_folder_h folder, void *user_data)
{
	if(folder != NULL)
	{
		media_folder_get_path(folder, &g_folder_path);

		tet_printf("folder path : %s\n", g_folder_path);

		if(strcmp(g_folder_path, g_test_folder_path) == 0) {
			tet_printf("TEST folder\n");
			media_folder_clone(&g_test_folder, folder);
		} else if(strcmp(g_folder_path, g_default_folder_path) == 0) {
			tet_printf("DEFAULT folder\n");
			media_folder_clone(&g_folder, folder);
		}
	}

	if (g_folder_path) free(g_folder_path);
	g_folder_path = NULL;

	return true;
}

/**
 * @brief Negative test case of media_folder_foreach_folder_from_db()
 */
static void utc_media_folder_foreach_folder_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_foreach_folder_from_db(NULL, NULL, NULL);

	dts_check_eq("utc_media_folder_foreach_folder_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_foreach_folder_from_db()
 */
static void utc_media_folder_foreach_folder_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter;

	media_filter_create(&filter);

	ret = media_folder_foreach_folder_from_db(filter, capi_folder_list_cb, NULL);
	dts_check_eq("utc_media_folder_foreach_folder_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to iterate the folder");
}

/**
 * @brief Negative test case of media_folder_get_media_count_from_db()
 */
static void utc_media_folder_get_media_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int cnt;

	ret = media_folder_get_media_count_from_db(NULL, NULL, &cnt);

	dts_check_eq("utc_media_folder_get_media_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_media_count_from_db()
 */
static void utc_media_folder_get_media_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int cnt;

	filter_h filter;
	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	char *folder_id = NULL;
	media_folder_get_folder_id(g_folder, &folder_id);

	ret = media_folder_get_media_count_from_db(folder_id, filter, &cnt);

	dts_check_eq("utc_media_folder_get_media_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the count of media");
}

bool sub_media_cb(media_info_h media, void *user_data)
{
	return true;
}

/**
 * @brief Negative test case of media_folder_foreach_media_from_db()
 */
static void utc_media_folder_foreach_media_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	filter_h filter;
	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_folder_foreach_media_from_db(NULL, filter, sub_media_cb, NULL);

	media_filter_destroy(filter);

	dts_check_eq("utc_media_folder_foreach_media_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_foreach_media_from_db()
 */
static void utc_media_folder_foreach_media_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	filter_h filter;
	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	char *folder_id = NULL;
	media_folder_get_folder_id(g_folder, &folder_id);

	ret = media_folder_foreach_media_from_db(folder_id, filter, sub_media_cb, NULL);

	media_filter_destroy(filter);

	dts_check_eq("utc_media_folder_foreach_media_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to iterate the media");
}

/**
 * @brief Negative test case of media_folder_destroy()
 */
static void utc_media_folder_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_destroy(NULL);

	dts_check_eq("utc_media_folder_destroy_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_destroy()
 */
static void utc_media_folder_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_destroy(g_folder);

	dts_check_eq("utc_media_folder_destroy_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destroy the folder");
}

/**
 * @brief Negative test case of media_folder_clone()
 */
static void utc_media_folder_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_folder_h dst_folder = NULL;
	
	ret = media_folder_clone(&dst_folder, NULL);

	dts_check_eq("utc_media_folder_clone_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_clone()
 */
static void utc_media_folder_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_folder_h dst_folder = NULL;
		
	ret = media_folder_clone(&dst_folder, g_folder);

	if(dst_folder != NULL)
		media_folder_destroy(dst_folder);

	dts_check_eq("utc_media_folder_clone_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone the folder");
}

/**
 * @brief Negative test case of media_folder_get_path()
 */
static void utc_media_folder_get_path_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;
	ret = media_folder_get_path(NULL, &path);

	dts_check_eq("utc_media_folder_get_path_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_path()
 */
static void utc_media_folder_get_path_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;
	ret = media_folder_get_path(g_folder, &path);

	if(path != NULL)
		free(path);
	
	dts_check_eq("utc_media_folder_get_path_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the path");
}

/**
 * @brief Negative test case of media_folder_get_name()
 */
static void utc_media_folder_get_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;
	ret = media_folder_get_name(NULL, &name);

	if(name != NULL)
		free(name);

	dts_check_eq("utc_media_folder_get_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_name()
 */
static void utc_media_folder_get_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;
	ret = media_folder_get_name(g_folder, &name);

	if(name != NULL)
		free(name);
	
	dts_check_eq("utc_media_folder_get_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the name");
}

/**
 * @brief Negative test case of media_folder_get_storage_type()
 */
static void utc_media_folder_get_date_modified_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t date_modifed = 0;

	ret = media_folder_get_modified_time(NULL, &date_modifed);

	dts_check_eq("utc_media_folder_get_storage_type_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_storage_type()
 */
static void utc_media_folder_get_date_modified_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t date_modifed = 0;
	ret = media_folder_get_modified_time(g_folder, &date_modifed);

	dts_check_eq("utc_media_folder_get_storage_type_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}

/**
 * @brief Negative test case of media_folder_get_storage_type()
 */
static void utc_media_folder_get_storage_type_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e type;

	ret = media_folder_get_storage_type(NULL, &type);

	dts_check_eq("utc_media_folder_get_storage_type_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_storage_type()
 */
static void utc_media_folder_get_storage_type_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e type;

	ret = media_folder_get_storage_type(g_folder, &type);

	dts_check_eq("utc_media_folder_get_storage_type_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}

/**
 * @brief Negative test case of media_folder_set_name()
 */
static void utc_media_folder_set_name_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_set_name(NULL, NULL);

	dts_check_eq("utc_media_folder_set_name_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_set_name()
 */
static void utc_media_folder_set_name_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_set_name(g_test_folder, "new test");

	dts_check_eq("utc_media_folder_set_name_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}

/**
 * @brief Negative test case of media_folder_update_to_db()
 */
static void utc_media_folder_update_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_update_to_db(NULL);

	dts_check_eq("utc_media_folder_update_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_update_to_db()
 */
static void utc_media_folder_update_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_update_to_db(g_test_folder);

	dts_check_eq("utc_media_folder_update_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}

/**
 * @brief Negative test case of media_folder_get_folder_id()
 */
static void utc_media_folder_get_folder_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_get_folder_id(NULL, NULL);

	dts_check_eq("utc_media_folder_get_folder_id_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_folder_id()
 */
static void utc_media_folder_get_folder_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *folder_id = NULL;
	ret = media_folder_get_folder_id(g_folder, &folder_id);

	dts_check_eq("utc_media_folder_get_folder_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}

/**
 * @brief Negative test case of media_folder_get_folder_from_db()
 */
static void utc_media_folder_get_folder_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_get_folder_from_db(NULL, NULL);

	dts_check_eq("utc_media_folder_get_folder_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_folder_from_db()
 */
static void utc_media_folder_get_folder_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *folder_id = NULL;
	media_folder_get_folder_id(g_folder, &folder_id);
	media_folder_h folder_info;

	ret = media_folder_get_folder_from_db(folder_id, &folder_info);

	dts_check_eq("utc_media_folder_get_folder_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}

/**
 * @brief Negative test case of media_folder_get_folder_count_from_db()
 */
static void utc_media_folder_get_folder_count_from_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_get_folder_count_from_db(NULL, NULL);

	dts_check_eq("utc_media_folder_get_folder_count_from_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of media_folder_get_folder_count_from_db()
 */
static void utc_media_folder_get_folder_count_from_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int cnt = 0;

	filter_h filter;
	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_folder_get_folder_count_from_db(filter, &cnt);

	dts_check_eq("utc_media_folder_get_folder_count_from_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the storage type");
}
