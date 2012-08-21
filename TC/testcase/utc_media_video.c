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

static void utc_video_meta_destroy_n(void);
static void utc_video_meta_destroy_p(void);
static void utc_video_meta_clone_n(void);
static void utc_video_meta_clone_p(void);
static void utc_video_meta_get_media_id_n(void);
static void utc_video_meta_get_media_id_p(void);
static void utc_video_meta_get_title_n(void);
static void utc_video_meta_get_title_p(void);
static void utc_video_meta_get_album_n(void);
static void utc_video_meta_get_album_p(void);
static void utc_video_meta_get_artist_n(void);
static void utc_video_meta_get_artist_p(void);
static void utc_video_meta_get_genre_n(void);
static void utc_video_meta_get_genre_p(void);
static void utc_video_meta_get_composer_n(void);
static void utc_video_meta_get_composer_p(void);
static void utc_video_meta_get_year_n(void);
static void utc_video_meta_get_year_p(void);
static void utc_video_meta_get_recorded_date_n(void);
static void utc_video_meta_get_recorded_date_p(void);
static void utc_video_meta_get_copyright_n(void);
static void utc_video_meta_get_copyright_p(void);
static void utc_video_meta_get_track_num_n(void);
static void utc_video_meta_get_track_num_p(void);
static void utc_video_meta_get_bit_rate_n(void);
static void utc_video_meta_get_bit_rate_p(void);
static void utc_video_meta_get_duration_n(void);
static void utc_video_meta_get_duration_p(void);
static void utc_video_meta_get_width_n(void);
static void utc_video_meta_get_width_p(void);
static void utc_video_meta_get_height_n(void);
static void utc_video_meta_get_height_p(void);
static void utc_video_meta_get_played_count_n(void);
static void utc_video_meta_get_played_count_p(void);
static void utc_video_meta_get_played_time_n(void);
static void utc_video_meta_get_played_time_p(void);
static void utc_video_meta_get_played_position_n(void);
static void utc_video_meta_get_played_position_p(void);
static void utc_video_meta_update_to_db_n(void);
static void utc_video_meta_update_to_db_p(void);
static void utc_video_meta_set_played_count_n(void);
static void utc_video_meta_set_played_count_p(void);
static void utc_video_meta_set_played_time_n(void);
static void utc_video_meta_set_played_time_p(void);
static void utc_video_meta_set_played_position_n(void);
static void utc_video_meta_set_played_position_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_video_meta_destroy_n, 5 },
	{ utc_video_meta_destroy_p, 5 },
	{ utc_video_meta_clone_n, 4 },
	{ utc_video_meta_clone_p, 4 },
	{ utc_video_meta_get_media_id_n, 1 },
	{ utc_video_meta_get_media_id_p, 1 },
	{ utc_video_meta_get_title_n, 1 },
	{ utc_video_meta_get_title_p, 1 },
	{ utc_video_meta_get_album_n, 1 },
	{ utc_video_meta_get_album_p, 1 },
	{ utc_video_meta_get_artist_n, 1 },
	{ utc_video_meta_get_artist_p, 1 },
	{ utc_video_meta_get_genre_n, 1 },
	{ utc_video_meta_get_genre_p, 1 },
	{ utc_video_meta_get_composer_n, 1 },
	{ utc_video_meta_get_composer_p, 1 },
	{ utc_video_meta_get_year_n, 1 },
	{ utc_video_meta_get_year_p, 1 },
	{ utc_video_meta_get_recorded_date_n, 1 },
	{ utc_video_meta_get_recorded_date_p, 1 },
	{ utc_video_meta_get_copyright_n, 1 },
	{ utc_video_meta_get_copyright_p, 1 },
	{ utc_video_meta_get_track_num_n, 1 },
	{ utc_video_meta_get_track_num_p, 1 },
	{ utc_video_meta_get_bit_rate_n, 1 },
	{ utc_video_meta_get_bit_rate_p, 1 },
	{ utc_video_meta_get_duration_n, 1 },
	{ utc_video_meta_get_duration_p, 1 },
	{ utc_video_meta_get_width_n, 1 },
	{ utc_video_meta_get_width_p, 1 },
	{ utc_video_meta_get_height_n, 1 },
	{ utc_video_meta_get_height_p, 1 },
	{ utc_video_meta_get_played_count_n, 1 },
	{ utc_video_meta_get_played_count_p, 1 },
	{ utc_video_meta_get_played_time_n, 1 },
	{ utc_video_meta_get_played_time_p, 1 },
	{ utc_video_meta_get_played_position_n, 1 },
	{ utc_video_meta_get_played_position_p, 1 },
	{ utc_video_meta_set_played_count_n, 2 },
	{ utc_video_meta_set_played_count_p, 2 },
	{ utc_video_meta_set_played_time_n, 2 },
	{ utc_video_meta_set_played_time_p, 2 },
	{ utc_video_meta_set_played_position_n, 2 },
	{ utc_video_meta_set_played_position_p, 2 },
	{ utc_video_meta_update_to_db_n, 3 },
	{ utc_video_meta_update_to_db_p, 3 },
	{ NULL, 0 },
};

