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



#ifndef __TIZEN_IMAGE_META_H__
#define __TIZEN_IMAGE_META_H__

#include <media_content_type.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_IMAGE_MODULE
 * @{
 */

/**
 * @brief Clones image metadata.
 * @details Function copies the image metadata handle from source to destination.
 *
 * @remark The destination handle must be released with image_meta_destroy() by you. 
 *
 * @param [out] dst A destination handle to image metadata
 * @param [in] src The source handle to image metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see image_meta_destroy()
 */
int image_meta_clone(image_meta_h *dst, image_meta_h src);


/**
 * @brief Destroys image metadata.
 * @details The function frees all resources related to the image metadata handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before next usage.
 *
 * @param [in] image The handle to image metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @pre Get copy of image_meta handle by calling image_meta_clone()
 * @see image_meta_clone()
 */
int image_meta_destroy(image_meta_h image);



/**
 * @brief Gets the longitude from image metadata.
 * @details Function gives geographic position: longitude value in degrees,
 * which is positive for east and negative for west.
 *
 * @param [in] image The handle to image metadata
 * @param [out] longitude The image longitude in degrees
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int image_meta_get_longitude(image_meta_h image, double *longitude);


/**
 * @brief Gets the latitude from image metadata.
 * @details Function gives geographic position: latitude value in degrees,
 * which is positive for north and negative for south.
 *
 * @param [in] image The handle to image metadata
 * @param [out] latitude The image latitude in degrees
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int image_meta_get_latitude(image_meta_h image, double *latitude);


/**
 * @brief Gets the image description.
 *
 * @remarks @a description must be released with free() by you.
 *
 * @param [in] image The handle to image metadata
 * @param [out] description The image description or NULL
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory 
 */
int image_meta_get_description(image_meta_h image, char **description);


/**
 * @brief Gets image's width in pixels.
 *
 * @param [in] image The handle to image metadata
 * @param [out] width The image width in pixels
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int image_meta_get_width(image_meta_h image, int *width);


/**
 * @brief Gets image's height in pixels.
 *
 * @param [in] image The handle to image metadata
 * @param [out] height The image height in pixels
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int image_meta_get_height(image_meta_h image, int *height);


/**
 * @brief Gets the image orientation.
 *
 * @param [in] image The handle to image metadata
 * @param [out] orientation The image orientation
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int image_meta_get_orientation(image_meta_h image, media_content_orientation_e *orientation);


/**
 * @brief Gets the date, when image was created as time_t structure.
 *
 * @param [in] image The handle to image metadata
 * @param [out] date_taken The time, when image was taken (in seconds, since the Epoch)
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int image_meta_get_date_taken(image_meta_h image, time_t *date_taken);


/**
 * @}
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__TIZEN_IMAGE_META_H__*/
