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



#ifndef __TIZEN_MEDIA_TAG_H__
#define __TIZEN_MEDIA_TAG_H__

#include <media_content_type.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_TAG_MODULE
 * @{
 */

/**
 * @brief Iterates through tags from the media database.
 * @details This function gets all tags meeting a desired @a filter
 * and calls a registered callback function for every retrieved tag. If NULL is passed to the @a filter, no filtering is applied. 
 *
 * @param[in] filter The handle to tag filter 
 * @param[in] callback  The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory 
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_tag_cb().
 * @see media_content_connect()
 * @see #media_tag_cb
 * @see media_tag_filter_create()
 *
 */


int media_tag_foreach_tag_from_db(media_tag_filter_h filter, media_tag_cb callback, void *user_data);


/**
 * @brief Iterates through media items for a given tag from the media database.
 * @details This function gets all media items associated with a given tag and
 * meeting a desired @a filter and calls a registered callback function for
 * every retrieved media item.  If NULL is passed to the @a filter, no filtering is applied. 
 *
 * @param[in] tag The handle to media tag
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
 */
int media_tag_foreach_media_from_db(media_tag_h tag, media_info_filter_h filter, media_info_cb callback, void *user_data);

/**
  * @brief Inserts a new tag in the media database.
  *
  * @remark The created tag handle must be released with media_tag_destroy() by you. 
  *
  * @param[in] tag_name The tag name to be inserted
  * @param[out] tag  A created handle to media tag
  * @return 0 on success, otherwise a negative error value.
  * @retval #MEDIA_CONTENT_ERROR_NONE Successful
  * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
  * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
  * @pre This function requires opened connection to content service by media_content_connect().   
  * @see media_content_connect()
  * @see media_tag_delete_from_db()
  * @see media_tag_destroy()
  *
  */
 int media_tag_insert_to_db(const char *tag_name, media_tag_h *tag);

/**
  * @brief Deletes a given tag from the media database.
  *
  * @param[in] tag   The handle to media tag
  * @return 0 on success, otherwise a negative error value.
  * @retval #MEDIA_CONTENT_ERROR_NONE Successful
  * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
  * @retval #MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO    Only video and image info can be added to Tag
  * @pre This function requires opened connection to content service by media_content_connect().
  * @see media_content_connect()
  * @see media_tag_insert_to_db()
  *
  */
 int media_tag_delete_from_db(media_tag_h tag);


/**
 * @brief Adds a new media info to the tag to media database.
 *
 * @param[in] tag The handle to media tag
 * @param[in] media  The handle to media info which is added
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO    Only video and image info can be added to Tag
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see media_tag_remove_media_from_db()
 *
 */
int media_tag_add_media_to_db(media_tag_h tag, media_info_h media);

/**
 * @brief Removes the media info from the given tag in the media database.
 * @param[in] tag The handle to media tag
 * @param[in] media  The media info  handle which should be removed
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO    Only video and image info can be supported to Tag 
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see media_tag_add_media_to_db()
 *
 */
int media_tag_remove_media_from_db(media_tag_h tag, media_info_h media);


/**
 * @brief Clones the media tag.
 * @details This function copies the media tag handle from a source to destination. 
 * There is no media_tag_create() function. The media_tag_h is created internally and available through media tag foreach function 
 * such as media_tag_foreach_tag_from_db(). 
 * To use this handle outside of these foreach functions, use this function. 
 * @remark The destination handle must be released with media_tag_destroy() by you. 
 *
 * @param[out] dst   A destination handle to media tag
 * @param[in] src    The source handle to media tag
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter  
 * @see media_tag_destroy()
 *
 */
int media_tag_clone(media_tag_h *dst, media_tag_h src);



/**
 * @brief Destroys the media tag.
 * @details This function frees all resources related to the tag handle. The tag handle can no longer
 * be used for any operation. A new tag handle has to be created before next usage.
 *
 * @param[in] tag The media tag handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre A copy of the media tag handle created by calling media_tag_clone() or media_tag_insert_to_db()
 * @see media_tag_clone()
 * @see media_tag_insert_to_db()
 *
 */
int media_tag_destroy(media_tag_h tag);


/**
 * @brief Gets the tag name.
 *
 * @remarks @a tag_name must be released with free() by you.
 *
 * @param[in] tag The handle to media tag
 * @param[out] tag_name The name of the tag
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 *
 */
int media_tag_get_name(media_tag_h tag, char **tag_name);

/**
 * @brief Updates the tag name.
 * @details This function updates the tag name in media database.
 *
 *
 * @param[in] tag The handle to media tag
 * @param[in] tag_name The new name for the tag
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory 
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int media_tag_update_name_to_db(media_tag_h tag, const char *tag_name);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_TAG_H__ */