static video_meta_h g_video;
static video_meta_h g_video_dst;
char *g_media_id = NULL;

bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL))
	{
		tet_printf("\n get media_id failed");
		return false;
	}

	ret = media_info_get_video(media, &g_video);
	if((ret != MEDIA_CONTENT_ERROR_NONE) || (g_video == NULL))
	{
		tet_printf("\n get video_meta failed");
		return false;
	}

	return true;
}

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
	filter_h filter;
	g_video = NULL;

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

	if(g_media_id != NULL)
		free(g_media_id);

	if(g_video != NULL)
		video_meta_destroy(g_video);

	int ret = media_content_disconnect();
	
	if(ret != MEDIA_CONTENT_ERROR_NONE)
		tet_printf("\n database disconnection is failed");
	else
		tet_printf("\n database disconnection is success");
}


/**
 * @brief Negative test case of content_imageinfo_destroy()
 */
static void utc_video_meta_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_destroy(NULL);

	dts_check_eq("utc_video_meta_destroy", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}


/**
 * @brief Positive test case of content_imageinfo_destroy()
 */
static void utc_video_meta_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_destroy(g_video_dst);

	dts_check_eq("utc_video_meta_destroy", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to destroy videoinfo object");

}

/**
 * @brief Negative test case of imageinfo_clone()
 */
