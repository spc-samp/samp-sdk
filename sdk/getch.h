/*  getch.h - POSIX-compatible character input functions
 *
 *  Copyright (c) Original Authors of POSIX-compatible Implementation
 *
 *  Licensed under the Mozilla Public License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      https://www.mozilla.org/en-US/MPL/2.0/
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Copyright (c) SPC (SA-MP Programming Community)
 *  The SA-MP Programming Community holds copyright solely for the improvements
 *  made to this file and does not claim any rights to the original content.
 *  SPC improvements are licensed under the MIT License, available at:
 *  https://opensource.org/licenses/MIT
 */

#ifndef GETCH_H
    #define GETCH_H

    #ifdef __cplusplus
        extern "C" {
    #endif

    int getch(void);
    int kbhit(void);

    #ifdef __cplusplus
        }
    #endif
#endif