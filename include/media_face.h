/*
* Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef __TIZEN_MEDIA_IMAGE_FACE_H__
#define __TIZEN_MEDIA_IMAGE_FACE_H__

#include <media_content_type.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @file media_face.h
 * @brief This file contains the media face API and related to all operations with the face information of the image in Meida DB. \n
 *             Functions include cloning and destroying the face handler, getting face information such as face id, face coordinates in file, \n
 *             face tag. Face information detected and managed by DB automatically when image contents scanning.  \n
 *             And you can insert,update,delete face information manually.
 */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_FACE_MODULE
 * @{
 */

/**
 * @brief Clones the face handle.
 * @details This function copies the face handle from a source to
 * destination. There is no media_face_create() function. The media_face_h is created internally and available through
 * media face foreach function such as media_face_foreach_face_from_db(). To use this handle outside of these foreach functions,
 * use this function.
 *
 * @since_tizen 3.0
 * @remark The destination handle must be released with media_event_destroy() by you.
 *
 * @param [in] src The source face handle
 * @param [out] dst A destination face handle
 *
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @see media_face_destroy()
 * @see media_face_foreach_face_from_db()
 */
int media_face_clone(media_face_h *dst, media_face_h src);

/**
 * @brief Destroys the face handle.
 * @details Function frees all resources related to face handle. This
 * handle no longer can be used to perform any operation. New handle has to
 * be created before next usage.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 *
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see media_face_clone()
 *
 * @pre Get copy of face handle by calling media_face_clone() or Get face handle by calling media_info_foreach_face_from_db()
 *
 */
int media_face_destroy(media_face_h face);

/**
 * @brief Gets the face id from the face handle.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 * @param [out] face_id The uuid of the face handle
 *
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int media_face_get_face_id(media_face_h face, char **face_id);

/**
 * @brief Gets the media uuid from the face handle.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 * @param [out] media_id The media uuid of the face handle
 *
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int media_face_get_media_id(media_face_h face, char **media_id);

 /**
 * @brief Gets the face's rectangle from the face handle.
 * @details This API can get the face's rectangle information. returned rectangle information includes the orientation value.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 * @param [out] rect_x The x position of face of the face handle
 * @param [out] rect_y The y position of face of the face handle
 * @param [out] rect_w The width of face of the face handle
 * @param [out] rect_h The height of face of the face handle
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int media_face_get_face_rect(media_face_h face, unsigned int *rect_x, unsigned int *rect_y, unsigned int *rect_w, unsigned int *rect_h);

/**
 * @brief Gets the orientation from the face handle.
 * @details This API can get the orientation value from the original image.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 * @param [out] orientation The orientation of the face handle
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int media_face_get_orientation(media_face_h face, media_content_orientation_e *orientation);

/**
 * @brief Gets the tag from the face handle.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 * @param [out] tag The tag of the face handle
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int media_face_get_tag(media_face_h face, char **tag);

/**
 * @brief Creates the face handle.
 *
 * @since_tizen 3.0
 *
 * @param [out] face The face handle
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_face_destroy()
 */
int media_face_create_handle(const char *media_id, media_face_h *face);

/**
 * @brief Sets the face rectangle of the face handle
 *
 * @since_tizen 3.0
 *
 * @param[in] face The face handle
 * @param[in] rect_x The integer to set as a position x of face rectangle
 * @param[in] rect_y The integer to set as a position y of face rectangle
 * @param[in] rect_w The integer to set as a width  of face rectangle
 * @param[in] rect_h The integer to set as a height of face rectangle
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @post media_face_insert_to_db()
 * @post media_face_update_to_db()
 *
 */
int media_face_set_face_rect(media_face_h face, unsigned int rect_x, unsigned int rect_y, unsigned int rect_w, unsigned int rect_h);

/**
 * @brief Sets the orientation of the face handle
 * @details This API may set the value of the original image orientation.
 *
 * @since_tizen 3.0
 *
 * @param[in] face The face handle
 * @param[in] orientation The integer to set as an orientation
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @post media_face_insert_to_db()
 * @post media_face_update_to_db()
 *
 */
int media_face_set_orientation(media_face_h face, media_content_orientation_e orientation);

/**
 * @brief Sets the tag of the face handle.
 *
 * @since_tizen 3.0
 *
 * @param [in] face The face handle
 * @param [in] tag The tag of the face handle
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @post media_face_insert_to_db()
 * @post media_face_update_to_db()
 */
int media_face_set_tag(media_face_h face, const char *tag);

/**
 * @brief Inserts a new face in the media database.
 * @since_tizen 3.0
 *
 * @privlevel public
 * @privilege %http://tizen.org/privilege/content.write
 *
 * @remarks The created tag handle must be released using media_tag_destroy().
 *
 * @param [in] face The face handle
 *
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
 *
 * @see media_content_connect()
 * @see media_face_destroy()
 * @see media_face_set_xxx()
 */
int media_face_insert_to_db(media_face_h face);

/**
 * @brief Updates the face details to the media database.
 *
 * @details The function updates the given media face in the media database. The function should be called after any change in face, to be updated to the media
 * database. For example, after using media_face_set_orientation() for setting the orientation of the face, media_face_update_to_db() function should be called so as to update
 * the given face attibutes in the media database.
 * @since_tizen 3.0
 *
 * @privlevel public
 * @privilege %http://tizen.org/privilege/content.write
 *
 * @param[in] face The face handle to update
 *
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre This function requires opened connection to content service by media_content_connect().
 *
 * @see media_content_connect()
 * @see media_face_destroy()
 * @see media_face_set_xxx()
 *
 */
int media_face_update_to_db(media_face_h face);

/**
 * @brief Deletes the face with given face uuid from the media database.
 *
 * @since_tizen 3.0
 *
 * @privlevel public
 * @privilege %http://tizen.org/privilege/content.write
 *
 * @param [in] face_id The id of media face
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 *
 */
int media_face_delete_from_db(const char *face_id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_IMAGE_FACE_H__ */
