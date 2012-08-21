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


#ifndef __TIZEN_MEDIA_UTIL_PRIVATE_H__
#define __TIZEN_MEDIA_UTIL_PRIVATE_H__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 *@internal
 */
int _media_util_get_store_type_by_path(const char *path, int *storage_type);

/**
 *@internal
 */
int _media_util_get_file_dir_modified_time(const char *path);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__TIZEN_MEDIA_UTIL_PRIVATE_H__*/
