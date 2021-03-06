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
*  @file     idt.h                            
*  @brief    中断描述符表                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/
#ifndef _KEVOS_ARCH_X86_X64_IDT_H_
#define _KEVOS_ARCH_X86_X64_IDT_H_

#include <arch/x86/x64/descriptor.h>

#include <cstddef>

#define FAULT0      0x00
#define IRQ0        0x20
#define SYSCALL0    0x80

namespace desc::idt
{

typedef void (*InterruptHandler)();

void setItem(std::size_t index,InterruptHandler handler,uint8_t dpl);
void initialize();

void registerCallback(std::size_t intNum,InterruptHandler handler);

constexpr uint16_t idtSize=256;
extern GateDescriptor items[idtSize];

}


#endif
