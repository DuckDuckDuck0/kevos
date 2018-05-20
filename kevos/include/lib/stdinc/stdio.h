/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C"{
#endif

int vsprintf(char *str,const char *fmt,va_list args);
int sprintf(char *str,const char *fmt,...);

#ifdef __cplusplus
}
#endif

#endif