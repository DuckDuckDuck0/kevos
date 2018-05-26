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

#include <sys/portable.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/vm.h>
#include <kernel/mm/mem_layout.h>
#include <kernel/mm/heap_mem.h>
#include <kernel/mm/kheap_mem.h>
#include <kernel/mm/page_mgr.h>
#include <arch/x86/common/cpuid.h>
#include <arch/common/interrupt.h>
#include <kernel/mm/new.h>

KEVOS_NSS_4(arch,x86,x64,boot);

using namespace kernel::mm;

extern "C" void entry64()
{
	__asm__("movq %[stack],%%rsp": : [stack]"i"((uint64_t)&kstack_end_address-0x10000));

	__asm__("mov %%rax, %%cr3" : : "a"(__knPML4));


	GDT::initialize();

	PageManager pm;

	common::CPUInfo cpuInfo;

	arch::common::InterruptManager::initialize();

	KernelHeap::initialize();

	int* a=new int[5];
	delete[]  a;

	*((uint16_t*)(0xB8000))=0x7575;
	while(1);
}


KEVOS_NSE_4(boot,x64,x86,arch);
