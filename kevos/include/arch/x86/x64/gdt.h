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
*  @file     gdt.h                            
*  @brief    全局描述符表                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_X64_GDT_H_
#define _KEVOS_ARCH_x86_X64_GDT_H_

#include <arch/x86/x64/descriptor.h>

#include <cstddef>

namespace desc::gdt
{

#define __KERNEL_CS               0x10
#define __KERNEL_DS               0x20
#define __USER_CS				  0x33
#define __USER_DS				  0x43
#define __KERNEL_TSS              0x50

void setItem(std::size_t index,std::size_t base,uint32_t limit,
					uint8_t dpl,uint8_t code,uint8_t tss);
void initialize();

constexpr uint16_t gdtSize=6;
extern SystemDescriptor items[gdtSize];

}


#endif