static void utc_video_meta_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	ret = video_meta_clone(&g_video_dst, NULL);

	dts_check_eq("utc_video_meta_clone", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of imageinfo_clone()
 */
static void utc_video_meta_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	ret = video_meta_clone(&g_video_dst, g_video);

	dts_check_eq("utc_video_meta_clone", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to clone videoinfo object");
}

static void utc_video_meta_get_media_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = video_meta_get_media_id(NULL, &media_id);

	dts_check_eq("utc_video_meta_get_media_id_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_media_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = video_meta_get_media_id(g_video, &media_id);

	dts_check_eq("utc_video_meta_get_media_id_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get video id");
}

/**
 * @brief Negative test case of sim_get_imageinfo_get_height()
 */
static void utc_video_meta_get_title_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *title = NULL;

	ret = video_meta_get_title(NULL, &title);

	dts_check_eq("utc_video_meta_get_title", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of sim_get_imageinfo_get_height()
 */
static void utc_video_meta_get_title_p(void)
{

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *title = NULL;

	ret = video_meta_get_title(g_video, &title);

	if(title)
		free(title);

	dts_check_eq("utc_video_meta_get_title", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the title");
}

/**
 * @brief Negative test case of imageinfo_get_description()
 */
static void utc_video_meta_get_album_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album = NULL;

	ret = video_meta_get_album(NULL, &album);

	dts_check_eq("utc_video_meta_get_album", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of imageinfo_get_description()
 */
static void utc_video_meta_get_album_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album = NULL;

	ret = video_meta_get_album(g_video, &album);

	if(album)
		free(album);

	dts_check_eq("utc_video_meta_get_album", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the album");
}

/**
 * @brief Negative test case of imageinfo_get_width()
 */
static void utc_video_meta_get_artist_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist = NULL;

	ret = video_meta_get_artist(NULL, &artist);

	dts_check_eq("utc_video_meta_get_artist", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of imageinfo_get_width()
 */
static void utc_video_meta_get_artist_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist = NULL;

	ret = video_meta_get_artist(g_video, &artist);

	if(artist)
		free(artist);

	dts_check_eq("utc_video_meta_get_artist", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the artist");
}

/**
 * @brief Negative test case of video_meta_get_genre()
 */
static void utc_video_meta_get_genre_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *genre = NULL;

	ret = video_meta_get_genre(NULL, &genre);

	dts_check_eq("utc_video_meta_get_genre_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}


/**
 * @brief Positive test case of video_meta_get_genre()
 */
static void utc_video_meta_get_genre_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *genre = NULL;

	ret = video_meta_get_genre(g_video, &genre);

	if(genre)
		free(genre);

	dts_check_eq("utc_video_meta_get_genre_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get genre");
}

/**
 * @brief Negative test case of video_meta_get_composer()
 */
static void utc_video_meta_get_composer_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *composer = NULL;

	ret = video_meta_get_composer(NULL, &composer);

	dts_check_eq("utc_video_meta_get_composer_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of video_meta_get_composer()
 */
static void utc_video_meta_get_composer_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *composer = NULL;

	ret = video_meta_get_composer(g_video, &composer);

	if(composer)
		free(composer);

	dts_check_eq("utc_video_meta_get_composer_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the composer");
}

/**
 * @brief Negative test case of sim_get_imageinfo_get_height()
 */
static void utc_video_meta_get_year_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *year = NULL;

	ret = video_meta_get_year(NULL, &year);

	dts_check_eq("utc_video_meta_get_year_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}


/**
 * @brief Positive test case of sim_get_imageinfo_get_height()
 */
static void utc_video_meta_get_year_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *year = NULL;

	ret = video_meta_get_year(g_video, &year);

	if(year)
		free(year);

	dts_check_eq("utc_video_meta_get_year_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get year");
}

/**
 * @brief Negative test case of video_meta_get_recorded_date()
 */
static void utc_video_meta_get_recorded_date_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *recorded_date = NULL;

	ret = video_meta_get_recorded_date(NULL, &recorded_date);

	dts_check_eq("utc_video_meta_get_recorded_date_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Failed to get recorded_date");
}

/**
 * @brief Positive test case of video_meta_get_recorded_date()
 */
static void utc_video_meta_get_recorded_date_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *recorded_date = NULL;

	ret = video_meta_get_year(g_video, &recorded_date);

	if(recorded_date)
		free(recorded_date);

	dts_check_eq("utc_video_meta_get_recorded_date_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get recorded_date");
}

/**
 * @brief Negative test case of video_meta_get_copyright()
 */
static void utc_video_meta_get_copyright_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copyright = NULL;

	ret = video_meta_get_copyright(NULL, &copyright);

	dts_check_eq("utc_video_meta_get_copyright_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of video_meta_get_copyright()
 */
static void utc_video_meta_get_copyright_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copyright = NULL;

	ret = video_meta_get_copyright(g_video, &copyright);

	if(copyright)
			free(copyright);

	dts_check_eq("utc_video_meta_get_copyright_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get copyright");
}

static void utc_video_meta_get_track_num_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *track_num = NULL;

	ret = video_meta_get_track_num(NULL, &track_num);

	dts_check_eq("utc_video_meta_get_track_num_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_track_num_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *track_num = NULL;

	ret = video_meta_get_track_num(g_video, &track_num);

	if(track_num)
		free(track_num);

	dts_check_eq("utc_video_meta_get_track_num_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get track num");
}

static void utc_video_meta_get_bit_rate_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bit_rate = 0;

	ret = video_meta_get_bit_rate(NULL, &bit_rate);

	dts_check_eq("utc_video_meta_get_bit_rate_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_bit_rate_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bit_rate = 0;

	ret = video_meta_get_bit_rate(g_video, &bit_rate);

	dts_check_eq("utc_video_meta_get_bit_rate_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get the bit_rate");
}

static void utc_video_meta_get_duration_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int duration = 0;

	ret = video_meta_get_duration(NULL, &duration);

	dts_check_eq("utc_video_meta_get_duration", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_duration_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int duration = 0;

	ret = video_meta_get_duration(g_video, &duration);

	dts_check_eq("utc_video_meta_get_duration", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get a duration");
}

static void utc_video_meta_get_width_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;
	ret = video_meta_get_width(NULL, &width);

	dts_check_eq("utc_video_meta_get_width", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_width_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = video_meta_get_width(g_video, &width);
	
	dts_check_eq("utc_video_meta_get_width", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get a width");
}


static void utc_video_meta_get_height_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = video_meta_get_height(NULL, &height);
	
	dts_check_eq("utc_video_meta_get_height", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_height_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = video_meta_get_height(g_video, &height);

	dts_check_eq("utc_video_meta_get_height", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get a height");
}

static void utc_video_meta_get_played_count_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int count = 0;

	ret = video_meta_get_played_count(NULL, &count);

	dts_check_eq("utc_video_meta_get_played_count_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_played_count_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int count = 0;

	ret = video_meta_get_played_count(g_video, &count);

	dts_check_eq("utc_video_meta_get_played_count_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get played count");
}

static void utc_video_meta_get_played_time_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t played_time = 0;

	ret = video_meta_get_played_time(NULL, &played_time);

	dts_check_eq("utc_video_meta_get_played_time_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_played_time_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t played_time = 0;

	ret = video_meta_get_played_time(g_video, &played_time);

	dts_check_eq("utc_video_meta_get_played_time_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get played time");
}

static void utc_video_meta_get_played_position_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int position = 0;

	ret = video_meta_get_played_position(NULL, &position);

	dts_check_eq("utc_video_meta_get_played_position_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_get_played_position_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int position = 0;

	ret = video_meta_get_played_position(g_video, &position);

	dts_check_eq("utc_video_meta_get_played_position_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to get played position");
}

static void utc_video_meta_set_played_count_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int played_count = 3;

	ret = video_meta_set_played_count(NULL, played_count);

	dts_check_eq("utc_video_meta_set_played_count_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_set_played_count_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int played_count = 3;

	ret = video_meta_set_played_count(g_video, played_count);

	dts_check_eq("utc_video_meta_set_played_count_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set played count");
}

static void utc_video_meta_set_played_time_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t played_time = 0;

	ret = video_meta_set_played_time(NULL, played_time);

	dts_check_eq("utc_video_meta_set_played_time_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_set_played_time_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t played_time = 0;

	ret = video_meta_set_played_time(g_video, played_time);

	dts_check_eq("utc_video_meta_set_played_time_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set played time");
}

static void utc_video_meta_set_played_position_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int played_position = 0;

	ret = video_meta_set_played_position(NULL, played_position);

	dts_check_eq("video_meta_set_played_position", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_set_played_position_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int played_position = 0;

	ret = video_meta_set_played_position(g_video, played_position);

	dts_check_eq("utc_video_meta_set_played_position_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to set playedposition");
}

static void utc_video_meta_update_to_db_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_update_to_db(NULL);

	dts_check_eq("utc_video_meta_update_to_db_n", ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER, "Must return MEDIA_CONTENT_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

static void utc_video_meta_update_to_db_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_update_to_db(g_video);

	dts_check_eq("utc_video_meta_update_to_db_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to update metadata");
}
