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

/*****************************************************************************
*  @file     config.h                            
*  @brief    暂时用来配置系统的一些宏定义              
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_COMMON_CONFIG_H_
#define _KEVOS_ARCH_COMMON_CONFIG_H_

/*编译成x64架构下的kevos内核*/
#ifndef __KEVOS_X64__
#define __KEVOS_X64__
#endif

/*使用multiboot规范*/
#ifndef __KEVOS_MULTIBOOT__
#define __KEVOS_MULTIBOOT__
#endif


#endif