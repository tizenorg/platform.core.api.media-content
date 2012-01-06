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



#ifndef __TIZEN_VIDEO_META_H__
#define __TIZEN_VIDEO_META_H__

#include <media_content_type.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_VIDEO_META_MODULE
 * @{
 */

/**
 * @brief Clones video metadata.
 * @details This function copies the video metadata handle from a source to
 * destination.

 * @remark The destination handle must be released with video_meta_destroy() by you. 
 *
 * @param [out] dst A destination handle to video metadata
 * @param [in] src The source handle to video metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory 
 * @see video_meta_destroy()
 */
int video_meta_clone(video_meta_h *dst, video_meta_h src);


/**
 * @brief Destroys video metadata.
 * @details Function frees all resources related to video metadata handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before the next use.
 *
 * @param [in] video The handle to video metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre Get copy of video metadata handle by calling video_meta_clone()
 * @see video_meta_clone()
 *
 */
int video_meta_destroy(video_meta_h video);


/**
 * @brief Gets the longitude from video metadata.
 * @details Function gives geographic position: @a longitude  in degrees,
 * which is positive for east and negative for west.
 *
 * @param [in] video The handle to video metadata
 * @param [out] longitude The video longitude in degrees
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_longitude(video_meta_h video, double *longitude);


/**
 * @brief Gets the latitude from video metadata.
 * @details Function gives geographic position: @a latitude  in degrees,
 * which is positive for north and negative for south.
 *
 * @param [in] video The handle to video metadata
 * @param [out] latitude The video latitude in degrees
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_latitude(video_meta_h video, double *latitude);


/**
 * @brief Gets the video's album.
 *
 * @remarks @a album must be released with free() by you.
 *
 * @param [in] video The handle to video metadata
 * @param [out] album The video album or NULL
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 */
int video_meta_get_album(video_meta_h video, char **album);


/**
 * @brief Gets the video's artist.
 *
 * @remarks @a artist must be released with free() by you.
 *
 * @param [in] video The handle to video metadata
 * @param [out] artist The artist of video metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 */
int video_meta_get_artist(video_meta_h video, char **artist);


/**
 * @brief Gets the video's title.
 *
 * @remarks @a title must be released with free() by you.
 *
 * @param [in] video The handle to video metadata
 * @param [out] title The title of video metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 */
int video_meta_get_title(video_meta_h video, char **title);


/**
 * @brief Gets the video's description.
 *
 * @remarks  @a description must be released with free() by you.
 *
 * @param [in] video The handle to video metadata
 * @param [out] description The description of video metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 */
int video_meta_get_description(video_meta_h video, char **description);


/**
 * @brief Gets the video's time played parameter.
 * @details Function returns video's elapsed playback time parameter as period
 * starting from the beginning of the movie.
 *
 * @param [in] video The handle to video metadata
 * @param [out] time_played The time period from the beginning of the video (in milliseconds)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see video_meta_update_time_played_to_db()
 */
int video_meta_get_time_played(video_meta_h video, int *time_played);


/**
 * @brief Gets duration of video metadata.
 *
 * @param [in] video The handle to video metadata
 * @param [out] duration The video duration in milliseconds
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_duration(video_meta_h video, int *duration);


/**
 * @brief Gets the video's width in pixels.
 *
 * @param [in] video The handle to video metadata
 * @param [out] width The video width in pixels
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_width(video_meta_h video, int *width);


/**
 * @brief Gets the video's height  in pixels.
 *
 * @param [in] video The handle to video metadata
 * @param [out] height The video height in pixels
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_height(video_meta_h video, int *height);


/**
 * @brief Gets the video's orientation.
 *
 * @param [in] video The handle to video metadata
 * @param [out] orientation The orientation of video metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_orientation(video_meta_h video, media_content_orientation_e *orientation);


/**
 * @brief Gets the date, when video was created
 *
 * @param [in] video The handle to video metadata
 * @param [out] date_taken The date, when video was taken (in seconds, since the Epoch)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_meta_get_date_taken(video_meta_h video, time_t *date_taken);


/**
 * @brief Updates video's time played parameter to the media database.
 * @details Function updates video's time played parameter
 * This parameter describes elapsed playback time, starting from the
 * beginning of the movie.
 *
 * @param [in] video The handle to video metadata
 * @param [in] time_played The video time played (in milliseconds)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see video_meta_get_time_played()
 */
int video_meta_update_time_played_to_db(video_meta_h video, int time_played);


/**
 *@}
 */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_VIDEO_BOOKMARK_MODULE
 * @{
 */


/**
 * @brief Iterates through video bookmarks with optional filter in the given video metadata from the media database.
 * @details This function gets all video bookmarks associated with the given folder and meeting desired filter option and 
calls registered callback function for every retrieved item. If NULL is passed to the @a filter, no filtering is applied. 
 * @remarks Only start position and offset details of filter can be set,
 * beacuse searching by bookmark name information is not supported.
 *
 * @param [in] video The handle to video metadata
 * @param [in] filter The handle to video bookmark filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function

 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes video_bookmark_cb().
 * @see media_content_connect()
 * @see #video_bookmark_cb 
 * @see video_bookmark_filter_create()
 *
 */
int video_bookmark_foreach_bookmark_from_db(video_meta_h video, video_bookmark_filter_h filter, video_bookmark_cb callback, void *user_data);


/**
 * @brief Clones video bookmark.
 * @details This function copies the video bookmark handle from a source to destination. There is no video_bookmark_create() function. 
 * The video_bookmark_h is created internally and available through video bookmark foreach function such as video_bookmark_foreach_bookmark_from_db(). 
 * To use this handle outside of these foreach functions, use this function.
 *
 * @remark The destination handle must be released with video_bookmark_destroy() by you.  
 *
 * @param [out] dst A destination handle to video bookmark
 * @param [in] src The source handle to video bookmark
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see video_bookmark_destroy()
 * @see video_bookmark_foreach_bookmark_from_db()
 *
 */
int video_bookmark_clone(video_bookmark_h *dst, video_bookmark_h src);


/**
 * @brief Destroys video bookmark.
 * @details Function frees all resources related to bookmark handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before the next use.
 *
 * @param [in] bookmark The handle to video bookmark
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre Get copy of bookmark handle by calling video_bookmark_clone() 
 * @see video_bookmark_clone()
 */
int video_bookmark_destroy(video_bookmark_h bookmark);


/**
 * @brief Gets bookmark's time marked parameter.
 * @details Function returns time offset in milliseconds from beginning of the movie on which bookmark
 * was placed.
 *
 * @param [in] bookmark The handle to video bookmark
 * @param [out] time_marked The bookmark time offset (in milliseconds)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int video_bookmark_get_time_marked(video_bookmark_h bookmark, time_t *time_marked);


/**
 * @brief Gets the video bookmark's thumbnail
 *
 * @remarks thumbnail must be released with free() by you.
 *
 * @param [in] bookmark The handle to video bookmark
 * @param [out] thumbnail_path The thumbnail path of video bookmark
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 */
int video_bookmark_get_thumbnail_path(video_bookmark_h bookmark, char **thumbnail_path);


/**
 * @brief Inserts a new bookmark in video on specified time offset to the media database.
 *
 * @param [in] video The handle to video metadata
 * @param [in] time The bookmark time offset (in seconds)
 * @param [in] thumbnail_path The thumbnail path of video bookmark.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see video_bookmark_delete_from_db()
 *
 */
int video_bookmark_insert_to_db(video_meta_h video, time_t time, const char *thumbnail_path);


/**
 * @brief Removes video bookmark from the media database.
 *
 * @param [in] bookmark The handle to video bookmark
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see video_bookmark_insert_to_db()
 *
 */
int video_bookmark_delete_from_db(video_bookmark_h bookmark);



/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__TIZEN_VIDEO_META_H__*/


