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


#ifndef __TIZEN_MEDIA_INFORMATION_H__
#define __TIZEN_MEDIA_INFORMATION_H__

#include <media_content_type.h>



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @{
 */

/**
 * @brief Iterates through media info from the media database.
 * @details This function gets all media info handles meeting the given @a filter. The @a callback function will be invoked for every retrieved media info. 
 *  If NULL is passed to the @a filter, no filtering is applied. 
 * @param[in] filter The handle to media info filter
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function 
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_info_cb().
 * @see media_content_connect()
 * @see #media_info_cb 
 * @see media_info_filter_create()
 *
 */
int media_info_foreach_media_from_db(media_info_filter_h filter, media_info_cb callback, void *user_data);



/**
 * @brief Iterates through the media tag  in the given @a media @a info from the media database.
 * @details This function gets all media tag associated with the given @a media and calls registered callback function for every retrieved media tag.
 * @param[in] media The handle to media info
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function 
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory 
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_tag_cb().
 * @see media_content_connect()
 * @see #media_tag_cb
 */
int media_info_foreach_tag_from_db(media_info_h media, media_tag_cb callback, void *user_data);



/**
 * @brief Clones the media info handle.
 *
 * @details This function copies the media info handle from a source to destination. 
 * There is no media_info_create() function. The media_info_h is created internally and 
 * available through media info foreach function such as media_info_foreach_media_from_db(). 
 * To use this handle outside of these foreach functions, use this function.
 * @remark The destination handle must be released with media_info_destroy() by you. 
 *
 * @param[out] dst A destination handle to media info
 * @param[in] src The source handle to media info
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see media_info_destroy()
 * @see audio_album_foreach_media_from_db()
 * @see audio_playlist_foreach_media_from_db()
 * @see audio_artist_foreach_media_from_db()
 * @see audio_author_foreach_media_from_db()
 * @see audio_genre_get_media_count_from_db()
 * @see media_tag_foreach_media_from_db()
 * @see media_info_foreach_media_from_db()
 * @see  media_folder_foreach_media_from_db()
 *
 */
int media_info_clone(media_info_h* dst, media_info_h src);


/**
 * @brief Destroys the media info.
 * @details The function frees all resources related to the media info handle. This handle
 * no longer can be used to perform any operation. New media info handle has to
 * be created before next usage.
 *
 * @param[in] media The handle to media info
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre Get copy of media_info handle by calling media_info_clone()
 * @see media_info_clone()
 */
int media_info_destroy(media_info_h media);



/**
 * @brief Gets path to media info.
 *
 * @remarks @a path must be released with free() by you.
 *
 * @param[in] media The handle to media info
 * @param[out] path The path of media info
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 *
 */
int media_info_get_file_path(media_info_h media, char **path);

/**
 * @brief Gets name to media info.
 *
 * @remarks @a name must be released with free() by you.
 *
 * @param[in] media The handle to media info
 * @param[out] name The name of media info
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory	 
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int media_info_get_display_name(media_info_h media, char **name);

/**
 * @brief Gets the thumbnail to media info.
 *
 * @remarks @a path must be released with free() by you.
 *
 * @param[in] media The handle to media info
 * @param[out] path The path to thumbnail of media info
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory	 
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int media_info_get_thumbnail_path(media_info_h media, char **path);

/**
 * @brief Gets media info's date of modification.
 *
 * @param[in] media The handle to media info
 * @param[out] time The date of modification
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int media_info_get_date_modified(media_info_h media, time_t *time);

/**
 * @brief Gets media info's content type.
 *
 * @param[in] media The handle to media info
 * @param[out] type The type of media content(#media_content_type_e). \n
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int media_info_get_media_type(media_info_h media, int *type);



/**
 * @brief Gets image metadata for a given media info from the media database.
 * @details This function returns an image metadata handle retrieved from the media info.
 *
 * @remark The @a image handle must be released with image_meta_destroy() by you. 
 *
 * @param[in] media The handle to media info
 * @param[out] image A handle to image meta
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().   
 * @see media_content_connect()
 * @see image_meta_destroy()
 */
int media_info_get_image_from_db(media_info_h media, image_meta_h* image);

/**
 * @brief Gets video metadata for a given media info from the media database.
 * @details This function returns a video metadata handle retrieved from the media info handle.
 *
 * @remark The @a video handle must be released with video_meta_destroy() by you. 
 *
 * @param[in] media The handle to media info
 * @param[out] video A handle to the video meta
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see video_meta_destroy()      
 *
 */
int media_info_get_video_from_db(media_info_h media, video_meta_h* video);

/**
 * @brief Gets audio metadata for a given media info from the media database.
 * @details This function returns an audio metadata handle retrieved from the media info handle.
 *
 * @remark The @a audio handle must be released with audio_meta_destroy() by you. 
 *
 * @param[in] media The handle to media info
 * @param[out] audio A handle to the audio meta
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @pre This function requires opened connection to content service by media_content_connect(). 
 * @see media_content_connect()
 * @see audio_meta_destroy()
 */
int media_info_get_audio_from_db(media_info_h media, audio_meta_h* audio);


/**
 * @brief Gets the given media info's favorite status.
 *
 * @param [in] media The handle to media info
 * @param [out] favorite The media favorite status(non zero if favorite, 0 if not favorite)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int media_info_get_favorite(media_info_h media, int* favorite);


/**
 * @brief Updates media info's favorite status to the media database.
 *
 * @param [in] media The handle to media info
 * @param [in] favorite The media favorite status(non zero if favorite, 0 if not favorite)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see media_info_meta_get_favorite()
 */
int media_info_update_favorite_to_db(media_info_h media, int favorite);



/**
 * @brief Inserts media file into the media database.
 * @details This function inserts an media item with desired @a type into the content storage.
 * Normally, inserting a media file in database is done automatically by media server, without calling this function.
 * This function is only called when media server is busy and user needs to get quick result of inserting 
 * e.g. Taking a photo while media server is busy and user want to see the quick snapshot of the photo taken.
 *
 * @param[in] type The type of media content
 * @param[in] path The path to the media file
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see #media_content_type_e media_content_connect()
 */
int media_info_insert_to_db(media_content_type_e type, const char *path);




/**
 * @}
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_INFORMATION_H__ */

